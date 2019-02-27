


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

3. PWDN���ţ�����BB����sensor�� power down���ţ�����sensor��sleep����������sensor���빤��ģʽ���Ǵ���ģʽ��һ�����š�

4. ldo�����Դ����BB��ֱ���ṩ��
VCAM_AF����Ȧ��﹩���Դ��һ��1.8V/2.8V
VCAM_IO������IO��Դ����I2C�ӿڡ�MIPI�ӿڹ��硣һ��1.8/2.8
VCAM_A�� ģ���Դ�����й�����ADC���硣һ��1.8/2.8
VCAM_D�� �����ں˵�Դ����BB�˵�ISP���硣һ��1.2/1.5/1.8/2.8

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
ʹ�� pinctrl_select_state() ʱ����Ҫʹ�û����� DEFINE_MUTEX(pinctrl_mutex)��

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





/***********************************************************************************************
*
************************************************************************************************/
2. �������� camerahalserver������ camerahalserver ����

(0) �� vendor/xxx/proprietary/hardware/xxxcam/main/hal/service/camerahalserver.rc 
���� camerahalserver ���̣�
service camerahalserver /vendor/bin/hw/camerahalserver

(1) ���� camerahalserver ���̵� main ������
vendor/xxx/proprietary/hardware/xxxcam/main/hal/service/service.cpp
mian ������������һ���̳߳ء�


(2) ���� CameraProvider ���캯����
hardware/interfaces/camera/provider/2.4/default/CameraProvider.cpp
���ε��ã�
CameraProvider::CameraProvider();
	CameraProvider::initialize();
		hw_get_module(CAMERA_HARDWARE_MODULE_ID,  (const hw_module_t **)&rawModule);
			load();
				android_load_sphal_library(); //��system/core/libvndksupport/linker.c�ж��塣
				//���ؿ⣺ /vendor/lib/hw/android.hardware.camera.provider@2.4-impl-xxx.so		
		mModule = new CameraModule(rawModule);
		err = mModule->init();
		mNumberOfLegacyCameras = mModule->getNumberOfCameras();


camera_module_t HAL_MODULE_INFO_SYM __attribute__ ((visibility("default"))) = {
	.common = {
		.tag                			= HARDWARE_MODULE_TAG,
		.module_api_version 	= CAMERA_MODULE_API_VERSION_2_2,
		.hal_api_version    		= HARDWARE_HAL_API_VERSION,
		.id                 			= CAMERA_HARDWARE_MODULE_ID,
		.name               		= "Default Camera HAL",
		.author             		= "The Android Open Source Project",
		.methods            		= &gCameraModuleMethods,
		.dso                		= NULL,
		.reserved           		= {0},
	},
	.get_number_of_cameras 	= get_number_of_cameras,
	.get_camera_info       		= get_camera_info,
	.set_callbacks         		= set_callbacks,
	.get_vendor_tag_ops    		= get_vendor_tag_ops,
	.open_legacy           		= NULL,
	.set_torch_mode        		= NULL,
	.init                  			= NULL,
	.reserved              			= {0},
};




/***********************************************************************************************
*
************************************************************************************************/
3.  �������� cameraserver������ cameraserver ����
(1) �� frameworks/av/camera/cameraserver/cameraserver.rc ��������
service cameraserver /system/bin/cameraserver

(2) ���� cameraserver ���̵� main ������
	sp<IServiceManager> sm = defaultServiceManager();
	CameraService::instantiate();//instantiate()�� CameraService �ĸ��� BinderService ��ʵ�֣����Ĺ����� new CameraService();


(3) ���� CameraService ���캯���� onFirstRef() ������framework/av/services/camera/libcameraservice/CameraService.cpp����

CameraService::CameraService();
CameraService::onFirstRef();
	CameraService::enumerateProviders();
		CameraProviderManager::initialize();��framework\av\services\camera\libcameraservice\common��


		//��� CameraDeviceManagerBase �� initialize �����Ǵ����ﱻ���õģ�������û���ҵ�......
		CameraDeviceManagerBase::CameraDeviceManagerBase();��vendor\mediatek\proprietary\hardware\mtkcam\legacy\main\hal\devicemgr��
			CameraProviderImpl::initialize();
		CameraDeviceManagerBase::initialize();
			CameraDeviceManagerBase::enumerateDevicesLocked();
			����>CameraDeviceManagerImpl::onEnumerateDevicesLocked()
			��������>sensorNum = HalSensorList::searchSensors();
			����������������>HalSensorList::enumerateSensor_Locked();
							����>SeninfDrvImp::init();
									mfd = open( "/dev/camera-isp", O_RDWR);
									m_fdSensor = open("/dev/kd_camera_hw", O_RDWR);
			    						mpIspHwRegAddr = (unsigned int *) mmap(0, ISP_HW_RANGE/*0x52000*/, (PROT_READ | PROT_WRITE), MAP_SHARED, mfd, cam_isp_addr/*0x15000000*/);
									......
							����>SeninfDrvImp::setAllMclkOnOff(ISP_DRIVING_8MA, TRUE);
							����>ImgSensorDrv::init();
									m_fdSensor = ::open("/dev/kd_camera_hw", O_RDWR);
							����>for(idx=0; idx<=1; idx++){
									ImgSensorDrv::searchSensor(idx);
										 featureControl(idx, SENSOR_FEATURE_SET_DRIVER, (MUINT8 *)&x, &featureParaLen);
										//�����kernel�ĺ�����imgsensor_set_driver() �� imgsensor_check_is_alive(). Ψһ�������ǣ���ȡ ǰ��ͺ��� �� sensorList.cpp �е���ţ������� x �С�
									querySensorDrvInfo(i);//query sensorinfo
									buildSensorMetadata(i);//fill in metadata
									pSensorInfo = pSensorDrv->getSensorInfo(i);
								}
							����>SeninfDrvImp::setAllMclkOnOff(0, FALSE);
							����>SeninfDrvImp::uninit();
									setSeninf1CSI2(0, 0, 0, 0, 0, 0, 0, 0, 0,0);   // disable CSI2
									munmap(mpIspHwRegAddr, ISP_HW_RANGE)
									close(mfd);
									close(m_fdSensor);
							����>ImgSensorDrv::uninit();
									::close(m_fdSensor);
			��������>for(i=0; i<sensorNum; i++){
						......
						sp<PhysEnumDevice> pPhysDevice = new PhysEnumDevice;
	  					pPhysDevice->mSensorName = pHalSensorList->queryDriverName(instanceId);
						......
					}	
			



/***********************************************************************************************
*
************************************************************************************************/
4��hal��searchSensor���Ĺ�����
1) ������������(id=0)���� kernel.config ���õ�ÿ��imgsensor��һ imgsensor_set_driver() �� imgsensor_check_is_alive().
2) Ȼ������ǰ��(id=1)���� kernel.config ���õ�ÿ��imgsensor��һ imgsensor_set_driver() �� imgsensor_check_is_alive().
	��Ϊֱ��ʹ�õ� kernel.config �е� sensor_list ���ã����� HAL �� kernel �е� sensor_list �е� imgsensor �б�Ҫһ�¡�
3) �ڲ���imgsensor֮ǰ���ȿ���imgsensor��ISPģ�顢MCLK��clockģ�顢ldo��ѹ���ر�imgsensor֮��ҲҪ�ر���Щ��
4) ͨ��ioctl����ȡimgsensor��ID��get_imgsensor_id()��ͨ��iic����ID������ܹ�����ID����imgsensor��ID��name���棬����hal�㡣
5) ���imgsensor��otp���ݣ������ڶ���ID֮��imgsensor�е�otp���ݶ��������棬�Ժ���Ҫ��open cameraʱ��ȥ��otp���ݣ�Ӱ�����ܡ�
6) ͨ��ioctl��ȡ�Ѿ���������imgsensor����Ϣ��Ԥ��/����/¼��ķֱ��ʡ�
7) ����hal3�������ȡ�ͽ���metadata���õĲ�����hal1����Ҫ����metadata���ݡ�metadata����APP��HAL�Ĳ������ݣ���ֱ���/FPS��
8) �����Ѿ�����ID��imgsensor��ͨ��ioctl��kernel����open���open imgsensor��
ִ��ƽ̨��otp����У׼����ƽ̨��lscУ׼��
ִ��tsf������Ч������color shading��
lens������Ч��FlashAWB����Ʋ�����Ч��
����AF�̣߳���Ҫ��ȡ������(�����ֻ�ƫת����б������)�����ݣ������Զ��Խ���
����һЩ stopPreview/cancelPicture/close �������camera��




/***********************************************************************************************
*
************************************************************************************************/
5. ��עһ�� kernel ��2����Ҫ�ĺ��� imgsensor_set_driver() �� imgsensor_check_is_alive()
���� kernel.config �е� CONFIG_IMGSENSOR �꣺���� kernel.config ���õ� sensor �� kdSensorList �е�λ�ã��������ǵ���ŵ�һ�������С�
�����к궨���е� sensor ��ѭ��������
	�������� init ��������ȡ����sensor�Ĳ���������open/get_info/feature_control/close��
	���� imgsensor_check_is_alive();
		imgsensor_hw_power(POWER_ON);//���� sensor ʱ����� gpio/mclk/regulator
		imgsensor_sensor_feature_control( SENSOR_FEATURE_CHECK_SENSOR_ID );
			get_imgsensor_id(...);
		imgsensor_hw_power(POWER_OFF);




/***********************************************************************************************
*
************************************************************************************************/
6. HAL sensor driver ������Ҫ����͹���

(1) class SeninfDrvImp
seninf ģ�飺
	TGǰ����һ��Seninf Module, Seninf Module����Ҫ�����Ǵ��� Parallel/Mipi/Serial �� interface ���͵��źš�
	TG moduleȫ��ΪTiming Generator������Ҫ���������ã�һ�ǲ���sensor ��������Ҫ�� Master Clock�����ǽ��� sensor �³����źš�

sensor data flow :
sensor ����> seninf module ����> TG ����> ISP ����> Raw/YUV.


���������ã�
IO��ַ��map��IspAddr, seninfAddr, MIPIRXAddr, gpioAddr
дһЩ�Ĵ�����ֵ��seninfReg, ispReg, MIPICSI2Reg
��/����/�ر� mclk��Ƶ�ʺ���������(24MHz/26MHz):  Ҳ��ͨ��д�Ĵ���ʵ�֡�
 
��������Ҫ�����ǣ����ã����ã������Ĵ��������� seninf module, TG module, ISP module, MCLK module��



(2) class HWSyncDrvImp
���������ã�
����ͬ������ʱ���ͬ�����жϵ�ͬ���������̸߳���ģ���ͬ������



(3) class ImgSensorDrv

���������ã�

searchSensor : featureControl(sensorIdx, SENSOR_FEATURE_SET_DRIVER, (MUINT8 *)&idx, &featureParaLen);

