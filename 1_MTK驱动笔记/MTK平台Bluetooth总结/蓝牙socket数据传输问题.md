

```c
һ����������˶��������ݵ����⣺

1. �ڿͻ��ˣ����ã�


//socke=23
socket = bt_status_t (*connect)(const bt_bdaddr_t *bd_addr, btsock_type_t type, const uint8_t* uuid, int channel, int* sock_fd, int flags);
lens=write(socket, (char *)sendbuffer, SEND);


2. �ڷ���ˣ����ã�


sock = bt_status_t (*listen)(btsock_type_t type, const char* service_name, const uint8_t* service_uuid, int channel, int* sock_fd, int flags);
lens=read(sock, recvbuffer, MAX);  	�����˿ͻ��˵ĵ�ַ��10 00 11 11 B6 65 80 01 19
lens=read(27, recvbuffer, MAX); 	�����˿ͻ��˷��������ݣ�55 66 77 88 99


3. �鿴log��


I/        (  236): btmtk_jsr82_int_compose_record: name=OBEX Object Push, channel=23 
E/Bluetooth(  236): accept socket3 fd = 23
I/        (  236): [JSR82][EXT]jbt_session_attach fd:27
I/        (  236): [JSR82] jbt_jsr82_channel_connected: channel: 23, session fd[24], subsessionfd[27]
I/        (  236): [session][stream]write_control_socket, fd 24, ctl 27, len 4, datalen 16, CMSG_SPACE(1)[16]


4.�ܽ�
(1)�������fd=27�Ǳ仯�ģ�����һ������ctl���Ǹ�fd��
(2)�ͻ����ڳɹ�connect�������ʱ���������˷���һ��sendmsg�����оͰ���������fd��
(3)�����ڷ����ʹ��recvmsg�������ͻ��˷���������fd��Ȼ��read�����Ϳ��Եõ��ͻ��˷�������˵������ˡ�

```

