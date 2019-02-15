

```c
���� mtk lk Դ����



��.��صĽṹ��
1.���߳���صĽṹ��
struct list_node {
	struct list_node *prev;
	struct list_node *next;
};  /* ˫������ṹ��*/

typedef struct thread {
	int magic;
	struct list_node thread_list_node;

	/* active bits */
	struct list_node queue_node;
	int priority;
	enum thread_state state;	
	int saved_critical_section_count;
	int remaining_quantum;

	/* if blocked, a pointer to the wait queue */
	struct wait_queue *blocking_wait_queue;
	status_t wait_queue_block_ret;

	/* architecture stuff */
	struct arch_thread arch;

	/* stack stuff */
	void *stack;
	size_t stack_size;

	/* entry point */
	thread_start_routine entry;
	void *arg;

	/* return code */
	int retcode;

	/* thread local storage */
	uint32_t tls[MAX_TLS_ENTRY];

	char name[32];
} thread_t; /* �߳����ݽṹ */

2. BOOT_ARGUMENT ���ݽṹ
typedef struct {
  u32      maggic_number;
  BOOTMODE boot_mode;
  u32      e_flag;
  u32      log_port;
  u32      log_baudrate;
  u8       log_enable;
  u8       part_num;
  u8       reserved[2];
  u32      dram_rank_num;
  u32      dram_rank_size[4];
  mblock_info_t mblock_info;	/* number of mblock should be max rank number + 1 */
  dram_info_t orig_dram_info;
  mem_desc_t lca_reserved_mem;
  mem_desc_t tee_reserved_mem;
  u32      boot_reason;
  META_COM_TYPE meta_com_type;
  u32      meta_com_id;
  u32      boot_time;
  da_info_t da_info;
  SEC_LIMIT sec_limit;
  part_hdr_t *part_info;
  u8 md_type[4];
  u32  ddr_reserve_enable;
  u32  ddr_reserve_success;
  u32  ddr_reserve_ready;
  ptp_info_t ptp_volt_info;
  u32  dram_buf_size;
  u32  meta_uart_port;
  u32  smc_boot_opt;
  u32  lk_boot_opt;
  u32  kernel_boot_opt;
  u32 non_secure_sram_addr;
  u32 non_secure_sram_size;
  u32 dtb_addr;
  u32 dtb_size;
  char pl_version[8];
} BOOT_ARGUMENT;

3.struct boot_img_hdr ���ݽṹ
struct boot_img_hdr
{
    unsigned char magic[BOOT_MAGIC_SIZE];

    unsigned kernel_size;  /* size in bytes */
    unsigned kernel_addr;  /* physical load addr */

    unsigned ramdisk_size; /* size in bytes */
    unsigned ramdisk_addr; /* physical load addr */

    unsigned second_size;  /* size in bytes */
    unsigned second_addr;  /* physical load addr */

    unsigned tags_addr;    /* physical addr for kernel tags */
    unsigned page_size;    /* flash page size we assume */
    unsigned unused[2];    /* future expansion: should be 0 */

    unsigned char name[BOOT_NAME_SIZE]; /* asciiz product name */
    
    unsigned char cmdline[BOOT_ARGS_SIZE];

    unsigned id[8]; /* timestamp / checksum / sha1 / etc */
};




һ.���� kmain ����
void kmain(void)
{
	thread_init_early();
/* �̵߳������ʼ�������һ����Ϊ"bootstrap"���̵߳Ľṹ�壬�������߳���ӵ��̱߳� thread_list��
ע�⣬��ʱ��û�� create ����̣߳�����ֻ��ʼ���������ݽṹ��
������ current_thread Ϊ bootstrap_thread ����̡߳�
 */	

	arch_early_init();
/* armV7�ܹ���صĳ�ʼ�����Ƚ�ֹ cache������ vector ��ַ����ʼ�� mmu map��Ȼ��ʹ�� cache�� */

	platform_early_init();
/* ƽ̨���ڵ�Ӳ����ʼ��������Ŷ������ú�����*/
	
	call_constructors();
/* �ú�������� system-onesegment.ld �е�ַΪ __ctor_list �� __ctor_end ֮��� .ctors ������ */	

	heap_init();
/* ��ʼ���ѣ���ʼ�����Ŀ�ʼ��ַ�ͳ��ȡ�
����malloc������أ���ջ���ɲ���ϵͳ�����ģ��纯���ľֲ������ȡ�*/

	dpc_init();
/*dpc ��ʼ������Ҫ�Ĺ����У���ʼ��һ�� dpc event������ dpc �̡߳�
thread_resume(thread_create("dpc", &dpc_thread_routine, NULL, DPC_PRIORITY, DEFAULT_STACK_SIZE));
ʹ��thread_create�����������̣߳���״̬ΪTHREAD_SUSPENDED���߳�ִ�к���Ϊ dpc_thread_routine��
ʹ��thread_resume������ʹ���߳�״̬ΪTHREAD_READY��
��ʵ�ϣ� thread_create ��������һ��������̣߳� thread_resume �����������������̡߳�
���Ѻ󣬿�ʼִ���̺߳������̺߳���ִ����󣬷������������ lk ���ǵ��߳�ִ�еġ�
*/

	timer_init();
/* ��ʼ���ں˶�ʱ�������峬ʱ�ص������� */

	thread_resume(thread_create("bootstrap2", &bootstrap2, NULL, DEFAULT_PRIORITY, DEFAULT_STACK_SIZE));
/*����һ�� bootstrap2 ���̣߳��̺߳�������ڵ�ַΪ bootstrap2 ��
����������̺߳��� bootstrap2��
*/
	
	exit_critical_section();
/* �ú����Ĺ������뿪�ٽ�����ʹ���ж�*/	

	thread_become_idle();
/*���õ�ǰ����Ϊ idle ���н���*/
}



��.���� platform_early_init ����
void platform_early_init(void)
{
	unsigned int time_wdt_early_init;
	unsigned int time_pmic_init;
	unsigned int time_platform_early_init;

	platform_init_interrupts();
/* ��ʼ���жϣ��������ж���صļĴ����� */

	platform_early_init_timer();
/* ��ʼ����ʱ���������붨ʱ����صļĴ����� */

	mt_gpio_set_default();
/* �� GPIO ��صļĴ������á� */

	uart_init_early();
/* ��ʼ�� uart */

    hwinfo_init(HWINFO_ADDR);
/* �ж� hwinfo �ĵ�ַ�� HWINFO_MAGIC �Ƿ�� preloader �����ĵ�ַƥ�䡣��ȡ hwinfo ��ַ�洢�����ݵ� size ��
magic ��һ����ַ��־�����ڵ�ַ�����ֽڣ�����õ�ַ�ı�־�� */

	mtk_wdt_init();
/* ��ʼ�� wdt�������뿴�Ź���صļĴ����� */

#ifdef CONFIG_BSP_HWINFO
	int power_on_vibrator = 0;
	if (hwinfo_parser_fetch("vibrator", "power_on_vibrator", &(power_on_vibrator), 1) <= 0) {
    vibr_Enable_HW();
	} 
	else if (power_on_vibrator != 0){
		vibr_Enable_HW();
	} 
	else {
        ;
	}
/* ʹ�ܿ������� */
#endif

	pmic_init();
/* �ú���ʵ����ʲôҲû���� pmic �Ѿ��� preloader ��ʼ���� ??? */
}



��.���� bootstrap2 ����
static int bootstrap2(void *arg)
{
	platform_init();
/*ƽ̨��ʼ��������
�������ϸ�����ú���*/

	apps_init();
/*���������ú���*/
	
	return 0;
}




��.���� platform_init ����
void platform_init(void)
{
	u64 pl_start_addr = 0;
	plinfo_get_brom_header_block_size(&pl_start_addr);
/*�ú������ܣ�ʹ pl_start_addr= EMMC_HDR_BLK_SIZE ��
��ȡ preloader image �� offset in preloader partition
 */

	time_nand_emmc = get_timer(0);
/*��ʼ�� nand/emmc ��ʱ��ʼ��ʹ�� get_timer(0)����ʼ����ʱʱ�䡣*/

	mmc_legacy_init(1);
/* ��ʼ�� emmc ����Ҫ���������У���� struct mmc_host �� struct mmc_card �� block_dev_desc_t �� part_dev_t  
�⼸����emmc���豸��صĽṹ�壬Ȼ����ú��� mt_part_register_device ע��һ�� part_dev_t �ṹ�塣
���Ҵ�ӡ��������Ϣ��[SD0] boot device found */

	dprintf(INFO, "[PROFILE] ------- NAND/EMMC init takes %d ms -------- \n", (int)get_timer(time_nand_emmc));
/* ��� emmc ��ʼ���ķѵ�ʱ�䣬ʹ�� get_timer(time_nand_emmc) ����ȡʱ�䡣*/
	
	if (bldr_load_dtb("boot")<0)
		dprintf(CRITICAL, "bldr_load_dtb fail\n");
/*����dtb��DRAM��*/

	leds_init();
/*��ʼ��led�ƺͱ���*/

#ifdef CONFIG_BSP_HWINFO
	int power_on_vibrator = 0;

	if (hwinfo_parser_fetch("vibrator", "power_on_vibrator", &(power_on_vibrator), 1) <= 0) {
		vibr_Disable_HW();
	} 
	else if (power_on_vibrator != 0){
		vibr_Disable_HW();
	} 
	else {
        ;
	}
/*�ر�����*/
#endif

	env_init();
	print_env();
/*env��ʼ�������Ҵ�ӡ��env���������logΪ��
[LK_ENV]ENV SIG Wrong
[LK_ENV]no valid env
*/
	
	g_fb_size = mt_disp_get_vram_size();
/* ��ʾ�����������ʼ������һ�λ���ã�
pgc->plcm = disp_lcm_probe(NULL, LCM_INTERFACE_NOTDEFINED);
����ʼ��LCM����
*/
	g_fb_base = mblock_reserve(&g_boot_arg->mblock_info, g_fb_size, 0x10000, 0x100000000, RANKMAX);
	mt_disp_init((void *)g_fb_base);
	mt_disp_fill_rect(0, 0, CFG_DISPLAY_WIDTH, CFG_DISPLAY_HEIGHT, 0x0);
	mt_disp_update(0, 0, CFG_DISPLAY_WIDTH, CFG_DISPLAY_HEIGHT);
/*��Щ�������漰disp�����ĳ�ʼ��������һ����ϸ����*/

	sec_func_init(pl_start_addr);
	seclib_set_oemkey(g_oemkey, OEM_PUBK_SZ);
/* ��2������������ļ� platform/mt6735/lib/libsec.a ��ء������ǳ�ʼ��security library*/

	drv_video_init();
/*video ������ʼ��������CFB_888RGB_24BIT�ȡ�����ʾ��ص����á�*/

	boot_mode_select();
/*ѡ������ģʽΪNORMAL_BOOT������F_FACTORY_MODE��DOWNLOAD_BOOT����RECOVERY_BOOT*/

	mboot_common_load_logo((unsigned long)mt_get_logo_db_addr_pa(), "logo");
/*����logo���ú���ʵ�ʵ��� mboot_common_load_part("logo", logo_addr);������logo��ָ����ַ��*/	
	
	mt65xx_bat_init();
/*��ʼ�������ء�����Ƿ�͵�����*/	

	mt65xx_backlight_on();
/*��������*/

	mt_disp_update(0, 0, CFG_DISPLAY_WIDTH, CFG_DISPLAY_HEIGHT);
/*ˢ����ʾ*/

	sw_env();
/*	�ú������У�video_printf(" => NORMAL BOOT\n");
�����ֻ�������ʾ����ַ�����*/
}



��. ���� apps_init ����
void apps_init(void)
{
	const struct app_descriptor *app;

	/* call all the init routines */
	for (app = &__apps_start; app != &__apps_end; app++) {
		if (app->init)
			app->init(app);
	}

	/* start any that want to start on boot */
	for (app = &__apps_start; app != &__apps_end; app++) {
		if (app->entry && (app->flags & APP_FLAG_DONT_START_ON_BOOT) == 0) {
			start_app(app);
		}
	}
/*�� mt_boot.c �У��� 
APP_START(mt_boot)
.init = mt_boot_init,
 APP_END
 mt_boot_init ����ʵ���ϵ����� boot_linux_from_storage ������
 ��������� boot_linux_from_storage ����
 */
}



��. ���� boot_linux_from_storage ����
int boot_linux_from_storage(void)
{
	ret = mboot_android_load_bootimg_hdr("boot", CFG_BOOTIMG_LOAD_ADDR);
/*����boot image header��DRAM��*/

	kimg_load_addr = (g_boot_hdr!=NULL) ? g_boot_hdr->kernel_addr : CFG_BOOTIMG_LOAD_ADDR;

	ret = mboot_android_load_bootimg("boot", kimg_load_addr);
/*���� bootimg*/

	memcpy((char *)g_boot_hdr->ramdisk_addr, (char *)(g_rmem_off), g_rimg_sz);
	g_rmem_off =  g_boot_hdr->ramdisk_addr;
/*�ض��� rootfs*/

	custom_port_in_kernel(g_boot_mode, cmdline_get());
/*�޸�cmdline�Ĵ��ںţ��޸ĺ��cmdlineΪ��
"console=tty0 console=ttyMT0,921600n1 root=/dev/ram vmalloc=496M androidboot.hardware=mt6735 slub_max_order=0 slub_debug=O"
*/
	cmdline_append(cmdline_tmpbuf);
/*׷��cmdline*/

	boot_linux((void *)g_boot_hdr->kernel_addr, (unsigned *)g_boot_hdr->tags_addr, (char *)cmdline_get(), 
		board_machtype(), (void *)g_boot_hdr->ramdisk_addr, g_rimg_sz);
/*��lk����kernel��ֵ�ĺ���ֱ�Ϊ�� 
g_boot_hdr->kernel_addr��kernel��ַ
g_boot_hdr->tags_addr��   tag��ַ
cmdline_get()��					cmdline
board_machtype()��			MACH_TYPE
g_boot_hdr->ramdisk_addr��ramdisk��ַ
g_rimg_sz��						ramdisk��С
����߷��� boot_linux ����
*/
		
	while (1) ;
	return 0;
}



��. ���� boot_linux ����
void boot_linux(void *kernel, unsigned *tags,char *cmdline, unsigned machtype,void *ramdisk, unsigned ramdisk_size)
{
#ifdef DEVICE_TREE_SUPPORT
	boot_linux_fdt((void *)kernel, (unsigned *)tags, (char *)cmdline, machtype,(void *)ramdisk, ramdisk_size);
/*��Ű˷��� boot_linux_fdt ����*/
	
	while (1) ;
#endif
}



��. ���� boot_linux_fdt ����
int boot_linux_fdt(void *kernel, unsigned *tags,char *cmdline, unsigned machtype,void *ramdisk, unsigned ramdisk_size)
{
	void *fdt = tags;
	void (*entry)(unsigned,unsigned,unsigned*) = kernel;

	zimage_size = *(unsigned int *)((unsigned int)kernel+0x2c) - *(unsigned int *)((unsigned int)kernel+0x28);
	dtb_addr = (unsigned int)kernel + zimage_size;
	dtb_size = fdt32_to_cpu(*(unsigned int *)(dtb_addr+0x4));
/*zimage�Ĵ�С��dtb�ĵ�ַ�ʹ�С*/
	
	target_fdt_model(fdt);

	load_modem_image();

	ret = setup_mem_property_use_mblock_info(&mem_reg_property[0],sizeof(mem_reg_property)/sizeof(dt_dram_info));

	ret = target_fdt_dram_dummy_read(fdt, g_nr_bank);
	
	offset = fdt_path_offset(fdt, "/memory");

	ret = fdt_setprop(fdt, offset, "reg", mem_reg_property, ((int)get_mblock_num? get_mblock_num(): g_nr_bank ) * sizeof(dt_dram_info));
	
	ret = platform_atag_append(fdt);

	ret = fdt_memory_append(fdt);

	ret = trusty_dts_append(fdt);

	offset = fdt_path_offset(fdt, "/chosen");

	ret = fdt_setprop_cell(fdt, offset, "linux,initrd-start",(unsigned int) ramdisk);
	
	ret = fdt_setprop_cell(fdt, offset, "linux,initrd-end", (unsigned int)ramdisk + ramdisk_size);
	
	ret = fdt_setprop(fdt, offset, "atag,boot", buf, ptr - buf);

	ret = fdt_setprop(fdt, offset, "atag,imix_r", buf, ptr - buf);

	ptr = (char *)target_atag_mem((unsigned *)buf);
	ret = fdt_setprop(fdt, offset, "atag,mem", buf, ptr - buf);

	ptr = (char *)target_atag_partition_data((unsigned *)buf);	
	ret = fdt_setprop(fdt, offset, "atag,mem", buf, ptr - buf);

	ptr = (char *)target_atag_nand_data((unsigned *)buf);
	ret = fdt_setprop(fdt, offset, "atag,mem", buf, ptr - buf);

	ptr = (char *)target_atag_devinfo_data((unsigned *)buf);
	ret = fdt_setprop(fdt, offset, "atag,devinfo", buf, ptr - buf);
	����
/*����ĺ������ã�����dtb��д�뵽DRAMָ������*/	

	sprintf(cmdline,"%s%s",cmdline," printk.disable_uart=0 ddebug_query=\"file *mediatek* +p ; file *gpu* =_\"");
	
	hwinfo_add_cmdline(cmdline);
	sprintf(cmdline, "%s%s%d", cmdline, " boot_reason=", boot_reason);

	entry(0, machtype, tags);
/*��ת��kernel��ַ��ִ��kernel������Ĳ���Ϊ MACH_TYPE��tags�ĵ�ַ*/	

	while (1);
	return 0;	
}


************************************************************************************************************************************************
�������fdt�Ĵ��ݹ���
һ. ���� mt_boot_init
1.mt_boot_init ������
void mt_boot_init(const struct app_descriptor *app)
	boot_linux_from_storage();
		
2.boot_linux_from_storage ������
int boot_linux_from_storage(void)
{
	ret = mboot_android_load_bootimg_hdr("boot", CFG_BOOTIMG_LOAD_ADDR);
	kimg_load_addr = CFG_BOOTIMG_LOAD_ADDR;
	ret = mboot_android_load_bootimg("boot", kimg_load_addr);
	memcpy((char *)CFG_RAMDISK_LOAD_ADDR, (char *)(g_rmem_off), g_rimg_sz);
	g_rmem_off =CFG_RAMDISK_LOAD_ADDR;

	boot_linux((void *)CFG_BOOTIMG_LOAD_ADDR, (unsigned *)CFG_BOOTARGS_ADDR,
  (char *)g_cmdline, 6735, (void *)CFG_RAMDISK_LOAD_ADDR, g_rimg_sz);


}

#define DRAM_PHY_ADDR   0x40000000
#define CFG_RAMDISK_LOAD_ADDR           (DRAM_PHY_ADDR + 0x4000000)
#define CFG_BOOTIMG_LOAD_ADDR           (DRAM_PHY_ADDR + 0x8000)
#define CFG_BOOTARGS_ADDR               (DRAM_PHY_ADDR + 0x100)


int boot_linux_fdt(void *kernel, unsigned *tags, char *cmdline, unsigned machtype, void *ramdisk, unsigned ramdisk_size)
{
	void *fdt = CFG_BOOTARGS_ADDR;
	void (*entry)(unsigned,unsigned,unsigned*) = CFG_BOOTIMG_LOAD_ADDR;
	zimage_size = *(unsigned int *)((unsigned int)kernel+0x2c) - *(unsigned int *)((unsigned int)kernel+0x28);
	dtb_addr = (unsigned int)kernel + zimage_size;
	
	if (fdt32_to_cpu(*(unsigned int *)dtb_addr) == FDT_MAGIC) 
		dtb_size = fdt32_to_cpu(*(unsigned int *)(dtb_addr+0x4));
	
	strcpy(&buf[FDT_BUFF_SIZE], "BUFFEND");

	g_CMDLINE = cmdline;
	
	target_fdt_model(fdt);
/*���ã�
[7160] model=MT6737
*/	

	dt_dram_info mem_reg_property[128];
	ret = setup_mem_property_use_mblock_info(&mem_reg_property[0], 128);
	
	g_nr_bank = 3;
	ret = target_fdt_dram_dummy_read(fdt, g_nr_bank);
/*��dtsi�ļ��� reserved-memory ���*/	
	
/* Get offset of the memory node */	
	offset = fdt_path_offset(fdt, "/memory");
	ret = fdt_setprop(fdt, offset, "reg", mem_reg_property,  3* sizeof(dt_dram_info));
	
	ret = platform_atag_append(fdt);
	
/* Get offset of the chosen node */	
	offset = fdt_path_offset(fdt, "/chosen");
	
/* Adding the linux,initrd-start to the chosen node */	
	ret = fdt_setprop_cell(fdt, offset, "linux,initrd-start",(unsigned int) ramdisk);
	ret = fdt_setprop_cell(fdt, offset, "linux,initrd-end", (unsigned int)ramdisk + ramdisk_size);
	
/*�� fdt ������һ��������Ϊ "atag,boot" �Ľڵ㣬�洢��������*/	
	ptr = (char *)target_atag_boot((unsigned *)buf);
	ret = fdt_setprop(fdt, offset, "atag,boot", buf, ptr - buf);
	
	ptr = (char *)target_atag_imix_r((unsigned *)buf);
	ret = fdt_setprop(fdt, offset, "atag,imix_r", buf, ptr - buf);

	ptr = (char *)target_atag_mem((unsigned *)buf);
	ret = fdt_setprop(fdt, offset, "atag,mem", buf, ptr - buf);
	
	ptr = (char *)target_atag_partition_data((unsigned *)buf);
		if (ptr != buf) 
			ret = fdt_setprop(fdt, offset, "atag,mem", buf, ptr - buf);
	
	ptr = (char *)target_atag_devinfo_data((unsigned *)buf);
	ret = fdt_setprop(fdt, offset, "atag,devinfo", buf, ptr - buf);

	ptr = (char *)target_atag_videolfb((unsigned *)buf);
	ret = fdt_setprop(fdt, offset, "atag,videolfb", buf, ptr - buf);
	
	ptr = (char *)target_atag_mdinfo((unsigned *)buf);
	ret = fdt_setprop(fdt, offset, "atag,mdinfo", buf, ptr - buf);
	
	ptr = (char *)target_atag_ptp((unsigned *)buf);
	ret = fdt_setprop(fdt, offset, "atag,ptp", buf, ptr - buf);

	ptr = (char *)target_atag_masp_data((unsigned *)buf);
	ret = fdt_setprop(fdt, offset, "atag,masp", buf, ptr - buf);

	sprintf(cmdline,"%s%s",cmdline," printk.disable_uart=0 ddebug_query=\"file *mediatek* +p ; file *gpu* =_\"");
	
	hwinfo_add_cmdline(cmdline);
	
	pl_t = g_boot_arg->boot_time;
	sprintf(cmdline, "%s%s%d", cmdline, " bootprof.pl_t=", pl_t);
	
	lk_t = ((unsigned int)get_timer(boot_time));
	sprintf(cmdline, "%s%s%d", cmdline, " bootprof.lk_t=", lk_t);
	
	boot_reason = g_boot_arg->boot_reason;
	sprintf(cmdline, "%s%s%d", cmdline, " boot_reason=", boot_reason);
	
	sprintf(cmdline,"%s%s%s",cmdline," audio_verno=", AUDIO_VERNO);
	
	entry(0, machtype, tags);
/*tags �� fdt*/	
}

```
