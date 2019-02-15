


```c

/***********************************************************************************************
*
************************************************************************************************/
platform:mt6761
kernel version:kernel-4.9
Android version:Android 8.1



/***********************************************************************************************
*
************************************************************************************************/
����base
1. imgsensor�ķֱ��ʣ���Ԥ���ֱ��ʡ����շֱ��ʡ�¼��ֱ��ʡ�
¼��size��720P��ʾ1280��720,1080P��ʾ1920��1080��
���磺
imgsensor��datasheetΪ640��480����ʾ���ֱ���Ϊ30W����߳ߴ�Ϊ��w:h=4:3��
ͨ����ֵ��������ֱ��ʡ���ֵ��һ���㷨�����ڲ������µ����ص�����£���������ͼ��ķֱ��ʡ�
�µĲ�ֵ������16�ı�����Ϊ4:3��16:9��18:9��

2. camera��ʱ�ӵĺ��壺
(1) MCLK�� ��MIPI CSI�ӿ��У�sensor����ʱ�ӣ���BB���ṩ��һ��Ϊ24MHz����26MHz��
(2) PCLK���ڲ��нӿ��У�sensor������ʱ�ӣ���ʱ��ÿ�仯һ�Σ�data����һ�Ρ�����VSYNC��HSYNC������MCU���л���֡�Ĳ�׽���أ�������ʽ��LCD�෴��
MIPI CSI�ӿڲ���ҪPCLK����MIPI��dataʱ���������ϵĽ�sensor�����ݴ���BB�ˡ�

3. PWDN���ţ�����BB����sensor�� power down���ţ�����sensor��sleep����������sensor���빤��ģʽ����ʡ��ģʽ��һ�����š�

4. ldo�����Դ����BB��ֱ���ṩ��
VCAM_AF����Ȧ��﹩���Դ��һ��1.8V/2.8V
VCAM_IO������IO��Դ����I2C�ӿڡ�MIPI�ӿڹ��硣һ��1.8/2.8
VCAM_A�� ģ���Դ�����й�����ADC���硣һ��1.8/2.8
VCAM_D�� �����ں˵�Դ����ISP���硣һ��1.2/1.5/1.8/2.8

5. ����
EIS�����ӷ���
OIS����ѧ����

6. sensor otp
��1��sensor otp��Ϣ�洢��sensorоƬ�ڲ��ռ����sensor��ҵ�EEPROM�У����ڴ洢sensor�� module ID��lens ID��lens shading��AWB��AF��
��2����ЩУ׼�������ڽ��ÿ��sensor��һ�������⡣��Щ������golden ģ���ṩ��
��3��module ID/lens ID������Բ�Ʒ���й���
��4��lens shading����ͷ��Ӱ���������ڽ����ͷ���ĺ����ܹ��ߺ�ɫ�ʲ�һ�µ����⣬һ��������������ܰ���ͨ��lens shading���Ը�����һ���⡣
��5��AWB���Զ���ƽ�⣬У��R/G��B/G��ֵ�� ����ƫɫ���⡣
��6��AF�������Զ��Խ�����У���������Զ��Խ����ٶȺ�׼ȷ�ԡ�
��6��������洢��Щ��Ϣ��
��sensorоƬ�ڲ��������EEPROM�С�
sensor�ڲ�һ��ʹ��otp�Ĵ�����������Щ���ݣ���Щ�Ĵ���һ��ֻ��дһ�Ρ�����Ρ�����sensor�ڲ�����������sensor��ͬһ��driver IC��
EEPROM������sensor��2���豸�������Զ�ζ�д������sensor���в�ͬ��driver IC��

7. ����ǰ����ͼ��ݵ����⣺
0��ǰ�᣺
ǰ���㹲��һ·iic���� SCL0/SDA0��
ǰ���㹲��vcama/vcamd/vcamio/MCLK�����㻹��vcamaf��
ǰ�����MIPI data 4 line��MIPI clock����ͬһIO�ڣ�
ǰ�����Reset��PWDN����ͬһIO�ڣ�

1��ǰ�������ʹ��ͬһ��imgsensor��
����ǰ�����ic����imx190��
��ǰ������Ϊimx190s(idΪimx190��ID��1)����������Ϊimx190��������Ч������ֳ�2�ݡ�
�������ǰ�㣬��ǰ��غ��㣺
�ڸ������ϵ��ʱ������/��ǰ���PWDN/Reset����ǰ�������
�ڸ�ǰ���ϵ��ʱ������/�ͺ����PWDN/Reset���ú��������
����ͨ��IICͨ��ʱ��ǰ���㲻���໥���š�

2������1�ͺ���2���ݵ������Ҳ����ʹ��ͬһ��imgsensor��
�������1�ͺ���2��ic����gc5025��ͨ��otp��module id������2����ͬ��ic��

3��ʲôʱ����Ҫ����ǰ����iic�ĸ��ţ�
ǰ�������·��ѹ��MCLK�������ˡ���ǰ���ʱ�������ϵ���������Ҳ���ڹ���״̬����������š�

4���ܽ᣺
IICͨ����������������IIC slave�豸�Ѿ��ϵ粢�Ҵ��ڹ���״̬���ܹ�������Ӧ�ź�ACK��Ӧ��IIC master��
����������ǣ��������ǰ�㣬��ǰ��غ��㡣



/***********************************************************************************************
*
************************************************************************************************/
һ. ����ʱ��camera����

1. kernel�е�probe��������ִ�У�����imgsensor driver��AF driver��flashlight driver��

A. imgsensor driver process��
1) imgsensor������Ϊһ�� platform_driver ע�ᣬ��dts�ж�����
compatible = "vendor,camera_hw"����Ϊһ�� platform_device��Ȼ���ִ��imgsensor �� probe ������

2) ���� imgsensor probe ������
2.1) �����Ѿ������ڴ�� platform_device Ϊһ��ȫ�ֱ�����
2.2) ע��һ�� imgsensor cdev���� cdev �� file_operation(open/close/ioctl) ��ϵ�����������豸�ڵ� /dev/kd_camera_hw��
2.3) ��ʼ�� imgsensor clock ��أ�����Ϊ imgsensor_clk_init��
2.4) ��ʼ�� imgsensor hw ��أ���MCLK��regulator��GPIO������Ϊ imgsensor_hw_init��
2.5) ��ʼ�� imgsensor i2c ��أ�����Ϊ imgsensor_i2c_create��
2.6) ��ʼ�� imgsensor proc ��أ�����Ϊ imgsensor_proc_init��

3) ���� imgsensor_clk_init ������
���� clock_name ��ͨ������ devm_clk_get() ����ȡʱ�ӣ�������һ���ṹ���С�

4) ���� imgsensor_hw_init ������
imgsensor ������ hw ��Ϊ3���֣�gpio��regulator��mclk�����Ƿֱ��ṩ�� init()��release()��set() ������
imgsensor_hw_init() ��������ֱ���� gpio_init()��regulator_init()��mclk_init��

4.3) ���� gpio ���֣�
gpio_init(): ���� pinctrl_lookup_state() ����ȡǰ��ͺ���� Reset �� PWDN ����״̬��
gpio_release(): ���� pinctrl_select_state() ����ǰ����� Reset �� PWDN ���š�
gpio_set(): ���� pinctrl_select_state() ����ǰ����� Reset �� PWDN ���š�
ʹ�� pinctrl_select_state() ʱ����Ҫʹ�������� DEFINE_MUTEX(pinctrl_mutex)��

4.4) ���� regulator ���֣�
regulator_init(): ���� regulator_get()��
regulator_release(): ���� regulator_disable()��
regulator_set(): ���� regulator_set_voltage()/regulator_enable() ���� regulator_disable()��
���ǰ���㹲�� regulator ����ʹ�� regulator ֮����� regulator_put() ��ʹ��֮ǰ���� regulator_get()����Ϊregulator�Ὣʹ�ù�����͵�ѹ����Ϊ������ߵ�ѹ������������ߵ�ѹʧ�ܡ�

4.5) ���� mclk ���֣�
mclk_init(): ���� pinctrl_lookup_state() ��ʼ��ǰ����� mclk pinctrl��
mclk_release():���� pinctrl_select_state() ��ֹǰ����� mclk pinctrl��
mclk_set():���� pinctrl_select_state() ����ǰ����� mclk pinctrl��

5) ���� imgsensor_i2c_create ������
���� i2c_add_driver() �����3�� i2c_driver��main��sub��main_two��
���ǵ�3�� probe ��������������Ե� i2c_client ��һ��ȫ�ֱ����С�

6) ���� imgsensor_proc_init ������
���� proc_create() ����һЩ proc�ļ��ӿڡ�

7) �����imgsensor ����(�� imx214mipiraw.c)��
7.1) ʵ���� open/close/ioctl �ľ���ʵ�֣�
7.2) imgsensor ���������úͼĴ��������ã�

8) �ܽ�
8.1) imgsensor �����У�����Ҫ���� imgsensor cdev file_operation �е� unlocked_ioctl() ������hal ��ͨ�� ioctl() �������� kernel �㷢�ͺͽ������ݡ�



B. AF driver process��
1) main lens ������ע����һ��platform_driver��platform_device��Ȼ���ִ������probe������
2) �� platform probe �����У���ֻ�ǵ��� i2c_add_driver() ���һ�� lens i2c driver����dts����һ���ڵ㣺compatible = "vendor,CAMERA_MAIN_AF"��Ȼ������i2c��probe������
3) �� i2c probe �����У�
3.1) ���ȱ��� i2c_client ��ȫ�ֱ����С�
3.2) Ȼ��ע��һ�� AF cdev �������� file_operation ��ϵ���������Ҵ���һ��/dev/MAINAF�ڵ㡣
3.3) Ȼ���ʼ�� AF��regulator����Ҫ�ǵ���regulator_get()����ȡregulator�ڵ㲢���档
3.4) �� AF_Ioctl �У���һ������ AF_SetMotorName()�������������ȷ����ǰimgsensorʹ�õ�lens��AF��name��hal��������imgsensor���ã�ͨ��hal�㴫��kernel��



C. flashlight driver process��
1)
ע��һ�� flashlight_core platform_driver ��ʹ��module_init����dts���нڵ㣺 compatible = "vendor,flashlight_core"��

���� flashlight_core �� probe ������
ע��һ�� flashlight cdev �豸���������ӵ� file_operation �����������豸�ڵ� /dev/flashlight ������һЩ device file���� pt(����)��strobe��charge��capability��

2��
ע���ض������ic�� platform_driver ������ע�� lm3643 ������dts���нڵ㣺compatible = "vendor,flashlights_lm3643"��

���� lm3643 �� probe ������
��ʼ�� lm3653 pinctrl��
���� i2c_add_driver ���һ�� lm3643 i2c_driver��

���� lm3643 i2c probe ������
����dts�е�lm3643���ã���ȡ�������ұ��棻
��ʼ��2����ʱ������ʱ��ֹlm3643��2��channel���ر�����ƣ�����û�п�����ʱ�����ڴ���ʱ��ŻῪ����ʱ����
���� flashlight_dev_register_by_device_id()������ lm3643 �� file_operation �ṹ������� flashlight_dev ��ӵ� flashlight_list ������ lm3643 file_operation ����ɶ����ļĴ�����д������

3��
hal ��ͨ��ioctl������ flashlight_core �� file_operation��
���� flashlight_open ����������� flashlight_list �ϵ����� flashlight ���������ǵ�open������
���� flashlight_release ����������� flashlight_list �ϵ����� flashlight���������ǵ�release������
���� flashlight_ioctl ���������� flashlight_list ���������� type �� ct �� ioctl��Ȼ�����ioctl��

4)
flashlight������Ϊ2���֣��ܹ���ص������;����flashlight������ͨ���Ѿ����flashlight�����Ĳ����Ͳ������浽һ������flashlight_list�ϣ��ϲ�ֻ����üܹ���ص�������




2. �������� camerahalserver������ camerahalserver ����
(0)�� vendor/xxx/proprietary/hardware/xxxcam/main/hal/service/camerahalserver.rc 
���� camerahalserver ����
service camerahalserver /vendor/bin/hw/camerahalserver

(1)main ������
vendor/xxx/proprietary/hardware/xxxcam/main/hal/service/service.cpp

(2)����CameraProvider���캯����
hardware/interfaces/camera/provider/2.4/default/CameraProvider.cpp
���ε��ã�
CameraProvider::CameraProvider();
CameraProvider::initialize();
hw_get_module();
load();
android_load_sphal_library(); //��system/core/libvndksupport/linker.c�ж��塣
���ؿ⣺
/vendor/lib/hw/android.hardware.camera.provider@2.4-impl-xxx.so



3. �������� cameraserver������ cameraserver ����
(1)��system/core/rootdir/init.zygote64.rc��������
onrestart restart cameraserver

(2)cameraservice���캯����
framework/av/services/camera/libcameraservice/CameraService.cpp:
CameraService::CameraService();
CameraService::onFirstRef();
CameraService::enumerateProviders();

framework/av/services/camera/libcameraservice/common/CameraProviderManager.cpp:
CameraProviderManager::initialize();

hardware/xxxcam/main/hal/devicemgr/:
CameraDeviceManagerBase::CameraDeviceManagerBase();
CameraProviderImpl::initialize();
CameraDeviceManagerBase::initialize();
CameraDeviceManagerBase::enumerateDevicesLocked();
CameraDeviceManagerImpl::onEnumerateDevicesLocked();
HalSensorList::searchSensors();
HalSensorList::enumerateSensor_Locked();
SeninfDrv::createInstance();
SeninfDrvImp::SeninfDrvImp();



4��hal��searchSensor���Ĺ�����
1) ������������(id=0)�������õ�ÿ��imgsensor��һ check_imgsensor_id()��
2) Ȼ������ǰ��(id=1)�������õ�ÿ��imgsensor��һ check_imgsensor_id()��
3) �ڲ���imgsensor֮ǰ���ȿ���imgsensor��ISPģ�顢MCLK��clockģ�顢ldo��ѹ���ر�imgsensor֮��ҲҪ�ر���Щ��
4) ͨ��ioctl����ȡimgsensor��ID��get_imgsensor_id()��ͨ��iic����ID������ܹ�����ID����imgsensor��ID��name���棬����hal�㡣
5) ���imgsensor��otp���ݣ������ڶ���ID֮��imgsensor�е�otp���ݶ��������棬�Ժ���Ҫ��open cameraʱ��ȥ��otp���ݣ�Ӱ�����ܡ�
6) ͨ��ioctl��ȡ�Ѿ���������imgsensor����Ϣ��Ԥ��/����/¼��ķֱ��ʡ�
7) ����hal3�������ȡ�ͽ���metadata���õĲ�����hal1����Ҫ����metadata���ݡ�metadata����APP��HAL�Ĳ������ݣ���ֱ���/FPS��
8) �����Ѿ�����ID��imgsensor��ͨ��ioctl��kernel����open���open imgsensor��
ִ��ƽ̨��otp����У׼����ƽ̨��lscУ׼��
ִ��tsf������Ч������color shading��
lens������Ч��FlashAWB����Ʋ�����Ч��
����AF�̣߳���Ҫ��ȡ������()�����ݣ������Զ��Խ���
����һЩ stopPreview/cancelPicture/close �������camera��



5. ��صĽ���
swapper(PID=1): probe ��������������н��С�
camerahalserver(PID=548):  power on imgsensor, search imgsensor.
initCamdevice(PID=781)��   power on imgsensor, open  imgsensor.


/***********************************************************************************************
*
************************************************************************************************/
��. ������ͷ����

1. open camera������̣߳�

1) camerahalserver
��/�ر�ISPģ�飻
����PMU mt6370��ģʽ��
����AF�µ磬�ر�AF��regulator��
����imgsensor�µ磬�ر�imgsensor��ص�regulator��ʱ�ӣ�ISP��
���������Ҫ�Ǵ򿪺͹ر�BB�˵�ISPģ�飬��������ر�imgsensor��AF��

2) initCamdevice
��imgsensor������ص�ʱ�ӣ�regulator����imgsensor�ϵ磬Ӧ��otp��
������̸����imgsensor��

3) 3ATHREAD
����flashlight ioctl�����ƴ�����
����imgsensor ioctl����Ҫ��cameraЧ����صĿ��ƣ���gain��flicker��shutter

4) AFthread
�����AF����������AF�ϵ磻
����AF������ioctl����move AF��

5) Camera@Display
��ʾ�̣߳�������ʾ���ݵĴ��䣻

6) FDClient@Previe
��������̣߳����������������ݣ�

7) CamClient@Previ
Ԥ���̣߳�Ԥ�����ݵĴ��䣬Ԥ���ص�������

8) AESenThd
�Զ��ع��̣߳�����camera AE��

9) pass1
pass1�̣߳�����pass1���ݴ��䣻

10) pass2
pass2�̣߳�����pass2���ݴ��䣻

11) EventThread
�û��ռ���¼������̡߳�

12) xxx-tpd
�ں��̣߳����ƻ�ȡTP���ݺ��ϱ����㣻

13) surfaceflinger
��ʾ�̡߳�

14) ISP��صļ�������
����BB�˵�ISPģ�飻

15) kworker
�ں˵Ĺ������̣߳�����ִ�й������С�
�������п���ͨ�� INIT_DELAYED_WORK() ���� INIT_WORK()+queue_work() ��ʵ�֡�
TP��ESD check���̼��������ϱ�TP���㶼��ͨ������������ʵ�֡�

�������к��ں��̵߳�����
������������ִ��һЩ��С�����񣬹��������ɹ������߳�ͳһ����

16) ksoftirqd
�ں����ն��̡߳�

17) Binder/HwBinder
binder�̣߳����Ʋ�ͬ�߳�֮������ݴ��䣻

```





