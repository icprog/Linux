


һ��ǰ��

���ֻ����������У��кܶ�i2c�豸�� LCD��ѹоƬ����sgm3804����TP��������������ͷ������ͷ�Խ�driver IC��ǰ����ͷ�������IC��Gsensor��alsps��ָʾ��LED IC��������һ������Щi2c slave�豸��

����i2c�豸����ʹ��ʵ��

1��LCD��ѹICоƬ

```c
module_init(_lcm_i2c_init);

static int __init _lcm_i2c_init(void)
{
	i2c_add_driver(&_lcm_i2c_driver);
	return 0;
}

static struct i2c_driver _lcm_i2c_driver = {
	.id_table = _lcm_i2c_id,
	.probe = _lcm_i2c_probe,
	.remove = _lcm_i2c_remove,
	.driver = {
	   .owner = THIS_MODULE,
	   .name = "I2C_LCD_BIAS",
	   .of_match_table = _lcm_i2c_of_match,
	},
};

static const struct i2c_device_id _lcm_i2c_id[] = {
	{"I2C_LCD_BIAS", 0},
	{}
};

static const struct of_device_id _lcm_i2c_of_match[] = {
	{ .compatible = "vendor,I2C_LCD_BIAS", },
	{}
};

static int _lcm_i2c_probe(struct i2c_client *client, const struct i2c_device_id *id)
{
	_lcm_i2c_client = client;
   //ȫ�ֱ��� static struct i2c_client *_lcm_i2c_client������i2c client��
	return 0;
}

�Լ�ʵ�� i2c д������
static int _lcm_i2c_write_bytes(unsigned char addr, unsigned char value)
{
	int ret = 0;
	struct i2c_client *client = _lcm_i2c_client;
	char write_data[2] = { 0 };

	write_data[0] = addr;
	write_data[1] = value;
	ret = i2c_master_send(client, write_data, 2);
	if (ret < 0)
		pr_err("[LCM][ERROR] _lcm_i2c write data fail !!\n");

	return ret;
}
```

2��TP������

```c
��Ȼ���ڳ�ʼ��probe�����У�
i2c_add_driver(&tpd_i2c_driver);

static struct i2c_driver tpd_i2c_driver = {
    .driver = {
        .name = "fts_ts",
        .of_match_table = fts_dt_match,
    },
    .probe = tpd_probe,
    .remove = tpd_remove,
    .id_table = fts_tpd_id,
    //.detect = tpd_i2c_detect,
    //detect��������ע�ͣ���ֻ�к�.address_listһ���壬���Żᱻ���ã����򲻻����
};

static const struct i2c_device_id fts_tpd_id[] = {
	{"fts_ts", 0}, 
	{} 
};

static const struct of_device_id fts_dt_match[] = {
    {.compatible = "vendor,cap_touch"},
    {},
};

static int tpd_i2c_detect(struct i2c_client *client, struct i2c_board_info *info)
{
    strcpy(info->type, "vendor-tp");
    return 0;
}

static int tpd_probe(struct i2c_client *client, const struct i2c_device_id *id)
{
	struct fts_ts_data *ts_data;
	ts_data = devm_kzalloc(&client->dev, sizeof(*ts_data), GFP_KERNEL);
	ts_data->client = client; 	
}

TP��д������
int fts_i2c_read(struct i2c_client *client, char *writebuf, int writelen, 
                 char *readbuf, int readlen)
{
    int ret = 0;
    int i = 0;

    mutex_lock(&i2c_rw_access);
	
    if (readlen > 0) {
        if (writelen > 0) {
            struct i2c_msg msgs[] = {
                {
                    .addr = client->addr,
                    .flags = 0,
                    .len = writelen,
                    .buf = writebuf,
                },
                {
                    .addr = client->addr,
                    .flags = I2C_M_RD,
                    .len = readlen,
                    .buf = readbuf,
                },
            };
            for (i = 0; i < I2C_RETRY_NUMBER; i++) {
                ret = i2c_transfer(client->adapter, msgs, 2);
                if (ret < 0) {
                    FTS_ERROR("[IIC]: i2c_transfer(write) error, ret=%d!!", ret);
                } else
                    break;
            }
        } else {
            struct i2c_msg msgs[] = {
                {
                    .addr = client->addr,
                    .flags = I2C_M_RD,
                    .len = readlen,
                    .buf = readbuf,
                },
            };
            for (i = 0; i < I2C_RETRY_NUMBER; i++) {
                ret = i2c_transfer(client->adapter, msgs, 1);
                if (ret < 0) {
                    FTS_ERROR("[IIC]: i2c_transfer(read) error, ret=%d!!", ret);
                } else
                    break;
            }
        }
    }

    mutex_unlock(&i2c_rw_access);
    return ret;
}

int fts_i2c_write(struct i2c_client *client, char *writebuf, int writelen)
{
    int ret = 0;
    int i = 0;

    mutex_lock(&i2c_rw_access);
    if (writelen > 0) {
        struct i2c_msg msgs[] = {
            {
                .addr = client->addr,
                .flags = 0,
                .len = writelen,
                .buf = writebuf,
            },
        };
        for (i = 0; i < I2C_RETRY_NUMBER; i++) {
            ret = i2c_transfer(client->adapter, msgs, 1);
            if (ret < 0) {
                FTS_ERROR("[IIC]: i2c_transfer(write) error, ret=%d!!", ret);
            } else
                break;
        }
    }
    mutex_unlock(&i2c_rw_access);

    return ret;
}

```

