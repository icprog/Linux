

Linux PlatformBus ��صĽṹ��



һ��PlatformBus����
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


����PlatformDevice����
```c
struct platform_device {
  const char	*name;
  int	id;
  bool	id_auto;
  struct device	dev;
  u32	num_resources;
  struct resource	*resource;
  const struct platform_device_id	*id_entry;
  char *driver_override;
  struct mfd_cell *mfd_cell;
  struct pdev_archdata	archdata;
};
```

����PlatformDriver����
```c
struct platform_driver {
  int (*probe)(struct platform_device *);
  int (*remove)(struct platform_device *);
  void (*shutdown)(struct platform_device *);
  int (*suspend)(struct platform_device *, pm_message_t state);
  int (*resume)(struct platform_device *);
  struct device_driver driver;
  const struct platform_device_id *id_table;
  bool prevent_deferred_probe;
};
```

�ġ�ע��

platformBus�����ͣ�Ϊ��ͨ��bus_type���͡�

platformDevice�����ͣ���device���͵ķ�װ��

platformDriver�����ͣ���driver���͵ķ�װ��

