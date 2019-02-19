


һ�� container_of ��ʵ�֣�

```c
#define container_of(ptr, type, member) ({			\
	const typeof( ((type *)0)->member ) *__mptr = (ptr);	\
	(type *)( (char *)__mptr - offsetof(type,member) );})

1��ptr��һ��ָ��ṹ���Աmember��ָ�룬 type �ǽṹ������ͣ�member�ǽṹ���е�ĳ����Ա�����ơ�
����귵�ص��������ṹ����׵�ַ�����֪��ĳ���ṹ����Ԫ�ص�ָ�룬���Ը����������������ṹ����׵�ַ��

2��GCC�Ա�׼C����չ�﷨ ({}) ��  x = ({1;2;}); x��ֵΪ2��

3�� 
const typeof( ((type *)0)->member ) *__mptr = (ptr);
//��ýṹ���Ա member �����ͣ�Ȼ������������һ����ʱָ�룬��ptr��ֵ���������ʱָ�롣��������Ŀ���Ǳ���Դ����ptrֱ�ӽ��в�����

(type *)( (char *)__mptr - offsetof(type,member) );
//��__mptr��ȥmember��ƫ��������Ϊ����ṹ����׵�ַ������Ϊ type *��

4���������ļ򵥻�����
 #define container_of(ptr, typex, member) (typex *) ( (size_t)ptr- offsetof(typex, member) ) 
```

���� offsetof ��ʵ��

```c
#define offsetof(TYPE, MEMBER)	((size_t)&((TYPE *)0)->MEMBER)

TYPE�ǽṹ������ͣ�MEMBER�ǽṹ���е�һ����Ա��offset�귵�ص���MEMBER��TYPE�ṹ����������׵�ַ��ƫ������

(TYPE *)0 ����0ǿ��ת����һ��ָ�룬���ָ��ָ�������Ϊ TYPE ��
��Ȼ0��һ���Ƿ�ָ�룬Ȼ���˴���û��������������ڴ���ʣ������ڣ���ֻ����������м��㣨�����ڣ������Բ�������κγ������

((TYPE *)0)->MEMBER ,ͨ��ָ�������ʽṹ���г�Աmember��
&((TYPE *)0)->MEMBER ���õ�member��Ա�ĵ�ַ����Ϊ�ṹ����׵�ַΪ0������member��Ա�ĵ�ַ����member��Ա����ڽṹ���׵�ַ��ƫ������
```

