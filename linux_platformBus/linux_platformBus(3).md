

platformDevice������ȥ��

�ڻ���of��platformBus�У�platform_driver�����Ǿ�̬����ģ���ôplatfo_device�������ģ�

���������Դ����platform_driver��probe����������ʱ��drv->probe(dev)��dev�������ģ�



һ������·��Ϊ kernel-4.9/drivers/of/Platform.c
```c
arch_initcall_sync(of_platform_default_populate_init);//���ȼ�Ϊ3s
static int __init of_platform_default_populate_init(void)
{
    struct device_node *node;
    if (!of_have_populated_dt())
        return -ENODEV;
    node = of_find_node_by_path("/reserved-memory");
    if (node) {
        node = of_find_compatible_node(node, NULL, "ramoops");
        if (node)
            of_platform_device_create(node, NULL, NULL);
    }
    of_platform_default_populate(NULL, NULL, NULL);
    return 0;
}
```
```c
int of_platform_default_populate(struct device_node *root,
const struct of_dev_auxdata *lookup,
struct device *parent)
{
    return of_platform_populate(root, of_default_bus_match_table, lookup,parent);
}
```
```c
const struct of_device_id of_default_bus_match_table[] = {
    { .compatible = "simple-bus", },
    {}
};
```
```c
int of_platform_populate(struct device_node *root,
const struct of_device_id *matches,
const struct of_dev_auxdata *lookup,
struct device *parent)
{
    struct device_node *child;
    int rc = 0;
    root = root ? of_node_get(root) : of_find_node_by_path("/");
//�Ӹ��ڵ�/��ʼ����
    if (!root)
        return -EINVAL;
    pr_debug(" starting at: %s\n", root->full_name);
    for_each_child_of_node(root, child) {
        rc = of_platform_bus_create(child, matches, lookup, parent, true);
        if (rc) {
            of_node_put(child);
            break;
        }
    }
    of_node_set_flag(root, OF_POPULATED_BUS);
    of_node_put(root);
    return rc;
}

```
```c
static int of_platform_bus_create(struct device_node *bus,
  const struct of_device_id *matches,
  const struct of_dev_auxdata *lookup,
  struct device *parent, bool strict)
{
    const struct of_dev_auxdata *auxdata;
    struct device_node *child;
    struct platform_device *dev;
    const char *bus_id = NULL;
    void *platform_data = NULL;
    int rc = 0;
    /* Make sure it has a compatible property */
    if (strict && (!of_get_property(bus, "compatible", NULL))) {
        pr_debug("%s() - skipping %s, no compatible prop\n",__func__, bus->full_name);
        return 0;
    }
    if (of_node_check_flag(bus, OF_POPULATED_BUS)) {
        pr_debug("%s() - skipping %s, already populated\n",__func__, bus->full_name);
    return 0;
    }
    auxdata = of_dev_lookup(lookup, bus);
    if (auxdata) {
        bus_id = auxdata->name;
        platform_data = auxdata->platform_data;
    }
    if (of_device_is_compatible(bus, "arm,primecell")) {
        of_amba_device_create(bus, bus_id, platform_data, parent);
        return 0;
    }
    dev = of_platform_device_create_pdata(bus, bus_id, platform_data, parent);
    if (!dev || !of_match_node(matches, bus))
        return 0;
    for_each_child_of_node(bus, child) {
        pr_debug("  create child: %s\n", child->full_name);
        rc = of_platform_bus_create(child, matches, lookup, &dev->dev, strict);
        if (rc) {
            of_node_put(child);
            break;
        }
    }
    of_node_set_flag(bus, OF_POPULATED_BUS);
    return rc;
}
```
```c
static struct platform_device *of_platform_device_create_pdata(
struct device_node *np,
const char *bus_id,
void *platform_data,
struct device *parent)
{
    struct platform_device *dev;
    if (!of_device_is_available(np) || of_node_test_and_set_flag(np, OF_POPULATED))
        return NULL;
    dev = of_device_alloc(np, bus_id, parent);
    if (!dev)
        goto err_clear_flag;
    dev->dev.bus = &platform_bus_type;
    dev->dev.platform_data = platform_data;
    of_dma_configure(&dev->dev, dev->dev.of_node);
    of_msi_configure(&dev->dev, dev->dev.of_node);
    if (of_device_add(dev) != 0) {//������� device_add()��
        of_dma_deconfigure(&dev->dev);
        platform_device_put(dev);
        goto err_clear_flag;
    }
    return dev;
    err_clear_flag:
    of_node_clear_flag(np, OF_POPULATED);
    return NULL;
}
```
```c
struct platform_device *of_device_alloc(struct device_node *np,
  const char *bus_id,
  struct device *parent)
{
    struct platform_device *dev;
    int rc, i, num_reg = 0, num_irq;
    struct resource *res, temp_res;
    dev = platform_device_alloc("", -1);
    //����һ�� platform_device ���ҳ�ʼ�� platform_device �ĳ�Ա device
    if (!dev)
        return NULL;
    /* count the io and irq resources */
    while (of_address_to_resource(np, num_reg, &temp_res) == 0)
    //�� device_node �� reg �Ĵ�����ַ������ resource
        num_reg++;
    num_irq = of_irq_count(np);//������� device_node ʹ�õ� IRQ����
    /* Populate the resource table */
    if (num_irq || num_reg) {
        res = kzalloc(sizeof(*res) * (num_irq + num_reg), GFP_KERNEL);
        if (!res) {
            platform_device_put(dev);
            return NULL;
        }
        dev->num_resources = num_reg + num_irq;
        dev->resource = res;
        for (i = 0; i < num_reg; i++, res++) {
            rc = of_address_to_resource(np, i, res);
            WARN_ON(rc);
        }
        if (of_irq_to_resource_table(np, res, num_irq) != num_irq)
        pr_debug("not all legacy IRQ resources mapped for %s\n",np->name);
    }
    dev->dev.of_node = of_node_get(np);
    dev->dev.fwnode = &np->fwnode;
    dev->dev.parent = parent ? : &platform_bus;
    //platform_bus����� deviceΪ��һ��device��parent
    if (bus_id)
        dev_set_name(&dev->dev, "%s", bus_id);
    else
        of_device_make_bus_id(&dev->dev);
    return dev;
}
```


