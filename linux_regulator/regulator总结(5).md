


regulator �ܽ�

1����Ϊ�� vendor �� camera �����У� ǰ�����VCAMA��VCAMD��VCAMIO��VCAMAF����ͨ��LDO regulator����ģ����ԲŻ��עһ��regulator��

2���� vendor �� pmic ������ע�� regulator �� regulator_register()��

3����imgsensor��������regulator����regulator_get()��regulator_put()��regulator_enable()��regulator_voltage()��regulator_disable()��regulator_is_enabled()��

4��If the regulator is shared between several devices then the lowest request voltage that meets the system constraints will be used.

��1����ͬ��ѹ�����Ź��� regulator ʱ�� regulator Ϊ�˱����͵�ѹ���Ų������ջ���

��ѵ͵�ѹ���ŵĵ�ѹ���ó� regulator ����ߵ�ѹ���Ӷ�ʹ�ߵ�ѹ�����޷��ϵ硣������ʵ�ֵĵط�Ϊ regulator_check_consumers() ��

```c
if (*max_uV > regulator->max_uV)	
  *max_uV = regulator->max_uV;
if (*min_uV < regulator->min_uV)	
  *min_uV = regulator->min_uV;
```

��2��ʵ�����������VCAMD=1.0V��ǰ��VCAMD=1.2V����ô�򿪺���ʱ�� regulator->min_uV = 1000000 �� regulator->max_uV = 1000000 �� 

Ȼ���Ǻ����е�ǰ�㣬 Ҫ���õĵ�ѹΪ�� *min_uV = 1200000 �� *max_uV = 1200000 ��

�������������жϺ� *min_uV = 1200000 �� *max_uV = 1000000 ����������

��3�������

���ڹ��� regulator ������ѹ����ͬ�����ţ�

(1) �µ�󣬵��� regulator_put �������ͷŵ� regulator��

(2) �ϵ�ǰ������ regulator_get �������������� regulator��

5�������������regulatorʧ�ܣ�����Ҫ�鿴pmic�������鿴��֧�����õĵ�ѹ�Ƕ��١����磺

```c
const static int VCAMD_voltages[] = {
	1000000,
    1200000,
    1300000,    
    1500000,
    1800000,        
};
```

6���ڵ��� regulator_set_voltage() ʱ����2�����/��С��ѹ�����������︳ֵ�ģ�

��1��
regulator->min_uV; 

regulator->max_uV;

�����������Ҫ���õ���С/����ѹ�� regulator consumer device ��ѹ��

��2��
rdev->constraints->max_uV; 

rdev->constraints->min_uV;

����������ƣ���pmic��regulator�г�ʼ�����������Լ��������С/����ѹ������VCAMD����С������ѹΪ��1000000��1800000��Ҳ������dts�ж��塣

7����������bug�ٲ��䡣


