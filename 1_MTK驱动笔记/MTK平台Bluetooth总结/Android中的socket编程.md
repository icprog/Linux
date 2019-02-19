

```c

ƽ̨��MT8321
Android�汾��Android L

һ��Android�е�socket
1����bt_socket.h����2���ӿڣ�


bt_status_t (*listen)(btsock_type_t type, const char* service_name, const uint8_t* service_uuid, int channel, int* sock_fd, int flags);

bt_status_t (*connect)(const bt_bdaddr_t *bd_addr, btsock_type_t type, const uint8_t* uuid, int channel, int* sock_fd, int flags);


��1���ȿ�listen�ӿڣ�
����ӿ�����ͨ��socket�������ݡ�
listen�ᴴ��������һ��socket��fd������ָ��sock_fd�С�
�����Զ���豸���ӵ������socket��read sock_fdʱ�����Զ���豸��������ַ��recvmsg sock_fdȻ�����CMSG������һ���µ�sockFd����ʱread sockFdʱ�����Զ���豸���������ݡ�

��2���ٿ�connect�ӿڣ�
����ӿ�����ͨ��socket�������ݡ�
connect������ָ����Զ���豸address��������ӳɹ����᷵��һ��fd������sock_fd�С���ʱwrite ���ݵ�sock_fd���ɽ����ݴ��䵽Զ���豸��

��3����MTK-Android�У�listen��connect�ӿڶ�����MTK������Э��ջbluetooth.blueangel.so��ʵ�ֵġ�������Դ��

��4������ͨ��socket����У�
������У�socket()��bind()��listen()��accept()��recv()��Щ���̡�
�ͻ����У�socket()��connect()��send()��Щ���̡�
������MTK-Android�У������ֻ��listen���ͻ���ֻ��connect����socket�ľ��������accept()�ȶ�����2���ӿڷ�װ���ˡ�

2��socket����ʵ��


BluetoothOppService.java
	startSocketListener
		mSocketListener.start(mHandler);
		
BluetoothOppRfcommListener.java
	public synchronized boolean start(Handler callback)
		 mBtServerSocket = mAdapter.listenUsingInsecureRfcommWithServiceRecord("OBEX Object Push", BluetoothUuid.ObexObjectPush.getUuid());
			createNewRfcommSocketAndRecord(name, uuid, false, false);
				socket.mSocket.bindListen();
					createSocketChannel(mType, mServiceName, mUuid, mPort, getSecurityFlags());
						com_android_bluetooth_btservice_AdapterService.cpp��createSocketChannelNative(type, serviceName, Utils.uuidToByteArray(uuid), port, flag);
		clientSocket = sSocket.accept();
			private BluetoothSocket acceptSocket(String RemoteAddr) throws IOException
			//ע�����ﲢû�е���socket��accept������


3�����ڶ�д���ݵĺ�����read/write/send/recv/readv/writev/sendmsg/recvmsg
��1��read/write
int read(int fd, void *buf, int nbyte);
int write(int fd, const void *buf, int nbyte);

��2��send/recv
int send( SOCKET s, const char *buf, int len, int flags);
int recv( SOCKET s, char *buf, int len, int flags);

send/recv��read/write�������������ڵ��ĸ�����flags�����flags=0��������read/write��ͬ��
���õ�flagΪ��MSG_NOSIGNAL����ֹ��ϵͳ�����쳣��Ϣ��

��3��readv/writev
����һ�ζ�д�����������
ssize_t readv(int filedes, const struct iovec *iov, int iovcnt);
ssize_t writev(int filedes, const struct iovec *iov, int iovcnt);

��4��sendto/recvfrom
ָ����ַ����/��������
�����ӵ����ݱ�socket��ʽ�£����ڱ���socket��û����Զ�˻����������ӣ������ڷ�������ʱӦָ��Ŀ�ĵ�ַ��
int sendto��int sockfd�� const void *msg��int len, unsigned int flags�� const struct sockaddr *to�� int tolen���� 
int recvfrom��int sockfd��void *buf��int len��unsigned int flags��struct sockaddr *from��int *fromlen���� 

��5��sendmsg/recvmsg
����λ�ã�frameworks\base\core\jni\android_net_LocalSocketImpl.cpp
�����Է���/���ո������ݡ�

�ȿ�sendmsg��
int sendmsg(int s, const struct msghdr *msg, unsigned int flags);


struct msghdr {
    void         *msg_name;
    socklen_t    msg_namelen;
    struct iovec *msg_iov;
    size_t     msg_iovlen;
    void       *msg_control;
    size_t     msg_controllen;
    int        msg_flags;
};
��1����Ա��
�׽ӿڵ�ַ��Ա��msg_name��msg_namelen��
I/O��������msg_iov��msg_iovlen��
�������ݻ�������Աmsg_control��msg_controllen��
������Ϣ���λmsg_flags��

��2����Աmsg_name��msg_namelen��
��Щ��Աֻ�е����ǵ��׽ӿ���һ�����ݱ��׽ӿ�ʱ����Ҫ��
msg_name��Աָ������Ҫ���ͻ��ǽ�����Ϣ���׽ӿڵ�ַ��
msg_namelenָ��������׽ӿڵ�ַ�ĳ��ȡ�
��������/�������ݲ���Ҫ�������

��3����Աmsg_iov��msg_iovlen��
��Щ��Աָ�������ǵ�I/O���������λ���Լ������������
msg_iovָ��һ��struct iovec���顣
msg_iovlenָ���������ǵ�I/O�����������ж���Ԫ�ء�
�����Աһ���������淢��/���յ����ݻ������ͳ��ȡ�

��һ��������ֵ��
uint8  buffer=0;
struct iovec iv;
memset(&iv, 0, sizeof(iv));
iv.iov_base = &buffer;
iv.iov_len = 1;
msghdr.msg_iov = &iv;
msghdr.msg_iovlen = 1;

��4����Աmsg_control��msg_controllen
��Щ��Աָ�������Ǹ������ݻ��������ұ����˻�������С��
msg_controlָ�������ݻ�������
msg_controllenָ���˻�������С��

��5����Աmsg_flags
MSG_EOR�������յ���¼��βʱ��������һλ����ͨ������SOCK_SEQPACKET�׽ӿ�����ʮ�����á�
MSG_TRUNC��������λ�������ݵĽ�β���ض̣���Ϊ���ջ�����̫С�����Խ���ȫ�������ݡ�
MSG_CTRUNC��������λ����ĳЩ��������(��������)���ض̣���Ϊ������̫С��
MSG_OOB��������λ���������˴������ݡ�
MSG_ERRQUEUE��������λ����û�н��յ����ݣ����Ƿ���һ����չ����

�õĽ϶��msg_flagsΪMSG_NOSIGNAL������Ϊ��
Linux �µ����ӶϿ������������ݵ�ʱ�򣬲��� send() �ķ���ֵ���з�ӳ�����һ�����ϵͳ����һ���쳣��Ϣ��
�����������������˳�������ڷ������ṩ�ȶ��ķ�����ɾ޴�����ѡ�
Ϊ�ˣ�send() ���������һ��������������Ϊ MSG_NOSIGNAL����ֹ send() ������ϵͳ���ͳ���Ϣ��


�ٿ�recvmsg��
int recvmsg(int s, struct msghdr *msg, unsigned int flags);
��sendmsg���ơ�

��4��CMSG��������
���ʸ������ݣ� CMSG_ALIGN, CMSG_SPACE, CMSG_NXTHDR, CMSG_FIRSTHDR

�������ݲ������׽��ָ��ص�һ���֡���Щ������Ϣ���ܰ����������ݰ��Ľӿڡ�����ʹ�õĸ��ֱ�ͷ�ֶΡ�����Ĵ���������һ���ļ���������Unixƾ�ݡ�
������˵��������Ϣ�������ڷ��Ͷ���ı�ͷ�ֶΣ�����IPѡ���������ͨ������sendmsg���ͣ�ͨ������recvmsg���ա�

CMSG������


#include <sys/socket.h>

struct cmsghdr *CMSG_FIRSTHDR(struct msghdr *msgh);
struct cmsghdr *CMSG_NXTHDR(struct msghdr *msgh, struct cmsghdr *cmsg);
size_t CMSG_ALIGN(size_t length);
size_t CMSG_SPACE(size_t length);
size_t CMSG_LEN(size_t length);
unsigned char *CMSG_DATA(struct cmsghdr *cmsg);

struct cmsghdr {
    socklen_t cmsg_len;    /* data byte count, including header */
    int       cmsg_level;  /* originating protocol */
    int       cmsg_type;   /* protocol-specific type */
    /* followed by unsigned char cmsg_data[]; */
};

CMSG_FIRSTHDR()������msghdr�����ĸ��������еĵ�һ��cmsghdr��ָ�롣
CMSG_NXTHDR()�����ز���ָ����cmsghdr֮�����һ����Ч��cmsghdr������������û���㹻�Ŀռ�ʱ��������NULL��
CMSG_ALIGN()������һ�����ȣ�������������Ķ���߽硣
CMSG_SPACE()������һ������������ռ�õ��ֽ�����
CMSG_DATA()������ָ��cmsghdr�����ݲ��ֵ�ָ�롣
CMSG_LEN()������cmsghdr�ṹ��cmsg_len��Ա��ֵ���������κα�Ҫ�Ķ��뷽ʽ�� �������ݳ�����Ϊ������


sendmsgʹ��CMSG�������ݷ���һ���ļ������������ݵ����ӣ�


int write_native(int fd, const void *buf, int nbyte)
{
    struct msghdr msg;
    unsigned char *buffer = (unsigned char *)buf;
    memset(&msg, 0, sizeof(msg));

    struct cmsghdr *cmsg;
    int countFds =3;
    int fds[countFds]={23,24,25};
    char msgbuf[CMSG_SPACE(countFds)];

    msg.msg_control = msgbuf;//ͨ���������ݷ����ļ���
    msg.msg_controllen = sizeof(msgbuf);
    cmsg = CMSG_FIRSTHDR(&msg);
    cmsg->cmsg_level = SOL_SOCKET;
    cmsg->cmsg_type = SCM_RIGHTS;
    cmsg->cmsg_len = CMSG_LEN(sizeof(fds));
    memcpy(CMSG_DATA(cmsg), fds, sizeof(fds));

    //����ֻ�ڵ�һ��write��ʱ���͸��������ļ���
    while (nbyte> 0){
        struct iovec iv;//ͨ��iv����������
        memset(&iv, 0, sizeof(iv));
        iv.iov_base = buffer;
        iv.iov_len = len;
        msg.msg_iov = &iv;
        msg.msg_iovlen = 1;

        do{
            ret = sendmsg(fd, &msg, MSG_NOSIGNAL);
        } while (ret < 0 && errno == EINTR);

        buffer += ret;
        nbyte -= ret;

        //�����msg�����Ը������� msg.msg_control ֻ����һ��
        memset(&msg, 0, sizeof(msg));
    }
    return 0;
}


recvmsgʹ��CMSG����һ���ļ������������ӣ�


��������Ƚ��ձ������ݺ��ļ���������Ȼ��������ļ���������

int read_native(int fd, void *buffer, int nbyte)
{
    ssize_t ret;
    ssize_t bytesread = 0;
    struct msghdr msg;
    struct iovec iv;
    uint8_t *buf = (uint8_t *)buffer;
    // Enough buffer for a pile of fd's. We throw an exception if this buffer is too small.
    struct cmsghdr cmsgbuf[2*sizeof(cmsghdr) + 0x100];//���ڱ��渨�������ļ�������

    memset(&msg, 0, sizeof(msg));
    memset(&iv, 0, sizeof(iv));

    iv.iov_base = buf;//���ݱ�����buf��
    iv.iov_len = nbyte;

    msg.msg_iov = &iv;
    msg.msg_iovlen = 1;
    msg.msg_control = cmsgbuf;
    msg.msg_controllen = sizeof(cmsgbuf);

    do {
        ret = recvmsg(fd, &msg, MSG_NOSIGNAL);
    } while (ret < 0 && errno == EINTR);

    if (ret < 0 && errno == EPIPE) {
        // Treat this as an end of stream
        return 0;
    }

    if (ret < 0) {
        return -1;
    }

    if ((msg.msg_flags & (MSG_CTRUNC | MSG_OOB | MSG_ERRQUEUE)) != 0) {
        // To us, any of the above flags are a fatal error
        return -1;
    }

    if (ret >= 0) {
        socket_process_cmsg(&msg);
    }
    return ret;
}

//����������
static int socket_process_cmsg(struct msghdr * pMsg)
{
    struct cmsghdr *cmsgptr;

    for (cmsgptr = CMSG_FIRSTHDR(pMsg); 
          cmsgptr != NULL; cmsgptr = CMSG_NXTHDR(pMsg, cmsgptr)) {

        if (cmsgptr->cmsg_level != SOL_SOCKET) {
            continue;
        }

        if (cmsgptr->cmsg_type == SCM_RIGHTS) {
            int *pDescriptors = (int *)CMSG_DATA(cmsgptr);
            int count = ((cmsgptr->cmsg_len - CMSG_LEN(0)) / sizeof(int));
            if (count < 0) {
                return -1;
            }
			
	    int *fd = (int *)malloc(sizeof(int)*count);
            if (fd == NULL) {
                return -1;
            }

            for (int i = 0; i < count; i++){
				fd[i]=pDescriptors[i];
            }
        }
    }
    return 0;
}

```




