

```c
һ�����⣺��������ͨ��ESD���

����LCM  FAE�ṩ�Ľ���������ڽ���ESD���ʱ����LCM�л���page 0F����ͨ��ESD��⡣
ESD��⣺��LCM������ʹ��+10V��-10V��ѹ����������10Kv���Ӵ�����6Kv��200�Σ���һֱ�򾲵絽��������
��������ĺ��壺
�ڳ�ʼ����������ɶ�LCM�ļĴ��������ú󣬽���LCM��page 0F����Чҳ����
������ESD���ʱ�����л���LCM��page 0����ȡ�Ĵ���0x0A��ֵ��Ȼ�����л���page 0F��
������ʱ��Ҳ�ڽ���ESD��⣬���л���LCM��page 0�����������ַ0x28��Display Off����0x10��Sleep In��������LCM����ģʽ�����л���page 0F��
ESD�������󣬰�����������LCM����lcd_init_para��ʼִ�У�������lcd_exist_sleep��

1. �ڳ�ʼ�������һ�м���page 0F�� {0xFF,03,{0x98,0x81,0x0F}}
���壺LCMĬ�Ϲ�����page 0����LCM��ʼ�������󣬽�LCM�л���page 0F��

2. �ٽ�ESD check�����̸�Ϊ���е�page 0��{0xFF,03,{0x98,0x81,0x00}},��
ȥcheck�� 0x0A�����е�page 0F��{0xFF,03,{0x98,0x81,0x0F}},����
���޸� ddp_dsi.c�ļ�
���壺����ESD���ʱ����LCM�л���page 0�������Ĵ���0x0a�����л���page F��
�޸�ǰ��
DSI_OUTREG32(cmdq_trigger_handle, &DSI_CMDQ_REG[dsi_i]->data[0], AS_UINT32(&t1));
DSI_OUTREG32(cmdq_trigger_handle, &DSI_CMDQ_REG[dsi_i]->data[1], AS_UINT32(&t0));
DSI_OUTREG32(cmdq_trigger_handle, &DSI_REG[dsi_i]->DSI_CMDQ_SIZE,2);
�޸ĺ�
DSI_OUTREG32(cmdq_trigger_handle, &DSI_CMDQ_REG[dsi_i]->data[0], 0x00043902);
DSI_OUTREG32(cmdq_trigger_handle, &DSI_CMDQ_REG[dsi_i]->data[1], 0x008198ff);
DSI_OUTREG32(cmdq_trigger_handle, &DSI_CMDQ_REG[dsi_i]->data[2], AS_UINT32(&t1));
DSI_OUTREG32(cmdq_trigger_handle, &DSI_CMDQ_REG[dsi_i]->data[3], AS_UINT32(&t0));
DSI_OUTREG32(cmdq_trigger_handle, &DSI_CMDQ_REG[dsi_i]->data[4], 0x00043902);
DSI_OUTREG32(cmdq_trigger_handle, &DSI_CMDQ_REG[dsi_i]->data[5], 0x0F8198ff);
DSI_OUTREG32(cmdq_trigger_handle, &DSI_REG[dsi_i]->DSI_CMDQ_SIZE,6);

3. �����������̸�Ϊ�е�page 0 ��0x28 & 0x10�����е�page 0F�������ߵ�ʱ����Ҫ��λ�����������£�
{0xFF,03,{0x98,0x81,0x00}},
{0x28,01,{0x00}},
Delay_ms(50);
{0x10,01,{0x00}},
Delay_ms(120);
{0xFF,03,{0x98,0x81,0x0F}},
���壺LCM������ʱ�����л���page 0 ������Display Off��Sleep in��Ȼ���л��� page 0F 
����
����������ע�⣺
1. �ڳ�ʼ�������һ�м���page 0F�� {0xFF,03,{0x98,0x81,0x0F}}������lcd_init_para�����һ����ӣ�0X9004,0xFF,0x98,0x81,0x0F
ע�⣬���һ�в����ж��š�

2. 0x00043902�ĺ���
�ο� LCM_Porting_Guide_DSI_V1.0_MT6735(P_M)_MT6753.pdf  ��DSI Command Queue�������� DSI CMDģʽ�������� video ģʽ��

4�ֽڣ�	Data1      Data0      Data ID      CONFG

���У�CONFGΪ��
Bit7��RPT	Bit6��RSV		Bit5��TE 		Bit4��CL
Bit3��HS		Bit2��BTA		[Bit1:Bit0]:  TYPE[1:0]
���壺bit3λ����HS=1��DSI����ģʽΪHSģʽ��
������		  �� HS=0��DSI����ģʽΪLPģʽ��

[Bit1:Bit0]:  TYPE[1:0]λ��

Type-0��00���̰�����/д���
ָ���ʽ��
Bit3			bit2			bit1			bit0
Data1		Data0			Data ID			CONFG

Type-1��01��������Frame buffer write command (from LCD)��
ָ���ʽ��
Bit3				bit2			bit1		bit0
Mem start 1(��ѡ)	mem start 0		Data ID		CONFG

Type-2��10��������Generic long packet write command (from command queue)
Bit3			bit2			bit1			bit0
WC 1		WC 0		Data ID		CONFG
Data3		Data2		Data1		Data0
						Data WC-1	Data WC-2	
						
Type-3��11���̰���FB�����
Bit3				bit2				bit1		bit0
Mem start 1(��ѡ)	mem start 0		Data ID	CONFG

���磺	0x00043902
02��0x10����ʾType-2������
39����ʾ Data ID
0004����ʾ����������4���ֽڵ�����

0x008198ff��
0xff������
98 81 00 ������

```