setScenario�����ø���ģʽ�µĲ����ʹ������������ FPS �� ���� HDR ģʽ�ȡ�
sendCommand��featureControl(sensorIdx, FeatureId,  (MUINT8*)pFeaturePara,(MUINT32*)&FeatureParaLen);  �� kernel �е� feature_control() ��Ӧ��
open��featureControl(sensorIdx, SENSOR_FEATURE_OPEN, (MUINT8 *)&featurePara, &featureParaLen);  �򿪾���� imgsensor��
close:   featureControl(sensorIdx, SENSOR_FEATURE_CLOSE, (MUINT8 *)&featurePara, &featureParaLen);  �رվ���� imgsensor��
getInfo: ioctl(m_fdSensor, KDIMGSENSORIOC_X_GET_CONFIG_INFO , &getInfo);  ��ȡ���� sensor ����Ϣ��
getInfo2�� ioctl(m_fdSensor, KDIMGSENSORIOC_X_GETINFO2 , &getInfo);
featureControl:   ioctl(m_fdSensor, KDIMGSENSORIOC_X_FEATURECONCTROL , &featureCtrl);
getCurrentSensorType�� ��ȡsensor�ĸ�ʽ��
	sensor ����Щ��ʽ��  	RAW ��RAW_B, RAW_Gb, RAW_Gr, RAW_R��,  һ�㶼�����ָ�ʽ��
						RAW8 (RAW8_B, RAW8_Gb, RAW8_Gr, RAW8_R),  
						YUV��UYVY, VYUY,	YUYV, YVYU�� �����ﶼ�� YUV422 ��ʽ��, ÿ����Y����һ��UV������
						YCBCR��CbYCrY,	CrYCbY,	YCbYCr,	YCrYCb��
						RAW12,  	RAW14,  RGB888,  RGB565,  JPEG
	YUV��ʽ��Դ��RGB������ɫ�ʺ����ȷ����ˣ�Y��ʾ���ȣ�UV��ʾɫ�ʶȡ�
	YCBCR��ʽ��Դ��YUV������Ҫ����������Ƶ��


��������Ҫ���ã�
����ö������ sensor�����·�һ�� SENSOR_FEATURE_SET_DRIVER ���
���ض��� sensor ���� ioctl ���� imx214 �� open/close/get_info/feature_control��




(4) class HalSensorList
���� query() �������� query sensor ID/name/type��info, number��metadata�ȡ�
buildStaticInfo()���������� metadata�������� "LENS",  "SENSOR",  "TUNING_3A",  "FLASHLIGHT",  "SCALER",  "FEATURE",  "CAMERA",  "REQUEST", ��Щ��Ϣ������ HAL �� custom Ŀ¼�������ú��˵ġ�
enumerateSensor_Locked()������ʱö�� sensor ����ȡ��ǰ�� sensor �� sensorList.cpp �����е���ţ�Ȼ�󱣴������ˡ���ö���� sensor ֮��ͻ���� buildStaticInfo() �� ���� metadata��
querySensorInfo�� ��ȡ sensor info, ͨ�� ImgSensorDrv->sendCommand() ��ʵ�ֵġ�





(5) class HalSensor
powerOn �� powerOff ����������MCLK������MCLK�������������� mpSensorDrv->open(sensorIdx) �� sensor ��
configure:  ���ò�ͬģʽ�µ�sensor������
sendCommand�� �൱�� HAL �� ioctl ��������ݴ���� cmd ���� ImgSensorDrv->sendCommand() �� SeninfDrvImp->sendCommand() ����������/��ȡ֡�ʵȡ�
setSensorMclkDrivingCurrent������ ImgSensorDrv->sendCommand() �� SeninfDrvImp->setMclkIODrivingCurrent() ��ʵ�֡�
seninfControl:  ���� SeninfDrvImp->configSensorInput()��

��������Ҫ�����ǣ�����Ҫ ImgSensorDrv �� SeninfDrvImp �Ĳ����ϲ�����һ����ơ�






/***********************************************************************************************
*
************************************************************************************************/
7. ��صĽ���
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
����PMU xx6370��ģʽ��
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



/***********************************************************************************************
*
************************************************************************************************/
2.  camera preview flow
(0) 
DisplayClient ������ʾͼ�����ݣ� �����ͼ���������� Surface ��ʾ��
CameraAdapter �����ṩͼ�����ݡ��������˶�� CamNode ����ͬ�� CamNode ������ͬ�� buffer ����

(1) ������ ��ʹ�ò�ͬ�� Node ��������ͬ�� buffer ����
Pass1Node�� ����� Sensor Driver��ISP Driver �򽻵�������Ԥ��ģʽ���ص㹤������������ɡ�
Pass2Node
DefaultCtlNode
CamGraph : ��Ϊ���� Node ͨѶ��������CamGraph ����������ϵͳ�� ���е� Node ����Ҫ���ӵ� CamGraph
����Node֮���ͨѶ����Ҫ�õ� connectData �� connectNotify ������ connectData Ϊ���� node ֮�� buffer ��������ӣ��� connectNotify Ϊ���� node ֮����Ϣ��������ӡ����磺

connectData( PASS1_RESIZEDRAW, CONTROL_RESIZEDRAW, mpPass1Node, mpDefaultCtrlNode);
Pass1Node �� DefaultCtrlNode ��������һ���¼��� PASS1_RESIZEDRAW��Ҳ����˵�� Pass1Node ���� handlePostBuffer(PASS1_RESIZEDRAW, buffer) ��ʱ��DefaultCtrlNode ����� onPostBuffer ����������ܵ� Pass1Node �� buffer��

connectNotify( PASS1_START_ISP, mpPass1Node, mpDefaultCtrlNode)���¼��� PASS1_START_ISP���� Pass1Node ���� handleNotify(PASS1_START_ISP) ��ʱ��DefaultCtrlNode ����� onNotify ����������յ� PASS1_START_ISP ��Ϣ��

connectData �� connectNotify �Ĳ�֮ͬ�����ڣ�һ�����Դ�������buffer����ֻ��һ��һ���ӣ�һ��ֻ�ܴ�����Ϣ��������һ�Զ����ӡ�


(2) data flow
pass1 ����> defaultNode ����> pass2 ����> Display


(3) DisplayClient
���ᴴ��һ�� DisplayThread��һ�� ImgBufQueue��
ImgBufQueue �������� Buf ���У�mTodoImgBufQue �� mDoneImgBufQue ��
prepareOneTodoBuffer ��������������Ǵ� dequePrvOps ���� deque �� StreamImgBuf������������ ImgBufQueNode��
�� ImgBufQueNode �ı�־λ�� eSTATUS_TODO ����� ImgBufQueue �� enqueProcessor ���������е� ImgBufQueNode �����뵽 mTodoImgBufQue ���������ݵ�׼����

DisplayClient ׼���� buffer �ŵ� mTodoImgBufQue ���档 
Pass1Node �ӵײ� deque һ֡���ݣ�Ȼ������ post �� DefaultCtrlNode��DefaultCtrlNode �ֽ����� post �� Pass2Node�� 
Pass2Node ����� buffer ֮��ᴥ�� threadLoopUpdate��threadLoopUpdate ͨ�� DefaultBufHandler �� mTodoImgBufQue ȡ��buffer���ٽ� buffer ���� IHalPostProcPipe ����
�� IHalPostProcPipe ������֮���ص� Pass2CbFunc ������Pass2CbFunc ͨ�� DefaultBufHandler �� buffer �Ż� mDoneImgBufQue ���档 
��� DisplayClient ���ϴ� mDoneImgBufQue ����ȡ���Ѿ�����õ� buffer �͵� Surface ����




/***********************************************************************************************
*
************************************************************************************************/
��. �ܽ�

1. �� mt6761 ƽ̨��, ����ǰ��ͺ���, ֻ������1���ַ��豸���: /dev/kd_camera_hw , ֻ��1�� file_operation �ṹ(open/release/unlocked_ioctl)����ô�������HAL��򿪵���ǰ�㻹�Ǻ��㣿

(1) ����HAL�����imgsensor������, �� imgsensor_drv.cpp ��: 
	fd = open("/dev/kd_camera_hw", O_RDWR);
	featureCtrl.InvokeCamera = sensorIdx;
	......
	ioctl(fd, SENSOR_FEATURE_SET_DRIVER , &featureCtrl);
	......
