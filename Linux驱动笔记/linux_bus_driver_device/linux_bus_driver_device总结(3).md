

linux bus��driver��device�ܽ�

1��bus��driver��device��ע���Ⱥ�˳��Ϊ��

��1������platformBus��

�������ں˳�ʼ��ע��һ��platform_bus��

bus_register(&platform_bus_type)������bus��

Ȼ���ǽ���device_node����ʼ��platform_device��of_platform_default_populate_init()������device��

Ȼ����Ǹ���platform_driver�ĳ�ʼ�������磺platform_driver_register(&mt_i2c_driver)������driver��

��2������i2cBus(����ָ����i2c client��������i2c adapter�����߹���platformBus��)��

������i2c-core.c��ע��һ��i2cBus��bus_register(&i2c_bus_type)������bus��

Ȼ����i2c-vendor.c�У������i2c_register_adapter()�����������������of_i2c_register_devices()������������������i2c client�豸��ע�ᣬ����device��

�����driver����2�������

i2c����driver����platform_driver_register��ʵ�֣�platform_driver_register(&mt_i2c_driver)��

i2c slave�豸driver����i2c_register_driver��ʵ�֣�i2c_add_driver(&tpd_i2c_driver)��

2������£����Ƕ������driver_register����deviceƥ�䡣



2��bus��driver��device���ԵĽṹ���У�������һ��˽�����ݽṹ����Ҫ��Ա����kset��kobject��klist��bus�ṹ�����kset��klist��driver�ṹ�����kobject��klist��klist_node��device�ṹ�����kobject��klist��klist_node��

3����עһ��driver_register()�������������ѭ������ÿһ��device��Ȼ�����drv->bus->match(dev, drv)��ƥ�����Լ�Ҳ����driver��device��

�������һ��deviceƥ�䣬�ͻ����drv->probe(dev)��������probe����ִ����ɺ󣬻����Ѱ��next_device()����������ܹ�ƥ�䣬��������drv->probe(dev)��

���ԣ�һ��driver���Զ�Ӧ���device��һ��driver��probe��������ִ�ж�Ρ�

������Գ�����i2c���������С�������dts��i2c0��i2c3��ƥ��ڵ㶼һ����compatible = "vendor,i2c"������ֻע����һ��i2c����driver��platform_driver_register(&mt_i2c_driver)��ֻ�������driver��probe�����ᱻ����4�Ρ�


4����device_register()�����У������bus_add_device(dev)�����device��bus��ϵ�����������device��klist_node������ӵ�bus��klist����β������

���������bus_probe_device(dev)����ͼƥ��driver���������ʱ��driver��û����ӵ�bus�ϣ������������û�����á�


5����driver_register()�У�Ҳ����� klist_add_tail �����driver��bus��ϵ�����������driver��klist_node������ӵ�bus��klist����β������

6����driver_register()������really_probe()�����У�

�����ж�ִ�е��ǣ�dev->bus->probe(dev);

�������ĺ��������ڣ���ִ�У�drv->probe(dev);

����ִ��һ����

��1����platformBus�У�

dev->bus->probeΪ��NULL��

drv->probeΪ��platform_drv_probe()��������ã�

platform_driver->probe(platform_device)�������Ƕ����platform probe������

��2����i2cBus�У�ָ����i2c client device��driver����

dev->bus->probeΪ��i2c_device_probe()��������ã�

i2c_driver->probe()�������Ƕ����i2c_driver�����probe������

drv->probeΪ��NULL��

7��ע��

��1������driver_register()ʱ����ִ�е�������
```c
bus_for_each_dev(drv->bus, NULL, drv, __driver_attach);
```
������bus�����ÿһ��device����ͼ����ƥ�䡣

��2������device_register()ʱ����ִ�е�������
```c
bus_for_each_drv(dev->bus, NULL, &data,__device_attach_driver);
```
������bus�����ÿһ��driver����ͼ����ƥ�䡣