����of_platform_populate()��������Ĺ���

1��ԭ�ͣ�
```c
of_platform_populate(struct device_node *root, 
const struct of_device_id *matches, 
const struct of_dev_auxdata *lookup, 
struct device *parent);
```
2���Ӳ���root��ʼ����ÿһ��device_node�����rootΪNULL����Ӹ��ڵ�  /  ��ʼ��������һ���ֵܽڵ���ߺ��ӽڵ�device_node ��

3���Ӳ���root�ڵ����ڵ㿪ʼ�������а��� compatible ���ԵĽڵ���� platform_device �� struct resource��reg��ַ��Ϣ��interrupts��Ϣ����

������� compatible ���ԺͲ��� matches ƥ�䣬��ô����Ϊ���ĺ��ӽڵ���� platform_device �� struct resource ������ǵݹ���� platform_device �������ڴ��� i2c �Ľڵ㡣

4��������� device_add()�������device��platformBus������ϵ������
��һ��device��parentΪ platform_bus����� platform_bus��һ��device������platform_bus��ʼ����ʱ���ں��ʼ��ʼ����ʱ�򣩱� device_add()��

5����һ��i2c  dts������
```c
i2c2@11009000 {
    compatible = "vendor,i2c";
    id = <0x2>;
    reg = <0x0 0x11009000 0x0 0x1000 0x0 0x11000180 0x0 0x180>;
    interrupts = <0x0 0x1e 0x8>;
    #address-cells = <0x1>;
    #size-cells = <0x0>;
        i2cslave-usb@60 {
            compatible = "vendor,usb";
            reg = <0x60>;
            status = "okay";
        };
};

odm {
    compatible = "simple-bus";
    linux,phandle = <0x9c>;
    phandle = <0x9c>;
        led@0 {
            compatible = "vendor,red";
            data = <0x1>;
            pwm_config = <0x0 0x0 0x0 0x0 0x0>;
        };
};
```
������dts��һ���֣�����of_platform_populate�Ĳ���matches�а����ˣ�
.compatible = "simple-bus";

��ô��i2c���ߵ����� compatible = "vendor,i2c"�����ڵ�device_node�ᴴ��һ�� platform_device ��

����������ĺ��ӽڵ�i2c slave�豸��compatible = "vendor,usb"�����ᱻ����platform_device��

��odm�ڵ��У�2���ڵ� compatible = "simple-bus"  ��   compatible = "vendor,red"�����ᱻ���� platform_device ��

����������������platform_device��i2c slave device��

