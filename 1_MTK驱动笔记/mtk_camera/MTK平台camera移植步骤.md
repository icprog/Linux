

```c

MTK ƽ̨camera��ֲ����


ƽ̨��MT6739
��׿�汾��Android 8.1
�ں˰汾��kernel-4.4


����ǰ��

Mediatekƽ̨camera������ֲ�漰�����ļ��϶࣬��һ����¼���Ժ�����µ�cameraģ�鰴�������������



һ��Ӳ����Ϣ
1��GPIO����
1�� imgsensor GPIO
1.1�� �ͺţ� ǰ��Ϊ imx190s_mipi_raw ������Ϊ imx214_mipi_raw  �� s5k4h7yx_mipi_raw
1.2�� ԭ��ͼ��GPIO��
����RST��		GPIO29
����PWDN��		GPIO30
ǰ��RST��		GPIO22
ǰ��PWDN��		GPIO23
ǰ���㹲��MCLK��GPIO126
ǰ����SCL2��		GPIO133
ǰ����SDA2��	GPIO132
camera MIPI�ӿ�(GPIO154��GPIO163)


2��  flashlight GPIO����ǰ����һ�㶼û��ǰ����
2.1�� �ͺţ� AW3643CSR
2.2�� ԭ��ͼ��GPIO��
GPIO_FLASH_STROBE(GPIO3)	��	���������IC Flash ����ʹ�ܽ�
GPIO_FLASH_F_EN(GPIO4)		��	�ֵ�Ͳģʽʹ�ܽ�
GPIO_FLASH_EN(GPIO10)		�� 	���������ICʹ�ܽ�



������������

1��dws
����Ӳ���ṩ��GPIO���ñ��޸�dws�ļ�����������/���/MIPI.

2��dts
��Ҫ������pinctrl
2.1) imgsensor
cam0_rst0			cam0_pnd0
cam1_rst0			cam1_pnd0
cam0_mclk_on		cam1_mclk_on
2.2) flashlight
flashlight_en_on				GPIO10
flashlight_strobe_high			GPIO3
flashlight_f_en_low			GPIO4



3�� proj.cfg 
3.1�� ProjectConfig.mk


CUSTOM_HAL_IMGSENSOR = imx190s_mipi_raw imx214_mipi_raw s5k4h7yx_mipi_raw gc5025_mipi_raw gc2385_mipi_raw gc0310_mipi_yuv gc0313_mipi_yuv gc2155_mipi_yuv gc2355_mipi_raw
CUSTOM_HAL_MAIN_IMGSENSOR = imx214_mipi_raw s5k4h7yx_mipi_raw gc5025_mipi_raw gc2155_mipi_yuv gc2355_mipi_raw
CUSTOM_HAL_SUB_IMGSENSOR = imx190s_mipi_raw gc2385_mipi_raw gc0310_mipi_yuv gc0313_mipi_yuv
CUSTOM_KERNEL_IMGSENSOR = imx190s_mipi_raw imx214_mipi_raw s5k4h7yx_mipi_raw gc5025_mipi_raw gc2385_mipi_raw gc0310_mipi_yuv gc0313_mipi_yuv gc2155_mipi_yuv gc2355_mipi_raw
CUSTOM_KERNEL_MAIN_IMGSENSOR = imx214_mipi_raw s5k4h7yx_mipi_raw gc5025_mipi_raw gc2155_mipi_yuv gc2355_mipi_raw
CUSTOM_KERNEL_SUB_IMGSENSOR = imx190s_mipi_raw gc2385_mipi_raw gc0310_mipi_yuv gc0313_mipi_yuv
ʣ�µ�MAIN2 �� BACKUP�����ݣ�����Ϊ�ա�

CUSTOM_HAL_LENS = dw9714af dw9763af lc898217af lc898212xdaf bu6424af ak7371af ad5820af dummy_lens
CUSTOM_HAL_MAIN_LENS = dw9714af dw9763af
CUSTOM_KERNEL_LENS = dw9714af dw9763af lc898217af lc898212xdaf bu6424af ak7371af ad5820af dummy_lens
CUSTOM_KERNEL_MAIN_LENS = dw9714af dw9763af
ʣ�µ�SUB �� BACKUP�����ݣ�����Ϊ�ա�


3.2�� kernel_config


CONFIG_CUSTOM_KERNEL_IMGSENSOR="imx190s_mipi_raw imx214_mipi_raw s5k4h7yx_mipi_raw gc5025_mipi_raw gc2385_mipi_raw gc0310_mipi_yuv gc0313_mipi_yuv gc2155_mipi_yuv gc2355_mipi_raw"
CONFIG_MTK_IMGSENSOR=y
CONFIG_MTK_FLASHLIGHT=y
CONFIG_MTK_FLASHLIGHT_LM3643=y



4��  �����ļ�����һ�£�
device/mediatek/common/kernel-headers/kd_imgsensor.h
kernel-4.4/drivers/misc/mediatek/imgsensor/inc/kd_imgsensor.h


#define S5K4H7YX_SENSOR_ID                      0x487b
#define SENSOR_DRVNAME_S5K4H7YX_MIPI_RAW        "s5k4h7yx_mipi_raw"




5��  �����ļ�����sensor˳�����
kernel�㣺
kernel-4.4/drivers/misc/mediatek/imgsensor/src/common/v1/imgsensor_sensor_list.c


#if defined(S5K4H7YX_MIPI_RAW)
    {S5K4H7YX_SENSOR_ID, SENSOR_DRVNAME_S5K4H7YX_MIPI_RAW, S5K4H7YX_MIPI_RAW_SensorInit},
#endif


HAL�㣺
vendor/mediatek/proprietary/custom/mt6739/hal/imgsensor_src/sensorlist.cpp


#if defined(IMX190S_MIPI_RAW)
    RAW_INFO(IMX190S_SENSOR_ID, SENSOR_DRVNAME_IMX190S_MIPI_RAW,NULL),
#endif



5.1  HAL�� lenslist.cpp


#if defined(DW9714AF)
        {S5K3L8S_SENSOR_ID, DW9714AF_LENS_ID, "DW9714AF", pDW9714AF_getDefaultData},
#endif


6��   
kernel-4.4/drivers/misc/mediatek/imgsensor/src/common/v1/imgsensor_sensor_list.h 


UINT32 S5K4H7YX_MIPI_RAW_SensorInit(PSENSOR_FUNCTION_STRUCT *pfFunc);


7�� �ϵ�ʱ��  
kernel-4.4/drivers/misc/mediatek/imgsensor/src/mt6739/camera_hw/imgsensor_cfg_table.c


#if defined(S5K4H7YX_MIPI_RAW)
	{
		SENSOR_DRVNAME_S5K4H7YX_MIPI_RAW,
		{
			{SensorMCLK, Vol_High, 0},
			{PDN, Vol_Low, 0},
			{RST, Vol_Low, 1},
			{DOVDD, Vol_1800, 0},
			{AVDD, Vol_2900, 0},
			{DVDD, Vol_1200, 2},
			{AFVDD, Vol_2800, 0},
			{PDN, Vol_High, 0},
			{RST, Vol_High, 0}
		},
	},
#endif


8���� imgsensor ������ӵ� kernel-4.4/drivers/misc/mediatek/imgsensor/src/mt6739/ Ŀ¼���ɡ��磺
kernel-4.4/drivers/misc/mediatek/imgsensor/src/mt6739/s5k4h7yx_mipi_raw


9�� HAL�� imgsensor Ч�����룺 vendor/mediatek/proprietary/custom/mt6739/hal/imgsensor/s5k4h7yx_mipi_raw/


10�� �޸�HAL�� featuretable ���룺  vendor/mediatek/proprietary/custom/mt6739/hal/sendepfeature/s5k4h7yx_mipi_raw

```

