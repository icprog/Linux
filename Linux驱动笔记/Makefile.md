Makefile

```c
һ������
1�� =	:=	?=	+=	������
=		��	��ֵ(������Makefile�ļ�չ�����پ���������ֵ)
:=		��	��ֵ(������ֵ����������Makefile�ļ��е�λ�ã�����������Makefile�ļ�չ���������ֵ)
?=		��	���û�и�ֵ�����Ͱ� = ֮���ֵ������
+=		��	׷��
=	��  :=  ������

x=foo
y=$(x) bar
x=xyz
�������棬 y=xyz bar

x:=foo
y:=$(x) bar
x:=xyz
�������棬 y=foo bar

һ��ʹ��	:=



��������
1�� filter ����
�÷��� $(filter	 PATTERN����   ,		TEXT)
���ã� ���� TEXT �з��� PATTERN ��ʽ���ַ��������û�з��ϵģ��򷵻ؿա�

2�� word ����
�÷���$(word  <n> ,    <text> )
���ã�ȡ�ַ��� text  �еĵ� n  ���ַ��� n  ��1��ʼ��

3�� sort ����
�÷���$(sort LIST)
���ã��� LIST �е��ַ���������������ȥ���ظ����ַ�����(������ĸΪ׼�Ƚϣ�����ĸ��ͬ���Դ���ĸΪ׼)
���ӣ�$(sort 	foo	bar	lose	   foo)
����ֵΪ��	"bar  foo  lose"

4�� strip ����
�÷��� $(strip <string> )
���ã� ȥ�� <string> �ִ��п�ͷ���м䡢��β�Ŀ��ַ��� 

5�� wildcard  ���� �������жϴ��ڻ��ǲ�����ĳһ·���µ��ļ�
�÷��� $(wildcard PATTERN...)
���ã� ��Makefile�У�����չ��Ϊ�Ѿ����ڵġ�ʹ�ÿո�ֿ��ġ�ƥ���ģʽ�������ļ��б�����������κη��ϴ�ģʽ���ļ������������ģʽ�ַ������ؿա�
���ӣ� $(wildcard 	$(IMGSENSOR_DRIVER_PATH)/$(MTK_PLATFORM)/camera_project/$(ARCH_MTK_PROJECT)/$(1))	�����ڲ����ڴ��ļ������Է��ؿա�

6�� eval  ����
�÷��� $(eval text)
���ã� text �����ݽ���Ϊmakefile��һ���ֶ���make������ִ��

7�� foreach  ����
�÷��� $( foreach  <var>,  <list>,  <text> )
���ã� 
�Ѳ���  <list>   �еĵ�����һȡ���ŵ�����  <var>  ��ָ���ı����У�Ȼ����ִ��  < text>  �������ı��ʽ��
ÿһ��  <text>  �᷵��һ���ַ�����ѭ�������У�<text>   �������ص�ÿ���ַ������Կո�ָ���
�������ѭ������ʱ��  <text>  �����ص�ÿ���ַ�������ɵ������ַ������Կո�ָ���������   foreach    �����ķ���ֵ��

$( foreach drv, gc2355_mipi_raw gc0310_mipi_yuv gc5025s_mipi_raw  ,  $(eval $(call FILTER_DRV,$(drv)))  )

8�� call  ����
�÷��� $(  call   <expression>,  <parm1>,  <parm2>,  <parm3>...  )
���ã� 
��makeִ���������ʱ�� <expression>  �����еı�������$(1)��$(2)��$(3)�ȣ��ᱻ�� �� <parm1>��<parm2>��<parm3>����ȡ����
<expression>  �ķ���ֵ����  call  �����ķ���ֵ��

9�� subset ����
�÷��� $(subst FROM,	 TO,  TEXT) 
���ã� ���ִ�  TEXT  �е�  FROM  �ַ��滻Ϊ TO  
���ӣ� $(subst $\",  ,   $(CONFIG_CUSTOM_KERNEL_IMGSENSOR)  )

10�� define �궨��
�÷��� 
define FILTER_DRV
endef
���ã� ����һ���������ϣ��������Զ�ִ�У�һ��ͨ�� call ���á�

define FILTER_DRV
ifeq ($(wildcard $(IMGSENSOR_DRIVER_PATH)/$(MTK_PLATFORM)/camera_project/$(ARCH_MTK_PROJECT)/$(1)), )

ifeq ($(wildcard $(IMGSENSOR_DRIVER_PATH)/$(MTK_PLATFORM)/$(1)), )
common_drv += ../common/$(COMMON_VERSION)/$(1)/					/* ������ common Ŀ¼�µ� camera ���� */
else
platform_drv += $(1)/				/* ������ mt6765 Ŀ¼�µ� camera ���� */	
endif

else
project_drv += ./camera_project/$(ARCH_MTK_PROJECT)/$(1)/       /* ������ camera_project Ŀ¼�µ� camera ���� */
endif

endef



��������(mt6739ƽ̨ imgsensor ����)

define FILTER_DRV
ifeq ($(wildcard $(IMGSENSOR_DRIVER_PATH)/$(MTK_PLATFORM)/camera_project/$(ARCH_MTK_PROJECT)/$(1)),)

ifeq ($(wildcard $(IMGSENSOR_DRIVER_PATH)/$(MTK_PLATFORM)/$(1)),)
common_drv += ../common/$(COMMON_VERSION)/$(1)/
else
platform_drv += $(1)/
endif

endif
endef


$(foreach drv,$(subst $\",,$(CONFIG_CUSTOM_KERNEL_IMGSENSOR)),$(eval $(call FILTER_DRV,$(drv))))

 ����>  $( foreach drv, gc2355_mipi_raw gc0310_mipi_yuv gc5025s_mipi_raw  ,  $(eval $(call FILTER_DRV,$(drv)))  )

���壺
����� imgsensor/src/mt6739/  ���Ŀ¼û�����õ� imgsensor ��
��ʹ�� imgsensor/src/common/v1/  �е� imgsensor ��
�� imgsensor/src/common/v1/  �У�ʹ�õ����� platform �޹ص� imgsensor ��
�� imgsensor/src/mt6739/ �У�ʹ�õ����� platform ��ص� imgsensor ��
```