3��AF����

```c
������ģ���ʼ�������� 
module_init(MAINAF_i2C_init);

static int __init MAINAF_i2C_init(void)
{
	if (platform_device_register(&g_stAF_device)) {
		LOG_INF("failed to register AF driver\n");
		return -ENODEV;
	}

	if (platform_driver_register(&g_stAF_Driver)) {
		LOG_INF("Failed to register AF driver\n");
		return -ENODEV;
	}
	return 0;
}

static struct platform_driver g_stAF_Driver = {
	.probe = AF_probe,
	.remove = AF_remove,
	.suspend = AF_suspend,
	.resume = AF_resume,
	.driver = {
		.name = PLATFORM_DRIVER_NAME, 
		.owner = THIS_MODULE,
	} 
};

static struct platform_device g_stAF_device = {
	.name = PLATFORM_DRIVER_NAME, 
	.id = 0, 
	.dev = {} 
};

static int AF_probe(struct platform_device *pdev)
{
	return i2c_add_driver(&AF_i2c_driver);
}

static struct i2c_driver AF_i2c_driver = {
	.probe = AF_i2c_probe,
	.remove = AF_i2c_remove,
	.driver.name = AF_DRVNAME,
	.driver.of_match_table = MAINAF_of_match,
	.id_table = AF_i2c_id,
};

static const struct of_device_id MAINAF_of_match[] = {
	{.compatible = "vendor,CAMERA_MAIN_AF"}, {},
};

static const struct i2c_device_id AF_i2c_id[] = {{AF_DRVNAME, 0}, {} };

static int AF_i2c_probe(struct i2c_client *client,	const struct i2c_device_id *id)
{
	g_pstAF_I2Cclient = client;
	...
}

ʵ��lens��i2c��д������
static int i2c_read(u8 a_u2Addr, u8 *a_puBuff)
{
	int i4RetValue = 0;
	char puReadCmd[1] = {(char)(a_u2Addr)};

	i4RetValue = i2c_master_send(g_pstAF_I2Cclient, puReadCmd, 1);
	if (i4RetValue < 0) {
		LOG_INF(" I2C write failed!!\n");
		return -1;
	}

	i4RetValue = i2c_master_recv(g_pstAF_I2Cclient, (char *)a_puBuff, 1);
	if (i4RetValue < 0) {
		LOG_INF(" I2C read failed!!\n");
		return -1;
	}

	return 0;
}

static int i2c_WriteReg(u16 a_u2Data)
{
	int i4RetValue = 0;

	char puSendCmd[3] = {0x02, (char)(a_u2Data >> 8), (char)(a_u2Data & 0xFF)};

	g_pstAF_I2Cclient->addr = AF_I2C_SLAVE_ADDR;
	g_pstAF_I2Cclient->addr = g_pstAF_I2Cclient->addr >> 1;

	i4RetValue = i2c_master_send(g_pstAF_I2Cclient, puSendCmd, 3);

	if (i4RetValue < 0) {
		LOG_INF("I2C send failed!!\n");
		return -1;
	}

	return 0;
}

```

