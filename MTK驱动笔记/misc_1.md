

```c

6. atomic_xchg
static inline int atomic_xchg(atomic_t *v, int new);
����ֵ����atomic_t���͵ı��������������ľ�ֵ���ء���ʹ��xchgָ��ʵ�֡�

7. 
b = a<<n,b ����a����2��n���ݡ�
b = a>>n,b ����a����2��n���ݣ�ȡ�����ࡣ

8. #if defined (BOOTLOADER)
BOOTLOADER ��ʾ lk��������preloader��

10. 
��֮ǰ�ľ��ļ�reset �����󣬸��Ƶı�ĵط���
�ٰѴ���pull�����£�
�ٸ��ƽ�ȥ��ɾ���ĸ�����ļ�������ύ
git reset DZX_LCM-Y87113-V01_ILI9881C_50_IVO_MIPI_DZTX.config

13. ��lk��disp_lcm.c�У�
if(lcm_drv->compare_id != NULL)
�����Ǳ�ʾlcm_drv���Ƿ����� compare_id ���������

if(lcm_drv->compare_id() != 0)
�����ǵ���lcdm_drv�е�compare_id ���������

14. module_init ���������ã������ú���ֻ��ģ���ʼ�������á��ڳ�ʼ������֮���ں˱�ᶪ���ú�����
module_init(initialization_function);
��ʼ������Ӧ�������ɾ�̬��,��Ϊ���ǲ������ض��ļ�֮��ɼ���
���������е�__init��־���ܿ������е�İ���������ں�������һ����ʾ,�����ú���ֻ���ڳ�ʼ��ʱʹ�á�
ģ���������ģ����غ�ᶪ�������ʼ������,�����ɽ��ú���ռ�õ��ڴ��ͷų������������á�
__init��__initdata��ʹ���ǿ�ѡ��,��Ȼ�е㷱�������Ǻ�ֵ��ʹ�á�
ע�⣬��Ҫ�ڳ�ʼ����ɺ�ʹ�õĺ���(�������ݽṹ)��ʹ����������ǡ�
moudle_init��ʹ����ǿ���Ե�,����궨�����ģ��Ŀ�����������һ������Ķ�,����˵���ں�ģ���ʼ���������ڵ�λ�á�û���������,��ĳ�ʼ���������ᱻ���á�

16. �ڴ����
kmalloc() / kzalloc()����������ڴ������ַ�������ַ���������ģ�һ����� 4M
                �ͷ��� kfree()
vmalloc() / vzalloc()��������ڴ棬�����ַһ�������������ַ���ܲ�����
                �ͷ��� vfree()
vmalloc / vzalloc ��Ҫ�Լ���ͷ�ļ� <linux/vmalloc.h>
�������ȴӸ߶��ڴ棨HIGH�������ڴ棬�߶��ڴ�û��ʱ��ȡ�Ͷ��ڴ�

17. prefetch
���ǰ�������ǰ�洢��cache�У���Ϊ���ڴ��еĶ�дЧ�ʱ�cache�еĵͣ��������cache�в����϶�Ҫ����

18. ������
mutex_lock(&g_color_reg_lock);
mutex_unlock(&g_color_reg_lock);
����кü����߳̿���ͬʱ��д������ݵĻ��͵��û�������


19. ���ض�ӦAndroid 8.0��release ��֧
repo_google init -u git@1.2.3.4:google/platform/manifest -b android-8.0.0_r17
repo_google sync  -j4
repo_google start master --all

���뻷����
sudo add-apt-repository ppa:openjdk/ppa
sudo add-apt-repository ppa:openjdk-r/ppa
sudo apt-get update
sudo apt-get install openjdk-8-jdk
sudo update-alternatives --config java
sudo update-alternatives --config javac

���룺
source build/envsetup.sh
lunch aosp_arm-eng
make -j4 2>&1 | tee build.log

20. MIPI�����üĴ�����ĳһλ��val��
#define MIPITX_OUTREG32(addr, val) \
	{\
		mt_reg_sync_writel(val, addr);\
/*���ַ addr ��д�� val ֵ*/
	}

#define MIPITX_OUTREGBIT(TYPE, REG, bit, value)  \
	{\
		do {	\
			TYPE r;\
/*����һ����ʱ TYPE ���͵ı��� r*/
			mt_reg_sync_writel(INREG32(&REG), &r);	  \
/*
INREG32(&REG) ��ʾ���Ĵ��� REG ��ֵ��
�����ʾ�� REG �Ĵ�����ֵ������������ ��ַr �С�
*/
			r.bit = value;	  \
/*���� �ṹ�� r �� ��Ա bit Ϊ val*/
			MIPITX_OUTREG32(&REG, AS_UINT32(&r));	  \
/*�� �ṹ�� r �е�ֵ��������д�� REG ��*/
			} while (0);\
	}

MIPITX_OUTREGBIT �ĺ��������üĴ��� REG �ĳ�Ա bit ��ֵΪ val ��

21. 
#define ALIGN_TO(x, n)    (((x) + ((n) - 1)) & ~((n) - 1))
�����Ĺ�������������������x����Ϊn����������ı��������磺n=8,x=7�������������еĽ����8��n=8,x=13�������������еĽ����16��

22. 
DSI video ������ģʽ��ͬ������ģʽ��ͬ���¼�ģʽ��Burstģʽ�����ǵ����ݴ���ĸ�ʽ��һ����
�ں��� DSI_PHY_CLK_LP_PerLine_config ���Կ������ǵĲ�֮ͬ����

23. dsi video ģʽ�ȴ�æ���ں��� ddp_dsi_stop �У�
	unsigned int tmp = 0;
	while (1) {
		tmp = INREG32(&DSI_REG[i]->DSI_INTSTA);
		if (!(tmp & 0x80000000))
			break;
/*���æ��ѭ���ȴ���ֱ����æ���˳�ѭ��*/
	}	

dsi cmd ģʽ�ȴ�æ��
DSI_WaitForNotBusy(module, cmdq_handle);

24. git ʹ��
ʹ�� git add teset.c ֮��test.c��� commit ����ɫ״̬��
Ȼ��ʹ�� git reset test.c ��test.c ��ɺ�ɫ(δcommit��״̬)��
git reset --hard �����������޸ġ�

25. 
struct a {
	int val;
	char b;
};
struct a ta = {0};

struct b {
	unsigned long fixed;
	unsigned int * param[5];
};
struct b tb = {0};

struct a * pa = &ta ;
struct b * pb = &tb;

pa = (struct a *) pb;

ָ����ָ��ĳһ���ڴ��׵�ַ�ı�����ָ����������ͣ�ָ������ָ��ı���ռ�õ��ڴ��С�����ԣ�ָ���ǿ��ת����ֻ�ܴӴ�ת����С�����ܴ�Сת������

���磺
unsigned long *params
unsigned int level = params[0];
unsigned char x = (unsigned char *)&level)

26. ���� dsi ����ģʽǰ������ʹ�� DSI_WaitForNotBusy(module, cmdq); �ȴ���һ������ִ�н�����

27. �� DSI_dcs_read_lcm_reg_v2 �����У�
t0.Data_ID = (cmd <  0xB0) ? DSI_DCS_READ_PACKET_ID :  DSI_GERNERIC_READ_LONG_PACKET_ID;
DSI_DCS_READ_PACKET_ID��0x06  ,DCS �� LCM REG��no params��
DSI_GERNERIC_READ_LONG_PACKET_ID��0x14    generic �� ��1 params��

28. cmdq�����������һ�����������棬�ȴ��� PC ָ��ִ�С�
p_command = (uint32_t *) ((uint8_t *) handle->pBuffer + handle->blockSize);
	case CMDQ_CODE_MOVE:
		*p_command++ = 0; /**/
		*p_command++ = CMDQ_CODE_MOVE << 24 | (arg_a & 0xffffff); /**/
		break;

29. �� ddp_dsi_build_cmdq �����У��� state == CMDQ_ESD_CHECK_READ �Ĵ���

30.
~(u32) 0 	��  ~0 �ǲ�ͬ�ġ�
~(u32)0 = 1111 1111 1111 1111
~0  		   = 1

31.
GPR��ͨ��Ŀ�ļĴ���

printk�������־��Ϣ������/proc/kmsg
dmesg �ڲ�ˢ�»�����������»�û����������ݣ��������ݷ��ظ�stdout��

�����ն����ݣ�
sudo script kmsg1.log
exit

adb shell dmesg > dmesg.log

cat proc/kmsg |grep -r "aal"
grep -E "aaa|bbb"


<3>[  283.562115]  (0)[53:pmic_thread]kpd: Power Key generate, pressed=1
<4>[  284.048875]  (1)[371:AALServiceMain][PWM] backlight is on (244), ddp_pwm power:(1)<212 -> 5095> 

<3>[  281.072144]  (0)[53:pmic_thread]kpd: Power Key generate, pressed=0
<4>[  282.412606]  (1)[235:surfaceflinger][PWM] backlight is off, ddp_pwm power:(0)



33.
ESD Check
Command mode, Please give priority to the use of pollingTE method
Video mode, Please do ESD by reading the LCM IC register


35.aal
Save the power consumption
Enhance the sun-light read-ability

36.��Ч .bashrc
source ~/.bashrc

37. DFO : dynamic display resolution adjustment


38.module_platform_driver(gpio_led_mtk_driver);

module_platform_driver(xxx)��
����չ�������������ʽ��
static int __init xxx_init(void)
{
	return platform_driver_register(&xxx);
}
module_init(xxx_init);
static void __exit xxx_exit(void)
{
	return platform_driver_unregister(&xxx);
}
module_exit(xxx_exit);


39. MODULE_DEVICE_TABLE(platform, xx_driver_ids);
MODULE_DEVICE_TABLE һ�������Ȳ�ε��豸�����С�
����xx_driver_ids�ṹ���Ǵ�������֧�ֵ��豸�б�
�����ǣ���xx_driver_ids�ṹ������û��ռ䣬����ģ�����ϵͳ�ڼ���ģ��ʱ����֪����ʲôģ���ӦʲôӲ���豸��
�÷��ǣ�MODULE_DEVICE_TABLE���豸���ͣ��豸�������У��豸���ͣ�����USB,PCI�ȣ�Ҳ�����Լ������֣���������������Բ�ͬ��ƽ̨�ֵ��ࣻ
�豸��Ҳ���Լ�����ģ��������һ������ǿգ�������ʶ������

40����64λ�ϣ�ָ�����ռ8���ֽڡ�����gcc��ϵͳλ����ȷ���ֽ�����

41�� mtk��PWM��ʹ��ʱ���Ż�ʹ�ܡ�lcd�� backlight ģʽΪ�� MT65XX_LED_MODE_CUST_BLS_PWM
red��green��blue��ģʽΪ�� MT65XX_LED_MODE_GPIO

42�� ������������(gamma���Ե�)ʱ�����gamma����ʧ�ܣ��ر� mtk aal ֧�֣�
�� defconfig �� �� #CONFIG_MTK_AAL_SUPPORT=y
�� ProjectConfig.mk �У� MTK_AAL_SUPPORT = no

43�� ͬһ����� module_init ������˳��Ϊ��
ͬһ�����init����makefile ����˳��obj -y += xxx.o��ǰ��ľ���������

���� mtk tp ������

makefile�ļ�Ϊ��
obj-y  += tpd_common_probe.o
obj-y  += mstar_drv/
obj-y	+= focaltech_touch_V1_4/

drivers\input\touchscreen\mediatek\tpd_common_probe.c
late_initcall(tpd_probe_init);  /*���ȼ�Ϊ7*/

drivers\input\touchscreen\mediatek\mstar_drv\ilitek_drv_mtk.c    ���ģ���ȱ�ִ��
module_init(tpd_driver_init);  /*���ȼ�Ϊ6*/

drivers\input\touchscreen\mediatek\focaltech_touch_v1_4\focaltech_core.c    ���ģ���ִ��
module_init(tpd_driver_init);  /*���ȼ�Ϊ6*/


46�� lcd ʱ��
clock-frequency = (h_active + hfp + hbp + h_sync) * (v_active + vfp + vbp + v_sync) * fps



48�� video ģʽ������ģʽ��
Non-burst mode sync pluses
Non-burst mode sync event
Burst mode

cat proc/bootprof


adb�����ȫ��

�ֻ��Ĵ洢�ռ��� adb shell �е�·��Ϊ��/sdcard/

49. ��Ļ��ͼ
adb shell /system/bin/screencap -p /sdcard/screenshot.png 
adb pull /sdcard/screenshot.png ./screenshot.png

50. ���ֻ��л�ȡ mtklog
adb pull /storage/emulated/0/mtklog mklog/

51.��װ/ж��Ӧ�ó���-r��ʾ�滻ԭ���� apk
adb install -r Ӧ�ó���.apk
adb uninstall xxx.apk

52.�����ļ����ֻ���
adb push test.c /sdcard/test

53.��ӡ log��������ļ����鿴�ϲ�log��Ϣ:
 adb logcat |grep "AAL"
 adb logcat > ./log.txt
 adb logcat > ./camera.txt

adb ¼����Ļ��
adb shell 
screenrecord /sdcard/demo.mp4	//180s

adb shell screenrecord  --time-limit 10 /sdcard/demo.mp4	//10s

adb shell screenrecord --size 1280*720 /sdcard/demo.mp4

adb pull /sdcard/demo.mp4



54.�鿴�ں���Ϣ
sudo script kmsg.log
exit
cat /proc/kmsg

55.adb ���빤��ģʽ
adb shell am start -n com.mediatek.engineermode/.EngineerMode

adb ������
adb shell input keyevent 26

56.��ο�������
adb shell
echo 3000 > /sys/devices/virtual/timed_output/vibrator/enable
��3��


system/core/rootdir/init.rc
device/mediatek/mt6735/init.mt6735.rc
out/target/product/gerneal/root/init.mt6735.rc


59�� ��д dts �ļ�ע�⣺
�����붥��1������2 ��tab ��,��from M_branch_OTP_porting_guide.pdf   page 8��

&i2c0 {
	#address-cells = <1>;
	#size-cells = <0>;
	camera_main@10 {
		compatible = "mediatek,camera_main";
		reg = <0x10>;
		status = "okay";
	};
	camera_main_af@0c {
		compatible = "mediatek,camera_main_af";
		reg = <0x0c>;
		status = "okay";
	};
	camera_sub@3c {
		compatible = "mediatek,camera_sub";
		reg = <0x3c>;
		status = "okay";
	};
};



60��
#define A1(name, type)  type name_##type##_type 
#define A2(name, type)  type name##_##type##_type

A1(a1, int);  	/* �ȼ���: int name_int_type; */
A2(a1, int);  	/* �ȼ���: int a1_int_type;   */



61�� camera bring up 
(1)
D1ʹ�� mt6737t 
D2 ʹ�� mt6737m 	mt6735m


MT6737V/W					MACH_TYPE=mt6737m
MT6737V/WT				MACH_TYPE=mt6737t
MT6737V/WH   			MACH_TYPE=mt6737t

ov8856b			����
OV9760    		����
ov8856			����
OV9760s 		ǰ��

���һ�� ��camera ����2�֣���׺Ϊ b ��Ϊ���㣬��׺Ϊ s ��Ϊǰ�㡣

�оߣ�
һ��ǰ�� gc0310_mipi_yuv 
���� gc2155_mipi_yuv �� gc2355_mipi_raw


62.�̼������͸�ʽ�����ص�����
���ز����ʽ����
��ʽ���Ǵ��������ڴ�ĸ�ʽ����
�̼�����ֻ���ʽ��ϵͳ���û���2�����ֶ��ѣ����������ڴ档


sudo apt-get add-apt-repository ppa:git-core/ppa
sudo apt-get update
sudo apt-get install git


67��strlen�����ǲ�������\0���ĳ��ȵģ�sizeof����Ľ���Ű���'\0'�ĳ��ȡ���Ҫȡһ���ַ����ĳ���ʱ��ʹ��strlen.


9��GPIO���ÿ���������������
adb shell cat /sys/devices/platform/1000b000.pinctrl/mt_gpio

 [MODE] [DIR] [DOUT] [DIN] [PULL_EN] [PULL_SEL] [IES] [SMT] [DRIVE]
  95: 110010101
  96: 110010101
 112: 110010101


���⣺��defconfig���У�CONFIG_TOUCHSCREEN_MTK_FOCALTECH_TS_FT8006M=y    �� .config ��ȴû��������ã�
������� proj.cfg �н� CONFIG_TOUCHSCREEN_MTK_FOCALTECH_TS_FT8006M=y ��ǰ��Ҳ��Ч��ֱ����˽�л��ļ��У�obj-y   +=  ...
ԭ����û������ Kconfig�ļ���©���� tpd_common_probe.o 

���⣺tp���Ի����������෴�ˡ�
������޸� report data ���롣



���뱨�����˰汾��
cd idh.code/packages/apps/360OS_Launcher
gitk .
git reset --hard f337c9760dfd7705d87a75f776bcf59789c3daf1
���Ϊ commit ID ������ change ID ��


10��gitʹ�÷�����
(1)���������ͻ���� Gerrit �ϵ�� abandon ��Ȼ���ڱ��� git  reset --hard 		git pull
(2)�ڱ��ػ��˵�ĳ���汾 cd dir		git reset --hard commitID

(3)���ύʱ�򣬽� yes д���� yesa �������ڱ��ط�֧�ύ�ˣ�������Զ�̷�֧ȴû�С�
�Ȱ��ύ���ļ����е����Ŀ¼��Ȼ��git rm ɾ������ύ���ļ���Ȼ��pushcode �����ļ��ύ����ʱ��Gerrit�ϣ������2���ύ��abandon�Ǵ���Ч���ύ���ɡ�


11��mt6737t  ��ͷ�ļ�Ϊ mt6735.dtsi �� cust.dtsi
mt6737m  ��ͷ�ļ�Ϊ mt6735m.dtsi 

12��i2c�豸������Ա�� .detect �� .address_data ����ʡ�ԣ�id_table ����ʡ�ԡ���kxtj_1009.c �У�

13��kxtj_1009.c �У� platform_driver �� kxtj2_1009_i2c_driver ����ͬһ���ڵ㣺 .compatible = "mediatek,gsensor"

14��HAL ���õ�������ͷ�ļ������Ŀ¼��
device/mediatek/common/kernel-headers/

15�� camera 3A�㷨��AE/AF/AWB ����Ӧ��������Ĺ��ܣ����Զ��ع⣬�Զ��Խ����Զ���ƽ��

16��incell ����

17��������ز���ȥʱ��ʹ�� ȫ����ʽ�������ؼ��ɡ�

18���ջ�ʱ��ʾ�� ERROR�� S_INVALID_BBCHIP_TYPE
�����CPU�ͺŲ��ԡ�

20��������ˢ��ʱ��USB��ʾΪ��Mediatek Inc ���ֶ�ѡ��USB����ˢ����

21��ˢ��ʱ��txt�ļ���Ҫ���ص�img�ļ���������ͬһ��Ŀ¼�������ء�

22���� ���� kernel ʱ��ע��Ҫ��ɾ�� out Ŀ¼���ϴα����������ص�Ŀ¼�� .o  �ļ���

23�� Linux V4L2 ����� UVC(usb��Ƶ�淶)�淶�ģ���USB����ͷ��UVC ����·��Ϊ�� kernel-3.10/drivers/media/usb/uvc/
MTK��׼��Camera��û�в���v4l2��ܣ�������Ҫ��jni��ʵ�ֻ�����v4l2��Ƶ�ɼ����̡�

27�� camera������HAL���sensorlist.cpp �� kernel��� kd_sensorlist.h ��˳�򱣴�һ�¡�

28��Ubuntuû�����������ó�ģ�������

29�� Makefile
$(wildcard PATTERN...) ����Makefile�У�����չ��Ϊ�Ѿ����ڵġ�ʹ�ÿո�ֿ��ġ�ƥ���ģʽ�������ļ��б�
����������κη��ϴ�ģʽ���ļ������������ģʽ�ַ������ؿա�
����
$(	wildcard 	$(IMGSENSOR_DRIVER_PATH)/$(MTK_PLATFORM)/camera_project/$(ARCH_MTK_PROJECT)/$(1)	)


31.
source build/envsetup.sh
lunch
mmm vendor/mediatek/proprietary/hardware/mtkcam/legacy/platform/mt6735/v1/common/paramsmgr

32.
git checkout -f
�������ļ����޸�

git reset --hard commitID
���Ի���ĳ��commitID�ύcommit��

git reset --hard
���׻��˵�ĳ���汾�����ص�Դ��Ҳ���Ϊ��һ���汾������

33������ָ����Ǻ�����������һ������ָ�룬�൱�ڵ��������������


34��Ubuntu��ô���ӵ���������
��Ubuntu�е��ļ��У�������ӵ���������Ȼ�����룺 smb://data1

git checkout -f 
git clean -fd


38�� MTK i2c ʹ��7λѰַ����ʹ�� i2c DMA��������ʱ������� 255 ���ֽڡ�

struct i2c_client {
	unsigned short flags;		/* div., see below		*/
	unsigned short addr;		/* chip address - NOTE: 7bit	*/
					/* addresses are stored in the	*/
					/* _LOWER_ 7 bits		*/
	char name[I2C_NAME_SIZE];
	struct i2c_adapter *adapter;	/* the adapter we sit on	*/
	struct device dev;		/* the device structure		*/
	int irq;			/* irq issued by device		*/
	struct list_head detected;
#ifdef CONFIG_MTK_I2C_EXTENSION
	__u32 timing;			/* parameters of timings		*/
	__u32 ext_flag;
#endif
};




39��EXPORT_SYMBOLʹ�÷���
   ��һ����ģ�麯������֮��ʹ��EXPORT_SYMBOL����������
   �ڶ����ڵ��øú�����ģ����ʹ��extern��֮����
   ���������ȼ��ض���ú�����ģ�飬�ټ��ص��øú�����ģ��



 Ҫ�鿴log��Ϣ ����Ҫ��һ������ �Ǿ����ڴ����н�usb�ӿڵ�log��Ϣ����Ĺر�״̬��������
���£���kernel/printk/printk.c�ĺ��� mt_disable_uart(void) �Լ� module_param_named(disable_uart, printk_disable_uart, bool, S_IRUGO | S_IWUSR); 
���ε� ��������ε� �Ͳ����ӡkernel��log��Ϣ
��
ʹ��UE�����Ķ����ƹ��ߴ�lk.bin ������ASCLL������disable_uart ��printk_disable_uart��Ĭ�ϵ�1��Ϊ0
�����ؽ����ӵ�ʱ��ѡ���ƽ̨�����Checksum.ini�ı��� ��ʱ����ɾ��Checksum.ini(�����У���õĶ��� Ŀ���Ƿ�ֹ��ȥ������Ĵ���)
  
40�� LCD������ߴ�
���LCDΪ 5.0 �磬1��Ϊ 25.4 mm�� �� LCD�ĶԽ��߳���Ϊ 12.7 cm �� ��Ļ�ķֱ���Ϊ 480*854 ��Ϊ 16:9 ���������ݹ��ɶ��ɣ���� ��
physic_width  =  62 mm
physic_height =  111 mm
����ֱ������Ŀ����Ӧ��Ҫ��������ߴ硣

41�� �����п��Դ���δ��ʼ����ָ�룬�������д��벻�����

unsigned int a = 6; 
void fun(unsigned int ** liu)
{
	 *liu = & a;
}
int main(void)
{
	 unsigned int * str;	//str ��һ�� unsigned int * ���ͣ�������û�г�ʼ���������ں��� fun �н��г�ʼ�������� fun ֮�� str ָ����ȫ�ֱ��� a ��

	 fun(&str);	// &str ��Ϊ NULL ��

	 printf("%d \n",*str);    //* str = 6

	 return 0;
}


git�ύ����
git add .
git commit -m description
git push ssh://xxxx@1.2.3.4:29418/xxxxxL1/kernel-3.10 mtk8321-L1-driver:refs/for/mtk8321-L1-driver --tags   
git push <Զ��������> <���ط�֧��>:<Զ��������֧��>

for mt8321 vendor:   
git push ssh://xxxx@1.2.3.4:29418/xxxxxL1/vendor mtk8321-L1-Pos:refs/for/mtk8321-L1-Pos --tags  
   

lk/app/mt_boot/rules.mk
�޸� ��	printk.disable_uart = 0
���ã�	user��userdebug�汾����kernel log


MTKƽ̨dump pass1��pass2�����ݣ�

ISP 2.x

Select dump buffer port
Normal Preview, Video Preview/Record and ZSD Preview (using bitmask)
dump Pass1 IMGO output
adb shell setprop camera.dumpbuffer.enable 1
dump Pass2 WDMA output (For Display)
adb shell setprop camera.dumpbuffer.enable 2
dump Pass2 WROT output (For Record)
adb shell setprop camera.dumpbuffer.enable 4
dump Pass1 IMGO and Pass2 WDMA output
adb shell setprop camera.dumpbuffer.enable 3
dump Pass1 IMGO, Pass2 WDMA and  Pass2 WROT output
adb shell setprop camera.dumpbuffer.enable 7
dump Pass1 pass2 when take picture (single shot)
adb shell setprop debug.camera.dump 1
dump VSS Pass1 Pass2
adb shell setprop camera.vss.dumpbuffer.enable 1

Pull buffer from device
adb pull /sdcard/camera_dump/

Clear buffer of device
adb shell rm -rf /sdcard/camera_dump/



ISP 3.x

Jade has display orientation for some features, when you want to dump display or record buffer, please try both WDMA and WROT port.

Select camera mode
Normal Preview
adb shell "setprop debug.PHO.dump 1"
Normal Capture
adb shell "setprop debug.SShot.dump 1"
Continue Shot
adb shell "setprop debug.MShot.dump 1"
Video Preview/Record
adb shell "setprop debug.VDO.dump 1"
ZSD Preview
adb shell "setprop debug.ZSD.dump 1"

Select dump buffer port
Normal Preview, Video Preview/Record and ZSD Preview
dump Pass1 RRZO output
adb shell "setprop debug.camnode.dump.1 1"
dump Pass1 IMGO output
adb shell "setprop debug.camnode.dump.2 1"
dump Pass2 input from RRZO
adb shell "setprop debug.camnode.dump.31 1"
dump Pass2 WDMA output (For Display)
adb shell "setprop debug.camnode.dump.41 1"
dump Pass2 WROT output (For Record)
adb shell "setprop debug.camnode.dump.43 1"
dump Pass2 IMG2O output
adb shell "setprop debug.camnode.dump.45 1"

Normal capture and ZSD capture
dump Pass2 input from RRZO (normal capture only)
adb shell "setprop debug.camnode.dump.31 1"
dump Pass2 input from IMGO
adb shell "setprop debug.camnode.dump.32 1" 
dump Pass2 WDMA output
adb shell "setprop debug.camnode.dump.42 1"
dump Pass2 WROT output
adb shell "setprop debug.camnode.dump.44 1"

Pull buffer from device
Normal Preview
adb pull /sdcard/cameradump_PHO ./cameradump_PHO/
Normal Capture
adb pull /sdcard/cameradump_SShot ./cameradump_SShot/
Continue Shot
adb pull /sdcard/cameradump_SShot ./cameradump_MShot/
Video Preview/Record
adb pull /sdcard/cameradump_VDO ./cameradump_VDO/
ZSD Preview
adb pull /sdcard/cameradump_ZSD ./cameradump_ZSD/

Clear buffer of device
adb shell "rm -rf /sdcard/cameradump_*"



#undef TAG
#define TAG "[USDK] "

ps |grep factory
getevent -l
getevent -t /dev/input/event0

tag:USDK text:TW_Kbd
text:fatal

. ~/.bashrc

```


