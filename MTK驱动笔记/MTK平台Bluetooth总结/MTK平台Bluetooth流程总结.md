

```c

ƽ̨��MT8321
Android�汾��Android L
����Э��ջ��blueangel

һ��xxxx��Ŀ��������(�ο�MTK-Androidԭ���汾����ʵ��)
1���ͻ��ˣ�ͨ��socket�������ݣ�


int OSSocketInitClientBt(void)//xxxx
{
	int ret;

	OSSockCtl(0, BT_HW_ON, 0, 0);
	OSSockCtl(0, BT_INQUIRY_START, 0, 0);

    //�����������ַ
	uint8_t addr[6]={0x22,0x22,0xa9,0x65,0x80,0x01};

	TW_SockAddr TwBdAddr;
	TwBdAddr.Addr.bdAddr.BD_ADDR0=addr[0];
	TwBdAddr.Addr.bdAddr.BD_ADDR1=addr[1];
	TwBdAddr.Addr.bdAddr.BD_ADDR2=addr[2];
	TwBdAddr.Addr.bdAddr.BD_ADDR3=addr[3];
	TwBdAddr.Addr.bdAddr.BD_ADDR4=addr[4];
	TwBdAddr.Addr.bdAddr.BD_ADDR5=addr[5];

	ret = OSConnect (0, &TwBdAddr, -1);
	if (ret < 0) {
		ALOGE("creat file descriptor on socket fd Fail: ret=%d",ret);
		return -1;
	}
	else{
		ALOGE("creat file descriptor on socket fd Sucess: ret=%d",ret);
	}

	#define SEND 10
	int len;
	uint8_t sendbuffer[SEND]={0x55,0x66,0x77,0x88,0x99,0xaa,0xbb,0xcc,0xdd,0xee};
	len = OSSend (0, sendbuffer, SEND, OSSocketFlagsNone);
	if(len<0){
		ALOGE("fail to send data : len=%d",len);
		return -1;
	}else if(len == SEND){
		ALOGE("Sucess to send data : len=%d",len);
	}
	sleep(1);
	return 0;
}


2������ˣ����տͻ��˷��������ݣ�


int OSSocketInitServerBt(void)//printer
{
	int ret,i;

	OSSockCtl(0, BT_HW_ON, 0, 0);

	int sock;
	sock = OSSocket (OSSocketBT, OSSocketStream, OSSocketBTRFCOMM);

	OSSockCtl(0, BT_INQUIRY_START, 0, 0);

	ALOGW("accept sock , server create socket fd:%d\n",sock);

	int sock2=-1;
	OSListen(sock,10);
	sock2 = OSAccept (sock, 0);
	if(sock2==-1)    return -1;

	#define RECV 10
	int len,j;
	uint8_t revcbuf[RECV];
	len = OSRecv (sock2, revcbuf, RECV, OSSocketFlagsNone);
	for(j=0;j<RECV;j++){
		ALOGE("accept sock, read socket data: %x",revcbuf[j]);
	}
	return 0;
}


����MTK-Android��������

1�������������


classInitNative();
initNative();
getAdapterPropertyNative(adapter_name);
getAdapterPropertyNative(adapter_address);
configHciSnoopLogNative(0);
enableNative();
setAdapterPropertyNative(scan_mode);//2
setAdapterPropertyNative(discovery_timeout);//120s
createSocketChannelNative(000eSMS/MMS);
startDiscoveryNative();
createSocketChannelNative(OBEX Phonebook Access Server);
createSocketChannelNative(OBEX Object Push);
sBluetoothInterface->remove_bond(address);
sBluetoothInterface->cancel_discovery();
sBluetoothInterface->create_bond(address, transport);
sspReplyNative();


2������������������
���������֮��ÿ�η����ļ������ã�
startDiscoveryNative();//���������豸
cancelDiscoveryNative();//ֹͣ����
connectSocketNative();//�����豸
���ɡ�

3������������������
��1����MTK-Android�У����豸�������򿪺󣬾ͻ����createSocketChannelNative()����socket��Ȼ��listen����
���������豸���������ļ�ʱ�����豸�����ļ����ɡ�

��2��������MTK-Android�����У������ڿͻ��˺ͷ���ˣ�ÿ�������ڴ������󣬾���һ������ˣ��ȴ������豸�����ӡ�
�෴��������Ҫ�������豸�����ļ�ʱ������connect()���ɡ�
ÿ����һ���ļ�������Ҫ����һ��connect()�ӿڡ�

��3�����������ļ�ʹ�õ�socket�����ǣ�OBEX Object Push

��4��Android����ֻ������3��socket����ͨ��uuid�����֣�
000eSMS/MMS��ͨ������������źͲ��š�uuid��0x1132
OBEX Phonebook Access Server���绰���벾����Э��PBAP��ͨ����������绰���롣uuid:0x112f
OBEX Object Push����������Э�飬��������Դ���豸��Ĺ����䣬�������������ļ������֡�uuid:0x1105

```


