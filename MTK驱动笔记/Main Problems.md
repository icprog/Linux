

```c

MTKƽ̨�������������¼��

һ��Z705ƽ����Ŀ
����������ǰ��GC2385������GC5025
ƽ̨��MT8735
��׿�汾��Android 8.1
�ں˰汾��kernel-3.18

1��
���⣺�ڵ��� camera ʱ����ʱ���޸��˴��룬���벻����Ч�������ڴ����м���һЩ�ַ����� test ���ж��Ƿ���뵽������ļ���
����취�����޸Ĵ����touch һ������ļ��������ļ���ʱ��Ϊϵͳ��ǰʱ�䣬�Ϳ��Ա����뵽�ˡ�

2��
���⣺�ڵ��� camera ʱ�������� sensorlist.cpp ���������2�� imgsensor�������ڿ��� log ��ȴû��ȥ search ��2�� imgsensor��
ԭ���� mt6735 ��  tb8735ba1_bsp ��2��Ŀ¼���� sensorlist.cpp ����ļ��� tb8735ba1_bsp ���Ŀ¼�µ��ļ����ȼ��ߣ��޸� mt6735 Ŀ¼�µ�����ļ�������Ч����

3��
���⣺ǰ�� GC2385 ���ܵ�����ǰ������ж�������ID�� 0x5025 �����Ǻ����ID��
ԭ��ǰ�����I2C��ַ����0x6e�����Ҳ鿴Ӳ��ԭ��ͼ����֪����ǰ�����VCAMA��VCAMD��VCAMIO��MCLK���ǹ��õġ��ڸ�ǰ���ϵ�ʱ�����ڵ�ѹ���Ź��ò������÷��Ϻ����ϵ�ʱ�����Դ�ʱ����Ҳ���ڹ���״̬��û�ж���ǰ���ID�����Ƕ����˺����ID��ǰ���㻥����š�
������޸��ϵ�ʱ���Բ���2��imgsensor�໥���š�
�ں�����ϵ�ʱ��֮������ǰ��� PWDN��GC2385sû��RESET���ţ����ù���������ǰ�������GC2385��datasheet���У�
If the sensor��s power cannot be cut off, please keep power supply, then set PWDN pin low. It will make sensor standby��
��ǰ����ϵ�ʱ��֮�����ߺ���� PWDN���ú��������GC5025��datasheet���У�
If the sensor��s power cannot be cut off, please keep power supply, then set PWDN pin high.It will make sensor standby��
�ܽ᣺�Ժ����ǰ���㹲�õ�ѹ���ź�MCLK���ţ����Ҷ��ߵ�i2c��ַ����һ����ʱ�򣬼ǵô�����ߵĸ��š�


4��
���⣺���㷭ת��180�ȣ��޸��� tb8735ba1_bsp Ŀ¼�� cfg_setting_imgsensor.cpp �ļ��е� sensor ��װ�Ƕȣ�����û����Ч��
ԭ��mt8735ʹ�õ���HAL3��ʹ�õ���metadata�������޸� metadata����Ч��
���� mt6735 Ŀ¼�� metadata ��Ŀ¼�������� tb8735ba1_bsp Ŀ¼û�� metadata Ŀ¼�����Բ�����Ч��
������� tb8735ba1_bsp �½�һ�� metadataĿ¼����� gc5025 �� metadata���룬�޸�����ļ��е� sensor orientation ��������Ч��



5�����⣺ǰ��GC2385s������ID
������ imgsensor�����ö���ȷ�����µ�ʱ���ǰ��������ֲ����ġ����˿���log�����ִ���log��IIC ACKERR��
���˿���ʱ����·��ѹ��IIC���Σ����У����Ҷ��ǰ���ʱ�����ġ�
���⣬ʹ�ô���Ŀʹ�ù�������һ��ǰ��ģ�� sp0a09 ��ȴ���������򿪡�������datasheet��֪����ֻ��Ҫ2·��ѹ������ҪVCAMD���缴�ɹ�����
ԭ�򣺺����鿴Ӳ��������VCAMD��sensor����֮��ĵ���û�н��ϣ�����ǰ��û�й��硣
������ʱ�����߽ӳ����Ķ��������ţ�ʵ����ǰ��� DVDDû�й��硣���ڿ���ʱ���ϵ�ʱ��̣ܶ������ñ����������ѹ��
�ܽ᣺���� IIC ACKERRʱ��������û���⣬��Ҫ�����������û��ȱ��ĳЩ�ϡ�
VCAMA			2.8V
VCAM_IO		1.8V
VCAMD			1.2V
ע�⣺ÿһ��ģ�鶼�ǲ�ͬ�ģ�ͬһ�ͺŵ�ģ�鶼�в��죬��ͬ�ͺŵ�ģ������в��죬��������һ��Ƚϡ�
����˵�����ģ����Ե����������ǿ�ģ�鲻���Ե�������ôӲ���϶�û���⡣



����W5528�ֻ���Ŀ
����������s5k3l8 ��VCM��Voice Coil Motor�� driverIC dw9718af ����
ƽ̨��MT6739
��׿�汾��Android 8.1
�ں˰汾��kernel-4.4

1��
���⣺�ڵ��� W5528 ��Ŀ�� S5K3L8 �� DW9718AFʱ��������i2c���� I2C ACKERR ��
ԭ����� dw9718af �����Ǵ� MT6737 ƽ̨��ֲ�����ģ��������ɹ�Ӧ���ṩ�� DW9718AF ����֮��(ע�͵��� init_drv()�������)���ɡ�

2��
���⣺��log�п�������move AF������ʵ���϶����鱾����Ԥ����ʱ��ȴû��Ч����
ԭ��ʹ�ý���ճס�˺��㣬�����޷��ƶ�lens��������ȥ����lens�����ƶ�������AF����Ч����

3��W5528����AF©�磺һ����AF���е�ѹ��
ԭ��AF��TP����2.8V��ѹ��TP������ʼ��������ϵ磬���AF©�硣���TP����Ҫ�ε�ѹ������ע�͵�TP��2.8V�ϵ硣


����FX707��ǿ����ĿLCD���Ե�VSP��VSN����
ƽ̨��MT6737
��׿�汾��Android 7.1
�ں˰汾��kernel-3.18


1��
���⣺�ڵ���FX707��LCDʱ�������ñ���Է����޷���LCD��VSP��VSN��ѹ���õ�5.8V��������5.4V����Ҫ����5.8V�����TP�������⣩����lk��kernel���޸ģ���û����Ч��
ԭ�򣺲鿴log������IIC ACKERR����ѹоƬû�й�����
�����Ӳ��ԭ��оƬ��I2C����û�мӵ��裬���Գ��ִ���
��Ӳ�����ϵ�ѹоƬ��SCL��SDA�ĵ��裬Ȼ����lk��kernel��������õ�ѹ�Ĵ���֮�������ñ���Բ��VSP��VSN������5.8V��-5.8V��
ע�⣺IIC ACKERR�����Ȳ鿴Ӳ����û�������������ݡ�



�ġ�W5528�ֻ���Ŀ��һ̨�������ְ�power��LCD�޷����ѵ�����
1��
���⣺��power����LCD�޷����ѡ��ఴ���Σ�LCD���ܻ��ѡ�
�������鿴log������ÿ��Ӧһ�ΰ��»����ɿ���log�������ж���LCD��������


01-02 19:31:14.218012    56    56 I [ 9823.943521].(1)[56:pmic_thread]: [PMIC] [PMIC_INT] Reg[0x91a]=0x1
01-02 19:31:14.218947    56    56 D [ 9823.944456].(1)[56:pmic_thread]: (pressed) HW keycode powerkey
01-02 19:31:14.367901    56    56 I [ 9824.093410].(0)[56:pmic_thread]: [PMIC] [PMIC_INT] Reg[0x91a]=0x4
01-02 19:31:14.683450     0     0 W [ 9824.408959].(2)[357:light@2.0-servi]: [PWM] disp_pwm_set_backlight_cmdq(id = 0x1, level_1024 = 0), old = 569

01-02 20:00:46.521538    56    56 I [10057.129681].(0)[56:pmic_thread]: [PMIC] [PMIC_INT] Reg[0x91a]=0x4
01-02 20:00:46.866407   463   463 W [10057.474550].(1)[463:AALServiceMain]: [PWM] disp_pwm_set_backlight_cmdq(id = 0x1, level_1024 = 417), old = 0


�������Ϊ�ǵ������⣬log��û�д��󣬻��ɰ����𻵣����¸���һ�������󲻻���ָ����⡣



�塢W5528�ֻ���Ŀ
����������ǰ��GC5025����
ƽ̨��MT6739
��׿�汾��Android 8.1
�ں˰汾��kernel-4.4

�����ܹ�����GC5025��sensor ID �� OTP �� module ID��Ҳ���Ե������������Ժͺ���s5k3l8һ����������ǲ��ܺͺ���imx214һ�������
log�г��֣�  [ISP]v1 ERR WaitIrq Timeout ��pass1][ISP]Fail ��û���յ� pass1 �����ݡ�

�����������gc5025��MCLK��24�ĳ�12�󣬽����

����ԭ��
regulator vcamd ���õ�ѹ������log�п��Կ�����


[  109.050292] <1>.(1)[6667:initCamdevice]ldo vcamio enable
[  109.052417] <1>.(1)[6667:initCamdevice]vcamd: Restricting voltage, 1200000-1000000uV
[  109.053398] <1>.(1)[6667:initCamdevice][regulator]fail to regulator_set_voltage, powertype:4 powerId:1200000
[  109.055419] <1>.(1)[6667:initCamdevice]ldo vcamd enable
[  109.064812] <1>.(1)[6667:initCamdevice]ldo vcama enable


��ӽ����
������ IMX214 �� vcamd ��ѹ��1.0V�ĳ�1.2V�󣬽����{DVDD, Vol_1000, 0} ����> {DVDD, Vol_1200, 0}
ǰ��gc5025�� VCAMD Ҳ�� 1.2V��

���ս����
[FAQ20676] camera sensor��ͬ��ѹ�����Ź���regulator�Ĵ�����
���ڹ���regulator ������ѹ����ͬ�����ţ�regulator Ϊ�˱����͵�ѹ���Ų������ջ���
��ѵ͵�ѹ���ŵĵ�ѹ���ó�regulator����ߵ�ѹ���Ӷ�ʹ�ߵ�ѹ�����޷��ϵ硣����취��
(1) �µ�󣬵��� regulator_put �������ͷŵ� regulator��
(2) �ϵ�ǰ������ regulator_get �������������� regulator��


����������
1�����������regulator�޸Ļ��ǻ���ִ���


06-29 17:43:33.650254  2277  2277 E [   43.838347].(1)[2277:initCamdevice]vcama: unsupportable voltage range: 2900000-2800000uV
06-29 17:43:33.651334  2277  2277 E [   43.839427].(1)[2277:initCamdevice]: [regulator]fail to regulator_set_voltage, powertype:3 powerId:2900000


2��ԭ��
PMIC mt6357 �Ĵ����У���vcama��֧��û��2.9V��

3��������ֶ�΢��pmic��ѹ���ɲο�pmic datasheet��pmic APIʵ�֣�


  + #include <mt-plat/upmu_common.h>
  static enum IMGSENSOR_RETURN regulator_set(
  ...
  pregulator = preg->pregulator[reg_type_offset + pin -  IMGSENSOR_HW_PIN_AVDD];
  enable_cnt = preg->enable_cnt + (reg_type_offset + pin - IMGSENSOR_HW_PIN_AVDD);
  + if (pin == IMGSENSOR_HW_PIN_AVDD && pin_state == IMGSENSOR_HW_PIN_STATE_LEVEL_2900) {
      + pin_state == IMGSENSOR_HW_PIN_STATE_LEVEL_2800;  //�趨��׼��ѹ2.8V
      + pmic_config_interface(0x1C8C, 10, 0xf, 0);   //�趨΢����ѹ100mV
  + }
  if (pregulator) {
  if (pin_state != IMGSENSOR_HW_PIN_STATE_LEVEL_0) {
  


����W5528�ֻ���Ŀ����΢ָ��������log���޷� set_prop


�����ץboot kernel log��grep "avc" 

[   14.570541] <1>.(1)[1:init]selinux: avc:  denied  { set } for property=sys.fingerprint.chip pid=509 uid=1000 gid=1000 scontext=u:r:hal_fingerprint_default:s0 tcontext=u:object_r:system_prop:s0 tclass=property_service permissive=0

Ȼ��ʹ��audit2allow�� sudo audit2allow -i avc.log

�����ն������
allow hal_fingerprint_default system_prop:property_service set;

�����ʾ�� unable to open (null):  ����ĵ�ַ
��avc.txt�е���Ч��ɾ�����ɡ�

audit2allow ��װ������
sudo apt-get install policycoreutils
whitch audit2allow



�ߡ�W5528�ֻ���Ŀ���ǰ��imx190/gc5025�������չ���
ƽ̨��MT6739
��׿�汾��Android 8.1
�ں˰汾��kernel-4.4

�ο�FAQʵ�֣���ftbl�����һ�����������HAL���ȡAPP���õ����������Ȼ����д����漰�����޸��У�


1��framework�㣺
frameworks/av/camera/CameraParameters.cpp
const char CameraParameters::KEY_MIRROR_FLIP[] = "camera-mirror-flip";

frameworks/av/camera/include/camera/CameraParameters.h
static const char KEY_MIRROR_FLIP[];

2��hardware�㣺
hardware/interfaces/camera/common/1.0/default/CameraParameters.cpp
const char CameraParameters::KEY_MIRROR_FLIP[] = "camera-mirror-flip";

hardware/interfaces/camera/common/1.0/default/include/CameraParameters.h
static const char KEY_MIRROR_FLIP[];

3��mhal�㣺
vendor/mediatek/proprietary/hardware/mtkcam/utils/fwk/CameraParameters.cpp
const char CameraParameters::KEY_MIRROR_FLIP[] = "camera-mirror-flip";

vendor/mediatek/proprietary/hardware/mtkcam/include/mtkcam/utils/fwk/CameraParameters.h
static const char KEY_MIRROR_FLIP[];

vendor/mediatek/proprietary/hardware/mtkcam/legacy/platform/mt6739/v1/adapter/MtkDefault/MtkDefaultCamAdapter.Capture.cpp
#include <string.h>
#include <utils/String8.h>
String8 s8false("false"), s8flip("false");
s8flip = mpParamsMgr->getStr(CameraParameters::KEY_MIRROR_FLIP);
if ( s8flip ==  s8false) {
	shotParam.flip = MFALSE;
	MY_LOGE("shotParam.flip is MFALSE");
}
else {
	shotParam.flip = MTRUE;
	MY_LOGE("shotParam.flip is MTRUE");
}

	if(getOpenId() == 1 && (shotParam.flip)){
		switch(shotParam.mu4Transform){
			case eTransform_ROT_90:
			shotParam.mu4Transform = eTransform_FLIP_V | eTransform_ROT_90;
			break;
			case eTransform_ROT_270:
			shotParam.mu4Transform = eTransform_FLIP_H | eTransform_ROT_90;
			break;
			case eTransform_ROT_180:
			shotParam.mu4Transform = eTransform_FLIP_V;
			break;
			default:
			shotParam.mu4Transform = eTransform_FLIP_H;
			break;
		}
	}

vendor/mediatek/proprietary/hardware/mtkcam/legacy/platform/mt6739/v1/adapter/inc/Scenario/Shot/IShot.h
, flip(MFALSE)

vendor/mediatek/proprietary/custom/mt6739/hal/sendepfeature/imx190s_mipi_raw/config.ftbl.imx190s_mipi_raw.h
FTABLE_CONFIG_AS_TYPE_OF_DEFAULT_SUPPORTED(
	KEY_AS_(MtkCameraParameters::KEY_MIRROR_FLIP),
	SCENE_AS_DEFAULT_SCENE(
		ITEM_AS_DEFAULT_(MtkCameraParameters::TRUE),
		ITEM_AS_SUPPORTED_(
			MtkCameraParameters::FALSE
		)
	),
)

vendor/mediatek/proprietary/custom/mt6739/hal/sendepfeature/gc5025s_mipi_raw/config.ftbl.gc5025smipi_raw.h
FTABLE_CONFIG_AS_TYPE_OF_DEFAULT_SUPPORTED(
	KEY_AS_(MtkCameraParameters::KEY_MIRROR_FLIP),
	SCENE_AS_DEFAULT_SCENE(
		ITEM_AS_DEFAULT_(MtkCameraParameters::TRUE),
		ITEM_AS_SUPPORTED_(
			MtkCameraParameters::FALSE
		)
	),
)



�ˡ�W5528��Ŀ����΢/���ָ�ƿ����
�����޸�hardware���hardware.c�ļ���Android8.1��VTSˢGSI�����滻 system.img ��
Ҫʹ��HAL��ָ�ƿ��module ID�����ݣ���FAE�޸�ָ�ƿ��module ID���С�
����������Ϊ:


hardware/interfaces/biometrics/fingerprint/2.1/default/BiometricsFingerprint.cpp

hw_get_module(fingerprint_id, &hw_mdl)
�Լ����ݲ�ͬ��ָ��ID���ƻ� fingerprint_id ���ɡ�


�š�������뱨��


You have tried to change the API from what has been previously approved.
To make these errors go away, you have two choices:
   1) You can add "@hide" javadoc comments to the methods, etc. listed in the errors above.
   2) You can update current.xml by executing the following commands:
         p4 edit frameworks/base/api/current.xml
         make update-api
      To check in the revised current.xml, you will need OWNERS approval


����� make update-api ���� ��� /** {@hide} */


ʮ�� W6002�ֻ���Ŀ����IMX214 imgsensor��ҵ�EEPROMоƬ iic��ͨ
ƽ̨��MT6761
��׿�汾��Android8.1
�ں˰汾��kernel-4.9
������ǰ��imx190������imx214���ԡ�AF������ֲ��otp��ֲ�������ƽ̨��otp LSC������ֲ��

�ڿ���search imgsensor��ʱ��ȥ��ȡ�洢��EEPROM�е�otp���ݣ����ǳ����� IIC ACKERR��


[   12.151837] <3>.(1)[507:camerahalserver]get_imgsensor_id, 1968.  i2c write id: 0x20, sensor id: 0x214
[   12.151846] <3>.(1)[507:camerahalserver]imx214_EEPROM_FMT[imx214_read_eeprom_mtk_fmt] OTP readed 0 
[   12.156157] <3>.(1)[507:camerahalserver]i2c i2c-2: error:addr=0x50,irq_stat=0x3,ch_offset=0x100,mask:0x129
[   12.156167] <3>.(1)[507:camerahalserver]i2c i2c-2: addr:0x50,ext_data skip more log
[   12.156170] <3>.(1)[507:camerahalserver]i2c i2c-2: addr:0x50,ACK error
[   12.156183] <3>.(1)[507:camerahalserver][bxx-err]reg, dir:0xffff,DIN:0xffff,rsel:0xff,pu:0x0,pd;0xfffc
[   12.156181] <3>.(1)[507:camerahalserver][bxx-err]reg, 103-mode:0x0,104-mode:0x0,EH:0xb6d
[   12.156185] <3>.(1)[507:camerahalserver]i2c i2c-2: trans done with error
[   12.156207] <3>.(1)[507:camerahalserver]I2C read failed (0x0)! speed(0=400) (0x0)
[   12.156211] <3>.(1)[507:camerahalserver],imx214_read_eeprom_mtk_fmt,169.read imx214_eeprom  i2c fail !!!
[   12.156215] <3>.(1)[507:camerahalserver]get_imgsensor_id,1970. imx214_read_eeprom_mtk_fmt err !!!


��otp��¼�淶���У� ����¼����Ϊ EEPROM����СΪ8K Bytes�����ظ���¼��

����취���� regulator ����� AF���ϵ磺


	if (pin > IMGSENSOR_HW_PIN_AFVDD   ||
		pin < IMGSENSOR_HW_PIN_AVDD    ||
		pin_state < IMGSENSOR_HW_PIN_STATE_LEVEL_0 ||
		pin_state >= IMGSENSOR_HW_PIN_STATE_LEVEL_HIGH)
		return IMGSENSOR_RETURN_ERROR;


�޸Ľ�AF�Ĺ������·��ѹһ�����µ磨���ƽ̨��camera������AF�Ĺ��絥����AF������ʵ�ֵģ�����Ϊ�е�imgsensor��ҵ�EEPROMоƬ��ҪAF��ѹ���ܹ�����
		

ע�⣺


struct REGULATOR_CTRL regulator_control[REGULATOR_TYPE_MAX_NUM] = {
	{"vcama"},
	{"vcamd"},
	{"vcamio"},
	{"vcamaf"},
	{"vcama_sub"},
	{"vcamd_sub"},
	{"vcamio_sub"},
	{"vcama_main2"},
	{"vcamd_main2"},
	{"vcamio_main2"},
	{"vcama_sub2"},
	{"vcamd_sub2"},
	{"vcamio_sub2"}
};


û���õ��� regulator ������Ϊ NULL �� ����������������Ҳ����Ļ���ʹ�� dummy regulator��


[    1.119667] <3>.(3)[1:swapper/0]kd_camera_hw supply vcama_main2 not found, using dummy regulator
[    1.120837] <3>.(3)[1:swapper/0]kd_camera_hw supply vcamd_main2 not found, using dummy regulator
[    1.121976] <3>.(3)[1:swapper/0]kd_camera_hw supply vcamio_main2 not found, using dummy regulator
[    1.123126] <3>.(3)[1:swapper/0]kd_camera_hw supply vcama_sub2 not found, using dummy regulator
[    1.124264] <3>.(3)[1:swapper/0]kd_camera_hw supply vcamd_sub2 not found, using dummy regulator
[    1.125396] <3>.(3)[1:swapper/0]kd_camera_hw supply vcamio_sub2 not found, using dummy regulator



ʮһ�� W6001�ֻ���Ŀǰ��GC5025�㲻��
ƽ̨��MT6761
��׿�汾��Android8.1
�ں˰汾��kernel-4.9

����GC5025����ȥ֮��Ԥ��������


[   62.333137] [ISP]v1 ERR WaitIrq Timeout Clear(0), Type(0), IrqStatus(0x00000000), WaitStatus(0x00000001), Timeout(503),user(5)
[   62.845087] [ISP]v1 ERR WaitIrq Timeout Clear(0), Type(0), IrqStatus(0x00000000), WaitStatus(0x00000400), Timeout(501),user(5)
[   62.877084] <1>-(1)[2855:pass1][ISP]v3 ERRRR WaitIrq Timeout(1000) Clear(1), Type(0), IrqStatus(0x00000000), WaitStatus(0x00000400), Timeout(1000),userKey(0)


���º���gc�ṩ��mt6763ƽ̨��gc5025����󣬽����



ʮ���� W6001�ֻ���Ŀ k61v1_64_bsp_debug_defconfig ����Ч����


CONFIG_MTK_ACCDET=y
CONFIG_ACCDET_EINT_IRQ=y
+CONFIG_ACCDET_SUPPORT_EINT0=y
-# CONFIG_ACCDET_EINT_IRQ is not set
-# CONFIG_ACCDET_SUPPORT_EINT0 is not set


�����һ��config֮����Ҫ�� XXX is not set ɾ������config�Ż���Ч��



ʮ���� W6001�ֻ���Ŀ imx214otp.c �������Ǳ���:  64 bit kernel���ݲ���
�޸ĳ������ok��


#if 1
    err |= get_user(p, data->pu1Params);
    err |= put_user(p, &data32->pu1Params);
#endif


err |= get_user(p, data->pu1Params);						get_user(compat_uptr_t,  u8 *)
err |= put_user(p, &data32->pu1Params);						put_user(compat_uptr_t,  compat_uptr_t * )

err |= get_user(p, &data32->pu1Params);						get_user(compat_uptr_t,  compat_uptr_t *)
err |= put_user(p, data->pu1Params);						put_user(compat_uptr_t,  u8 *)



ʮ�ġ�C5527������Ŀ
1. ����Ƶ�����Ԥ���ӳ�ʱ�䲻�ԣ������ICŪ���£����°����µ�AW3643�������������ƵļĴ������ɡ�
2. CCT�������Ӳ��ϣ��޸�����ͷԤ���ߴ硣


ʮ�塢W5528�ֻ���Ŀ���ֻ���ǰ��򲻿�
ǰ���㶼����IIC����2���棬����ǰ�����IIC��ַ��ͻ�ˣ�
���ں���S5K3L8��   	.i2c_addr_table = {0x5a, /*0x20,*/ 0xff},
����ǰ��IMx190��	.i2c_addr_table = {0x20, /*0x34,*/ 0xff},
���������ַ��ͻû�й�ϵ����Ϊǰ�����MCLK���ǹ��õģ������໥���ţ�ǰ��򲻿���ԭ����ģ�鱾�����⡣
�Ժ����������Ե�����ǵñ����ֳ�����Ҫ�����ƻ��ֳ���



ʮ������дһ����ִ��C���뵽mtk6739ƽ̨��ִ�У�
�ο�AndroidԴ�����龰���������������ֱ��adb push�� /system/bin ִ�м��ɡ�
����RTCʱ�䣺
https://blog.csdn.net/wofeile880_jian/article/details/72312239




ʮ�ߡ�P2406 POS��Ŀ�����빤��ģʽ�ֶ������������û��Ԥ�����档
ƽ̨��MT8321
��׿�汾��Android5.1
�ں˰汾��kernel-3.10
imgsensor�ͺţ�sp0a09��30W

�����
�޸� vendor/mediatek/proprietary/platform/mt6580/hardware/mtkcam/acdk/src/acdk/AcdkMain.cpp ��
mOrientation = 90;
��HAL���sensor�İ�װ�Ƕȴ�90�ĳ�0����Ч������Ԥ��������ת90�ȡ�
�޸ĳ���ת0��ʱ����kernel log����camera preview m4u error��
�����Ŀ�Ǻ�����LCMΪ 240:320���ߣ���Ϊ 3��4��������lcm��תrotation 90��

��Ԥ�������ƶ����ƣ����ֻ����ƶ������ʵ�ʵ��ƶ�����һ�£���90�ȡ���sensor������ģ��й�оƬ�Ŀ�߸�LCD��߳�90�ȣ���ģ�鳧���´�����

�鿴sensor�����ֲ����֪����sensor�Ĵ���ֻ֧�ֵ�������ת180�ȣ����Ҿ������¾���

��ģ������󣬷���Ԥ����������log���Ҳ�����imgsensor��صĴ���log��
�����
���POS��Ŀֻ�к��㣬û������ƺ�ǰ�㣬����Ҫȥ����ص����á�
ȥ�� kernel flashlight �����ã���Ϊû������ơ�
Ȼ��Ҳȥ��dws��flashlight��ǰ��GPIO���á�
ͬʱ��Ҫ�޸�����ͷ������ȥ��ǰ��GPIO������صĴ��롣


����ģʽ����ͷ�Զ����Բ������ԣ�
����ͷ����ģ������޸ļĴ�����Ч��
���´���ģ�飬Ȼ���޸ļĴ������ɡ�


ʮ�ˡ�POS����ĿP2409
ƽ̨��MT6260
������ESP8266 WiFiģ����ԣ�ͨ�����ڸ�WiFiģ�鷢��AT����������ڶ��������ݡ�
���⣺
MT6260ͨ��TXD��AT�����ESP8266��û�з���ֵ��
ͨ��PC���ڹ��߸�ESP8266��AT���MT6260��RXD�����յ�����ֵ��
����ͨ�����ڹ��߷���MT6260��TXDû�����ݳ��������ǰε�ESP8266��USB����ӿڣ�MT6260��TXD�����ݳ�����
������
1������MT6260�Ĵ��ڵ�ѹ2.8V��ESP8266�Ĵ��ڵ�ѹ3.3V�����ɵ�ѹ��һ�µ��µġ�
�ĳɴ���1��3.3Vͨ�ţ�Ҳ���С�
2��MT6260��TXD���ӵ�ESP8266��RXD����������USBת����оƬ��TXD��Ȼ����WiFiģ���ڲ���USBת����оƬӰ�죬���Ǹ�оƬ����TX��RX�ĵ���ȥ��֮��������WiFiģ�鴮��ͨ�������ˡ�

```


