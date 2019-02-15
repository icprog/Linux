
```c
��������
	struct device_node *node = NULL;
	node = of_find_compatible_node(NULL, NULL, "mediatek,lcd-backlight");

���ڴ�������ô������� compitible �ַ����ģ�
�ڱ���ʱ��dts�ļ�ͨ��dct���߱����dtb�ļ�����kernel��ʼ��ʱ��������dtb�ļ��������е��������ַ�������ʽ�������ڴ��С�
	


һ�� kernel �� ��fdt API��


1�� of_get_flat_dt_prop ���� node �ڵ��в��� name ���ַ��������������׵�ַ��
ԭ�ͣ� 
const void *__init of_get_flat_dt_prop(unsigned long node, const char *name,int *size)
ʾ����
struct tag_videolfb *videolfb_tag = NULL;
videolfb_tag = (struct tag_videolfb *)of_get_flat_dt_prop(node, "atag,videolfb", (int *)&size);



2�� fb_early_init_dt_get_chosen ��
ԭ�ͣ�
static int fb_early_init_dt_get_chosen(unsigned long node, const char *uname, int depth, void *data)
{
	if (depth != 1 || (strcmp(uname, "chosen") != 0 && strcmp(uname, "chosen@0") != 0))
		return 0;

	*(unsigned long *)data = node;
	return 1;
}
���壺
depth ���ҪΪ1����ʾ�ڸ��ڵ���(һ����ڵ�/ ��depthΪ0)
���ڵ����Ƿ�Ϊchosen�ڵ�



3�� 
of_scan_flat_dt(fb_early_init_dt_get_chosen, &node);
���壺���Ҹ��ڵ� / �µ� chosen �ڵ㣬�������׵�ַ������ node �С�

int __init of_scan_flat_dt(int (*it)(unsigned long node, const char *uname, int depth,  void *data),  void *data)
/* of_scan_flat_dt : scan flattened tree blob and call callback on each.*/



���� lk �е� fdt API��
1�� ��С�ˣ�
cpu_to_fdt32()


2�� fdt_property
const struct fdt_property *fdt_get_property(const void *fdt, int nodeoffset,  const char *name, int *lenp)
ʾ����
/* Becuase the model is at the begin of device tree.
 * use nodeoffset=0
*/
	nodeoffset = 0;
	char *prop_name = "model";
	const char *str = "MT6735"
	
	prop = fdt_get_property(fdt, nodeoffset, prop_name, &len);
/* ���壺�� fdt �л���ַ���Ϊ prop_name �����ԣ����������׵�ַ�� */

	if(prop) {
		fdt_setprop_string(fdt, nodeoffset, prop_name, str);
		
/*ԭ��Ϊ��
#define fdt_setprop_string(fdt, nodeoffset, name, str) 	fdt_setprop((fdt), (nodeoffset), (name), (str), strlen(str)+1)
���壺Ϊ���� name ���һ��value str������� fdt ��û�� name ������ԣ������һ�����ԡ�
*/
		prop = fdt_get_property(fdt, nodeoffset, prop_name, &len);
		namestroff = fdt32_to_cpu(prop->nameoff);
		dprintf(CRITICAL, "%s=%s\n", fdt_string(fdt, namestroff), (char *)prop->dat
	}

3�� fdt_path_offset
ԭ�ͣ�
int fdt_path_offset(const void *fdt, const char *path)
{
	return fdt_path_offset_namelen(fdt, path, strlen(path));
}

ʾ����
	dt_dram_info mem_reg_property[128];
	offset = fdt_path_offset(fdt, "/memory");
/*���壺�� fdt �� ��� �ַ���  "memory" ��ƫ�ƣ�����  "memory" ���׵�ַ��*/	
	
	ret = fdt_setprop(fdt, offset, "reg", mem_reg_property,3 * sizeof(dt_dram_info));
/*�� memory �ڵ��в�������reg��Ϊ�����һ��valueΪ mem_reg_property������� fdt ��û��������ԣ������������Լ� value*/


4�� �������

	offset = fdt_path_offset(fdt, "/chosen");
/*�ӵ�ַ fdt �в��� chosen �ڵ㣬���������׵�ַ*/	
	
	ret = fdt_setprop_cell(fdt, offset, "linux,initrd-start",(unsigned int) ramdisk);
	ret = fdt_setprop_cell(fdt, offset, "linux,initrd-end", (unsigned int)ramdisk + ramdisk_size);
/* set a property to a single cell value*/	
	
static inline int fdt_setprop_cell(void *fdt, int nodeoffset, const char *name,  uint32_t val)
{
	return fdt_setprop_u32(fdt, nodeoffset, name, val);
}


5�� �������
	offset = fdt_path_offset(fdt, "/chosen");
	char buf[FDT_BUFF_SIZE+8], *ptr;

	ptr = (char *)target_atag_boot((unsigned *)buf);
/*Ϊ���� buf ��ֵ��ptrָ�� buf ��β�������� ptr ָ��*/	
	
	ret = fdt_setprop(fdt, offset, "atag,boot", buf, ptr - buf);
/*�ӵ�ַ fdt �е� chosen �ڵ��в��� ������Ϊ "atag,boot" �Ĳ���׷�� buf �ַ��������û��������ԣ��򴴽���׷�ӡ�*/	
	
```

