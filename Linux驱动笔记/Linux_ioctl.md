
```c
1. ioctl �����ں��̻߳����û��̣߳�
������ͷ��kernel log���У�
<4>[  155.789506] .(2)[3185:AFthread]moveAF, 204.  move [curr] 8 [target] 108

���û��ռ�hal���д��룺
::prctl(PR_SET_NAME,"AFthread", 0, 0, 0);
�������������̵߳�����Ϊ AFthread ��

moveAF, 204.  move [curr] 8 [target] 108�����logλ��kernel��ioctl����moveAF()�С�

���ԣ�ioctlϵͳ���������û��ռ���̡߳�

2. �û��ռ���ִ��ioctlϵͳ����ʱ�����ô����������ں�̬����������߳���Ȼ�����û��ռ䡣

3. Ϊʲô��Ҫϵͳ���ã�
Linuxϵͳ��Ϊ�û�̬���ں�̬�����ȼ���ֱ�Ϊ1��0���ں�̬������ߵ�Ȩ�ޡ�
�û�̬����Դ����Ȩ���ܵ����ƣ��ں�̬����Դ����Ȩ�޲������ơ�
���ڰ�ȫ�Ŀ��ǣ�ĳЩ����ֻ�����ں˿ռ��н��У������Ӳ����صĲ������쳣���жϴ���
���û�̬���ں�̬���л������У����û�ջתΪ�ں�ջ�������ֳ����ܻ����������ġ�

4. �û�̬�л����ں�̬�ķ�ʽ��
1��ϵͳ���ã���read/write/malloc��
2���쳣����CPU���������û��ռ�ĳ���ʱ��������һ���쳣���ᵼ�µ�ǰ�����л��������쳣���ں˳����У������ں�̬�������û��ռ���ʿ�ָ�롣
3����Χ�豸���жϣ�
CPU����ִ���û����򣬴�ʱ���յ���һ���ж��źţ�CPU�ͻ��л����ں�̬ȥִ���жϴ������

5. ʹ�� ioctl ʱ�����õ� IOR �� IRW 
 _IO(type,nr) //û�в���������
_IOR(type,nr,size) //�������Ǵ�������ȡ����
_IOW(type,nr,size) //�������Ǵ�����д������
_IOWR(type,nr,size) //˫�����ݴ���


һ�� �� mtkcam LENS HAL�����Ϊ��

#define mcuIOC_G_MOTORINFO    				_IOR('A',0,mcuMotorInfo)
#define mcuIOC_T_MOVETO       						_IOW('A',1,u32)
#define mcuIOC_T_SETINFPOS    					_IOW('A',2,u32)
#define mcuIOC_T_SETMACROPOS  				_IOW('A',3,u32)
#define mcuIOC_G_MOTORCALPOS  			_IOR('A',4,mcuMotorCalPos)
#define mcuIOC_S_SETPARA      						_IOW('A',5,mcuMotorCmd)
#define mcuIOC_S_SETDRVNAME   				_IOW('A',10,mcuMotorName)
#define mcuIOC_G_MOTOROISINFO 			_IOR('A',12,mcuMotorOISInfo)




#define _IOR(type,nr,size)	_IOC(_IOC_READ,(type),(nr),(_IOC_TYPECHECK(size)))
#define _IOW(type,nr,size)	_IOC(_IOC_WRITE,(type),(nr),(_IOC_TYPECHECK(size)))


# define _IOC_WRITE	1U
# define _IOC_READ	2U

#define _IOC_TYPECHECK(t) (sizeof(t))

#define _IOC(dir,type,nr,size) \
	(((dir)  << _IOC_DIRSHIFT) | \
	 ((type) << _IOC_TYPESHIFT) | \
	 ((nr)   << _IOC_NRSHIFT) | \
	 ((size) << _IOC_SIZESHIFT))


#define _IOC_NRSHIFT	0
#define _IOC_TYPESHIFT	(_IOC_NRSHIFT+_IOC_NRBITS)       //8
#define _IOC_SIZESHIFT	(_IOC_TYPESHIFT+_IOC_TYPEBITS) //16
#define _IOC_DIRSHIFT	(_IOC_SIZESHIFT+_IOC_SIZEBITS)   //30



#define _IOC(dir,type,nr,size) \
	(((dir)  << 30) | \
	 ((type) << 8) | \
	 ((nr)   << 0) | \
	 ((size) << 16))

��/д		bit31~bit30 	2λΪ �������д�� ���������������Ƕ�ȡ�����д�����
size			bit29~bit16 	14λΪ "���ݴ�С" ������ʾ ioctl() �е� arg �������͵��ڴ��С��
type			bit15~bit08  	8λΪ ��ħ��"(Ҳ��Ϊ"����")�������ֵ�����������豸��������� ioctl �����������
nr			bit07~bit00    8λΪ "�������" �������������������˳����š�




ioctl ���ݲ�����

1������Ϊ���ͣ�kernel�п���ֱ��ʹ��������ݣ�
2������Ϊָ�룬kernel�б���ʹ�� cpoy_from_user()  ��  cpoy_to_user()

3����������ʱ��һ��ʹ�� _IO 
 _IO(type,nr) //û�в���������
_IOR(type,nr,size) //�������Ǵ�������ȡ����
_IOW(type,nr,size) //�������Ǵ�����д������
_IOWR(type,nr,size) //˫�����ݴ���


4�� ��Ϊֻ�д���ָ��ʱ���Ż�ʹ�� _IOR �� _IOW �� _IOWR ���������� kernel �л�ʹ�� cpoy_from_user �� cpoy_to_user ���������İ�ȫ�ԣ�������⴫�Ρ�


5�� cpoy_from_user �� cpoy_to_user �����ã���������û��ռ䴫���ں˿ռ��ָ���Ƿ�ȫ��

6��һ���ں˿ռ䶼���Է����û��ռ�ĵ�ַ��

```


