
```c
MKTƽ̨��ֲLCD������

һ�������ļ�
1���Ķ�Ӳ��ԭ��ͼ��GPIO���ñ�ȷ��LCD�����������Ƿ���ȷ����xxx��ĿΪ����
MIPI����(GPI150��GPI159)��TCP/TCN��TDP0/TDN0��TDP1/TDN1��TDP2/TDN2��TDP3/TDN3
DSI_TE(GPIO147) �� 
LCM_RST(GPIO146) �� 
LCM_ID(GPIO122) ,
LCM_LEDA/LCM_LEDK(����������ţ��뱳��оƬAW9961 ����)��GPIO69Ϊ����������š�
VIO18 �� VIO28

2������ dws �ļ�(dws�ļ���4��·����preloader��lk��kernel��custom)��
DSI_TE���ţ�GPIO147��				IN
LCM��λ���ţ�GPIO146��				OUT
LCM ID������ţ�GPIO122��			IN
LCM����������ţ�GPIO69��			OUT
LCM MIPI���ţ�GPI150��GPI159��		MIPI

3������ dts �ļ���$(project).dts
���ñ������� GPIO69 �� output-low �� output-high ״̬����backlight�Ĺ���ģʽΪ GPIO ʱ���õ��������ط��ò�����

**********��עһ��MTK�ı��⼸�ֹ���ģʽ(һ����õڶ���)��
a����PWM������ backlight ��
(1)PWM��		ֱ�Ӳ���BB�˵�PWMģ�������			����Ϊ�� MT65XX_LED_MODE_PWM
(2)AAL(BLS)��		����BB�˵�BLSģ�������PWMģ�������	����Ϊ�� MT65XX_LED_MODE_CUST_BLS_PWM
(3)GPIO��		ֱ��ͨ��GPIO69�����PWM���Σ�		����Ϊ�� MT65XX_LED_MODE_GPIO
(4)CABC��		ͨ��MIPIдLCM IC�˼Ĵ�������backlight IC ���PWM����(LCM�б����б���IC)��	����Ϊ�� MT65XX_LED_MODE_CUST_LCM

b����PMIC����backlight��  ����Ϊ MT65XX_LED_MODE_PMIC

c��lk���� cust_led_list ������������ñ���ģʽΪMT65XX_LED_MODE_CUST_BLS_PWM ��kernel����dts������ led_mode = <5> ������Ч��

**********��עһ��AAL��CABC���������ʣ�
a��AAL�����ֺ��壺һ�Ǳ�ʾAAL����backlightģʽ(��BLS)�����Ǳ�ʾAALServer

b��CABCҲ�����ֺ��壺һ�Ǳ�ʾCABC����backlightģʽ(ֱ����LCM backlight ICд�Ĵ���)�����Ǳ�ʾAALServer�µ�һ����feature��
												
c��AALServer(MTK���е�һ�ּ���)����������feature��
(1)LABC�����ݻ�������backlight(��L�汾֮��ʹ��Androidԭ�����Զ����⹦��)
(2)CABC������Context���ڱ���(ʡ��)
(3)DRE����ǿ�����µĿɶ���(��L sensor��أ���backlight�޹�)


������ֲ����
1��	ֱ��ʹ��ͨ�������������hwinfo��
		����ʹ���������ļ����޸�list��Makefile���ļ��������������
		
2���鿴��ʼ�������еĶ�LCD ID�ĵ�ַ���Ӵ���log�п���������LCD ID �������ʼ�����롣

3��LCD��˯��дLCD�ļĴ���0x28��0x10��LCD����ֱ���ܳ�ʼ�����롣

4����עLCD�� esd check�ĵ�ַ��value��

5����עLCD�� PCLK�� RGB timing ��PCLKӰ�����߸��š�ҲӰ��FPS��fps���㹫ʽΪ��
(1)DSI VDO mode��
�������ʣ�data_rate = (height+VSA+VBP+VFP) * (width+HSA+HBP+HFP) * bpp * fps / (data_lane_num)
fps=60, RGB888��bpp=24�� data_lane_num=4����data_rate=453MHz

(2)DSI CMD mode:
�������ʣ� data_rate = width*height*1.2*bpp*fps/data_lane_num

(3)DSI����˫�߲���(�����غ��½��ز�������)��ʱ������ PCLK=data_rate/2
PCLK ��Ϊ hwinfo �����õ� PCLK��

```