4�������IC

```c
module_init(flashlight_lm3643_init);

static int __init flashlight_lm3643_init(void)
{
	int ret;
	ret = platform_device_register(&lm3643_platform_device);
	if (ret) {
		pr_err("Failed to register platform device\n");
		return ret;
	}

	ret = platform_driver_register(&lm3643_platform_driver);
	if (ret) {
		pr_err("Failed to register platform driver\n");
		return ret;
	}
	return 0;
}

static struct platform_device lm3643_platform_device[] = {
	{
		.name = LM3643_NAME,
		.id = 0,
		.dev = {}
	},
	{}
};
MODULE_DEVICE_TABLE(platform, lm3643_platform_device);

static const struct of_device_id lm3643_of_match[] = {
	{.compatible = LM3643_DTNAME},
	{},
};
MODULE_DEVICE_TABLE(of, lm3643_of_match);

static struct platform_driver lm3643_platform_driver = {
	.probe = lm3643_probe,
	.remove = lm3643_remove,
	.driver = {
		.name = LM3643_NAME,
		.owner = THIS_MODULE,
		.of_match_table = lm3643_of_match,
	},
};

static int lm3643_probe(struct platform_device *dev)
{
	i2c_add_driver(&lm3643_i2c_driver);
	...
}

static struct i2c_driver lm3643_i2c_driver = {
	.driver = {
		.name = LM3643_NAME,
		.of_match_table = lm3643_i2c_of_match,
	},
	.probe = lm3643_i2c_probe,
	.remove = lm3643_i2c_remove,
	.id_table = lm3643_i2c_id,
};

static const struct of_device_id lm3643_i2c_of_match[] = {
	{.compatible = LM3643_DTNAME_I2C},
	{},
};

static const struct i2c_device_id lm3643_i2c_id[] = {
	{LM3643_NAME, 0},
	{}
};

static int lm3643_i2c_probe(struct i2c_client *client, const struct i2c_device_id *id)
{
	lm3643_i2c_client = client;
	...
}

ʵ��i2c��д������
static int lm3643_write_reg(struct i2c_client *client, u8 reg, u8 val)
{
	int ret;
	struct lm3643_chip_data *chip = i2c_get_clientdata(client);

	mutex_lock(&chip->lock);
	ret = i2c_smbus_write_byte_data(client, reg, val);
    //i2c smbus��i2c��Ҫ���٣�һ��Ϊ100KHZ��
	mutex_unlock(&chip->lock);

	if (ret < 0)
		pr_err("failed writing at 0x%02x\n", reg);

	return ret;
}

```

5��Gsensor

