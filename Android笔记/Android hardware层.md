Android HAL �� API�����ݽṹ


```c
1�� variant_keys �ṹ��
static const char *variant_keys[] = {
	"ro.hardware",
	"ro.product.board",
	"ro.board.platform",
	"ro.arch"
};
Ӳ������������淶Ϊ�� module_ID.variant.so �������������Щ���ļ����ͻ��������⣺ module_ID.default.so 



2�� struct hw_module_t �ṹ��
typedef struct hw_module_t {
	uint32_t tag;
	uint16_t version_major;
	uint16_t version_minor;
	const char *id;
	const char *name;
	const char *author;
	struct hw_module_methods_t *methods;
	void *dso; //����ʹ�� dlopen �ķ���ֵ������þ���� dlsym ʹ��
	uint32_t reserved[32-7];
} hw_module_t; /* struct hw_module_t ����ṹ���ڴ����о�̬���� */



3�� struct hw_module_methods_t �ṹ��
typedef struct hw_module_methods_t {
	int (*open) (const struct hw_module_t *module, const char *id, struct hw_device_t **device);
	/* �� struct hw_module_methods_t �еĳ�Ա open �ж�̬����һ�� struct hw_device_t �ṹ�� */
} hw_module_methods_t;



4�� struct hw_device_t �ṹ��
typedef struct hw_device_t {
	uint32_t tag;
	uint32_t version;
	struct hw_module_t *module;
	uint32_t reserved[12];
	int (*close) (struct hw_device_t *device);
} hw_device_t; /* struct hw_device_t �� open �ж�̬���� */



5�� Ӳ�������ģ��ļ�������
(1)
int hw_get_module(const char *id, const struct hw_module_t **module);
���У� module �����������������سɹ��� module ����ָ��һ���Զ����Ӳ�������ģ��ṹ�塣
����ֵ��0�����ɹ���С��0����ʧ��

(2) ʵ��
#define HAL_LIBRARY_PATH1 "/system/lib/hw"
#define HAL_LIBRARY_PATH2 "/vendor/lib/hw"

static const char *variant_keys[] = {
	"ro.hardware",
	"ro.product.board",
	"ro.board.platform",
	"ro.arch"
};

static const int HAL_VARIANT_KEYS_COUNT = (sizeof(variant_keys)/sizeof(variant_keys[0]));

int hw_get_module(const char *id, const struct hw_module_t **module)
{
	int status;
	int i;
	const struct hw_module_t *hmi = NULL;
	char prop[PATH_MAX];
	char path[PATH_MAX];
	
	for(i=0; i<HAL_VARIANT_KEYS_COUNT+1; i++) {
		if (i< HAL_VARIANT_KEYS_COUNT) {
			if (property_get(variant_keys[i], prop, NULL) == 0)
				continue;
		
			snprint(path, sizeof(path), "%s/%s.%s.so", HAL_LIBRARY_PATH1, id, prop);
			if (access(path, R_OK) ==0)
				break;
			
			snprint(path, sizeof(path), "%s/%s.%s.so", HAL_LIBRARY_PATH2, id, prop);
			if (access(path, R_OK) ==0)
				break;
		} else {
			snprint(path, sizeof(path), "%s/%s.default.so", HAL_LIBRARY_PATH1, id);
			if (access(path,R_OK) ==0)
				break;
		}
	}
	
	status = -ENOENT;
	if (i< HAL_VARIANT_KEYS_COUNT+1) {
		status = load(id, path, module);
	}
	
	return status;
}



static int load(const char *id, const char *path, const struct hw_module_t **pHmi)
{
	int status;
	vodi *handle;
	struct hw_module_t *hmi;
	
	handle = dlopen(path, RTLD_NOW);
	if (handle == NULL) {
		char const * err_str = dlerror();
		LOGE("load: module=%s\n%s", path, err_str?err_str:"unknown");
		status = -EINVAL;
		goto done;
	}
	
	const char *sym = HAL_MODULE_INFO_SYM_AS_STR;	//"HMI"
	hmi = (struct hw_module_t *)dlsym(handle, sym);
	//dlsym �����Ǹ��ݶ�̬���ӿ�����������ţ����ط��Ŷ�Ӧ�ĵ�ַ���������Ի�ȡ������ַ��Ҳ���Ի�ȡ������ַ��
	/*
		fingerprint_module_t HAL_MODULE_INFO_SYM = {
			.common = {
				.tag                = HARDWARE_MODULE_TAG,
				.module_api_version = FINGERPRINT_MODULE_API_VERSION_2_0,
				.hal_api_version    = HARDWARE_HAL_API_VERSION,
				.id                 = FINGERPRINT_HARDWARE_MODULE_ID,
				.name               = "Demo Fingerprint HAL",
				.author             = "The Android Open Source Project",
				.methods            = &fingerprint_module_methods,
			},
		};
		
		#define HAL_MODULE_INFO_SYM     HMI
		HMI ��ʾ����ṹ�������
	*/
	if (hmi == NULL) {
		LOGE("load: couldn't find symbol %s",sym);
		status = -EINVAL;
		goto done;
	}
	
	if (strcmp(id, hmi->id) != 0) {
		LOGE("load: id=%s != hmi->id=%s", id, hmi->id);
		status = -EINVAL;
		goto done;
	}
	
	hmi->dso = handle;
	
	status = 0;
	
	done:
	if(status != 0) {
		if (handle != NULL) {
			dlclose(handle);
			handle = NULL;
		}
	} else {
		LOGV("loaded HAL id=%s path=%s hmi=%p handle=%p", id, path, *pHmi, handle);
	}
	*pHmi = hmi;
	return status;
}
```

