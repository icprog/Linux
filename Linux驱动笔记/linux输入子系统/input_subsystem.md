
```c
mtk input��ϵͳ

������ص�֪ʶ

0�� list_add_tail(struct list_head *new, struct list_head *head);
		�� new ��ӵ� head ��β����

1�� list_for_each_entry(pos, head, member)  ��ѭ������ÿһ�� pos ������ member ��ԭ�����£�

#define list_for_each_entry(pos, head, member)              \  
    for (pos = list_entry((head)->next, typeof(*pos), member);   \  
         prefetch(pos->member.next), &pos->member != (head);  \  
         pos = list_entry(pos->member.next, typeof(*pos), member))  

prefetch�ĺ����Ǹ���cpu��ЩԪ���п������Ͼ�Ҫ�õ�������cpuԤȡһ�£�������������ٶȣ�����Ԥȡ����߱����ٶȣ�

#define list_entry(ptr, type, member) 	    container_of(ptr, type, member)       
//type Ϊĳ���ṹ������ͣ� member Ϊ�ṹ���ĳ����Ա�� ptr Ϊ member ��ָ�롣���� ptr ��ȡ�����ṹ��ĵ�ַ��

2��Linux input��ϵͳ���ϵ��·�Ϊ3�㣺�¼������(event_handler)�� input���Ĳ㣬input�����㡣
1��input ��������Ӳ����������ȡ touch panel �����ݣ��жϲ����ȡ�
2��input ���Ĳ��ṩ�ӿںͲ����������¼������� input �����㣬�� input ����������ݴ����¼�����㡣
3���¼���������û��ռ��Ӧ�ó��򽻻���Ӧ�ó���ֻ����� event_handler ���ļ����豸�ڵ�ӿڣ�������ĵײ���������

3�� attention��
1�� input_register_handler() �ǻ��� module_init() ���� input_register_handler() �����У��У�
    list_add_tail(&handler->node, &input_handler_list); 
    list_for_each_entry(dev, &input_dev_list, node)  		
        input_attach_handler(dev, handler);	
		
1.1�������� handler ������ input_dev �������ӣ����ڴ�ʱ input_dev_list ���滹û�� input_dev ���أ�����handler ���� input_dev ��ʧ�ܡ�

2)	input_register_device() �ǻ��� late_initcall() ���� input_register_device() �����У��У�
    list_add_tail(&dev->node, &input_dev_list);		
    list_for_each_entry(handler, &input_handler_list, node)				
        input_attach_handler(dev, handler);

2.1�� ������ input_dev ������ handler �������ӣ����ڴ�ʱ input_handler_list ���������һ�� handler ����������� handler �� input_dev ���ӳɹ������� evdev_connect() ������

3�� �� evdev_connect() �����У������ input_register_handle() ����ע��һ�� handle �� input_handle ������ input_dev �� input_handler ��������ֻ�е� input_dev �� input_handler ���ӳɹ�ʱ���Ż�ע��һ�� input_handle �ṹ�壬�����߹�����

4����4����Ҫ�Ľṹ�壺
input_dev �� input_handler �� input_handle �� evdev 
4.1) input_dev  �� input ������Ľṹ��
4.2) input_handler ��
4.3) input_handle 	��
4.4) evdev  �� ����һ���ַ��豸���ṩ��Ӧ�ó���Ľӿڡ�


һ��������Ҫ�Ľṹ��
0�� evdev �ṹ�壺
struct evdev {
	int open;
	struct input_handle handle;
	wait_queue_head_t wait;
	struct evdev_client __rcu *grab;
	struct list_head client_list;
	spinlock_t client_lock; /* protects client_list */
	struct mutex mutex;
	struct device dev;
	struct cdev cdev;
	bool exist;
};

1�� input_handle �ṹ�壺
struct input_handle {
	void *private;
	int open;
	const char *name;
	struct input_dev *dev;
	struct input_handler *handler;
	struct list_head	d_node;
	struct list_head	h_node;
};

2�� input_handler �ṹ�壺
struct input_handler {
	void *private;
	void (*event)(struct input_handle *handle, unsigned int type, unsigned int code, int value);
	void (*events)(struct input_handle *handle,   const struct input_value *vals, unsigned int count);
	bool (*filter)(struct input_handle *handle, unsigned int type, unsigned int code, int value);
	bool (*match)(struct input_handler *handler, struct input_dev *dev);
	int (*connect)(struct input_handler *handler, struct input_dev *dev, const struct input_device_id *id);
	void (*disconnect)(struct input_handle *handle);
	void (*start)(struct input_handle *handle);
	bool legacy_minors;
	int minor;
	const char *name;
	const struct input_device_id *id_table;
	struct list_head	h_list;
	struct list_head	node;
};

3�� input_dev �ṹ�壺
struct input_dev {
	const char *name;
	const char *phys;
	const char *uniq;
	struct input_id id;
	unsigned long propbit[BITS_TO_LONGS(INPUT_PROP_CNT)];
	unsigned long evbit[BITS_TO_LONGS(EV_CNT)];
	unsigned long keybit[BITS_TO_LONGS(KEY_CNT)];
	unsigned long relbit[BITS_TO_LONGS(REL_CNT)];
	unsigned long absbit[BITS_TO_LONGS(ABS_CNT)];
	unsigned long mscbit[BITS_TO_LONGS(MSC_CNT)];
	unsigned long ledbit[BITS_TO_LONGS(LED_CNT)];
	unsigned long sndbit[BITS_TO_LONGS(SND_CNT)];
	unsigned long ffbit[BITS_TO_LONGS(FF_CNT)];
	unsigned long swbit[BITS_TO_LONGS(SW_CNT)];
	unsigned int hint_events_per_packet;
	unsigned int keycodemax;
	unsigned int keycodesize;
	void *keycode;
	int (*setkeycode)(struct input_dev *dev,  const struct input_keymap_entry *ke,  unsigned int *old_keycode);
	int (*getkeycode)(struct input_dev *dev,  struct input_keymap_entry *ke);
	struct ff_device *ff;
	unsigned int repeat_key;
	struct timer_list timer;
	int rep[REP_CNT];
	struct input_mt *mt;
	struct input_absinfo *absinfo;
	unsigned long key[BITS_TO_LONGS(KEY_CNT)];
	unsigned long led[BITS_TO_LONGS(LED_CNT)];
	unsigned long snd[BITS_TO_LONGS(SND_CNT)];
	unsigned long sw[BITS_TO_LONGS(SW_CNT)];
	int (*open)(struct input_dev *dev);
	void (*close)(struct input_dev *dev);
	int (*flush)(struct input_dev *dev, struct file *file);
	int (*event)(struct input_dev *dev, unsigned int type, unsigned int code, int value);
	struct input_handle __rcu *grab;
	spinlock_t event_lock;
	struct mutex mutex;
	unsigned int users;
	bool going_away;
	struct device dev;
	struct list_head	h_list;
	struct list_head	node;
	unsigned int num_vals;
	unsigned int max_vals;
	struct input_value *vals;
	bool devres_managed;
};

һ��input��ϵͳ�ܹ�(�ֲ�ܹ�)��

--------------------------------------------------------------------------------------------------------------------------
APP�㣺Ӧ�ó����ļ��ӿ�
/dev/input/event6
��������
/dev/input/event0
/dev/input/ts0
/dev/input/mouse0
/dev/ttyn
-------------------------------------------------------------------------------------------------------------------------
�¼������(event_handler)��
evdev.c
tsdev.c
mousedev.c
keyboard.c
event_handler ʵ���˶���¼��Ĵ����������� ����ͨ���豸�� evdev ����������������豸�� mousedev ��������Ϸ�� joydev ��
--------------------------------------------------------------------------------------------------------------------------
input���Ĳ�(input core)��
input.c(���� input_event() ����)
--------------------------------------------------------------------------------------------------------------------------
input driver�㣺
1) mtk tp driver 
2) 3rd tp driver
--------------------------------------------------------------------------------------------------------------------------
Ӳ���㣺		
cap touch panel
--------------------------------------------------------------------------------------------------------------------------

�����¼������ event_handler �ĳ��� evdev.c 
0����صĽṹ��
0.1 �ļ������ӿڣ� evdev �ṩ��Ӧ�ó���Ľӿ�
static const struct file_operations evdev_fops = {
	.owner		= THIS_MODULE,
	.read		= evdev_read,
	.write		= evdev_write,
	.poll		= evdev_poll,
	.open		= evdev_open,
	.release	= evdev_release,
	.unlocked_ioctl	= evdev_ioctl,
#ifdef CONFIG_COMPAT
	.compat_ioctl	= evdev_ioctl_compat,
#endif
	.fasync		= evdev_fasync,
	.flush		= evdev_flush,
	.llseek		= no_llseek,
};

struct evdev {
	int open;
	struct input_handle handle;
	wait_queue_head_t wait;
	struct evdev_client __rcu *grab;
	struct list_head client_list;
	spinlock_t client_lock; /* protects client_list */
	struct mutex mutex;
	struct device dev;
	struct cdev cdev;
	bool exist;
};

struct input_handle {
	void *private;
	int open;
	const char *name;
	struct input_dev *dev;
	struct input_handler *handler;
	struct list_head	d_node;
	struct list_head	h_node;
};

static const struct input_device_id evdev_ids[] = {
	{ .driver_info = 1 },	/* Matches all devices */
	{ },			/* Terminating zero entry */
};

static struct input_handler evdev_handler = {
	.event		= evdev_event,
	.events		= evdev_events,
	.connect	= evdev_connect,
	.disconnect	= evdev_disconnect,
	.legacy_minors	= true,
	.minor		= EVDEV_MINOR_BASE,		//64
	.name		= "evdev",			//name is to be shown in /proc/bus/input/handlers
	.id_table	= evdev_ids,
};

1�� module_init(evdev_init);
static int __init evdev_init(void)
{
	return input_register_handler(&evdev_handler);			
    //һ�� handler ���Դ����� devices
}

2��  evdev_connect ����(�� input_register_device �б�����)
static int evdev_connect(struct input_handler *handler, struct input_dev *dev, const struct input_device_id *id)
{
	struct evdev *evdev;
	int minor;
	int dev_no;
	int error;

	minor = input_get_new_minor(EVDEV_MINOR_BASE, EVDEV_MINORS, true);
	if (minor < 0) {
		error = minor;
		pr_err("failed to reserve new minor: %d\n", error);
		return error;
	}

	evdev = kzalloc(sizeof(struct evdev), GFP_KERNEL);
	if (!evdev) {
		error = -ENOMEM;
		goto err_free_minor;
	}

	INIT_LIST_HEAD(&evdev->client_list);
	spin_lock_init(&evdev->client_lock);
	mutex_init(&evdev->mutex);
	init_waitqueue_head(&evdev->wait);
	evdev->exist = true;

	dev_no = minor;
	/* Normalize device number if it falls into legacy range */
	if (dev_no < EVDEV_MINOR_BASE + EVDEV_MINORS)
		dev_no -= EVDEV_MINOR_BASE;
	dev_set_name(&evdev->dev, "event%d", dev_no);

	evdev->handle.dev = input_get_device(dev);
	evdev->handle.name = dev_name(&evdev->dev);
	evdev->handle.handler = handler;
	evdev->handle.private = evdev;

	evdev->dev.devt = MKDEV(INPUT_MAJOR, minor);
	evdev->dev.class = &input_class;
	evdev->dev.parent = &dev->dev;
	evdev->dev.release = evdev_free;
	device_initialize(&evdev->dev);

	error = input_register_handle(&evdev->handle);
	if (error)
		goto err_free_evdev;

	cdev_init(&evdev->cdev, &evdev_fops);
	evdev->cdev.kobj.parent = &evdev->dev.kobj;
	error = cdev_add(&evdev->cdev, evdev->dev.devt, 1);
	if (error)
		goto err_unregister_handle;

	error = device_add(&evdev->dev);
	if (error)
		goto err_cleanup_evdev;

	return 0;

 err_cleanup_evdev:
	evdev_cleanup(evdev);
 err_unregister_handle:
	input_unregister_handle(&evdev->handle);
 err_free_evdev:
	put_device(&evdev->dev);
 err_free_minor:
	input_free_minor(minor);
	return error;
}

int input_register_handle(struct input_handle *handle)
{
	struct input_handler *handler = handle->handler;
	struct input_dev *dev = handle->dev;
	int error;

	/*
	 * We take dev->mutex here to prevent race with
	 * input_release_device().
	 */
	error = mutex_lock_interruptible(&dev->mutex);
	if (error)
		return error;

	/*
	 * Filters go to the head of the list, normal handlers
	 * to the tail.
	 */
	if (handler->filter)
		list_add_rcu(&handle->d_node, &dev->h_list);
	else
		list_add_tail_rcu(&handle->d_node, &dev->h_list);  	
        //�� handle ��ӵ� input_dev ������

	mutex_unlock(&dev->mutex);

	/*
	 * Since we are supposed to be called from ->connect()
	 * which is mutually exclusive with ->disconnect()
	 * we can't be racing with input_unregister_handle()
	 * and so separate lock is not needed here.
	 */
	list_add_tail_rcu(&handle->h_node, &handler->h_list);				
    //�� handle ��ӵ� input_handler ������

	if (handler->start)	//handler->start = NULL 
		handler->start(handle);
	return 0;
}

����input���Ĳ�ĳ��� input.c ���ϱ����� input_event() ����
0����صĽṹ��
struct class input_class = {
	.name		= "input",
	.devnode	= input_devnode,
};

1��subsys_initcall(input_init);
static int __init input_init(void)
{
	int err;

	err = class_register(&input_class);			//����  /sys/class/input Ŀ¼�ṹ
	if (err) {
		pr_err("unable to register input_dev class\n");
		return err;
	}

	err = input_proc_init();
	if (err)
		goto fail1;

	err = register_chrdev_region(MKDEV(INPUT_MAJOR, 0),  INPUT_MAX_CHAR_DEVICES, "input");			//INPUT_MAJOR=13    ,   INPUT_MAX_CHAR_DEVICES=1024
//register a range of device numbers
	if (err) {
		pr_err("unable to register char major %d", INPUT_MAJOR);
		goto fail2;
	}

	return 0;

 fail2:	input_proc_exit();
 fail1:	class_unregister(&input_class);
	return err;
}

static int __init input_proc_init(void)
{
	struct proc_dir_entry *entry;

	proc_bus_input_dir = proc_mkdir("bus/input", NULL);			//���� /proc/bus/input Ŀ¼�ṹ
	if (!proc_bus_input_dir)
		return -ENOMEM;

	entry = proc_create("devices", 0, proc_bus_input_dir,   &input_devices_fileops);		//���� proc�ļ��� /proc/bus/input/devices
	if (!entry)
		goto fail1;

	entry = proc_create("handlers", 0, proc_bus_input_dir,  &input_handlers_fileops);      //���� proc �ļ��� /proc/bus/input/handlers
	if (!entry)
		goto fail2;

	return 0;

 fail2:	remove_proc_entry("devices", proc_bus_input_dir);
 fail1: remove_proc_entry("bus/input", NULL);
	return -ENOMEM;
}

2��  input_register_handler()/input_allocate_device()/input_register_device()/input_event() ������

1����صĽṹ��

static struct input_handler evdev_handler = {
	.event		= evdev_event,
	.events		= evdev_events,
	.connect	= evdev_connect,
	.disconnect	= evdev_disconnect,
	.legacy_minors	= true,
	.minor		= EVDEV_MINOR_BASE,		//64
	.name		= "evdev",			//name is to be shown in /proc/bus/input/handlers
	.id_table	= evdev_ids,
};

2�� input_register_handler() �����壺
int input_register_handler(struct input_handler *handler)
{
	struct input_dev *dev;
	int error;

	error = mutex_lock_interruptible(&input_mutex);		//��ȡһ�����Ա��жϵ��ź���
	if (error)
		return error;

	INIT_LIST_HEAD(&handler->h_list);		//��ʼ�� handler ˫���� �� ���˫���� handler->h_list ���� handler �������� handler ������ϵ�á�

	list_add_tail(&handler->node, &input_handler_list);  //�� handler->node ���뵽 input_handler_list ��β����

//list_for_each_entry(pos, head, member)  ��ѭ������ÿһ�� pos ������ member ��	
	list_for_each_entry(dev, &input_dev_list, node)  		//ѭ������ input_dev_list �ϵ�ÿһ�� dev �� node Ϊ dev ��һ����Ա��
		input_attach_handler(dev, handler);							
//������ handler ������ input_dev_list �ϵ����� input_dev ���б������ӣ�Ȼ����� handler->connect ���� evdev_connect() ������
//���Ǵ�ʱ input_dev_list ���滹û�� input_dev ���أ�������δ���û�����塣

	input_wakeup_procfs_readers();

	mutex_unlock(&input_mutex);
	return 0;
}

static inline void input_wakeup_procfs_readers(void)
{
	input_devices_state++;
	wake_up(&input_devices_poll_wait);
}

//�� input_dev �� input_handler ��������
static int input_attach_handler(struct input_dev *dev, struct input_handler *handler)
{
	const struct input_device_id *id;
	int error;

	id = input_match_device(handler, dev);
	if (!id)
		return -ENODEV;  //ֱ���˳���

	error = handler->connect(handler, dev, id);		//���� evdev_connect() ����
	if (error && error != -ENODEV)
		pr_err("failed to attach handler %s to device %s, error: %d\n",  handler->name, kobject_name(&dev->dev.kobj), error);

	return error;
}


static const struct input_device_id *input_match_device(struct input_handler *handler,	struct input_dev *dev)
{
	const struct input_device_id *id;

	for (id = handler->id_table; id->flags || id->driver_info; id++) {			//id->driver_info=1

		if (id->flags & INPUT_DEVICE_ID_MATCH_BUS)
			if (id->bustype != dev->id.bustype)
				continue;

		if (id->flags & INPUT_DEVICE_ID_MATCH_VENDOR)
			if (id->vendor != dev->id.vendor)
				continue;

		if (id->flags & INPUT_DEVICE_ID_MATCH_PRODUCT)
			if (id->product != dev->id.product)
				continue;

		if (id->flags & INPUT_DEVICE_ID_MATCH_VERSION)
			if (id->version != dev->id.version)
				continue;

		if (!bitmap_subset(id->evbit, dev->evbit, EV_MAX))		//��� dev->evbit �� id->evbit ���Ӽ�����  EV_MAX < BITS_PER_LONG  ������1�����򷵻�0
			continue;

		if (!bitmap_subset(id->keybit, dev->keybit, KEY_MAX))
			continue;

		if (!bitmap_subset(id->relbit, dev->relbit, REL_MAX))
			continue;

		if (!bitmap_subset(id->absbit, dev->absbit, ABS_MAX))
			continue;

		if (!bitmap_subset(id->mscbit, dev->mscbit, MSC_MAX))
			continue;

		if (!bitmap_subset(id->ledbit, dev->ledbit, LED_MAX))
			continue;

		if (!bitmap_subset(id->sndbit, dev->sndbit, SND_MAX))
			continue;

		if (!bitmap_subset(id->ffbit, dev->ffbit, FF_MAX))
			continue;

		if (!bitmap_subset(id->swbit, dev->swbit, SW_MAX))
			continue;

		if (!handler->match || handler->match(handler, dev))		//handler->match =0 ������Ϊ�棬 return id ��
			return id;
	}

	return NULL;
}


3��  input_allocate_device() ������
��صĽṹ�壺

static struct device_type input_dev_type = {
	.groups		= input_dev_attr_groups,
	.release	= input_dev_release,
	.uevent		= input_dev_uevent,
#ifdef CONFIG_PM_SLEEP
	.pm		= &input_dev_pm_ops,
#endif
};

struct class input_class = {
	.name		= "input",
	.devnode	= input_devnode,
};

struct input_dev *input_allocate_device(void)
{
	static atomic_t input_no = ATOMIC_INIT(0);
	struct input_dev *dev;

	dev = kzalloc(sizeof(struct input_dev), GFP_KERNEL);
	if (dev) {
		dev->dev.type = &input_dev_type;
		dev->dev.class = &input_class;
		device_initialize(&dev->dev);
		mutex_init(&dev->mutex);
		spin_lock_init(&dev->event_lock);
		init_timer(&dev->timer);
		INIT_LIST_HEAD(&dev->h_list);
		INIT_LIST_HEAD(&dev->node);

		dev_set_name(&dev->dev, "input%lu",  (unsigned long) atomic_inc_return(&input_no) - 1);

		__module_get(THIS_MODULE);
	}

	return dev;
}



4�� input_register_device() ������ 

int input_register_device(struct input_dev *dev)
{
	struct input_devres *devres = NULL;
	struct input_handler *handler;
	unsigned int packet_size;
	const char *path;
	int error;

	if (dev->devres_managed) {
		devres = devres_alloc(devm_input_device_unregister,   sizeof(struct input_devres), GFP_KERNEL);
		if (!devres)
			return -ENOMEM;

		devres->input = dev;
	}

	/* Every input device generates EV_SYN/SYN_REPORT events. */
	__set_bit(EV_SYN, dev->evbit);

	/* KEY_RESERVED is not supposed to be transmitted to userspace. */
	__clear_bit(KEY_RESERVED, dev->keybit);

	/* Make sure that bitmasks not mentioned in dev->evbit are clean. */
	input_cleanse_bitmasks(dev);

	packet_size = input_estimate_events_per_packet(dev);
	if (dev->hint_events_per_packet < packet_size)
		dev->hint_events_per_packet = packet_size;

	dev->max_vals = dev->hint_events_per_packet + 2;
	dev->vals = kcalloc(dev->max_vals, sizeof(*dev->vals), GFP_KERNEL);
	if (!dev->vals) {
		error = -ENOMEM;
		goto err_devres_free;
	}

	/*
	 * If delay and period are pre-set by the driver, then autorepeating
	 * is handled by the driver itself and we don't do it in input.c.
	 */
	if (!dev->rep[REP_DELAY] && !dev->rep[REP_PERIOD]) {
		dev->timer.data = (long) dev;
		dev->timer.function = input_repeat_key;
		dev->rep[REP_DELAY] = 250;
		dev->rep[REP_PERIOD] = 33;
	}

	if (!dev->getkeycode)
		dev->getkeycode = input_default_getkeycode;

	if (!dev->setkeycode)
		dev->setkeycode = input_default_setkeycode;

	error = device_add(&dev->dev);
	if (error)
		goto err_free_vals;

	path = kobject_get_path(&dev->dev.kobj, GFP_KERNEL);
	pr_info("%s as %s\n",
		dev->name ? dev->name : "Unspecified device",
		path ? path : "N/A");
	kfree(path);

	error = mutex_lock_interruptible(&input_mutex);
	if (error)
		goto err_device_del;

	list_add_tail(&dev->node, &input_dev_list);		//����� input_dev ��ӵ� input_dev_list ����

	list_for_each_entry(handler, &input_handler_list, node)				
		input_attach_handler(dev, handler);
//ѭ������ input_handler_list  �ϵ�ÿһ�� handler ������ input_attach_handler()  �� input_dev  attach ����ʱ input_handler_list ��Ϊ�ա�

	input_wakeup_procfs_readers();

	mutex_unlock(&input_mutex);

	if (dev->devres_managed) {
		dev_dbg(dev->dev.parent, "%s: registering %s with devres.\n",	__func__, dev_name(&dev->dev));
		devres_add(dev->dev.parent, devres);
	}
	return 0;

err_device_del:
	device_del(&dev->dev);
err_free_vals:
	kfree(dev->vals);
	dev->vals = NULL;
err_devres_free:
	devres_free(devres);
	return error;
}




5�� input_event() ������

void input_event(struct input_dev *dev, unsigned int type, unsigned int code, int value)
{
	unsigned long flags;

	if (is_event_supported(type, dev->evbit, EV_MAX)) {

		spin_lock_irqsave(&dev->event_lock, flags);
		input_handle_event(dev, type, code, value);
		spin_unlock_irqrestore(&dev->event_lock, flags);
	}
}

static void input_handle_event(struct input_dev *dev,   unsigned int type, unsigned int code, int value)
{
	int disposition;

	disposition = input_get_disposition(dev, type, code, &value);

	if ((disposition & INPUT_PASS_TO_DEVICE) && dev->event)
		dev->event(dev, type, code, value);

	if (!dev->vals)
		return;

	if (disposition & INPUT_PASS_TO_HANDLERS) {
		struct input_value *v;

		if (disposition & INPUT_SLOT) {
			v = &dev->vals[dev->num_vals++];
			v->type = EV_ABS;
			v->code = ABS_MT_SLOT;
			v->value = dev->mt->slot;
		}

		v = &dev->vals[dev->num_vals++];
		v->type = type;
		v->code = code;
		v->value = value;
	}

	if (disposition & INPUT_FLUSH) {
		if (dev->num_vals >= 2)
			input_pass_values(dev, dev->vals, dev->num_vals);
		dev->num_vals = 0;
	} else if (dev->num_vals >= dev->max_vals - 2) {
		dev->vals[dev->num_vals++] = input_value_sync;
		input_pass_values(dev, dev->vals, dev->num_vals);
		dev->num_vals = 0;
	}

}







6��  input_report_key()/input_report_rel()/input_report_abs()
static inline void input_report_key(struct input_dev *dev, unsigned int code, int value)
{
	input_event(dev, EV_KEY, code, !!value);
}

static inline void input_report_rel(struct input_dev *dev, unsigned int code, int value)
{
	input_event(dev, EV_REL, code, value);
}

static inline void input_report_abs(struct input_dev *dev, unsigned int code, int value)
{
	input_event(dev, EV_ABS, code, value);
}



�ġ�input ������
0����صĽṹ��

struct tpd_device *tpd = 0;

struct tpd_device {
	struct device *tpd_dev;
	struct regulator *reg;
	struct regulator *io_reg;
	struct input_dev *dev;
	struct input_dev *kpd;
	struct timer_list timer;
	struct tasklet_struct tasklet;
	int btn_state;
};

1�� late_initcall(mtk_tp_probe)
static int tpd_probe(struct platform_device *pdev)
{
	tpd = kmalloc(sizeof(struct tpd_device), GFP_KERNEL);
	memset(tpd, 0, sizeof(struct tpd_device));
	
	tpd->dev = input_allocate_device();
	tpd->dev->name = TPD_DEVICE;
	set_bit(EV_ABS, tpd->dev->evbit);
	set_bit(EV_KEY, tpd->dev->evbit);
	set_bit(ABS_X, tpd->dev->absbit);
	set_bit(ABS_Y, tpd->dev->absbit);
	set_bit(ABS_PRESSURE, tpd->dev->absbit);
	
	input_register_device(tpd->dev);
}


2�� 3rd tp driver interrupt handle 

static int fts_input_report_b(struct fts_ts_data *data)
{
    int i = 0;
    int uppoint = 0;
    int touchs = 0;
    bool va_reported = false;
    u32 max_touch_num = tpd_dts_data.touch_max_num;
    u32 key_y_coor = TPD_RES_Y;
    struct ts_event *events = data->events;

    for (i = 0; i < data->touch_point; i++) {
        if (KEY_EN && TOUCH_IS_KEY(events[i].y, key_y_coor)) {
            fts_input_report_key(data, i);
            continue;
        }

        if (events[i].id >= max_touch_num)
            break;

        va_reported = true;
        input_mt_slot(tpd->dev, events[i].id);

        if (EVENT_DOWN(events[i].flag)) {
            input_mt_report_slot_state(tpd->dev, MT_TOOL_FINGER, true);

#if FTS_REPORT_PRESSURE_EN
            if (events[i].p <= 0) {
                events[i].p = 0x3f;
            }
            input_report_abs(tpd->dev, ABS_MT_PRESSURE, events[i].p);
#endif
            if (events[i].area <= 0) {
                events[i].area = 0x09;
            }
            input_report_abs(tpd->dev, ABS_MT_TOUCH_MAJOR, events[i].area);
            input_report_abs(tpd->dev, ABS_MT_POSITION_X, events[i].x);
            input_report_abs(tpd->dev, ABS_MT_POSITION_Y, events[i].y);

            touchs |= BIT(events[i].id);
            data->touchs |= BIT(events[i].id);

            FTS_DEBUG("[B]P%d(%d, %d)[p:%d,tm:%d] DOWN!", events[i].id, events[i].x,
                      events[i].y, events[i].p, events[i].area);
        } 
		
		else {
            uppoint++;
            input_mt_report_slot_state(tpd->dev, MT_TOOL_FINGER, false);
            data->touchs &= ~BIT(events[i].id);
            FTS_DEBUG("[B]P%d UP!", events[i].id);
        }
    }

    if (unlikely(data->touchs ^ touchs)) {
        for (i = 0; i < max_touch_num; i++)  {
            if (BIT(i) & (data->touchs ^ touchs)) {
                FTS_DEBUG("[B]P%d UP!", i);
                va_reported = true;
                input_mt_slot(tpd->dev, i);
                input_mt_report_slot_state(tpd->dev, MT_TOOL_FINGER, false);
            }
        }
    }
    data->touchs = touchs;

    if (va_reported) {
        /* touchs==0, there's no point but key */
        if (EVENT_NO_DOWN(data) || (!touchs)) {
            FTS_DEBUG("[B]Points All Up!");
            input_report_key(tpd->dev, BTN_TOUCH, 0);
        } 
		else {
            input_report_key(tpd->dev, BTN_TOUCH, 1);
        }
        input_sync(tpd->dev);
    }

    return 0;
}



�塢 �ܽ�
1. input ��ϵͳһ����3������ģ�飺

1�� input ���Ĳ�
subsys_initcall(input_init);
����ֻע��һ�� input �ࡢע��һ�� input �ַ��豸��š���ʼ�� input proc �ļ�ϵͳ��

2�� �¼������ event_handler
module_init(evdev_init);
����ֻע��һ�� input_handler: input_register_handler(&evdev_handler);
һ�� evdev_handler ���Դ����� input_dev.

int input_register_handler(struct input_handler *handler)
{
	......
	list_add_tail(&handler->node, &input_handler_list);  
	//�� handler->node ���뵽 input_handler_list ��β����

	//���� input_dev_list �ϵ�ÿһ�� dev �� node Ϊ dev ��һ����Ա��
	list_for_each_entry(dev, &input_dev_list, node)  		
		input_attach_handler(dev, handler);							
	//������ handler ������ input_dev_list �ϵ����� input_dev ���б������ӣ�Ȼ����� handler->connect ���� evdev_connect() ������
	//���Ǵ�ʱ input_dev_list ���滹û�� input_dev ���أ�������δ���û��Ч����
	......	
}

���� input_register_handler() �����ý������ǽ���� evdev_handler ��ӵ����� input_handler_list ��β�ˡ�

3�� input ������
late_initcall(tpd_device_init);
�����ע��һ�� input_dev: input_register_device(tpd->dev);

int input_register_device(struct input_dev *dev)
{
	......
	list_add_tail(&dev->node, &input_dev_list);		
	//����� input_dev ��ӵ� input_dev_list ����

	list_for_each_entry(handler, &input_handler_list, node)				
		input_attach_handler(dev, handler);
	//���� input_handler_list �ϵ�ÿһ�� handler ������ input_attach_handler().
	//������ input_dev ������ handler �������ӣ����ڴ�ʱ input_handler_list ���������һ�� handler ����������� handler �� input_dev ���ӳɹ������� evdev_connect() ������
	......	
}

�� evdev_connect() �����У�
���� input_register_handle() ����ע��һ�� input_handle ��
ע��һ�� cdev ���ṩ open/ioctl ���ϲ�Ӧ�õ��á�

input_handle ������ input_dev �� input_handler ��������ֻ�е� input_dev �� input_handler ���ӳɹ�ʱ���Ż�ע��һ�� input_handle �ṹ�壬�����߹�����

int input_register_handle(struct input_handle *handle)
{
	......
	list_add_tail_rcu(&handle->d_node, &dev->h_list);  	
	//�� input_handle ��ӵ� input_dev->h_list.

	list_add_tail_rcu(&handle->h_node, &handler->h_list);				
    //�� input_handle ��ӵ� input_handler->h_list.
	......	
}

2. input ��ϵͳ��4����Ҫ�Ľṹ�壺
1) input_dev: input ������Ľṹ�壻
2) input_handler: ��Ҫ�ṩ��һ�� connect() ���������� input_dev �� input_handler ���ӡ����ṩ�� event ��������
3) input_handle: ��ϵ input_dev �� input_handler ���������ڶ������ӳɹ�ʱ����ע��һ�� input_handle ��
4) evdev: ����һ�� cdev ���ṩ��Ӧ�ó���Ľӿڡ�

3. Ӧ�ó���ֻ����¼������ event_handler ��������������� input ���Ĳ�� input �����㣬Ӧ�ó��򲻻��ע��
�¼������ event_handler �Ż�ͺ��Ĳ�������㽻����

4. ���� input_register_handler �� input_register_device
0)
input_register_handler() �����¼������ע��һ�� evdev_handler.
input_register_device() ���� input ������ע��һ�� input_dev.

1�� input_register_handler() �����������ǣ�
����ע��� evdev_handler ��ӵ����� input_handler_list ��β�ˣ�
���� input_dev_list, �������ÿһ�� input_dev, ���� input_attach_handler().

2�� input_register_device() �����������ǣ�
����ע��� input_dev ��ӵ����� input_dev_list ��β�ˣ�
���� input_handler_list, �������ÿһ�� evdev_handler, ���� input_attach_handler().

3) input_attach_handler() �����������ǣ�
���� input_match_device(), ��� evdev_handler �� match ����Ϊ�գ����� id_table.driver_info = 1, ��ʾ match ���� input_dev, ������û��Ч��.
���� handler->connect(handler, dev, id), �� evdev_connect().

4) evdev_connect() �����������ǣ�
���� input_register_handle() ע��һ�� input_handle.
�ڽṹ evdev ֮��ע��һ�� cdev, �ṩ open/read/write/ioctl ��Ӧ�ó���ʹ�á�
���� device_add(&evdev->dev), ����������豸��ӵ� bus ���ߡ�

5) input_register_handle() �����������ǣ�
�� input_handle ��ӵ� input_dev->h_list.
�� input_handle ��ӵ� input_handler->h_list.
```



