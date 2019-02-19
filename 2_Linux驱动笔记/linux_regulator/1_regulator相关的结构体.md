


һ�� machine �� �������� regulator �ڰ弶��Ӳ�����ã���dts�ж��������

```c
��̬������ regulator �ڰ弶��������״
struct regulator_init_data {

	//regulator��parent�����ڼ���regulatorʹ�á�
	const char *supply_regulator;
	
	//��regulator��Լ�������������ѹ��Χ�����������Χ�ȡ�
	struct regulation_constraints constraints;
	
	//��regulator�ṩ��consumer�ĸ�����Ҳ���ǿ�������ĸ�����	
	int num_consumer_supplies;
	
	//ʹ�ô˽ṹȷ��regulator��consumer֮�����ϵ��	
	struct regulator_consumer_supply *consumer_supplies;
	
	//regulatorע��ʱ��Ļص�������	
	int (*regulator_init)(void *driver_data);
	
	//regulator_init�ص������Ĳ���	
	void *driver_data;
};
```

```c
�� regulator ����������
struct regulation_constraints {

	//������Լ��������
	const char *name;
	
	//��С�����������ѹ
	int min_uV;
	int max_uV;
	
	//consumer�����ĵ�Դ��ʵ�ʵ�Դ֮���ƫ��ֵ�����ڵ�Դ����
	int uV_offset;
	
	//��С�������������
	int min_uA;
	int max_uA;

/*
��regulator֧�ֵĲ���ģʽ��
#define REGULATOR_MODE_FAST 		0x1  //���ٸı�ģʽ
#define REGULATOR_MODE_NORMAL   	0x2  //����ģʽ�������������ʹ������ģʽ
#define REGULATOR_MODE_IDLE     		0x4  //�豸��idle״̬��regulator���豸�ṩ����
#define REGULATOR_MODE_STANDBY  	0x8  //�豸��standby״̬��regulator���豸�ṩ����
*/
	unsigned int valid_modes_mask;

/*
��regulator֧�ֵĲ�����
#define REGULATOR_CHANGE_VOLTAGE 	0x1   //��regulator���Ըı��ѹ
#define REGULATOR_CHANGE_CURRENT 	0x2   //��regulator���Ըı����
#define REGULATOR_CHANGE_MODE 	0x4   //��regulator���Ըı�mode
#define REGULATOR_CHANGE_STATUS  	0x8   //��regulator���Ըı�״̬��Ҳ����enable/disable power
#define REGULATOR_CHANGE_DRMS    	0x10  //��regulator���Զ�̬�ñ�mode
#define REGULATOR_CHANGE_BYPASS  	0x20  //��regulator֧��bypass mode
*/
	unsigned int valid_ops_mask;

	//��ʾ��regulator��input����һ��regulator
	int input_uV;

	//�����regulator�ĸ���suspend״̬��
	struct regulator_state state_disk;
	struct regulator_state state_mem;
	struct regulator_state state_standby;
	
	//suspend state to set at init
	suspend_state_t initial_state;

	//mode to set on startup
	unsigned int initial_mode;

	//�ı��ѹ����Դ�ȶ���ʱ�䡣��ΪӲ��ԭ�򣬸ı��Դ�������̾ͳɹ���������Ҫ��һ�����ӳ�
	unsigned int ramp_delay;

	//�Ƿ���ϵͳ������һֱʹ��
	unsigned always_on:1;
	
	//�Ƿ���boot�׶�ʹ��
	unsigned boot_on:1;
	
	/* apply uV constraint if min == max */
	unsigned apply_uV:1;
};
```

regulator ����������һ����dts�����������磺

```c
ldo_vcama {
	regulator-name = "vcama";
	regulator-min-microvolt = <0x2625a0>;
	regulator-max-microvolt = <0x2ab980>;
	regulator-enable-ramp-delay = <0x108>;
	linux,phandle = <0x62>;
	phandle = <0x62>;
	regulator-default-on = <0x1>;
	status = "okay";
};
```

���� regulator driver

ע���Լ��� regulator ���� regulator core framework �У��� consumer �ṩ����

regulator driver ͨ������

regulator_register(const struct regulator_desc *regulator_desc, const struct regulator_config *config)

ע�� regulator_ops ��regulator core ��

��һ������struct regulator_desc����̬��regulator���ã���ν��̬���ǲ��ٻ�ı�����á�

�ڶ�����������regulator�Ķ�̬������Ϣ��

```c
���� regulator �ľ�̬��Ϣ
struct regulator_desc {

	//��regulator�����֡�
	const char *name;
	
	//��regulator parent��name���ڼ���ʱʹ��
	const char *supply_name;
	
	//���ڱ�ʶ��regulator��Ҳ���Ա�ʶϵͳ�ж��ٸ�regulator	
	int id;
	
	//��ʾregulator�Ƿ�����ڵ�ѹԼ����Χ�����������ѹ
	bool continuous_voltage_range;
	
	//ͨ��ops.list_voltage������ȡ���õĵ�ѹ����	
	unsigned n_voltages;
	
	//regulator�Ĳ�����������	
	struct regulator_ops *ops;
	
	//��regulator���жϺ�	
	int irq;
	
	//����ǰregulator�����ͣ���ѹ�����
	enum regulator_type type;
	
	struct module *owner;

	//���������mapp�Ļ���ʹ����͵�selector��ȡ�ĵ�ѹ	
	unsigned int min_uV;
	
	//ÿ��selector�µ�ѹ����step	
	unsigned int uV_step;
	
	//����mapp����С��selector��	
	unsigned int linear_min_sel;
	
	//��ѹ�ı�֮����Ҫ���ʱ���ȶ�����	
	unsigned int ramp_delay;
	
	//��ѹ��mapp��
	const unsigned int *volt_table;
	
	unsigned int vsel_reg;
	unsigned int vsel_mask;
	unsigned int apply_reg;
	unsigned int apply_bit;
	unsigned int enable_reg;
	unsigned int enable_mask;
	bool enable_is_inverted;
	unsigned int bypass_reg;
	unsigned int bypass_mask;
	
	// regulator��ʼ������Ҫ��ʱ��
	unsigned int enable_time;
};
```

```c
regulator����������
struct regulator_ops {
	int (*list_voltage) (struct regulator_dev *, unsigned selector);
	int (*set_voltage) (struct regulator_dev *, int min_uV, int max_uV, unsigned *selector);
	int (*map_voltage)(struct regulator_dev *, int min_uV, int max_uV);
	int (*set_voltage_sel) (struct regulator_dev *, unsigned selector);
	int (*get_voltage) (struct regulator_dev *);
	int (*get_voltage_sel) (struct regulator_dev *);
	int (*set_current_limit) (struct regulator_dev *, int min_uA, int max_uA);
	int (*get_current_limit) (struct regulator_dev *);
	int (*enable) (struct regulator_dev *);
	int (*disable) (struct regulator_dev *);
	int (*is_enabled) (struct regulator_dev *);
	int (*set_mode) (struct regulator_dev *, unsigned int mode);
	unsigned int (*get_mode) (struct regulator_dev *);
	int (*enable_time) (struct regulator_dev *);
	int (*set_ramp_delay) (struct regulator_dev *, int ramp_delay);
	int (*set_voltage_time_sel) (struct regulator_dev *, unsigned int old_selector, unsigned int new_selector);
	int (*get_status)(struct regulator_dev *);
	unsigned int (*get_optimum_mode) (struct regulator_dev *, int input_uV,  int output_uV, int load_uA);
	int (*set_bypass)(struct regulator_dev *dev, bool enable);
	int (*get_bypass)(struct regulator_dev *dev, bool *enable);
	int (*set_suspend_voltage) (struct regulator_dev *, int uV);
	int (*set_suspend_enable) (struct regulator_dev *);
	int (*set_suspend_disable) (struct regulator_dev *);
	int (*set_suspend_mode) (struct regulator_dev *, unsigned int mode);
};
```

```c
���� regulator �Ķ�̬��Ϣ
struct regulator_config {
	struct device *dev;
	
	//�弶����س�ʼ����Ϣ��ͨ������DT�������ڴ�
	const struct regulator_init_data *init_data;
	void *driver_data;
	struct device_node *of_node;
	struct regmap *regmap;

	int ena_gpio;
	unsigned int ena_gpio_invert:1;
	unsigned int ena_gpio_flags;
};
```

```c
���豸�ĽǶ����� regulator , regulator_register �ķ���ֵ���͡�
struct regulator_dev {
	const struct regulator_desc *desc;
	int exclusive;
	u32 use_count;
	u32 open_count;
	u32 bypass_count;

	/* lists we belong to */
	struct list_head list; /* list of all regulators */

	/* lists we own */
	struct list_head consumer_list; /* consumers we supply */

	struct blocking_notifier_head notifier;
	struct mutex mutex; /* consumer lock */
	struct module *owner;
	struct device dev;
	struct regulation_constraints *constraints;
	struct regulator *supply;	/* for tree */
	struct regmap *regmap;

	struct delayed_work disable_work;
	int deferred_disables;

	void *reg_data;		/* regulator_dev data */

	struct dentry *debugfs;

	struct regulator_enable_gpio *ena_pin;
	unsigned int ena_gpio_state:1;
};
```

���� consumer

```c
�� regulator consumer �ĽǶȣ����� regulator �豸
/*
 * One for each consumer device.
 */
struct regulator {
	struct device *dev;
	struct list_head list;
	unsigned int always_on:1;
	unsigned int bypass:1;
	int uA_load;
	int min_uV;
	int max_uV;
	char *supply_name;
	struct device_attribute dev_attr;
	struct regulator_dev *rdev;
	struct dentry *debugfs;
};
```

�ġ� core

�ṩ regulator �ӿڣ��� regulator_register()�� regulator_get()�� regulator_put()�� regulator_enable()��regulator_disable()�� regulator_set_voltage()�� regulator_is_enabled()��

�塢 vendor pmic ʵ��

```c
struct vendor_regulator {
	struct regulator_desc desc;
	struct regulator_init_data init_data;
	struct regulator_config config;
	struct device_attribute en_att;
	struct device_attribute voltage_att;
	struct regulator_dev *rdev;
	PMU_FLAGS_LIST_ENUM en_reg;
	PMU_FLAGS_LIST_ENUM vol_reg;
	PMU_FLAGS_LIST_ENUM qi_en_reg;
	PMU_FLAGS_LIST_ENUM qi_vol_reg;	
	const void *pvoltages;
	bool isUsedable;
	struct regulator *reg;
};
```

�ο����ϣ�

https://blog.csdn.net/longwang155069/article/details/53129378