```c
i2c_add_driver(&mxc400x_i2c_driver);

static struct i2c_driver mxc400x_i2c_driver = {
	 .driver = {
		.owner	= THIS_MODULE,
		.name	= MXC400X_DEV_NAME,
		.pm = &mxc400x_i2c_pm_ops,
		.of_match_table = accel_of_match,
	 },
	 .probe 	= mxc400x_i2c_probe,
	 .remove	= mxc400x_i2c_remove,
	 .id_table  = mxc400x_i2c_id,
};

static const struct of_device_id accel_of_match[] = {
	{.compatible = "vendor,gsensor"},
	{},
};

static const struct i2c_device_id mxc400x_i2c_id[]={{MXC400X_DEV_NAME, 0 }, {},};

static int mxc400x_i2c_probe(struct i2c_client *client, const struct i2c_device_id *id)
{
	obj_i2c_data->client = client;
}

i2c �Ķ�������
static int mxc400x_i2c_read_block(struct i2c_client *client, u8 addr, 
u8 *data, u8 len)
{
	struct i2c_msg msgs[2] = 
	{
		{
			.addr = client->addr,	
			.flags = 0,
			.len = 1,	
			.buf = &addr
		},
		{
			.addr = client->addr,	
			.flags = I2C_M_RD,
			.len = len,	
			.buf = data,
		}
	};

	err = i2c_transfer(client->adapter, msgs, 2);
	
	if (err != 2) 
		err = -EIO;
	else 
		err = 0;

	return err;
}
```

6��alsps����봫����

```c
i2c_add_driver(&ltr559_i2c_driver);

static struct i2c_driver ltr559_i2c_driver = {
	.probe = ltr559_i2c_probe,
	.remove = ltr559_i2c_remove,
	.detect = ltr559_i2c_detect,
	.id_table = ltr559_i2c_id,
	.driver = {
		.name = LTR559_DEV_NAME,
		.pm   = &ltr559_pm_ops,
		.of_match_table = alsps_of_match,
	},
};

static const struct i2c_device_id ltr559_i2c_id[] = { {LTR559_DEV_NAME, 0}, {} };

static const struct of_device_id alsps_of_match[] = {
	{.compatible = "vendor,alsps"},
	{},
};

static int ltr559_i2c_detect(struct i2c_client *client, struct i2c_board_info *info)
{
	strlcpy(info->type, LTR559_DEV_NAME, sizeof(info->type));
	return 0;
}

static int ltr559_i2c_probe(struct i2c_client *client, const struct i2c_device_id *id)
{
	client->addr = 0x23;
	ltr559_obj->client = client;
	...
}

ʵ��i2c�Ķ�д������
static int8_t I2C_Read(uint8_t *rxData, uint8_t length)
{
	int8_t index;
	struct ltr559_priv *obj = ltr559_obj;
	
	struct i2c_msg data[] = {
		{
			.addr = obj->client->addr,
			.flags = 0,
			.len = 1,
			.buf = rxData,
		},
		{
			.addr = obj->client->addr,
			.flags = I2C_M_RD,
			.len = length,
			.buf = rxData,
		},
	};

	for (index = 0; index < I2C_RETRY; index++) {
		if (i2c_transfer(obj->client->adapter, data, 2) > 0)
			break;

		mdelay(10);
	}

	if (index >= I2C_RETRY) {
		pr_alert("%s I2C Read Fail !!!!\n", __func__);
		return -EIO;
	}

	return 0;
}

static int ltr559_i2c_read_reg(u8 regnum)
{
	u8 buffer[1],reg_value[1];
	int res = 0;
	struct ltr559_priv *obj = ltr559_obj;

	mutex_lock(&ltr559_mutex);
	buffer[0]= regnum;
	res = i2c_master_send(obj->client, buffer, 1);
	if(res <= 0)
	{	  
		mutex_unlock(&ltr559_mutex);
		APS_PR_ERR("read reg send res = %d\n",res);
		return res;
	}
	
	res = i2c_master_recv(obj->client, reg_value, 1);
	if(res <= 0)
	{	
		mutex_unlock(&ltr559_mutex);
		APS_PR_ERR("read reg recv res = %d\n",res);
		return res;
	}
	
	mutex_unlock(&ltr559_mutex);
	return reg_value[0];
}

static int ltr559_i2c_write_reg(u8 regnum, u8 value)
{
	u8 databuf[2];    
	int res = 0;
	struct ltr559_priv *obj = ltr559_obj;

	mutex_lock(&ltr559_mutex);
	databuf[0] = regnum;   
	databuf[1] = value;
	res = i2c_master_send(obj->client, databuf, 0x2);
	mutex_unlock(&ltr559_mutex);

	if (res < 0)
	{
		printk("wirte reg send regnum=0x%x,value=0x%x,res = %d\n",databuf[0],databuf[1],res);
		return res;
	}		
	else
		return 0;
}
```

