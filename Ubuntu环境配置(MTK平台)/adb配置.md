

```c
ʹ��adbʱ����Ҫ���������ļ���
1�� /etc/udev/rules.d
��1��51-android.rules �����ݣ������û�и��ļ������д�����
SUBSYSTEM=="usb", ENV{DEVTYPE}=="usb_device", MODE="0666"

��2��51-MTKinc.rules �����ݣ����û�и��ļ������д�����
SUBSYSTEM=="usb", ENV{DEVTYPE}=="usb_device", MODE="0666"
KERNEL=="ttyACM*", MODE="0666"

2.  ~/.android
��1��adb_usb.ini �����ݣ������û�и��ļ������д�����
0x0e8d

��2��0e8d�����ģ�
���ն������룺lsusb�����У�
Bus 001 Device 029: ID 0e8d:2003 MediaTek Inc.

```

