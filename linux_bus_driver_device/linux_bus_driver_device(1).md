

linux bus driver device ��صĽṹ��

һ��bus��صĽṹ��

1��bus�ṹ��
```c
struct bus_type {
    const char	*name;
    const char	*dev_name;
    struct device	*dev_root;
    struct device_attribute	*dev_attrs;	/* use dev_groups instead */
    const struct attribute_group **bus_groups;
    const struct attribute_group **dev_groups;
    const struct attribute_group **drv_groups;
    int (*match)(struct device *dev, struct device_driver *drv);
    int (*uevent)(struct device *dev, struct kobj_uevent_env *env);
    int (*probe)(struct device *dev);
    int (*remove)(struct device *dev);
    void (*shutdown)(struct device *dev);
    int (*online)(struct device *dev);
    int (*offline)(struct device *dev);
    int (*suspend)(struct device *dev, pm_message_t state);
    int (*resume)(struct device *dev);
    const struct dev_pm_ops *pm;
    const struct iommu_ops *iommu_ops;
    struct subsys_private *p;
    struct lock_class_key lock_key;
};
```
2��bus��˽������
```c
struct subsys_private {
    struct kset subsys;
    struct kset *devices_kset;
    struct list_head interfaces;
    struct mutex mutex;
    struct kset *drivers_kset;
    struct klist klist_devices;
    struct klist klist_drivers;
    struct blocking_notifier_head bus_notifier;
    unsigned int drivers_autoprobe:1;
    struct bus_type *bus;
    struct kset glue_dirs;
    struct class *class;
};
```
3��ע��

��1��bus�ṹ�壬��Ҫ��ע����match������ʵ�֣����match��������ƥ��device��driver�ġ�

��2��bus��˽�����ݣ���Ҫ��һЩkset ��klist�ķ�װ����������bus�����driver��device��

��3��bus��˽������������һ��drivers_autoprobe�����������driver_register�������õ���



����driver��صĽṹ��

1��driver�ṹ��
```c
struct device_driver {
    const char	*name;
    struct bus_type	*bus;
    struct module	*owner;
    const char	*mod_name;	/* used for built-in modules */
    bool suppress_bind_attrs;	/* disables bind/unbind via sysfs */
    enum probe_type probe_type;
    const struct of_device_id	*of_match_table;
    const struct acpi_device_id	*acpi_match_table;
    int (*probe) (struct device *dev);
    int (*remove) (struct device *dev);
    void (*shutdown) (struct device *dev);
    int (*suspend) (struct device *dev, pm_message_t state);
    int (*resume) (struct device *dev);
    const struct attribute_group **groups;
    const struct dev_pm_ops *pm;
    struct driver_private *p;
};
```
2��driver˽������
```c
struct driver_private {
    struct kobject kobj;
    struct klist klist_devices;
    struct klist_node knode_bus;
    struct module_kobject *mkobj;
    struct device_driver *driver;
};
```
3��ע��

��1��driver�ṹ�壬һ�㲻����ʹ�ã���һ�㱻��װ��platform_driver��i2c_driver����Ӧ��ĳһ���ض������µ�driver��

��2��driver˽�����ݣ�����kobject ��klist�ṹ�塣



����device��صĽṹ��
1��device�ṹ��
```c
struct device {
    struct device	*parent;
    struct device_private	*p;
    struct kobject kobj;
    const char	*init_name;
    const struct device_type *type;
    struct mutex	mutex;
    struct bus_type	*bus;	/* type of bus device is on */
    struct device_driver *driver; 
    void	*platform_data;
    void	*driver_data; 
    struct dev_pm_info	power;
    struct dev_pm_domain	*pm_domain;
#ifdef CONFIG_GENERIC_MSI_IRQ_DOMAIN
    struct irq_domain	*msi_domain;
#endif
#ifdef CONFIG_PINCTRL
    struct dev_pin_info	*pins;
#endif
#ifdef CONFIG_GENERIC_MSI_IRQ
    struct list_head	msi_list;
#endif
#ifdef CONFIG_NUMA
    int	numa_node;	/* NUMA node this device is close to */
#endif
    u64	*dma_mask;	/* dma mask (if dma'able device) */
    u64	coherent_dma_mask
    unsigned long	dma_pfn_offset;
    struct device_dma_parameters *dma_parms;
    struct list_head	dma_pools;	/* dma pools (if dma'ble) */
    struct dma_coherent_mem	*dma_mem;
#ifdef CONFIG_DMA_CMA
    struct cma *cma_area;
#endif
    struct dev_archdata	archdata;
    struct device_node	*of_node; /* associated device tree node */
    struct fwnode_handle	*fwnode; /* firmware device node */
    dev_t	devt;	/* dev_t, creates the sysfs "dev" */
    u32	id;	/* device instance */
    spinlock_t	devres_lock;
    struct list_head	devres_head;
    struct klist_node	knode_class;
    struct class	*class;
    const struct attribute_group **groups;	/* optional groups */
    void	(*release)(struct device *dev);
    struct iommu_group	*iommu_group;
    bool	offline_disabled:1;
    bool	offline:1;
};
```
2��device˽������
```c
struct device_private {
    struct klist klist_children;
    struct klist_node knode_parent;
    struct klist_node knode_driver;
    struct klist_node knode_bus;
    struct list_head deferred_probe;
    struct device *device;
};
```
3��ע��

��1��device�ṹ�壬��������һ���豸��������Ϣ��

��2����������kobject ��klist �ṹ�塣

