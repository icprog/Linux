

```c

Android O platfrom ��֧���룺
repo_google init -u http://1.2.3.4:8080/xxxx/platform/manifest.git -m xxxx-O1-platform-dev.xml
repo_google sync -j4
repo_google start xxxx-O1-platform-dev --all


(2)��װopenjdk-8:
sudo add-apt-repository ppa:openjdk/ppa
sudo add-apt-repository ppa:openjdk-r/ppa
sudo apt-get update
sudo apt-get install openjdk-8-jdk

sudo chmod -R 755 /usr/lib/jvm/java-8-openjdk-amd64

sudo gedit ~/.bashrc
�ļ�ĩβ�������������Ϣ��
#for openJDK:
export JAVA_HOME=/usr/lib/jvm/java-8-openjdk-amd64
export JRE_HOME=/usr/lib/jvm/java-8-openjdk-amd64/jre
export PATH=$JAVA_HOME/bin:$JAVA_HOME/jre/bin:$PATH
export CLASSPATH=$CLASSPATH:.:$JAVA_HOME/lib:$JAVA_HOME/jre/lib

. ~/.bashrc

sudo update-alternatives --config java
sudo update-alternatives --config javac
ѡ����Ҫʹ�õ�JDK�汾��

ȷ��һ��·����
printenv JAVA_HOME
java -version



(3)����
source ./build/envsetup.sh 
lunch full_xxxx_bsp-eng 
make -j8 2>&1 |tee build.log

3��DDR ·���� preloader/tools/emigen/MT6739/MemoryDeviceList_MT6739.xls

12������cameraģ�飺

#mmm vendor/mediatek/proprietary/custom/mt6739/hal
#mmm vendor/mediatek/proprietary/hardware/mtkcam/legacy/v1/common/paramsmgr
#mmm vendor/mediatek/proprietary/hardware/mtkcam/legacy/platform/mt6739/v1/common/paramsmgr
#rm libcam.paramsmgr.so

mmma vendor/mediatek/proprietary/hardware/mtkcam/legacy/platform/mt6739/v1/common/paramsmgr
cd out/target/product/k39tv1_bsp/vendor/lib/

mmm vendor/mediatek/proprietary/packages/apps/Camera
adb push libcam.paramsmgr.so /vendor/lib


mmma vendor/mediatek/proprietary/platform/mt65XX/hardware/mtkcam/v1/common/paramsmgr


feature table��̬��ᱻ���뵽libcam.paramsmgr.so�С�

touch vendor/mediatek/proprietary/hardware/mtkcam/legacy/v1/common/paramsmgr/feature/custom/custom.cpp && \
mmm vendor/mediatek/proprietary/hardware/mtkcam/legacy/v1/common/paramsmgr/ 2>&1 | tee ft.lib.log && \
mmm vendor/mediatek/proprietary/hardware/mtkcam/legacy/platform/mt6739/v1/common/paramsmgr 2>&1 | tee ft.so.log

adb shell stop media && adb shell start media

touch vendor/mediatek/proprietary/hardware/mtkcam/legacy/v1/common/paramsmgr/feature/custom/custom.cpp 
mmma vendor/mediatek/proprietary/hardware/mtkcam/legacy/v1/common/paramsmgr/
mmma vendor/mediatek/proprietary/hardware/mtkcam/legacy/platform/mt6739/v1/common/paramsmgr 

mmma vendor/mediatek/proprietary/hardware/mtkcam/legacy/platform/mt6735m/v1/common/paramsmgr

cd out/target/product/gernal/system/vendor/lib/
ls libcam.paramsmgr.so
adb push libcam.paramsmgr.so /system/vendor/lib

�޸� HAL�� sensor.list ���뷽����
mmma vendor/mediatek/proprietary/hardware/mtkcam/legacy/platform/mt6735m/hal/sensor
adb push libcam.halsensor.so /system/vendor/lib


13��
regulator_get ��ȡ���� supply ֮ǰ�����֣������� regulator-name = "vcamio";
vcamio_sub-supply = <0x85>;
vcamaf-supply = <0x86>;

15���ϲ�������win7�½��У���Ҫ��Ubuntu�н��У���ΪUbuntu��ϲ�����win7�����滻��

17������Linux����
1��at ����
�����ڶ�ʱִ��ĳһ�ű�

/etc/init.d/atd start
ps -ef | grep atd

���磺
at 14:30 -f ./time
atq
atrm 3

2��sudo script kmsg1.log
exit

3��grep -E "aaa|bbb"


16��adb�����ȫ��

�ֻ��Ĵ洢�ռ��� adb shell �е�·��Ϊ��/sdcard/

49. ��Ļ��ͼ
adb shell /system/bin/screencap -p /sdcard/screenshot.png 
adb pull /sdcard/screenshot.png ./screenshot.png

50. ���ֻ��л�ȡ mtklog
adb pull /storage/emulated/0/mtklog ./mklog3/

51.��װ/ж��Ӧ�ó���-r��ʾ�滻ԭ���� apk
adb install -r Ӧ�ó���.apk
adb uninstall xxx.apk

52.�����ļ����ֻ���
adb push test.c /sdcard/test

23
6739ƽ̨ ʹ��adb shellû��Ȩ��ʱ��
error: insufficient permissions for device

sudo ~/bin/adb kill-server
sudo ~/bin/adb devices

59�� adb ����������
adb shell input keyevent 26


60�� adb ��������
1000���� = 1��
adb shell  echo 1000 > /sys/devices/virtual/timed_output/vibrator/enable"

24���� camera ���
adb shell input keyevent 23
���ĳ������ adb shell input tap x  y 
��		adb shell input swipe 664 930 45 930
�һ�		adb shell input swipe 45 930 664 930

53.��ӡ log��������ļ����鿴�ϲ�log��Ϣ:
 adb logcat |grep "AAL"
 adb logcat > ./log.txt
 adb logcat > ./camera.txt

adb ¼����Ļ��
adb shell 
screenrecord /sdcard/demo.mp4			//180s

adb shell screenrecord  --time-limit 10 /sdcard/demo.mp4	//10s

adb shell screenrecord --size 1280*720 /sdcard/demo.mp4

adb pull /sdcard/demo.mp4

55.adb ���빤��ģʽ
adb shell am start -n com.mediatek.engineermode/.EngineerMode

Android 8.1Ĭ�Ͽ���dm-verify  ��  userdebug�汾adb remount��������Ҫ�滻����Ĭ��adbΪAndroid8.1������� out/host/linux-x86/bin/adb�ļ���
adb root��ִ��adb disable-verity������������Ȼ�����adb remount �޸�system��vendor�����ļ���
1��	adb root
2��	adb remount
3��	adb disable-verity
4��	adb reboot
��������4������֮��userdebug�汾�ſ�������adb push 

56.��ο�������
adb shell
echo 3000 > /sys/devices/virtual/timed_output/vibrator/enable
��3��

59�� ��д dts �ļ�ע�⣺
�����붥��1������2 ��tab ��,��from M_branch_OTP_porting_guide.pdf   page 8��

18�������ں��̵߳�һ��bug
1����FT8006m��TP�����У�����i2c probe������ͨ��mtk tp probe���õģ���mtk tp probe������ͨ��һ����������ʵ�ֵġ�
2��FT8006m�Ĺ̼�������������ͨ��һ����������ʵ�ֵġ�
3�����ߵĹ������ڲ�ͬ�Ĺ������У��ֱ����ں��̵߳���ִ�С�
4������ִ�е��Ⱥ�˳��һ�������Զ��߲���ͨ����������ϵ������ extern ��

19������ Gerrit �� abandon ����ô�����ύ��
		git log .
		git reset --hard commitID
		git pull
		git status

20�� i2c�ļ��ִ��䣺
kernel�У�
i2c_transfer()
i2c_master_send
i2c_smbus_write_byte_data

22��
ȡ�������  	fatal: ssh variant 'simple' does not support setting port
�����  				git config --global ssh.variant ssh

23.���һ����ͬ��camera ����2�֣���׺Ϊ b ��Ϊ���㣬��׺Ϊ s ��Ϊǰ�㡣
ov8856b			����
OV9760    		����
ov8856			����
OV9760s 		ǰ��

24.
git������
sudo apt-get add-apt-repository ppa:git-core/ppa
sudo apt-get update
sudo apt-get install git

9��GPIO���ÿ���������������
adb shell cat /sys/devices/platform/1000b000.pinctrl/mt_gpio

 [MODE] [DIR] [DOUT] [DIN] [PULL_EN] [PULL_SEL] [IES] [SMT] [DRIVE]
  95: 110010101
  96: 110010101
 112: 110010101

23�� Linux V4L2 ����� UVC(usb��Ƶ�淶)�淶�ģ���USB����ͷ��UVC ����·��Ϊ�� kernel-3.10/drivers/media/usb/uvc/
MTK��׼��Camera��û�в���v4l2��ܣ�������Ҫ��jni��ʵ�ֻ�����v4l2��Ƶ�ɼ����̡�

27��YuSu.cmp
vendor/mediatek
proprietary/bootable/bootloader/lk/scripts/dct/config/YuSu.cmp
proprietary/bootable/bootloader/preloader/tools/dct/config/YuSu.cmp
proprietary/scripts/dct/YuSu.cmp
proprietary/scripts/dct/python/config/YuSu.cmp


29.
lcd enter sleep:
0x9001,0x28,
0xa000,5,
0x9001,0x10,
0xa000,120

lcd_exist_sleep:
0x9001,0x11,
0xa000,120,
0x9001,0x29,
0xa000,5

33�� DB�ļ�λ�ã�
/data/vendor/mtklog/aee_exp
/data/aee_exp 
/sdcard/mtklog/aee_exp
/data/anr

Android O�仯��
Android O ,mtklog ��db ����ͬһ��Ŀ¼���ύlog ʱ��Ҫͬʱ��������
adb pull /sdcard/mtklog
adb pull /data/aee_exp
adb pull /data/vendor/mtklog/aee_exp

35���ر�TSF
/vendor/mediatek/proprietary/custom/mt6739/hal/imgsensor/gc5025s_mipi_raw/camera_tuning_para_gc5025smipi_raw.cpp
isTsfEn

adb shell "echo 0 > /sys/module/printk/parameters/disable_uart" 

�����鿴log��
 cat /proc/last_kmsg
adb logcat -v threadtime
 echo 8 > /proc/sys/kernel/printk  		//��ӡ����log
cat proc/bootprof

39�� strings �÷�
�� .so �ļ��в鿴���������ĸ� .cpp  �ļ��� XXXXΪ�����е�ĳ���ַ���
strings -f "*.so" | grep "xxxxxx"
strings cam.so

40���Ӵ�ӡ���ʱ���������ܴ�ӡ������
printk("xxx %s line=%d\n",__FUNCTION__,__LINE__);

45��
������æ�ֱ�dump����sensor����90��270ʱpass2 data:

adb root
adb shell setenforce 0
adb shell setprop camera.dumpbuffer.enable 2


46�� adb ��ȡ mtklog 
adb pull /storage/emulated/0/mtklog ./mklog10/


47��camera���ԣ�
ov8856b			����
OV9760    		����
ov8856			����
OV9760s 		ǰ��

48��imgsensor ��ת���⣺
1���޸� s5k3l8mipiraw_Sensor.c  ��  set_mirror_flip(IMAGE_NORMAL);	
2���޸� .sensor_output_dataformat = SENSOR_OUTPUT_FORMAT_RAW_Gr,

3���޸� vendor Ŀ¼�� cfg_setting_imgsensor.cpp

4��ƽ����Ŀ�޸� vendor Ŀ¼�� imgsensor_metadata

51��at����
at 01:00 -f ~/work/test

52��git pull ʱ������ͷָ������� 0adad89afda ʱ��ʹ������2�����
repo_google sync
repo_google start xxxx-driver-dev --all

56�� alsps
ps_data > ps_threshold_high : close			ps_data_report! 0, 3    �ӽ�
ps_data < ps_threshold_low : far away		ps_data_report! 1, 3   Զ��

9��GPIO���ÿ���������������
adb shell cat /sys/devices/platform/1000b000.pinctrl/mt_gpio

  1 PIN: [MODE] [DIR] [DOUT] [DIN] [PULL_EN] [PULL_SEL] [IES] [SMT] [DRIVE] ( [R1] [R0] )
  95: 110010101
  96: 110010101
 112: 110010101
 6: 000000110
119: 011100100 00

61�������ó�NC��gpioʵ�ʿ������Ǹ�ʲô״̬��
ͨ����Mode 0��GPIO Mode������ģʽ��ʹ���ڲ�������

62��
�ڽ���i2c ����ǰ���ã�i2c_client->timing = timing_number;
���豸��֧�ֿ���		mode timing_number <= 100;
���豸֧�ֿ���			mode timing_number <= 400;
��ͨģʽ:100kHz
����ģʽ��400kHz
����ģʽ��3.4MHz
û���κα�Ҫʹ�ø���SCL����SCL������100k�����£�

63��������Ͳ����� LCM RESET PIN ��Ϊ�� ��ƽ
ƽ̨Ĭ�� RESET PIN �����Ϊ��ƽ�ģ����һ����Ҫ���ͣ���������RESET PIN��ΪGPIOģʽ����ͨ��GPIO��ʽ���͡�
ʹ��mediatek/dctĿ¼�µ�DCT���ߣ�ʹ�����custom/XXX/kernel/dct/dctĿ¼�µ�DWS�ļ�����GPIO131���ó� 0:GPIO131. 
��GPIO PIN�ŵĿ���������һЩ������
lcm_util.set_gpio_mode(GPIO131, GPIO_MODE_00);
lcm_util.set_gpio_dir(GPIO131,GPIO_DIR_OUT);
lcm_util.set_gpio_out(GPIO131,0);


64��DSI�ӿ�������sync ģʽ��video mode��command mode
����video mode��BB��һֱˢ���ݵ�LCM��cmd mode�������� �ݸ���ʱˢ���ݵ�LCM GRAM��)
��DSI command mode��ȣ�video mode ����Ҫʵʱ����image data��lcm�ˣ�DSI ��refresh rate������lcm��refresh rate��


66���������USB�ʹ����߲���ͬʱ���ӡ�

67��
ret =  tee_spi_transfer(&smt_conf, cfg_len, writebuf, readbuf, 7);
��ָ�������У���������������ô������ƣ�
��ǰ6737ƽ̨������ܵ���20�Σ�����6739ƽ̨��֪���ܵ��ö��ٴΣ�


ISP register ��ʾ seninf û���յ�sensor ���������ݣ�
[0x15008134 00000000]

69��camera otpȨ���ļ� CAM_CAL_DRV

device/mediatek/mt6739/init.mt6739.rc
device/mediatek/sepolicy/basic/non_plat/cameraserver.te
device/mediatek/sepolicy/basic/non_plat/device.te
device/mediatek/sepolicy/basic/non_plat/file_contexts
device/mediatek/sepolicy/basic/non_plat/mediaserver.te
device/mediatek/sepolicy/basic/non_plat/mtk_hal_camera.te
device/mediatek/sepolicy/basic/prebuilts/api/26.0/nonplat_sepolicy.cil
device/mediatek/sepolicy/bsp/non_plat/atci_service.te
mediatek/sepolicy/bsp/prebuilts/api/26.0/nonplat_sepolicy.cil
mediatek/sepolicy/full/prebuilts/api/26.0/nonplat_sepolicy.cil

70��gc5025 ��ת180��/��������

#if defined(GC5025_MIRROR_NORMAL)
.sensor_output_dataformat = SENSOR_OUTPUT_FORMAT_RAW_R,//sensor output first pixel color
#elif defined(GC5025_MIRROR_H)	//���·�ת
.sensor_output_dataformat = SENSOR_OUTPUT_FORMAT_RAW_Gr,//sensor output first pixel color
#elif defined(GC5025_MIRROR_V)		 //���ҷ�ת
.sensor_output_dataformat = SENSOR_OUTPUT_FORMAT_RAW_Gb,//sensor output first pixel color
#elif defined(GC5025_MIRROR_HV)		//�������ҷ�ת
.sensor_output_dataformat = SENSOR_OUTPUT_FORMAT_RAW_B,//sensor output first pixel color
#else
.sensor_output_dataformat = SENSOR_OUTPUT_FORMAT_RAW_R,//sensor output first pixel color
#endif


71�� LSC
1)ƽ̨��otp LSC��ͨ��֤��
����eng�汾��
��ʽ�����أ�
adb shell logcat > lsc.log 	ץ��һ�ο���log
2������������
û��ִ��imx214_camera_calibration_cam_cal.cpp����ļ�������ִ����camera_calibration_cam_cal.cpp����ļ�
�������� imx214��devȨ�ޡ�

3)��lsc golden ����ǰ��68������Ҫע�͵���ֻҪ����1800������

4) PixId:    0,      //first pixel:����{0,2��4,8} �ֱ��Ӧ {B,Gb,Gr,R},
����pixel id.ͨ���� module����ȷ����¼��OTP��first pixel


grep -rn madev ./mediatek/

72��W5528����΢ָ�ƣ�
hardware/interfaces/biometrics/fingerprint/2.1/default/BiometricsFingerprint.cpp
hardware/libhardware/hardware.c

     <hal format="hidl">
        <name>android.hardware.biometrics.fingerprint</name>
        <transport>hwbinder</transport>
        <version>2.1</version>
        <impl level="generic"></impl>
        <interface>
            <name>IBiometricsFingerprint</name>
            <instance>default</instance>
        </interface>
     </hal>


adb logcat -v time



�޸��� vendor Ŀ¼��ֻ���� systemimage�������������ַ����в�ͨ��
find . -type f -name "*cam*"
find . -type f -name "*cam*" -delete
source ./build/envsetup.sh
lunch
make -j8 systemimage
ˢ��ʱˢд system.img �� vendor.img��
�޸���HAL�㣬��ȷ��Ӧ���ǣ�
ɾ��productĿ¼��ȫ�����롣


rm out/target/product/top6739_36_n1/system/vendor/lib/libcam.paramsmgr.so
rm out/target/product/top6739_36_n1/obj/SHARED_LIBRARIES/libcam.paramsmgr_intermediates/LINKED/libcam.paramsmgr.so


//for MT8321
rm out/target/product/top8321_fgemmc/system/lib/libcam.paramsmgr.so && rm out/target/product/top8321_fgemmc/system/lib/libcameracustom.so
touch vendor/mediatek/proprietary/hardware/mtkcam/v1/common/paramsmgr/feature/custom/custom.cpp
source ./build/envsetup.sh
lunch
mmma -j4 vendor/mediatek/proprietary/hardware/mtkcam/v1/common/paramsmgr/
//grep libcameracustom.so ./ -nr
//grep libcam.paramsmgr.so ./ -nr
mmma -j4 vendor/mediatek/proprietary/platform/mt6580/hardware/mtkcam/v1/common/paramsmgr 2>&1 |tee camhal.log
//end

//for MT6739
rm out/target/product/k39tv1_bsp/vendor/lib/libcam.paramsmgr.so && rm out/target/product/k39tv1_bsp/vendor/lib/libcameracustom.so
touch vendor/mediatek/proprietary/hardware/mtkcam/legacy/v1/common/paramsmgr/feature/custom/custom.cpp 
source ./build/envsetup.sh
lunch
mmma  vendor/mediatek/proprietary/hardware/mtkcam/legacy/v1/common/paramsmgr/
mmm  vendor/mediatek/proprietary/hardware/mtkcam/legacy/platform/mt6739/v1/common/paramsmgr 
mmm  vendor/mediatek/proprietary/hardware/mtkcam/legacy/platform/mt6761/v1/common/paramsmgr
mmm  vendor/mediatek/proprietary/hardware/mtkcam/legacy/platform/mt6580/v1/common/paramsmgr 2>&1 |tee camhal.log
//end

Android 8.1 push ������
�����ֻ�
cd out/target/product/k39tv1_bsp/vendor/lib/
ls libcam.paramsmgr.so -l && ls -l libcameracustom.so
adb root && adb remount
adb push libcam.paramsmgr.so ./vendor/lib/
adb push libcameracustom.so ./vendor/lib/
//ע��64λϵͳҪpush��lib64
//adb shell sync
//adb shell rm ./vendor/nvdata/media/CAMERA*
//adb shell rm ./system/vendor/nvdata/media/CAMERA*
�����ֻ�
//�ָ���������



Android 7.1 push ������    //Android 7.1 push 2�� ��ȥ������������Ч��
��������������
adb root && adb remount
adb push libcam.paramsmgr.so ./system/vendor/lib/
Ȼ������������


Android 5.1 push������
adb root && adb remount
cd out/target/product/top8321_fgemmc/system/lib
ls libcam.paramsmgr.so -l && ls -l libcameracustom.so
adb push libcam.paramsmgr.so /system/lib/libcam.paramsmgr.so
adb push libcameracustom.so /system/lib/libcameracustom.so
adb push libacdk.so /system/lib/libacdk.so
rm /data/nvram/APCFG/APRDCL/CAM*
adb shell sync
adb reboot

��adb pushһ���ļ��������У��Ƚ�����޸ĵ��ļ�touchһ�£���
touch factory.ini
adb push factory.ini /etc/factory.ini
rm /data/nvram/APCFG/APRDCL/CAM*



һ�������ܣ�

1����ص�Ŀ¼
frameworks/
hardware/
packages/
vendor/mediatek/proprietary/packages/apps/

vendor/
	//./vendor/mediatek/proprietary/hardware/mtkcam/legacy/platform/mt6739/
	./vendor/mediatek/proprietary/hardware/mtkcam/legacy/v1/
	./vendor/mediatek/proprietary/hardware/mtkcam/include/
	./vendor/mediatek/proprietary/hardware/mtkcam/utils/fwk/
	./vendor/mediatek/proprietary/custom/mt6739/hal/imgsensor/

	
���� KEY_PICTURE_SIZE ��

2���ײ���ص��ļ������뵽��framework��HAL���ļ���
frameworks/av/camera/CameraParameters.cpp
frameworks/av/camera/CameraParameters2.cpp
frameworks/av/camera/include/camera/CameraParameters.h
frameworks/base/core/java/android/hardware/Camera.java

hardware/interfaces/camera/common/1.0/default/CameraParameters.cpp
hardware/interfaces/camera/common/1.0/default/include/CameraParameters.h

vendor/mediatek/proprietary/hardware/mtkcam/include/mtkcam/utils/fwk/CameraParameters.h
vendor/mediatek/proprietary/hardware/mtkcam/utils/fwk/CameraParameters.cpp
vendor/mediatek/proprietary/hardware/mtkcam/utils/fwk/MtkCameraParameters.cpp
vendor/mediatek/proprietary/hardware/mtkcam/legacy/v1/common/paramsmgr/params/ParamsManager.update.cpp
vendor/mediatek/proprietary/hardware/mtkcam/legacy/v1/common/paramsmgr/params/ParamsManager.cpp				ParamsManager::getStr
vendor/mediatek/proprietary/hardware/mtkcam/legacy/platform/mt6739/v1/adapter/MtkEng/MtkEngCamParameter.cpp
vendor/mediatek/proprietary/hardware/mtkcam/legacy/platform/mt6739/v1/adapter/MtkDefault/MtkDefaultCamParameter.cpp
vendor/mediatek/proprietary/hardware/mtkcam/legacy/platform/mt6739/v1/adapter/MtkDefault/MtkDefaultCamAdapter.Capture.cpp
vendor/mediatek/proprietary/hardware/mtkcam/legacy/platform/mt6739/v1/adapter/inc/Scenario/Shot/IShot.h
vendor/mediatek/proprietary/hardware/mtkcam/legacy/platform/mt6739/v1/adapter/Scenario/Shot/NormalShot/NormalShot.cpp
vendor/mediatek/proprietary/hardware/mtkcam/legacy/platform/mt6739/v1/adapter/Scenario/Shot/CapBufShot/CapBufShot.cpp
vendor/mediatek/proprietary/custom/mt6739/hal/sendepfeature/imx190s_mipi_raw/config.ftbl.imx190s_mipi_raw.h


//add for front camera mirror flip start
FTABLE_CONFIG_AS_TYPE_OF_DEFAULT_SUPPORTED(
	KEY_AS_(MtkCameraParameters::KEY_MIRROR_FLIP),
	SCENE_AS_DEFAULT_SCENE(
		ITEM_AS_DEFAULT_(MtkCameraParameters::TRUE),
		ITEM_AS_SUPPORTED_(
			MtkCameraParameters::FALSE
		)
	),
)
//add for front camera mirror flip end


KEY_ANTIBANDING
KEY_VIDEO_SNAPSHOT_SUPPORTED
KEY_ZSD_MODE


74�� sepolicy 

�ر�selinux��ΪPermissiveģʽ��
adb shell setenforce 0


audit2allow��·���ڣ�
audit2allow -i avc_log.txt

[FAQ11483] ��ο�����֤ SELinux Policy ����
MTK ����Ŀ¼ alps/device/mediatek/common/sepolicy/  ע�����������basic, bsp, full Ŀ¼. 
����basic Ŀ¼���еİ汾����Ե�; bsp Ŀ¼����bsp �汾 + Turnkey �汾����Ե�;  full Ŀ¼����ֻ��Turnkey �汾��Ե���

/device/mediatek/sepolicy/basic|bsp|full/
non_plat: ������vendor Ŀ¼��sepolicy �趨. ��Google vendor Ŀ¼����.
plat_private: ������system Ŀ¼��sepolicy �趨, ��Google ��private Ŀ¼����.
plat_public: ͬʱ������vendor/system ��sepolicy �趨, ��Google ��public Ŀ¼����.


[FAQ11486] [SELinux Policy] �������SELinux ���Թ��� ? ��Kernel Log �г���"avc: denied" Ҫ��δ���
[FAQ11483] ��ο�����֤ SELinux Policy ����

N:
     mmm system/sepolicy
     make -j24 ramdisk-nodeps
     make -j24 bootimage-nodeps
 
 Ȼ��������ˢbootimage ����.
 
O:
     mmm system/sepolicy
    Ȼ���ٸ��ݶ�Ӧ��sepolicy �Ǵ����system image, ���� vendor image �� system, vendor image �ֱ���.


75���鿴 camera ��Ϣ(HAL1 ���� HAL3.2)
adb shell dumpsys media.camera -v 2


cct�����Ĳ���������ȥ�Ĳ�����һ��
kernel�к�MAX_NUM_OF_SUPPORT_SENSOR��device�еĲ�һ�µ��µ�


camera 18��9 �ֱ��ʣ�
preview ��ӣ�"1440x720",
capture��ӣ� "4032x2016",
video ��ӣ�"1440x720",
icΪimx214 13m sensor


�鿴CPU�¶ȣ�
cat /proc/mtktz/mtktscpu
cat /sys/devices/virtual/thermal/thermal_zone1/temp


camera ������ֵ�޸ģ�

�޸� g_AE_PreviewAutoTable  g_AE_CaptureAutoTable   g_AE_VideoAutoTable


camera ��ֵ��
1�����㷽����
��1��4��3�Ĳ�ֵ��ʽ(n�Լ�����)��
X = 16*4*n
Y = 16*3*n

��2��16:9�Ĳ�ֵ
X = 16*16*n
Y = 16*9*n

��3��18:9�Ĳ�ֵ
X = 16*18*n
Y = 16*9*n

2��Ϊ���ܹ���CTS��Ҫ��֤��� KEY_PICTURE_SIZE �� ��� KEY_PREVIEW_SIZE �ı���һ��������16:9���߶���4:3.


HAL���lens����λ�ã�
hardware/mtkcam/legacy/platform/mt6739/core/featureio/drv/lens
mtkcam/legacy/platform/mt6739/core/featureio/drv/inc/mcu_dev.h


int regulator_is_enabled(struct regulator *regulator)
����ֵ��
���regular�Ѿ�ʹ���ˣ���������
���regularû��ʹ�ܣ�����0
���򣬷��ظ��� error code��


int regulator_enable/regulator_disable(struct regulator *regulator)
����ֵ��
0��disable �ɹ�
��0�� disable ʧ��

int regulator_set_voltage(struct regulator *regulator, int min_uV, int max_uV)
����ֵ��
0���ɹ����õ�ѹ
������error code��ʧ��


AF�����������̷�����
һ��������û���޸�֮ǰ�Ĵ��룺

1���򿪺���ʱ��
1����������·��ѹ��
[ 1541.338905] <0>.(0)[7820:initCamdevice]ldo vcama enable
[ 1541.342002] <0>.(0)[7820:initCamdevice]ldo vcamio enable
[ 1541.343862] <0>.(0)[7820:initCamdevice]ldo vcamd enable
2��Ȼ��AF���磺
2.1����AF open
[ 1541.581185] <1>.(1)[7824:3ATHREAD]MAINAF [AF_Open] Start
											g_s4AF_Opened = 1;
[ 1541.581859] <1>.(1)[7824:3ATHREAD]MAINAF [AFRegulatorCtrl] AFIOC_S_SETPOWERCTRL regulator_put cf017480
[ 1541.583086] <1>.(1)[7824:3ATHREAD]MAINAF [AFRegulatorCtrl] regulator_is_enabled 1	//regular�Ѿ�ʹ��
[ 1541.584066] <1>.(1)[7824:3ATHREAD]MAINAF [AFRegulatorCtrl] AF Power on
[ 1541.585064] <1>.(1)[7824:3ATHREAD]MAINAF [AF_Open] End

2.2��Ȼ�� AF set motor name
[ 1541.585730] <1>.(1)[7824:3ATHREAD]MAINAF [AF_SetMotorName] Set Motor Name : DW9763AF (6)
											g_pAF_Opened = g_s4AF_Opened = 1;
2.3��Ȼ�� AF release
[ 1541.586772] <1>.(1)[7824:3ATHREAD]MAINAF [AF_Release] Start
[ 1541.587470] <1>.(1)[7824:3ATHREAD] DW9763AF_Release Start
[ 1541.588214] <1>.(1)[7824:3ATHREAD] Free 288 
[ 1541.588821] <1>.(1)[7824:3ATHREAD] DW9763AF_Release End
											g_pAF_Opened = g_s4AF_Opened = 0;
[ 1541.589548] <1>.(1)[7824:3ATHREAD]MAINAF [AFRegulatorCtrl] AFIOC_S_SETPOWERCTRL regulator_put cf017480
[ 1541.590714] <1>.(1)[7824:3ATHREAD]MAINAF [AFRegulatorCtrl] regulator_is_enabled 1	//regular�Ѿ�ʹ��
[ 1541.591641] <1>.(1)[7824:3ATHREAD]MAINAF [AFRegulatorCtrl] Camera Power enable
[ 1541.595164] <1>.(1)[7824:3ATHREAD]MAINAF [AFRegulatorCtrl] regulator_disable 0		//������ regulator_disable()
[ 1541.596083] <1>.(1)[7824:3ATHREAD]MAINAF [AFRegulatorCtrl] AFIOC_S_SETPOWERCTRL regulator_put cf017480
[ 1541.597510] <1>.(1)[7824:3ATHREAD]MAINAF [AF_Release] End

2.4��Ȼ�� AF open 
[ 1541.603611] <1>.(1)[7824:3ATHREAD]MAINAF [AF_Open] Start
											g_s4AF_Opened = 1;
[ 1541.604284] <1>.(1)[7824:3ATHREAD]MAINAF [AFRegulatorCtrl] AFIOC_S_SETPOWERCTRL regulator_put cf017480
[ 1541.605448] <1>.(1)[7824:3ATHREAD]MAINAF [AFRegulatorCtrl] regulator_is_enabled 0	//regular���� disable ��״̬
[ 1541.606376] <1>.(1)[7824:3ATHREAD]MAINAF [AFRegulatorCtrl] regulator_set_voltage 0
[ 1541.608756] <1>.(1)[7824:3ATHREAD]MAINAF [AFRegulatorCtrl] regulator_enable 0		//��� regulator_enable()
[ 1541.615329] <1>.(1)[7824:3ATHREAD]MAINAF [AF_Open] End

2.5��Ȼ�� AF set motor name
[ 1541.616003] <1>.(1)[7824:3ATHREAD]MAINAF [AF_SetMotorName] Set Motor Name : DW9763AF (6)
											g_pAF_Opened = g_s4AF_Opened = 1;

2.6��Ȼ���ʼ�� AF������ dw9763�е� moveAF������
[ 1541.619610] <1>.(1)[7824:3ATHREAD] initdrv success
[ 1541.620562] <3>.(3)[7824:3ATHREAD] Init Pos      0
											g_pAF_Opened = g_s4AF_Opened = 2;

2.7��Ȼ���ƶ�AF��ʵ���Զ��Խ�
[ 1542.537557] <3>.(3)[7838:AFthread]moveAF, 204.  move [curr] 327 [target] 343
[ 1542.576100] <0>.(0)[7838:AFthread]moveAF, 204.  move [curr] 343 [target] 357
[ 1542.616521] <3>.(3)[7838:AFthread]moveAF, 204.  move [curr] 357 [target] 371
[ 1542.657741] <0>.(0)[7838:AFthread]moveAF, 204.  move [curr] 371 [target] 387


2���رպ���ʱ��

2.1��AF�����µ磬���� AF release ����
[ 1544.111985] <3>.(3)[504:camerahalserver]MAINAF [AF_Release] Start
[ 1544.112764] <3>.(3)[504:camerahalserver] DW9763AF_Release Start
[ 1544.119070] <3>.(3)[504:camerahalserver] Wait DW9763AF_Release 276 
[ 1544.262137] <2>.(2)[504:camerahalserver] Free 288 
[ 1544.262827] <2>.(2)[504:camerahalserver] DW9763AF_Release End
											g_pAF_Opened = g_s4AF_Opened = 0;
[ 1544.264151] <2>.(2)[504:camerahalserver]MAINAF [AFRegulatorCtrl] AFIOC_S_SETPOWERCTRL regulator_put cf017480
[ 1544.265458] <2>.(2)[504:camerahalserver]MAINAF [AFRegulatorCtrl] regulator_is_enabled 1		//regular�Ѿ�ʹ��
[ 1544.266462] <2>.(2)[504:camerahalserver]MAINAF [AFRegulatorCtrl] Camera Power enable
[ 1544.267441] <2>.(2)[504:camerahalserver]MAINAF [AFRegulatorCtrl] regulator_disable 0			//������ regulator_disable()
[ 1544.268399] <2>.(2)[504:camerahalserver]MAINAF [AFRegulatorCtrl] AFIOC_S_SETPOWERCTRL regulator_put cf017480
[ 1544.269626] <2>.(2)[504:camerahalserver]MAINAF [AF_Release] End
[ 1544.321462] <3>.(3)[504:camerahalserver]WARNING: CPU: 3 PID: 504 at /home//work/comio-mtk6739-M9528-W5528-userdebug/kernel-4.4/drivers/regulator/core.c:2200 _regulator_disable+0x38/0x114()
[ 1544.342047] <1>.(1)[504:camerahalserver]unbalanced disables for vldo28


2.2��Ȼ������·��ѹ
[ 1544.378408] <1>.(1)[504:camerahalserver]ldo vcamd disable
[ 1544.379094] <1>.(1)[504:camerahalserver]ldo vcamio disable
[ 1544.379783] <1>.(1)[504:camerahalserver]ldo vcama disable
[ 1559.886099] <3>.(3)[504:camerahalserver]imgsensor_hw_power_sequence, delay 30



�����������޸�֮��Ĵ��룺


1���򿪺���
1.1��ʹ����·��ѹ
[  112.541577] <2>.(2)[5254:initCamdevice]ldo vcama enable
[  112.542854] <2>.(2)[5254:initCamdevice]lwang.regulator.enable: regulator_set.139. powertype:3. powerId:2800000
[  112.544146] <2>.(2)[5254:initCamdevice]ldo vcamio enable
[  112.545384] <2>.(2)[5254:initCamdevice]lwang.regulator.enable: regulator_set.139. powertype:5. powerId:1800000
[  112.546678] <2>.(2)[5254:initCamdevice]ldo vcamd enable
[  112.547753] <0>.(0)[5254:initCamdevice]lwang.regulator.enable: regulator_set.139. powertype:4. powerId:1000000

[  113.000798] <0>.(0)[5256:3ATHREAD]MAINAF [AF_Open] Start
											g_s4AF_Opened = 1;
[  113.001474] <0>.(0)[5256:3ATHREAD]MAINAF [AFRegulatorCtrl] AFIOC_S_SETPOWERCTRL regulator_put cf0058c0
[  113.002726] <0>.(0)[5256:3ATHREAD]MAINAF [AFRegulatorCtrl] regulator_is_enabled 0
[  113.003681] <0>.(0)[5256:3ATHREAD]MAINAF [AFRegulatorCtrl] regulator_set_voltage 0
[  113.006079] <0>.(0)[5256:3ATHREAD]MAINAF [AFRegulatorCtrl] regulator_enable 0		//regulator_enable
[  113.012535] <1>.(1)[5256:3ATHREAD]MAINAF [AF_Open] End

[  113.013212] <1>.(1)[5256:3ATHREAD]MAINAF [AF_SetMotorName] Set Motor Name : DW9763AF (6)
											g_pAF_Opened = g_s4AF_Opened = 1;

[  113.014231] <1>.(1)[5256:3ATHREAD]MAINAF [AF_Release] Start
[  113.014923] <1>.(1)[5256:3ATHREAD] DW9763AF_Release Start
[  113.015677] <1>.(1)[5256:3ATHREAD] Free 288 
[  113.016329] <1>.(1)[5256:3ATHREAD] DW9763AF_Release End
											g_pAF_Opened = g_s4AF_Opened = 0;

[  113.017062] <1>.(1)[5256:3ATHREAD]MAINAF [AFRegulatorCtrl] AFIOC_S_SETPOWERCTRL regulator_put cf0058c0
[  113.018235] <1>.(1)[5256:3ATHREAD]MAINAF [AFRegulatorCtrl] regulator_is_enabled 1
[  113.019159] <1>.(1)[5256:3ATHREAD]MAINAF [AFRegulatorCtrl] Camera Power enable
[  113.020076] <1>.(1)[5256:3ATHREAD]MAINAF [AFRegulatorCtrl] regulator_disable 0		//regulator_disable
[  113.020973] <1>.(1)[5256:3ATHREAD]MAINAF [AFRegulatorCtrl] AFIOC_S_SETPOWERCTRL regulator_put cf0058c0
[  113.022741] <1>.(1)[5256:3ATHREAD]MAINAF [AF_Release] End

[  113.026078] <1>.(1)[5256:3ATHREAD]MAINAF [AF_Open] Start
											g_s4AF_Opened = 1;
[  113.026754] <1>.(1)[5256:3ATHREAD]MAINAF [AFRegulatorCtrl] AFIOC_S_SETPOWERCTRL regulator_put cf0058c0
[  113.027919] <1>.(1)[5256:3ATHREAD]MAINAF [AFRegulatorCtrl] regulator_is_enabled 0
[  113.028868] <1>.(1)[5256:3ATHREAD]MAINAF [AFRegulatorCtrl] regulator_set_voltage 0
[  113.031264] <1>.(1)[5256:3ATHREAD]MAINAF [AFRegulatorCtrl] regulator_enable 0		//regulator_enable
[  113.037785] <3>.(3)[5256:3ATHREAD]MAINAF [AF_Open] End

[  113.038462] <3>.(3)[5256:3ATHREAD]MAINAF [AF_SetMotorName] Set Motor Name : DW9763AF (6)
											g_pAF_Opened = g_s4AF_Opened = 1;

[  113.043438] <0>.(0)[5256:3ATHREAD] initdrv success
[  113.044368] <0>.(0)[5256:3ATHREAD] Init Pos      0
											g_pAF_Opened = g_s4AF_Opened = 2;

[  114.033623] <1>.(1)[5266:AFthread]moveAF, 204.  move [curr] 311 [target] 327
[  114.066919] <1>.(1)[5266:AFthread]moveAF, 204.  move [curr] 327 [target] 343
[  114.100447] <1>.(1)[5266:AFthread]moveAF, 204.  move [curr] 343 [target] 357
[  114.134006] <1>.(1)[5266:AFthread]moveAF, 204.  move [curr] 357 [target] 371

[  210.102677] <2>.(2)[2552:HwBinder:465_4]MAINAF [AF_Release] Start
[  210.103486] <2>.(2)[2552:HwBinder:465_4] DW9763AF_Release Start
[  210.104299] <2>.(2)[2552:HwBinder:465_4] Wait DW9763AF_Release 276 
[  210.221923] <1>.(1)[2552:HwBinder:465_4] Free 288 
[  210.222604] <1>.(1)[2552:HwBinder:465_4] DW9763AF_Release End
											g_pAF_Opened = g_s4AF_Opened = 0;
											
[  210.223391] <1>.(1)[2552:HwBinder:465_4]MAINAF [AFRegulatorCtrl] AFIOC_S_SETPOWERCTRL regulator_put cf0058c0
[  210.224625] <1>.(1)[2552:HwBinder:465_4]MAINAF [AFRegulatorCtrl] regulator_is_enabled 1
[  210.225614] <1>.(1)[2552:HwBinder:465_4]MAINAF [AFRegulatorCtrl] Camera Power enable
[  210.226595] <1>.(1)[2552:HwBinder:465_4]MAINAF [AFRegulatorCtrl] regulator_disable 0		//regulator_disable
[  210.227550] <1>.(1)[2552:HwBinder:465_4]MAINAF [AFRegulatorCtrl] AFIOC_S_SETPOWERCTRL regulator_put cf0058c0
[  210.228928] <1>.(1)[2552:HwBinder:465_4]MAINAF [AF_Release] End

[  210.238666] <1>.(1)[2552:HwBinder:465_4]ldo vcamd disable
[  210.239370] <1>.(1)[2552:HwBinder:465_4]lwang.regulator.disable: regulator_set.149. powertype:4. powerId:0
[  210.240576] <1>.(1)[2552:HwBinder:465_4]ldo vcamio disable
[  210.241257] <1>.(1)[2552:HwBinder:465_4]lwang.regulator.disable: regulator_set.149. powertype:5. powerId:0
[  210.242533] <1>.(1)[2552:HwBinder:465_4]ldo vcama disable
[  210.243208] <1>.(1)[2552:HwBinder:465_4]lwang.regulator.disable: regulator_set.149. powertype:3. powerId:0

[  210.274576] <1>.(1)[2552:HwBinder:465_4]imgsensor_hw_power_sequence, delay 30



�鿴Android��32λ����64λ��
cat /proc/cpuinfo 


gitk .
�鿴��
Follows: INIT-BRANCH-mtk6739-O1-Comio-Trunck, t-alps-release-o1.mp1-V1.102


�ں��еĶ�ʱ����
HZ����ʾÿ���ں˶�ʱ����HZ��ʱ���жϡ�
jiffies��ÿ����һ��ʱ���жϣ� jiffies ��ֵ��1����ϵͳ����ʱ��������ʼ��Ϊ0������ʾ��ǰ���жϴ�����
jiffies + HZ �� ��ʾδ����1��
jiffies + HZ/2 �� ��ʾδ����0.5��
jiffies + n*HZ/1000 �� ��ʾδ����n����


adb shell dumpsys meminfo |grep "camerahalserver"

 PixId:    8,    //otp��¼��first pixel:����{0,2��4,8} �ֱ��Ӧ {B,Gb,Gr,R},ע����kernel�еĴ��벻ͬ



��ôɾ������ͷ�� nvram
android 8.1:
adb shell
su
rm -rf /system/vendor/nvdata
rm -rf /vendor/nvdata

android 7.1 
rm -rf /data/nvram
rm -rf /nvdata


�鿴���ԣ�
getprop


mtk�ͷŰ汾�鿴�� vendor/mediatek/release_note/MT6739


#�ǰѺ������Ϊһ���ַ�����##�ǰ����������������һ��ע��ֻ���������������
#define A(x) T_##x
#define C(x) #x
A(1)------��T_1
C(1)------��"1"
���궨��������'#'��'##'�ĵط�������ǲ�����չ����Ȼ������������ķ����ܼ�. �Ӷ�һ���м�ת����. 
������������ǰ����к�Ĳ����������ȫ��չ��, ��ô��ת���������һ������ܵõ���ȷ�ĺ��������ת������չ����Ȼ����ת�����ַ�����
https://blog.csdn.net/qq1321211724/article/details/78561065
#define TOSTRING(value)           #value
#define STRINGIZE(stringizedName) TOSTRING(stringizedName)
char *sensor_kconfig = STRINGIZE(CONFIG_CUSTOM_KERNEL_IMGSENSOR);


����char *str="abcd";
memset(str+3, 0, 1) ==> str="abc"
memset(str+3,'\0',1) ==> str="abc" �˶��ߵȼ�

memset(str+3,'0',1) ==> str="abc0"

�ַ������� '\0' ���� 0 ��β����ʾһ���ַ�������β����


Linux�ʼ��б�
https://lkml.org/lkml/


adb push factory ./system/bin ��������
adb push factory /system/bin/factory ��������


�鿴�ڴ�
procrank


ProjectConfig.mk�е�CUSTOM_HAL_IMGSENSOR���ã�ֻ������vendorĿ¼�����Android.mk�ļ����档

����ͷģ��Ĺ��ɣ�
lens��ͷ��VCM��Ȧ��sensor�й�оƬ��driver IC��


git �ύ���뷽����
git add/rm
git commit  -m "test"
git push ssh://@1.2.3.4:29418/xxxx/vendor mtk8321-L1-Pos:refs/for/mtk8321-L1-Pos --tags

git push ssh://@1.2.3.4:29418/xxxx/device mtk8321-L1-Pos:refs/for/mtk8321-L1-Pos --tags

git push ssh://@1.2.3.4:29418/xxxx/docs mtk8321-L1-Pos:refs/for/mtk8321-L1-Pos --tags

�鿴GPIO״̬��
cat /sys/devices/virtual/misc/mtgpio/pin

*(*(a+0)+2);  	// a[0][2] = 3


*(remote_name+1);	//ָ��remote_name[1][0]

��������device���̣�
01-04 19:12:58.858  2462  2483 D BluetoothRemoteDevices: aclStateChangeCallback: State:Connected to Device:F4:F5:DB:50:5D:CB

�ؼ�log��
btmtk_jsr82_sdp_registration
btmtk_inquired_dev_cache_find found
0xF4:0xF5:0xDB:0x50:0x5D:0xCB

adb push MH1902_sec.bin /system/vendor/firmware/app.bin
adb push app_unsigned.bin /system/vendor/firmware/app.bin

��װNTP��MT8321��ֱ��ʹ��socketʵ�֣�ע����������������ܸ���NTPʱ�䡣
https://blog.csdn.net/u013485792/article/details/51154583


��װarm-none-linux-gnueabi��
wget http://www.codesourcery.com/sgpp/lite/arm/portal/package4571/public/arm-none-linux-gnueabi/arm-2009q1-203-arm-none-linux-gnueabi-i686-pc-linux-gnu.tar.bz2
��ѹ���Ƶ���/usr/local/arm-2009q1
chmod���Ȩ�ޡ�
.bashrc����ӣ�export PATH=/usr/bin:/usr/local/arm-2009q1/bin:$PATH
. ~/.bashrc

arm-none-linux-gnueabi-gcc ��cc1��Linuxϵͳ�и���ֻ����һ����ɾ��/usr/bin ����ļ��ɡ�


./configure --enable-static --prefix=$PWD/install --exec-prefix=$PWD/install --host=arm-none-linux-gnueabi CC=arm-none-linux-gnueabi-gcc
./configure --enable-static --prefix=$PWD/install --exec-prefix=$PWD/install --host=arm-none-linux-gnueabi CC=arm-none-linux-gnueabi-gcc --with-yielding-select=yes
make
make install

��install/bin���ļ����Ƶ���
device/mediatek/mt6580/device.mk
PRODUCT_COPY_FILES += vendor/top/topwise/tools/busybox:/system/bin/busybox
PRODUCT_COPY_FILES += vendor/top/topwise/tools/wpa_cli:/system/bin/wpa_cli

�ڻ����ն�ִ�У�ntpdate
����/system/bin/sh: ntpdate: No such file or directory
busybox����ִ�С�

@:/work2/ntp-4.2.8p12$ file busybox 
busybox: ELF 32-bit LSB  executable, ARM, EABI5 version 1 (SYSV), statically linked, stripped

@:/work2/ntp-4.2.8p12/ntp-4.2.8p12/install/bin$ file ntpdate 
ntpdate: ELF 32-bit LSB  shared object, ARM, EABI5 version 1 (SYSV), dynamically linked (uses shared libs), for GNU/Linux 2.6.14, not stripped

@:/work2/ntp-4.2.8p12$ file date
date: ELF 32-bit LSB  shared object, ARM, EABI5 version 1 (SYSV), dynamically linked (uses shared libs), stripped

@:/work2/ntp-4.2.8p12$ file sh
sh: ELF 32-bit LSB  shared object, ARM, EABI5 version 1 (SYSV), dynamically linked (uses shared libs), stripped


./configure -help

./configure --enable-static=yes --enable-shared=no --prefix=$PWD/install --exec-prefix=$PWD/install --host=arm-none-linux-gnueabi CC=arm-none-linux-gnueabi-gcc --with-arch=armv7-a-neon --with-yielding-select=yes
make
make install

--with-gnu-ld=yes
ac_cv_c_bigendian=no

https://blog.csdn.net/qiuen311/article/details/41647637
https://blog.csdn.net/zmc1216/article/details/46777897?locationNum=3
https://bbs.csdn.net/topics/390349057?page=1#post-393513107

readelf -l ntpdate
mount -o rw,remount /
mkdir /lib



"202.112.31.197"
"ntp.neu.edu.cn"


���һ�����Դ�ӡ��log��
#define PDEBUG(fmt, args...) printf("[%s:%d]" fmt "\n", __func__, __LINE__, ##args)

```


