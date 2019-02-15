

```c
���� mtk preloader Դ����



��.��صĽṹ�壺
1.struct bldr_command_handler �ṹ�壺
struct bldr_command_handler {
    void *priv;
    u32   attr;
    bldr_cmd_handler_t cb;  /* bldr_cmd_handler_tΪһ������ָ�룬������ʾ��*/
};
typedef bool (*bldr_cmd_handler_t)(struct bldr_command_handler *handler, struct bldr_command *cmd, struct bldr_comport *comm);

2. bl_param_t �ṹ�壺
typedef struct {
    u32 ver;
    u32 hdr_blk_dev_addr;
    hdrblk_info_t hdr_blk_info[4];        
    bl_info_t bl_loadinfo[MAX_BL_NUM];
    u32 brom_flags;
    u32 meid[ME_IDENTITY_LEN>>2];
} bl_param_t;

3.boot_arg_t �ṹ��
typedef struct {
    u32 magic;
    boot_mode_t mode;
    u32 e_flag;
    u32 log_port;
    u32 log_baudrate;
    u8  log_enable;
    u8  part_num;
    u8  reserved[2];
    u32 dram_rank_num;
    u32 dram_rank_size[4];
    mblock_info_t mblock_info;	/* number of mblock should be max rank number + 1 */
    dram_info_t orig_dram_info;
    mem_desc_t lca_reserved_mem;
    mem_desc_t tee_reserved_mem;
    u32 boot_reason;
    u32 meta_com_type;
    u32 meta_com_id;
    u32 boot_time;
    da_info_t da_info;
    SEC_LIMIT sec_limit;
    part_hdr_t *part_info;
    u8  md_type[4];
    u32  ddr_reserve_enable;
    u32  ddr_reserve_success;
	ptp_info_t ptp_volt_info;
    u32  dram_buf_size;
    u32  meta_uart_port;
    u32  smc_boot_opt;
    u32  lk_boot_opt;
    u32  kernel_boot_opt;
    u32 non_secure_sram_addr;
    u32 non_secure_sram_size;
    char pl_version[8];
} boot_arg_t;


4.boot_tag �ṹ��
typedef struct {
    struct boot_tag_header hdr;
    union {
        struct boot_tag_boot_reason boot_reason;
        struct boot_tag_boot_mode boot_mode;
        struct boot_tag_meta_com meta_com;
        struct boot_tag_log_com log_com;
        struct boot_tag_mem mem;
        struct boot_tag_md_info md_info;
        struct boot_tag_boot_time boot_time;
        struct boot_tag_da_info da_info;
        struct boot_tag_sec_info sec_info;
        struct boot_tag_part_num part_num;
        struct boot_tag_part_info part_info;
        struct boot_tag_eflag eflag;
        struct boot_tag_ddr_reserve ddr_reserve;
        struct boot_tag_dram_buf dram_buf;
        struct boot_tag_boot_opt boot_opt;
        struct boot_tag_sram_info sram_info;
        struct boot_tag_ptp ptp_volt;
        struct boot_tag_dtb_info dtb_info;
        struct boot_tag_pl_version pl_version;
    } u;
}boot_tag;

5.dram_buf_t �ṹ��
typedef struct{
    part_hdr_t   part_info[PART_MAX_NUM];
    part_t  partition_info[128];
    struct part_meta_info meta_info[128];
    boot_arg_t bootarg; /* ��������*/
    u8 log_dram_buf[LOG_BUFFER_MAX_SIZE];
    boot_tag *boottag; /*boot args pass to LK by ATAG*/
} dram_buf_t;




һ.main������

static bl_param_t *bldr_param = NULL;

void main(u32 *arg)
{
    struct bldr_command_handler handler;
    u32 jump_addr, jump_arg;

    /* get the bldr argument */
    bldr_param = (bl_param_t *)*arg;

    mtk_uart_init(UART_SRC_CLK_FRQ, CFG_LOG_BAUDRATE);
/*mtk���ڳ�ʼ�������� ʱ��Ϊ12000000��������Ϊ921600��
UART_SRC_CLK_FRQ �궨��Ϊ 12000000 ��CFG_LOG_BAUDRATE �� default.mak �ж���Ϊ 921600��
��preloader�У������ڴ�����δ�ҵ��ĺ꣬������ platform/mt6735/default.mak ���ҵ������磬CFG_UART_LOG :=UART1
*/
	
    bldr_pre_process();
/* ���������Ŷ��з��� bldr_pre_process ���� */

    handler.priv = NULL;
    handler.attr = 0;
    handler.cb   = bldr_cmd_handler;
/* bldr_cmd_handler �������ݴ����cmd��������Ӧ�����úʹ���*/
	
    bldr_handshake(&handler);
/* ����usb_handshake��������usb�������ӣ��������� g_meta_com_type = META_USB_COM;*/

    sec_boot_check();
/* ����ʱ�İ�ȫ�Լ�� */
	 
    device_APC_dom_setup();
/* APC��ʼ��*/
	
#if CFG_ATF_SUPPORT
    trustzone_pre_init();
/* ���֧��ATF����ʼ��trustzone */	
#endif

   bldr_load_images(&jump_addr)��
 /* ��lk��emmc�м��ص�DRAM��ȥ������ķ����ú���
�����ú�����jump_addrΪlk����ڵ�ַ
 */

    bldr_post_process();
/* �ú���������platform_post_init���������������ú��� */	

#if CFG_ATF_SUPPORT
    trustzone_post_init();
/* ��ʼ��trustzone(��TEE��ATF���) */
#endif

#if CFG_BOOT_ARGUMENT_BY_ATAG
    jump_arg = (u32)&(g_dram_buf->boottag);
/* jump_arg �б�����bootargs ��������ATAG����ʽ���档�õ�ַ���ᴫ��lk*/	
#endif

#if CFG_ATF_SUPPORT
    /* 64S3,32S1,32S1 (MTK_ATF_BOOT_OPTION = 0)
	 * pre-loader jump to LK directly and then LK jump to kernel directly */
    if ( BOOT_OPT_64S3 == g_smc_boot_opt &&
         BOOT_OPT_32S1 == g_lk_boot_opt &&
         BOOT_OPT_32S1 == g_kernel_boot_opt) {
        print("%s 64S3,32S1,32S1, jump to LK\n", MOD);
        bldr_jump(jump_addr, jump_arg, sizeof(boot_arg_t));
    } else {
        print("%s Others, jump to ATF\n", MOD);
        bldr_jump64(jump_addr, jump_arg, sizeof(boot_arg_t));
/* ����ATFִ�У�jump_addr Ϊlk����ڵ�ַ��jump_arg��ATAG��ʽ��bootargs�����ĵ�ַ
��������� bldr_jump64 ����
*/		
    }
#endif
}




��.���� bldr_pre_process ����

1.��صĽṹ�壺
typedef enum {
    NORMAL_BOOT         = 0,
    META_BOOT           = 1,
    RECOVERY_BOOT       = 2,
    SW_REBOOT           = 3,
    FACTORY_BOOT        = 4,
    ADVMETA_BOOT        = 5,
    ATE_FACTORY_BOOT    = 6,
    ALARM_BOOT          = 7,
    FASTBOOT            = 99,
    DOWNLOAD_BOOT       = 100,
    UNKNOWN_BOOT
} boot_mode_t;

2.bldr_pre_process�����壺

boot_mode_t g_boot_mode;

static void bldr_pre_process(void)
{
    int isLocked = 0;
	
    platform_safe_mode(1, CFG_EMERGENCY_DL_TIMEOUT_MS);
/* CFG_EMERGENCY_DL_TIMEOUT_MS=1000*5
�ú���������wdt Reset����ؼĴ���
 */
	
    platform_pre_init();
/* ����������ú��� */

    g_boot_mode = NORMAL_BOOT;
    platform_init();
/* ����Ӳ����ʼ�����жϴ�nand����mmc��������ʼ������ý��mmc������DDR������mmc��(ʹ���Լ����õĻ���mtk��)
��ʼ��EMI����ʼ��dram buffer����ʼ��ram console���ж��Ƿ����preloader������ģʽ������dram����Ϣ��bootarg��
 */	
	
#ifdef CONFIG_BSP_FLASH
	emi_write_ddr_para_2_block();
/* ����DDR������mmc��  */
#endif

    part_init();
/*  ��ʼ��partition */	

    log_buf_ctrl(1); /* switch log buffer to dram */
/* log��������  */
}



��.  ����platform_pre_init();
void platform_pre_init(void)
{
	mtk_timer_init();
/*��ʼ����ʱ��*/
	
	g_boot_time = get_timer(0);
/*��ʼ������ʱ��Ϊ0 */	
	
	mt_pll_init();
/*��ʼ��pll*/
	
	mtk_uart_init(12000000, 921600);
/*������pll�����³�ʼ������ʱ�ӺͲ����ʡ����ô��ں󣬿�����log�п�����������������롣*/
	
	clk_buf_all_on();
/*������ʱ��*/
	
	pwrap_init_preloader();
/*��ʼ��pmic wrapper*/
	
	pmic_ret = pmic_init();
/*��ʼ��pmic,�ú������������´��룺    
print("[pmic_init] Preloader Start,MT6328 CHIP Code = 0x%x\n", get_MT6328_PMIC_chip_version());
�ڴ���log���Կ�����
�ú������������Ƿ���ڣ�����ص�ѹ�ͳ���ѹ�����������log��
*/

    mt_pll_post_init();
/*after pmic_init*/

    PMIC_enable_long_press_reboot();
/* ʹ�ܳ�������������*/

    platform_core_handler();
/* CPU�������������8��CPU����(8��)*/

    ptp_init();
/* ��ʼ��ptp*/
}



��.���� bldr_load_images ����
static int bldr_load_images(u32 *jump_addr)
{
    blkdev_t *bootdev;
	bootdev = blkdev_get(BOOTDEV_SDMMC);
/* ��������豸��Ϣ */	

#ifdef CFG_LOAD_UBOOT
#ifdef CONFIG_BSP_HWINFO
    addr = CFG_HWINFO_MEMADDR;
    ret = bldr_load_part("HWINFO", bootdev, &addr, &size);
/* ����HWINFO��Ϣ��DRAM*/
	if(ret == -1)
    	ret = bldr_load_part("hwinfo", bootdev, &addr, &size);
#endif

    addr = CFG_UBOOT_MEMADDR;
    ret = bldr_load_part("lk", bootdev, &addr, &size);
/* ����lk��DRAM��*/
    if (ret)
       return ret;
    *jump_addr = addr;
/* ����ת��ַjump_addr��Ϊlk����ڵ�ַ*/
#endif
	
#if CFG_ATF_SUPPORT
    addr = CFG_ATF_ROM_MEMADDR;
    ret = bldr_load_tee_part("tee1", bootdev, &addr, 0, &size);
/* ����tee1��DRAM��*/

    if (ret) {
        addr = CFG_ATF_ROM_MEMADDR;
        ret = bldr_load_tee_part("tee2", bootdev, &addr, 0, &size);
/* ����tee1ʧ��ʱ�������tee2��DRAM��*/
        if (ret)
    	    return ret;        
    }

    print("%s bldr load tee part ret=0x%x, addr=0x%x\n", MOD, ret, addr);

    addr = CFG_BOOTIMG_HEADER_MEMADDR;
    size = 0x100;
    bldr_load_bootimg_header("boot", bootdev, &addr, 0, &size);
/* ����bootimageͷ��DRAM��*/

    print("%s part_load_images ret=0x%x\n", MOD, ret);
#endif
}



��.����platform_post_init����
void platform_post_init(void)
{
#if CFG_BATTERY_DETECT

    /* normal boot״̬ʱ������ش��ڻ�� */
    if (g_boot_mode == NORMAL_BOOT && !hw_check_battery() && usb_accessory_in()) {
        print("%s Wait for battery inserted...\n", MOD);
       
	   /* ��ֹ���led�� */
        pl_close_pre_chr_led();
		
        /* ʹ��ǿ�Ƴ��ģʽ */
        pl_charging(1);
		
        do {
            mdelay(300);
            /* check battery exists or not */
            if (hw_check_battery())
                break;
/* ѭ��������Ƿ���ڣ�����⵽�����غ��˳�ѭ��*/

            /* kick all watchdogs */
            platform_wdt_all_kick();
        } while(1);
		
        /* ��ֹǿ�Ƴ��ģʽ */
        pl_charging(0);
    }
	
    /* Disable usb download wo battery */
    pmic_disable_usbdl_wo_battery();
#endif

    platform_parse_bootopt();
/* �ú�����Ҫ������ smc��lk��kernel������־λ�����飬��main���������������������־λ���ж��Ƿ�����ATF */
    
	platform_set_boot_args();
/* �ú�������    platform_set_boot_args_by_atag(&(g_dram_buf->boottag)); 
����bootargs�������ò�����ATAG����ʽ����lk��bootargs�Ķ���Ϊ��
#define bootarg  g_dram_buf->bootarg
*/
}

boot_tag�Ķ���Ϊ��
typedef struct {
    struct boot_tag_header hdr;
    union {
        struct boot_tag_boot_reason boot_reason;
        struct boot_tag_boot_mode boot_mode;
        struct boot_tag_meta_com meta_com;
        struct boot_tag_log_com log_com;
        struct boot_tag_mem mem;
        struct boot_tag_md_info md_info;
        struct boot_tag_boot_time boot_time;
        struct boot_tag_da_info da_info;
        struct boot_tag_sec_info sec_info;
        struct boot_tag_part_num part_num;
        struct boot_tag_part_info part_info;
        struct boot_tag_eflag eflag;
        struct boot_tag_ddr_reserve ddr_reserve;
        struct boot_tag_dram_buf dram_buf;
        struct boot_tag_boot_opt boot_opt;
        struct boot_tag_sram_info sram_info;
        struct boot_tag_ptp ptp_volt;
        struct boot_tag_dtb_info dtb_info;
        struct boot_tag_pl_version pl_version;
    } u;
}boot_tag;



��. ���� bldr_jump64����
/*  ʵ��Ϊ�� bldr_jump64(jump_addr, jump_arg, sizeof(boot_arg_t)); */
void bldr_jump64(u32 addr, u32 arg1, u32 arg2)
{
	platform_wdt_kick();
/* restart wdt */

    platform_safe_mode(0, 0);
/* ��ֹ preloader��ȫģʽ*/

#if CFG_ATF_SUPPORT
    trustzone_jump(addr, arg1, arg2);
#endif
}

������ trustzone_jump������
void trustzone_jump(u32 addr, u32 arg1, u32 arg2)
{
    tee_sec_config();
/*��tee��ص����ã���secro.img���*/
	
    jumparch64(addr, arg1, arg2, ATF_BOOT_ARG_ADDR);
/* ATF_BOOT_ARG_ADDR = 0x00101000*/
}

������ jumparch64 �Ķ��壬�� preloaderĿ¼��init.s�ļ��У�
jumparch64:
    MOV r4, r1   /* ATAG��ʽ��bootargs�����ĵ�ַ */
    MOV r5, r2   /* sizeof (boot_arg_t) */
    MOV r6, r0   /* keep LK jump addr */
    MOV r7, r3   /* r3 = TEE boot entry */
��lk�ĵ�ַ��bootargs�����ĵ�ַ��bootargs�����Ĵ�С��TEE��������ڵ�ַ�����ڼĴ�����ִ��lk��
	
���ˣ�����preloader�����̽�����

```