�ڿ��� searchSensor ʱ, sensorIdx �ֱ𱻸�ֵΪ 0(main), 1(sub), 2(main2)......��HAL��� InvokeCamera ����������� kernel�㣬��������ǰ���㡣

(2) �� kernel ��� imgsensor.c ��:
	psensor->inst.sensor_idx = pFeatureCtrl->InvokeCamera;
	drv_idx = imgsensor_set_driver(psensor);
ʹ�� sensorIdx ����������ǰ����� i2c driver/gpio/mclk/regulator������ǰ��������µ硣
���� cdev �� file_operation�ṹ����ֻ��һ����ͨ�� sensorIdx �����֡�

2. imgsensor �� gpio ����
(1) ���� pinctrl �� regulator ����:
pinctrl������PWDN, Reset, MCLK.
regulator������VCAMA, VCAMD, VCAMIO, VCAMAF.

3. imgsensor i2c
(1) imgsensor ǰ���� i2c_driver �� probe() ����ֻ����һ���£����� i2c_client Ϊһ��ȫ�ֱ�����


4. camera֡��
(1) �ع⣺��sensor�й⣬�������۵ĵ��ź�ת��Ϊ�����źš�sensor�ع���һ��һ�еĽ��еģ����� dummyLine����Ч�У��������ع�ʱ�䡣
(2) ���ţ�����sensor���ع�ʱ�䡣�����е� shutter ��ʾ�ع�������
(3) FrameLength��һ֡��֡�����������Ϊһ֡��������FrameLength= shutter + dummyLine ��
(4) ֡�ʼ��㷽ʽ��FrameLength = pclk / framerate * 10 / lineLength �� framerate = (10*pclk) / (linelength * FrameLength) ��
(5) linelength���ڲ�ͬģʽ��(Ԥ��/����/¼��)��sensorһ�е��ع�ʱ�䣬�ǹ̶�ֵ��pclk Ҳ�ǹ̶�ֵ��FrameLength �ǿɱ�ġ�
(6) ����֡�ʣ���Ԥ��ģʽ�£�pclk = 320000000��linelength = 5008��framelength = 2110����� framerate =302��30֡��
(7) kernel ��ֻ���������֡��Ϊ 30 ֡�����ṩ������֡�ʵĺ�����ʵ�����Ǹ���֡�ʼ����֡����Ȼ��֡��д��Ĵ�������
������Ҫ���ö���֡����app���õġ��� HAL �� fbtl �п������ü����̶���֡�ʣ�5/15/20/24/30.


5. camera flicker
ԭ�� sensor���չ����Ϊ��Դ�»�ȡͼ������ʱ����� flicker��ԭ�������ڲ�ͬsensor�����ϵĹ�������ͬ��ɵġ�
��Դ��Ƶ����50Hz��60Hz�����Ҳ�����Ӧ��������һ��100Hz��120Hz�Ĳ��Ρ�
�ع���һ��һ�еĽ��У�ÿ�����ص��ع�ʱ�䶼��һ���ġ�ͬһ�е����е���ܵ���������һ���ģ���ͬ�н��յ��������ǲ�һ���ġ�
������˸�����ҵ�һ�������ò�ͬ�н��յ���������һ���ģ��������ع�ʱ������ǹ��������ڵ�������ʱ�䡣
����ڴ�����ʹ���� autoflicker ����ô������֡�ʵ�ʱ�򣬻����֡�ʵ�ֵ������һ�����ϱ��� flicker ��֡�ʣ����磺
	if ((framerate == 300) && (imgsensor.autoflicker_en == KAL_TRUE))
		imgsensor.current_fps = 296;
	else if ((framerate == 150) && (imgsensor.autoflicker_en == KAL_TRUE))
		imgsensor.current_fps = 146;
	......
�� HAL �� ftbl�п������� flicker ģʽΪ��OFF/50Hz/60Hz/auto��


```





