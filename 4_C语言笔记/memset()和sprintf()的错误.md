
```c
һ��memset��һ����������

char main_info[1024];
char * info=main_info;

memset(main_info,0,sizeof(main_info));//������飬��ȷʹ����memset��

info += sprintf(info, "%s%ds\n", "start camera test,test time:",test_time);
info += sprintf(info, "%s%ds\n","camera test pass, test time:", use_time);
info += sprintf(info, "%s%d\n","camera test count:", count);

memset(info,0,sizeof(char)*1024);
//��������ʱ����������AEE���󣬿����������ԭ������Ϊinfoָ��Ĳ����׵�ַ�ˣ���ָ���sizeû��1024.

1������ĵڶ���ԭ��
�ַ������ǿ��Ա��޸ĵģ����Զ�������ʹ��memset����ա�
�ַ���������ֻ���ģ������ܱ��޸ģ���memset�ֱ����޸�info�����Ի��������
�������ԣ��������˵���Ǵ���ġ���Ϊsnprintf���е��ǿ������������ַ���������ֵ�����鱣��������memset�Ƕ�������в����������޸��ַ���������

��1��char str1[] = "mediatek_camera_test";
str1��һ���ַ����飬���������һ�������ַ������Զ�str1ʹ��memset������ʵ�����ǽ����������ַ���������ȫ��/�ֲ����������б���������

��2�� char *str2 = "mediatek_camera_test";
str2�������һ���ַ������������ܶ�str2ʹ��memset����Ϊ���������һ���ַ���������ֻ���ģ��������޸ġ�ʵ����str2������ǳ������ַ������׵�ַ���������޸���ָ������ݡ�

����sprintf����
int sprintf( char *buffer, const char *format, [argument] ��);
���ܣ��Ѹ�ʽ��������д��ĳ���ַ�����������
����ֵ��
���󣺷���-1��
�ɹ������سɹ�д��buffer ���ֽ����������ַ���\0���������ڡ�
ʹ�÷�����

char	main_info[1024];
char * info=main_info;
memset(main_info,0,sizeof(main_info));//������飬��ȷʹ����memset��

info += sprintf(info, "%s%ds\n", "start camera test,test time:",test_time);
info += sprintf(info, "%s%ds\n","camera test pass, test time:", use_time);
info += sprintf(info, "%s%d\n","camera test count:", count);


���������ַ����� '\0'
1���ַ�������ַ�������������'\0'�ַ�����β��

```