7�� LED I2C�豸����

```c
��platform bus��probe�����У�
i2c_add_driver(&led_i2c_driver)

struct i2c_driver led_i2c_driver = {
	.probe = led_i2c_probe,
	.remove = led_i2c_remove,
	.driver = {
		.name = "lp8557_led",
		.owner = THIS_MODULE,
		.of_match_table = lp855x_id,
	},
	.id_table = lp855x_i2c_id,
};

static const struct of_device_id lp855x_id[] = {
	{.compatible = "vendor,8173led_i2c"},
	{.compatible = "ti,lp8557_led"},
	{},
};
MODULE_DEVICE_TABLE(OF, lp855x_id);
/*
MODULE_DEVICE_TABLE һ�������Ȳ�ε��豸�����С�
���� lp855x_id �ṹ���Ǵ�������֧�ֵ��豸�б�
�����ǣ��� lp855x_id �ṹ������û��ռ䣬����ģ�����ϵͳ�ڼ���ģ��ʱ����֪����ʲôģ���ӦʲôӲ���豸��
�÷��ǣ� MODULE_DEVICE_TABLE ���豸���ͣ��豸��
���У��豸���ͣ�����USB,PCI�ȣ�Ҳ�����Լ������֡�
�豸��Ҳ���Լ�����ģ��������һ������ǿգ�������ʶ������
*/

static const struct i2c_device_id lp855x_i2c_id[] = {{"lp8557_led", 0}, {} };

static int led_i2c_probe(struct i2c_client *client, const struct i2c_device_id *id)
{
	g_client = client;
    //g_client ��һ��ȫ�ֱ���������Ϊ��static struct i2c_client *g_client;
//��i2c�� probe �����У����� LED ��Ӧ�� i2c_client �ṹ��ָ�룬Ȼ�����ʹ����� i2c_client
	return 0;
}

Ȼ�����ʹ�� i2c smbus ϵ�ж�д������
value = i2c_smbus_read_byte_data(g_client, 0x10);//��0x10��ֵ
i2c_smbus_write_byte_data(client, 0x14, 0xdf);//��0x14д0xdf
```

8��  imgsensor i2c�豸����

```c
�� imgsensor �� platform bus �� probe �����У������ imgsensor_i2c_create

int imgsensor_i2c_create(void)
{
	i2c_add_driver(&camera_main_driver);
	i2c_add_driver(&camera_sub_driver);
	return 0;
}

static struct i2c_driver camera_main_driver = {
		.probe = imgsensor_i2c_probe_0,
		.remove = imgsensor_i2c_remove,
		.driver = {
			.name = "camera_main",
			.owner = THIS_MODULE,
			.of_match_table = main_cam_device_id,
		},
		.id_table = camera_dev_id,
};

static struct i2c_driver camera_sub_driver = {	
		.probe = imgsensor_i2c_probe_1,
		.remove = imgsensor_i2c_remove,
		.driver = {
			.name = "camera_sub",
			.owner = THIS_MODULE,
			.of_match_table = sub_cam_device_id,
		},
		.id_table = camera_dev_id,
};

static const struct of_device_id main_cam_device_id[] = {
	{ .compatible = "vendor,camera_main", },
	{}
};
static const struct of_device_id sub_cam_device_id[] = {
	{ .compatible = "vendor,camera_sub", },
	{}
};
static const struct i2c_device_id camera_dev_id[] = {
	{"camera_main", 0},
	{"camera_sub", 0},
	{}
};

static int imgsensor_i2c_probe_0(struct i2c_client *client, const struct i2c_device_id *id)
{
	gi2c.inst[0].pi2c_client = client;
	return 0;
}

static int imgsensor_i2c_probe_1(struct i2c_client *client, const struct i2c_device_id *id)
{
	gi2c.inst[1].pi2c_client = client;
	return 0;
}

struct IMGSENSOR_I2C_CFG {
	struct IMGSENSOR_I2C_INST *pinst;
	struct mutex               i2c_mutex;
};

struct IMGSENSOR_I2C_INST {
	struct i2c_client   *pi2c_client;
	struct i2c_msg       msg[255];
    //��ͨ��i2c transfer ����ܳ���8�ֽڣ�����DMA������������255���ֽ�
};

struct IMGSENSOR_I2C {
	struct IMGSENSOR_I2C_INST inst[2];
};

struct IMGSENSOR_I2C gi2c;

Ȼ���Լ�ʵ�� i2c-vendor �� read/write ������

int imgsensor_i2c_read(	struct IMGSENSOR_I2C_CFG *pi2c_cfg, u8 *pwrite_data,	
u16 write_length, u8 *pread_data, u16 read_length, u16 id, int speed )
{
	struct IMGSENSOR_I2C_INST *pinst = pi2c_cfg->pinst;
	int ret   = 0;

	mutex_lock(&pi2c_cfg->i2c_mutex);

	pinst->msg[0].addr  = id >> 1;
	pinst->msg[0].flags = 0;
	pinst->msg[0].len   = write_length;
	pinst->msg[0].buf   = pwrite_data;

	pinst->msg[1].addr  = id >> 1;
	pinst->msg[1].flags = I2C_M_RD;
	pinst->msg[1].len   = read_length;
	pinst->msg[1].buf   = pread_data;

	//vendor_i2c_transfer() ��������� i2c-vendor.c ��vendorʵ�ֵġ�
	if (vendor_i2c_transfer(  pinst->pi2c_client->adapter,  pinst->msg,   2,  I2C_A_FILTER_MSG,   speed * 1000) != 2 ) {
		ret = -1;
	}

	mutex_unlock(&pi2c_cfg->i2c_mutex);

	return ret;
}



enum IMGSENSOR_RETURN imgsensor_i2c_write(	struct IMGSENSOR_I2C_CFG *pi2c_cfg,	   
u8 *pwrite_data, u16 write_length, u16 write_per_cycle, u16 id, int speed)
{
	struct IMGSENSOR_I2C_INST *pinst = pi2c_cfg->pinst;
	int ret   = 0;
	struct i2c_msg     *pmsg  = pinst->msg;
	u8                 *pdata = pwrite_data;
	u8                 *pend  = pwrite_data + write_length;
	int i   = 0;

	mutex_lock(&pi2c_cfg->i2c_mutex);

	while (pdata < pend && i < 255) {
		pmsg->addr  = id >> 1;
		pmsg->flags = 0;
		pmsg->len   = write_per_cycle;
		pmsg->buf   = pdata;

		i++;
		pmsg++;
		pdata += write_per_cycle;
	}

	if (vendor_i2c_transfer(   pinst->pi2c_client->adapter,    pinst->msg,    i,    I2C_A_FILTER_MSG,    speed * 1000) != i) {
		ret = -1;
	}

	mutex_unlock(&pi2c_cfg->i2c_mutex);

	return ret;
}
```

9��һ�����͵�i2c�豸��д����

