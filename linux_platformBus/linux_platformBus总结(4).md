

Linux PlatformBus �ܽ�


1�����ʹ��platform_driver��
��ģ���ʼ��������ʹ�ã�platform_driver_register()ע��һ��platform_driver��
����Ҫ������ĳ�Աprobe��remove��driver.name��driver.owner��driver.of_match_table��
of_match_table�����.compatible ����dts�ж����Ҫ��ͬ��


2��platform_driver_register�����������Щ���ܣ�
��1�����driver�ĳ�Ա����bus��probe��remove
��2������driver_register()ע�����driver
��3��ע��һ��platform_driver��ʵ���Ͻ���������platformBus��ϵ������Ȼ�����driver_register()ע��һ��driver�����Ļ�����driver_register()��



3��platformBus��ôƥ��platform_driver��platform_device�ģ�
��driver_register()�У������drv->bus->match(dev, drv)��ƥ��device��driver��������platform_match������һ���õ����������2��ƥ�䷽ʽ��
��1������ofƥ�䣺�Ƚ�device��driver��compatible����ֵ�Ƿ���ͬ��
��2������nameƥ�䣺�Ƚ�platform_device.name �� platform_driver.name�Ƿ���ͬ��



4��platformBus�������������ﶨ���ע��ģ�
���ں˳�ʼ����ʱ�򣬻����bus_register()ע��һ��platformBus��bus_register()����Ҫ�Ĺ����Ǹ�bus��˽������struct subsys_private�����ڴ沢��䡣



5���ڻ���of��ƥ��ʱ������ֻ������һ��platform_driver����û�ж���platform_device����ô���platform_device�����ģ�
�ڻ���of��ƥ���У���ͨ�� driver->of_match_table �� device->of_node ��ƥ��ġ�

device�ĳ�Աof_node��������struct device_node�������ں˳�ʼ��ʱ��unflatten_dt_node()�з����ڴ沢�ҽ�dtb����Ϣ�������������

�����ȼ�Ϊ3��ģ���ʼ�������У�platform_device����Դ���ڴ�����������б�ͳһ���䣺of_platform_populate()��



6��platformBus��platformDevice��platformDriver�ĳ�ʼ��
���ں˳�ʼ��ʱ��platformBus�ĳ�ʼ������ǰ�棺bus_register(&platform_bus_type)��

Ȼ������ do_initcalls()��

��1��������platformDevice�ĳ�ʼ����arch_initcall_sync�У����ȼ�Ϊ3s��sync��ʾͬ�������ȴ������ȼ�Ϊ3s����3�ͣ���arch_initcall_sync(of_platform_default_populate_init)��

��2��Ȼ���Ǹ���platformDriver�ĳ�ʼ����module_init�У����ȼ�Ϊ6����


