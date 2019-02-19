

```c
һ�� MTK
MTKоƬ�ڲ���һ��BootRom��һ��ISRAM
��������Ϊ��BootRom ��preloader��   lk��kernel��Android

�����ֻ��ڴ�ĸ��
1. �����ڴ�RAM(���8G)
RAM���ص㣺�������ݶ�ʧ
��չ���̣�SDRAM ��  DDR  ��LPDDR

2. ROM(���256G)
�洢�ֻ������ݣ��������ݲ��ᶪʧ���ֻ���preloader,lk,bootimage,systemimage���Ǵ洢��ROM�С�
��չ���̣�Nand  Flash  ��  Nor Flash�� eMMC��Nand����оƬ����UFS

���� MTK�������̣�
1. �ֻ��ϵ������bootROM�еĳ���bootROM��ʼ��eMMC��Ȼ�� eMMC�е� preloader���ص�MTK���ڲ� ISRAM �У�Ȼ������preloader.
2. Preloader���ȳ�ʼ��DDR��Ȼ�� eMMC�е� lk ���ص� DDR�У�Ȼ������ DDR ��ִ�� lk.
3. lk ��eMMC �е� bootimage��Linux kernel�� RamDisk���ļ�ϵͳ�����ص� DDR�У�ִ��kernel.
4. Kernel����init���̣�����Android


�ģ� ��������
1. BootROM����Ҫ������
       ARM Cores execute from RESET vector��
       ��ʼ��оƬ�ڲ�SRAM��stack��
       �ҵ��ͳ�ʼ������ý�飨����eMMC����
       ������ý�����preloader���ڲ�SRAM��
       ����preloaderִ�С�

2. preloader����Ҫ������
       ��ʼ��C��������ʼ���Ĵ�������ʼ����ջ��BSS�Σ���ֹIRQ
       ��ʼ���ؼ�Ӳ������ʼ��Timer, clocks, UART, EMI for external DRAM
       Security setup��Only loads MTK-certified binary
       ����  lk

Preloader��صĴ��룺
idh.code/vendor/mediatek/proprietary/bootable/bootloader/preloader/platform/mt6735/src/init/ init.s
idh.code/vendor/mediatek/proprietary/bootable/bootloader/preloader/platform/mt6735/src/core/main.c   partition.c
idh.code/vendor/mediatek/proprietary/bootable/bootloader/preloader/platform/mt6735/src/drivers/platform.c







3. lk ����Ҫ������
������preloader�������Ĳ�����
ʹ��MMU cache
ʹ�����裻
��������ģʽ��
����kernel��
����kernelִ�У�����   lk/app/mt_boot/mt_boot.c /Boot_linux_from_storage����������ת��Linux Kernel�����ٷ��ء�

LK������ATAG�Ľṹ��Kernel ���Ρ�
ATAG������ATAG_CORE��ʼATAG_NONE����������Bank����ATAG_MEM����
����Kernel ǰ����ر�DCACHE�ͽ���MMU��Ȼ������kernel��
PCָ��CFG_BOOTIMG_LOAD_ADD��Kernel���ڵ�ַ������machtype��tags��ַ�ֱ����R1��R2��R0Ϊ0��

Lk��صĴ��룺
idh.code/vendor/mediatek/proprietary/bootable/bootloader/lk/arch/arm/crt0.s
vendor/mediatek/proprietary/bootable/bootloader/lk/kernel/main.c    thread.c
vendor/mediatek/proprietary/bootable/bootloader/lk/platform/mt6735/platform.c
vendor/mediatek/proprietary/bootable/bootloader/lk/app/app.c
vendor/mediatek/proprietary/bootable/bootloader/lk/app/mt_boot/mt_boot.c






preloader��lk�Ĳ������ݣ�
preloader�Ĳ�����
vendor/mediatek/proprietary/bootable/bootloader/preloader/platform/mt6735/src/drivers/inc/platform.h     �нṹ��boot_arg_t��
vendor/mediatek/proprietary/bootable/bootloader/preloader/platform/mt6735/src/drivers/platform.c     �Բ�����ֵ
lk�Ĳ�����
vendor/mediatek/proprietary/bootable/bootloader/lk/platform/mt6735/include/platform/boot_mode.h   �нṹ��BOOT_ARGUMENT
vendor/mediatek/proprietary/bootable/bootloader/lk/kernel/main.c  �е�kamin��������ȡ����ֵ

4. Linux kernel��ʼ��
Entry point----stext
	����
����__create_page_tables �Ӻ���������һ��ҳ����Ϊ�ں˴����õĶ��������ַ����ʹ��֮ǰ���Ǳ���Ҫ����MMU�������MMUֻ��Ҫ������ҳ����ʶ���ں˴����ⲿ�ֵ������ַ�͹��ˡ���ҳ��4 GB �ĵ�ַ�ռ�ֳ����ɸ�1 MB�Ķ�(section)��ÿ��ҳ������32 bits(4 bytes)�������ҳ��ռ��
 4096 *4 = 16k���ڴ�ռ䡣
����
Start Kernel
Boot param
Kthread
Kernel_init()
Init.rc		������������ִ��android���׸�����init

��صĴ��룺
idh.code/kernel-3.18/arch/arm/kernel/head.s  head-common.s
5. UART������Ϣ����������?
idh.code/vendor/mediatek/proprietary/bootable/bootloader/preloader/platform/mt6735/src/drivers/platform.c  �е�CFG_UART_LOG ��
vendor/mediatek/proprietary/bootable/bootloader/preloader/custom/top6737t_36_a_n/cust_bldr.mak �иú궨��

6.Ϊ��ENG�汾��ʾ�׸���۽logo�����½ǵ�bootmode, USER����ʾ��
vendor/mediatek/proprietary/bootable/bootloader/lk/platform/mt6735/platform.c��
�к�NORMAL_BOOT


�����ڴ�֪ʶ��
BSS�Σ�������ų�����δ��ʼ����ȫ�ֱ�����һ���ڴ��������ھ�̬�ڴ���䡣
���ݶΣ�������ų������ѳ�ʼ����ȫ�ֱ�����һ���ڴ��������ھ�̬�ڴ���䡣
����Σ�������ų���ִ�д����һ���ڴ������ⲿ������Ĵ�С�ڳ�������ǰ���Ѿ�ȷ���������ڴ�����ͨ������ֻ��, ĳЩ�ܹ�Ҳ��������Ϊ��д���ڴ�����У�Ҳ�п��ܰ���һЩֻ���ĳ��������������ַ��������ȡ�
�ѣ�heap�����������ڴ�Ž��������б���̬������ڴ�Σ����Ĵ�С�����̶����ɶ�̬���Ż������������̵���malloc�Ⱥ��������ڴ�ʱ���·�����ڴ�ͱ���̬��ӵ����ϣ��ѱ����ţ���������free�Ⱥ����ͷ��ڴ�ʱ�����ͷŵ��ڴ�Ӷ��б��޳����ѱ�������
ջ(stack)��ջ�ֳƶ�ջ�� ���û���ų�����ʱ�����ľֲ�������Ҳ����˵���Ǻ���������{}���ж���ı�������������static�����ı�����static��ζ�������ݶ��д�ű��������������⣬�ں���������ʱ�������Ҳ�ᱻѹ�뷢����õĽ���ջ�У����Ҵ������ý����󣬺����ķ���ֵҲ�ᱻ��Ż�ջ�С�����ջ���Ƚ��ȳ��ص㣬����ջ�ر𷽱���������/�ָ������ֳ���
ջ��stack���Ͷѣ�heap��������
ջ��stack���ɱ������Զ������ͷ� ����ź����Ĳ���ֵ���ֲ�������ֵ��
�ѣ�heap�� һ���ɳ���Ա�����ͷţ� ������Ա���ͷţ��������ʱ������OS����
```


