MTK TP FAQ


```c
FAQ08115
��getevent�鿴C-TouchPanel�ϱ�����

adb shell
getevent -i
cat /proc/bus/input/devices		�鿴"Name="mtk-tpd"�����еġ�Handlers=����Ӧ�ĸ�event
getevent /dev/input/event5

���磬����һ��tp��
type									code																					value
0003					 				0039 																					0000004c
0003					 				0035 																					000001d0
0003					 				0036 																					00000212
0001					 				014a 																					00000001
0000			 		 				0000 																					00000000
0003			 		 				0039 																					ffffffff
0001				 	 				014a 																					00000000
0000				 	 				0000 																					00000000

3=EV_ABS						0x39(57)   = ABS_MT_TRACKING_ID
1=EV_KEY						0x35(53)   = ABS_MT_POSITION_X								x=0x1d0(464)
0=EV_SYN						0x36(54)   = ABS_MT_POSITION_Y								y=0x212(530)
								0x14a(330) = BTN_TOUCH										Down=1�� Up=0
								0x0(0)     = SYN_REPORT										0
											
											


FAQ03862
�鿴���ⰴ�������꣺
adb shell
cat /sys/board_properties/virtualkeys.mtk-tpd

```

