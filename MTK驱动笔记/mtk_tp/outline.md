
```c
platform:mt6761
kernel version:kernel-4.9
Android version:Android 8.1

���� base
1. tp ��㴥��
��㴥��Э��A��B��
type-A��ÿ�ζ��ϱ����ݣ�
type-B��BЭ����ҪӲ��֧�֡�����ͨ��slot���棬����id����ʶһ�����㣬���ٴ����ϱ����û��ռ��������


һ��MTK tp driver
1. tp driver ��Ϊ2���֣�mtk-tpd driver���ֺ� 3rd tp driver���֡�
mtk-tpd driver ʹ�� late_initcall() ע�᣻
3rd tp driver ʹ�� module_init() ע�᣻
mtk-tpd driver �����ȼ��ϵͣ������ڼ��� 3rd tp dirver �� tp driver ���ݴ���

2. ���Ƚ��� 3rd tp driver ��
1�� ����dts�е�tp��Ϣ�����棬��ֱ��ʣ����ⰴ��ֵ�ȡ�
2�� ���ʹ����tp�ľ��봫�������ܣ���Ҫ���� alsps_driver_add() ���һ�����봫������driver��
3�� ���� tpd_driver_add() ��� 3rd tp dirver �� tp driver �����б��档

3. Ȼ���� mtk-tpd driver��
1�� ͨ����������ע�� tpd platform driver��
    static struct workqueue_struct *tpd_init_workqueue;
    static struct work_struct tpd_init_work;
    tpd_init_workqueue = create_singlethread_workqueue("mtk-tpd");
    INIT_WORK(&tpd_init_work, tpd_init_work_callback);
    queue_work(tpd_init_workqueue, &tpd_init_work);
�������лص�����������Ǵ���һ�� tpd platform driver��

2�� ���� tpd probe �����У�
ע��һ�� misc device�����Զ� tp open �� ioctl�����ݸ��û��ռ�һЩ���ݣ�
��ʼ�� tp pinctrl ����λ���ж����ţ�
���� input_allocate_device() ����һ�������豸�����ڴ��������豸��
����һЩ�������豸֧�ֵ��¼���EV_ABS/EV_KEY/ABS_X/ABS_Y/ABS_PRESSURE/INPUT_PROP_DIRECT��
���� tp driver ���飬�������� tpd_local_init() ������
--���� 3rd tp driver �� tpd_local_init() ������
--��ʼ�� regulator ���� tp �ϵ磻
--���� i2c_add_driver() ��� tp i2c ������
--���� tp i2c probe������3rd tp ��ʼ����
----�����������У� ts_data->ts_workqueue = create_singlethread_workqueue("fts_wq");
----����һ����dmaӳ������i2c�������ݣ� dma_alloc_coherent();
----ʹ��Э��B����ʼ��slot�� input_mt_init_slots()��
----ͨ��i2c��ȡ tp ic id����Ϣ��
----����proc��sysfs�ļ���
----gesture init��input_set_capability/set_bit������֧�ֵ����ƣ�
----����ESD check���������Ĵ�����ֵ�Ƿ���ȷ��
	INIT_DELAYED_WORK(&ts_data->esdcheck_work, esdcheck_func);
	queue_delayed_work(ts_data->ts_workqueue, &ts_data->esdcheck_work, msecs_to_jiffies(ESDCHECK_WAIT_TIME));
	�� esdcheck_func �У� queue_delayed_work(ts_data->ts_workqueue, &ts_data->esdcheck_work,msecs_to_jiffies(ESDCHECK_WAIT_TIME)); һֱѭ�����������
	ESD���ʧ�ܾ�ִ�и�λ��recovery��
----����һ���ϱ�������̣߳� 
      ts_data->thread_tpd = kthread_run(touch_event_handler, 0, TPD_DEVICE);
----����߳�һ��ȥ��������һ���ȴ������ϣ����жϴ������б����ѣ� 
      wait_event_interruptible(waiter, tpd_flag != 0);
----����ȴ����б������ˣ��Ż��ȡ���ݲ����ϱ���
----ע���жϣ� request_irq()��tp���жϴ��������ѵȴ����У�
      wake_up_interruptible(&waiter);
----����tp�̼��������� 
	INIT_WORK(&ts_data->fwupg_work, fts_fwupg_work);
	queue_work(ts_data->ts_workqueue, &ts_data->fwupg_work);
----�˳� 3rd dirver probe ������
���� tp resume �������У�
    touch_resume_workqueue = create_singlethread_workqueue("touch_resume");
    INIT_WORK(&touch_resume_work, touch_resume_workqueue_callback);
�����ں�֪ͨ��������tp resume�¼��Ĵ���
    tpd_fb_notifier.notifier_call = tpd_fb_notifier_callback;
    fb_register_client(&tpd_fb_notifier);
����յ���LCD�����¼������ã�
    queue_work(touch_resume_workqueue,&touch_resume_work);
    ����������� callback �е��� tp �� resume ������
����յ���LCD����¼������ã�
    g_tpd_drv->suspend(NULL);
�����Ͳ�����tp��resume��LCD����ʱ�䣬������LCD����һ˲��tp�޷�ʹ�á�
����set_bit()���ø������豸֧�ֵ��¼����� ABS_MT_TRACKING_ID��
ע�������豸��input_register_device(tpd->dev)��
��������ⰴ�������ã�tpd_button_init()���������������Ϊ���ⰴ�������ע��һ�������豸��input_allocate_device��input_register_device��
Ϊ�豸����sysfs�����ļ���device_create_file��

3. tp ����ʹ�����ж��ϰ벿���°벿���ں��̡߳��������С��ȴ����У�
1�� 
tp ���ϱ�����������һ���ں��߳��н��У�����ں��߳�һ��ʼ��������һ���ȴ������ϡ�
�� tp �жϴ�������(�ж��ϰ벿)�����ѵȴ����У�Ȼ��ִ���ں��߳�(�ж��°벿)��
2�� tp ����������2���������У�
��1������������2��������
ESD check ���������Ǹ�ѭ���Ĺ�����һֱ����ִ�У�
tp �̼������������������ִֻ��һ�Σ�
��2������������1������������ tp resume:
���ﻹʹ�����ں�֪ͨ����
���յ�LCD����֪ͨ�󣬽� tp resume ������ӵ��������У���������Ժ󽫻�õ�ִ�У�
���յ�LCD���֪ͨ��ֱ��ִ�� tp suspend ������
```

