
```c
TP ����֪ʶ��

һ�� MTK TP����ܹ�
1��MTK��TP��ΪMTK TP �� ������TP������

2��TP����Ĺ������С��жϡ����߳�
1��MTK TP �Ĺ������У�
1.1��  init workqueue �� ������һ�� work ��platform driver register ����� work ֱ��ִ�У�queue_work()

1.2�� tp resume workqueue �� ������һ�� work �����Ĺ��������ǵ��� tp->resume() ������LCD����ʱͨ���ں�֪ͨ����ִ�� queue_work() ����TP �� resume �� suspend ����ͨ��LCD�ں�֪ͨ�������á���


2��ft8006m �Ĺ������У�����1���������У���3�������� fwupd �� esd �� point_report_check ������ ��esd work ��ÿ��1s�ͻ�ִ��һ�Ρ�

3��TP����һ���ں��̣߳�touch_event_handler ����ͨ���ȴ����к��ж���ʵ�֣��߳�ִ�к����ȴ��жϷ�����������һ���ȴ�����ͷ�ϡ����������жϣ����ѵȴ�����ͷ�ϵ�����̡߳�

4) TP �еĶ��߳���2����esd ���� �� �жϴ���װ벿�����̡߳����ж��ϰ벿�� request_irq ���жϺ����������ǻ����˵ȴ�����ͷ�ϵ��жϵװ벿�̡߳��жϵװ벿�ϱ������;������꣩

5���ж�һ����ȴ����н��ʹ�á��������п��Ժ��ں��߳����Ტ�ۡ�


2�� 
set_bit()	����input������ϵͳ֧����Щ�¼�����Щ������
input_set_abs_params()		���ò�����Χ��

3�� MTKƽ̨GPIO���������ַ�����
ʹ��GPIOlib �� gpio_request()   gpio_direct_output()	gpio_set_value()	 gpio_free()
ʹ��pinctrl ��	 devm_pinctrl_get()	pinctrl_lookup_state()		pinctrl_select_state()
ʹ��legacy mtk ������ mt_set_gpio_mode()   mt_set_gpio_dir()


```