```c
int iReadReg(u16 a_u2Addr, u8 *a_puBuff, u16 i2cId)
{
	int i4RetValue = 0;
	char puReadCmd[2] = { (char)(a_u2Addr >> 8), (char)(a_u2Addr & 0xFF) };

	spin_lock(&sensor_lock);
	g_pstI2Cclient->addr = (i2cId >> 1);
	g_pstI2Cclient->ext_flag = (g_pstI2Cclient->ext_flag) & (~I2C_DMA_FLAG);
	g_pstI2Cclient->ext_flag = (g_pstI2Cclient->ext_flag) & (~I2C_A_FILTER_MSG);
	spin_unlock(&sensor_lock);

	i4RetValue = i2c_master_send(g_pstI2Cclient, puReadCmd, 2);
	if (i4RetValue != 2) {
		PK_ERR("[CAMERA SENSOR] I2C send failed, addr = 0x%x, data = 0x%x !!\n",  a_u2Addr, *a_puBuff);
		return -1;
	}

	i4RetValue = i2c_master_recv(g_pstI2Cclient, (char *)a_puBuff, 1);
	if (i4RetValue != 1) {
		PK_ERR("[CAMERA SENSOR] I2C read failed!!\n");
		return -1;
	}

	return 0;
}

int iReadRegI2C(u8 *a_pSendData , u16 a_sizeSendData, u8 *a_pRecvData, u16 a_sizeRecvData, u16 i2cId)
{
	int i4RetValue = 0;

	spin_lock(&sensor_lock);
	g_pstI2Cclient->addr = (i2cId >> 1);
	g_pstI2Cclient->ext_flag = (g_pstI2Cclient->ext_flag) & (~I2C_DMA_FLAG);
	g_pstI2Cclient->ext_flag = (g_pstI2Cclient->ext_flag) & (~I2C_A_FILTER_MSG);
	spin_unlock(&sensor_lock);

	i4RetValue = i2c_master_send(g_pstI2Cclient, a_pSendData, a_sizeSendData);
	if (i4RetValue != a_sizeSendData) {
		return -1;
	}

	i4RetValue = i2c_master_recv(g_pstI2Cclient, (char *)a_pRecvData, a_sizeRecvData);
	if (i4RetValue != a_sizeRecvData) {
		return -1;
	}
	
	return 0;
}
```

10�� i2cʹ�� dma i2c ���亯��

```c
static struct platform_device camerahw_platform_device = {
	.name = "image_sensor",
	.id = 0,
	.dev = {
		.coherent_dma_mask = DMA_BIT_MASK(32),
	}
};

#define MAX_CMD_LEN          255

int iBurstWriteReg_multi(u8 *pData, u32 bytes, u16 i2cId, u16 transfer_length)
{
	uintptr_t phyAddr = 0;
	u8 *buf = NULL;
	u32 old_addr = 0;
	int ret = 0;
	int retry = 0;

	if (bytes > MAX_CMD_LEN) {
		PK_DBG("[iBurstWriteReg] exceed the max write length\n");
		return 1;
	}

	buf = dma_alloc_coherent( &(camerahw_platform_device.dev),   bytes,  
                             (dma_addr_t *) &phyAddr,  GFP_KERNEL );
	if (NULL == buf) {
		PK_DBG("[iBurstWriteReg] Not enough memory\n");
		return -1;
	}
	
	memset(buf, 0, bytes);
	memcpy(buf, pData, bytes);

	old_addr = g_pstI2Cclient->addr;
	
	spin_lock(&sensor_lock);
	g_pstI2Cclient->addr = (i2cId >> 1);
	g_pstI2Cclient->ext_flag =(g_pstI2Cclient->ext_flag | I2C_ENEXT_FLAG | I2C_DMA_FLAG);
	g_pstI2Cclient->ext_flag = (g_pstI2Cclient->ext_flag) & (~I2C_POLLING_FLAG);
	spin_unlock(&sensor_lock);

	ret = 0;
	retry = 3;
	
	do {
		ret = i2c_master_send( g_pstI2Cclient, (u8 *)phyAddr,  transfer_length );
		retry--;
		if ((ret & 0xffff) != transfer_length) {
			PK_ERR("Error sent I2C ret = %d\n", ret);
		}
	} while (((ret & 0xffff) != transfer_length) && (retry > 0));

	dma_free_coherent(&(camerahw_platform_device.dev), bytes, buf, phyAddr);
	
	spin_lock(&sensor_lock);
	g_pstI2Cclient->addr = old_addr;
	spin_unlock(&sensor_lock);

	return 0;
}

int iBurstWriteReg(u8 *pData, u32 bytes, u16 i2cId)
{
	return iBurstWriteReg_multi(pData, bytes, i2cId, bytes);
}

```

