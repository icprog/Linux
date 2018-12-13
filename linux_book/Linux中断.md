�����ؼ���

�жϣ��ϰ벿���°벿�����жϣ�tasklet���������У��ȴ����С�



һ���жϻ���֪ʶ

1���ж���ָCPU�յ��жϴ��������ִֹͣ�е�ǰ����תȥִ���жϳ���ִ�����жϳ���󣬷��������жϵĳ��򴦼���ִ�С�

2���ж��ź���Ӳ��������������Ӳ������һ���ж��ź�(������/�½���/�ߵ�ƽ/�͵�ƽ)ʱ��ͨ����Ӧ���ж��ߴ����жϿ�������Ȼ�󴫸�CPU��CPU��������һ���ж��ߣ�תȥִ���ж��������ж�Ӧ���жϴ�������

3��Linux�жϲ�����Ƕ�׵��ã����жϴ�������ִ�е�ʱ�򣬲��ܱ�������жϸ���ϡ�

4��Linux�жϷ�Ϊ�ϰ벿���°벿��������Ŀ�������жϴ����㹻��Ѹ�٣������������̴��ڼ���״̬��

5���ϰ벿���ϰ벿���жϴ�������һ��ִ��һЩӲ����صĲ���������жϱ�־λ�ȣ�Ȼ������°벿��Ȼ�󷵻ء��ϰ벿�������Ѹ�١��ϰ벿�������ж������ģ��ж�������û���Լ�����Դ�����빲��ǰ���̵���Դ����Ҳ�����������������������жϣ�����ֹʹ�ÿ�������˯�ߵ����绥����mutex_lock��

6���°벿�����ϰ벿���ò����Ӻ�ִ�е�һЩ�������°벿������Ӧ�жϡ��°벿��ʵ�ַ��������жϣ�tasklet���������С�



����ע��/�ͷ�һ���ж�

1���ж�ע�ắ��
```c
int request_irq( unsigned int irq, irq_handler_t handler, unsigned long flags,  
const char *name, void * dev );

typedef irqreturn_t (*irq_handler_t) (int ,void *)  irq_handler_t;

irq���ж��ߵ����                  
handler���жϴ�����
flags���жϱ�־�����жϴ�����ʽ�������ش�����ߵ�ƽ�������������жϣ������ж�
name���ж���������ͨ�� cat /proc/interrupts ������                   
dev������handler������ָ��

����ֵ��Ϊ0���ɹ�����ֵ��ʧ�ܡ�

request_irq()�������ܻ�����˯�ߣ���Ϊ�������kmalloc()��
��һ����������probe()�����е�����ע��һ���жϺš�
```
2���ͷ��ж�
```c
void free( unsigned int irq, void * dev );
```


�������ж�

1�����ж��������°벿���ж������ġ����ڱ����ڼ侲̬�ķ��䣬���ܶ�̬���䡣kernel-4.9ʹ����10�����ж�(10��ö�ٱ���)��

2�����жϵ�ִ�У����е����ж϶��ᱻ do_softirq() ����ִ�С�do_softirq()��������жϵ�ִ�к������д���

3�����ʹ�����жϣ�

(1)������ö�ٱ���NR_SOFTIRQS������һ���µ�ö�ٱ����������ж����ƣ�����RCU_SOFTIRQ

(2)ע��һ�����жϣ�open_softirq( RCU_SOFTIRQ,  rcu_action ); RCU_SOFTIRQ�����ж�ö�ٱ�������rcu_action �����ж�ִ�к�����

(3)���жϴ������д������жϣ�raise_softirq(RCU_SOFTIRQ);  ����ִ�к���rcu_action �ͻ����ں���һ�ε���do_softirqʱ�õ�ִ�С�

4�����жϵ�ִ�к���Ҫ�ر�ע�Ⲣ������Ϊ������һ�����ж�ִ�к�����һ��CPU��ִ�У���������һ��CPU�ϱ�����Ȼ��ִ���ˣ���ʱ��2����ͬ�����жϾͻ���2����ͬ��CPU��ͬʱ���У��������ж���Ҫ�ϸ������������һ��ʹ�������ڲ���������������(���ݽ�������ĳ���������������������޷�ʹ�ø�����)��

5��ksoftirqd/n��n��ʾCPU����š�ÿ������������һ�������������жϵ��ں��߳� ksoftirqd ���������ȼ���ͣ�����������߳�������Դ�����ں��е����ж��ر���ʱ�����ᱻ������������Щ���ж�ִ�к���������֤�������ж��ر���ʱ���û��ռ�ĳ��򲻻�ò������������������ڿ��е�ʱ�����жϵĴ���Ҳ�ر�Ѹ�١�



�ġ�tasklet

1��tasklet�������°벿���ж������ģ���������Ҳ�����жϵ�һ�֣���ʹ����2�����ж�ö�ٱ�����ʵ���Լ���HI_SOFTIRQ(0) �� TASKLET_SOFTIRQ(6)�������������ݽṹΪ��
```c
struct tasklet_struct {
    struct tasklet_struct *next;//ָ����һ��tasklet

    unsigned long state;              
    //0��TASKLET_STATE_SCHED(�Ѿ���������׼������)
    //1��TASKLET_STATE_RUN(��������)

    atomic_t count;  
    //��0��ʾtasklet��ִֹ�У�0��ʾtasklet���������ִ�С�

    void (*func)(unsigned long);//taskletִ�к���
    unsigned long data; //����taskletִ�к���������
};
```
2�����ʹ��tasklet��

(1)��̬����һ��tasklet��
```c
DECLARE_TASKLET( name, func, data );
//��tasklet��count��Ϊ0�������taskletִ��

DECLARE_TASKLET_DISABLED( name, func, data );
//�������෴�Ĳ���

���磺
DECLARE_TASKLET(my_tasklet, tasklet_handler, dev);   
�ȼ��ڣ�
struct tasklet_struct my_tasklet{ NULL,0,ATOMIC_INIT(0),tasklet_handler,dev};

Ҳ���Զ�̬�Ĵ���һ��tasklet��
tasklet_init( struct tasklet_struct * t, void(* func)(unsigned long),  
unsigned long data );
```
(2)����ִ��tasklet�� tasklet_schedule(&my_tasklet);  ��tasklet�����Ⱥ�ֻҪ���л��ᣬ���ͻᾡ��ı�ִ�С�

(3)tasklet��ص�API
```c
tasklet_disable(&my_tasklet); 
���ڽ�ֹĳ��tasklet��������tasklet��ִ�к�������ִ�У���ô���������ȴ���ִ���꣬
Ȼ���ֹ���tasklet��

tasklet_disable_nosync(&my_tasklet); 
��ͬ����ֹtasklet������ȴ����taskletִ���꣬�ú����ͻ᷵�ء�

tasklet_enable(&my_tasklet);
ʹ��ĳ��tasklet��

tasklet_kill();
ɾ��ĳ��tasklet����ȴ����ĳ��taskletִ������ɾ����
```


�塢��������

1���������������ڽ��������ģ������ߣ���ʹ�������ɱ��жϡ�

2���ں��ṩ��һ��Ĭ�ϵĹ������߳� events/n��n��ʾCPU����ţ�ÿ��CPUӵ��һ���������̣߳�����ȱʡ�������̡߳����������Ҫִ�д����Ĳ����������Լ�����һ���������̣߳������ڼ���ȱʡ�������̵߳ĸ��أ�����ȱʡ�������߳������������ڼ���״̬��

3�������������̵߳Ľṹ�� workqueue_struct �����������Ľṹ��work_struct��

4�����ʹ�ù������У�

��1��ʹ��ȱʡ�Ĺ������У�
```c
��̬�Ĵ���һ��������
DECLARE_WORK(name,  func );

��̬�Ĵ���һ��������
static struct work_struct my_work;              
INIT_WORK(&my_work, func );

����������ԭ�ͣ�
void(*func)(struct work_struct work); 
���������������ڽ��������ģ���˯�ߣ�����Ӧ�жϡ�

����ִ�й�����
schedule_work(&my_work);              
schedule_delayed_work(&my_work, delay);

ˢ�£�
void flush_schedule_work(void);
�ȴ�event/n�����еĹ���ִ����ϲŷ��أ��ú������������ߡ�

ͨ��schedule_delayed_work()ִ�еĹ��������������ӳ�ʱ�仹û�е�����ô
flush_schedule_work()����ȴ�����ɣ���Ҫʹ��cancel_delayed_work()ȡ���ӳٹ�����
```
��2���Լ�����һ���������У�
```c
��ÿ��CPU�������������У�
struct workqueue_struct create_workqueue(name);

ֻ�ڵ�ǰCPU�����������У�
struct workqueue_struct create_singlethread_workqueue(name);

�������ύ��ָ���Ĺ������д���
int queue_work(struct workqueue_struct * wq, struct work_struct *work);
int queue_delay_work(struct workqueue_struct *wq, struct delayed_work *dwork, 
unsigned long delay);

ˢ��ָ���Ĺ������У�
void flush_workqueue( struct workqueue_struct *wq );

���ٹ������У�
void destroy_workqueue(struct workqueue_struct *wq);
```


����һЩ��ֹ�жϵ�API

1����ֹ/ʹ�ܵ�ǰ�������ϵ������жϣ�
```c
local_irq_disable();/local_irq_enable(); 
ֱ�ӽ�ֹ/ʹ�ܵ�ǰCPU�ϵ������жϡ�

local_irq_save(flags);/local_irq_restore(flags); 
�ڽ�ֹ�ж�ǰ���浱ǰCPU���ж�״̬(���ж�ջ��Ϣ)����ʹ���жϺ�ָ���ǰCPU���ж�״̬��
```
2����ָֹ����ĳһ���ж���

��1��API
```c
void disable_irq(unsigned int irq); 
��ֹ�ж���irq�ϵ������жϣ����������ȴ���ǰirq�ж����������жϴ���������֮��Ż᷵�أ�
������������������һ�����ڷ��жϴ������С�

void disable_irq_nosync(unsigned int irq); 
��������Ƿ�ͬ���ģ�����ȴ�irq���ϵ��жϴ�����ɾͻ᷵�أ�
�����������������������ܹ������жϴ������С�

void enable_irq(unsigned int irq); 
ʹ��ĳһ���ж��ߵ��ж�
```
��2��ΪʲôҪ��ֹ�ж��ߣ�

��һ���жϴ������֮��Ȼ����жϴ�����򷵻أ���������������������ʱ�����жϴ����������ִ�е�ʱ������Ӳ���ָ��ж��߷���һ���жϣ����Ǵ�ʱ��ǰ�жϻ�û����ɣ�����������жϵ�Ƕ�ף�����Linux��ֹ�ж�Ƕ�ס����ԣ�����ĳЩ�жϲ���Ƶ����Ӳ����˵(���о����)���ڽ����жϴ����ʱ��Ҫ��ֹ�ж��ߣ��������ܱ����ж�Ƕ�׵Ĳ�����

��3��ע�⣬�������жϴ�������ʹ��disable_irq()����Ϊ�������������ߣ����жϴ����ֹ���ߡ�

��4�����ʹ����Щ�ж���API��

һ������ʹ�ã����ж��ϰ벿�жϴ������� disable_irq_nosync()����ֹ�ж��ߣ�Ȼ�����ִ��ĳ���������н����ж��°벿��Ȼ���ڹ��������˳�֮ǰenable_irq()��

3����ֹ/ʹ�ܵ�ǰCPU���°벿�ж�

local_bh_disable();/local_bh_enable; //��ֹ/ʹ�ܵ�ǰCPU�ϵ��°벿�ж�(��ʵ�ǽ�ֹ/ʹ�ܵ�ǰCPU�ϵ����жϺ�tasklet�Ĵ���)��

4�����������Ĺ�ϵ

��ֹ/ʹ�ܵ�ǰ�������ϵ������ж� local_irq_disable();/local_irq_enable();  ��

��ֹ/ʹ�ܵ�ǰCPU���°벿�ж� local_bh_disable();/local_bh_enable();

��2�ֺ���һ�������������ʹ�ã���Ϊ�������еĴ�����ܻᱻ�жϻ����°벿����ϣ������ڻ�ȡ������֮��Ҫ��ֹ�жϻ��°벿���˳�������֮��ʹ���жϻ��°벿��
```c
spin_lock();       
spin_unlock();      
   
local_irq_disable();
local_irq_enable();

local_bh_disable();
local_bh_enable();
```


�ߡ��ȴ�����

1���ж���ʱ��Ҳʹ�õȴ�������ʵ�֡�

2���ȴ�����ʹ�����ӣ�
```c
static wait_queue_head_t my_wait_queue_head;
����һ���ȴ�����ͷ

static atomic_t my_atomic = ATOMIC_INIT(0);
�ȴ���������

static task_struct *my_task;
�ں��߳�

request_irq(irq_num,  my_irq_handler, NULL, "my_irq", NULL);
ע���жϴ�����

my_task=kthread_create(my_task_func, NULL, "my_task");
�����ں��߳�

init_waitqueue_head(&my_wait_queue_head);
��ʼ���ȴ�����ͷ

wake_up_process(my_task);
ִ���ں��߳�

static int my_task_func( void *data ) 
{
        wait_event_interruptible( my_wait_queue_head, atomic_read(&my_atomic);
        //�߳�ִ�к�������������
        return 0;
}

static irqreturn_t my_irq_handler( int irq, void * dev) 
{
        atomic_set( &my_atomic,  1);//���ȴ�����������1
        wake_up_interruptible(&my_wait_queue_head);//���������ڵȴ�����ͷ�ϵ��߳�

}
```
3����� wait_event_interruptible(wq, condition)

��1���ú����������ǣ���һ���߳����ߵ��ȴ�����ͷwq�ϡ�

��2���ú������Ȼ���condition�����conditionΪ�棬��������0�������߸��̡߳�

��3�����conditionΪ�٣��ó����������������ߡ�ֱ��condition��Ϊ�����ʹ����wake_up_interruptible(wq) ���߳��˳����ߣ�����ִ�С�



�ˡ����Գ���

1��ʲôʱ��ʹ���ϰ벿����ôʱ��ʹ���°벿��

��һ�������ʱ�����С���һ�������Ӳ��������ء���һ������Ҫ��֤���������жϸ���ϣ��������������ϰ벿��ɡ�

��������������ŵ��°벿ִ�С�

�ϰ벿������Ӧ�жϣ��°벿������Ӧ�жϡ�

2��ʲôʱ��ʹ�����жϡ�tasklet���������У�

���жϱ��뱣֤�������ݵİ�ȫ����Ϊ2����ͬ�����жϿ�����2����ͬ�Ĵ�������ͬʱ���У�����������ϵͳʹ�õ����������������жϷǳ��ʺϡ�����ִ��Ƶ�ʸߺͶ�ʱ��Ҫ���ϸ���������жϷǳ��ʺϡ�

tasklet�������ж�ʵ�֣�����taskletֻ���ڵ������Ĵ�������ִ�У�����������2����ͬ��tasklet����ͬʱִ�У��ڲ�ͬ�Ĵ�����Ҳ����ͬʱִ�С������������ȿ���ʹ��tasklet���ٿ���ʹ�����жϡ�tasklet���ں̵ܶ�ʱ���ڱ�ִ�У�������ԭ�ӷ�ʽִ�С�

���жϺ�tasklet�������ж������ģ��������ߣ�ʹ����֮ǰ�����ֹ�жϡ��������������ڽ��������ģ��������ߣ�����ʹ�������������߶�������Ӧ�жϡ�

3���°벿���ֻ������жϡ�tasklet���������е����������

��1�����жϣ�

�������ж������ģ���������/����/ʹ�û�����mutex����������Ӧ�жϡ����ж�ִ�нϿ죬���ڶ�ʱ�����е�����

2����ͬ�����ж�ִ�к���������2����ͬ��CPU��ͬʱִ�У��������жϱ����ϸ�������������ж�һ�����ڴ������������ݡ�

���ں�����ĳһ��ʱ����ִ������жϴ�����ʱ����ʱ���ں��߳�ksoftirqd/n(n��ʾCPU�����)�ͻᱻ���ѣ����������ж�ִ�к������Ա�֤�û��ռ�ĳ��򲻱�������

���жϵ��ŵ��������Ŀ���չ�ԣ��������ڲ�ͬCPU��ִ��ͬһ���жϣ�������Ҫ�������ʱ��ʹ��tasklet��

ʹ�����ж�ʱֻ�ܾ�̬���壺����һ�����ж�ö�ٱ�����ע�����жϴ�������Ȼ�����ж��ϰ벿�д��������жϡ��˳��ж��ϰ벿�����жϾͻᱻ�ں�ͨ�����ú��� do_softirq() ִ�С�

��2��tasklet��

�������ж������ģ���������/����/ʹ�û�����mutex����������Ӧ�жϡ�taskletִ�нϿ죬���ڶ�ʱ�����е�����

tasklet������ͨ�����ж���ʵ�ֵģ���ʹ����2�����ж�ö�ٱ�����HI_SOFTIRQ(0)��TASKLET_SOFTIRQ(6)��

1��taskletֻ���ڵ�������CPU��ִ�У�����������CPU��ִ�С�2����ͬ��tasklet������2����ͬ��CPU��ͬʱִ�С�

tasklet��ʹ�÷����ܼ򵥣�����ͨ����̬DECLARE_TASKLET���߶�̬tasklet_inti()����һ��tasklet��Ȼ�����ִ�������ɣ�tasklet_schedule()��tasklet������֮��ֻҪ�л������ͻ�����ִ�С�

��3���������У�

�����ڽ��������ģ���������/����/ʹ�û�����mutex����������Ӧ�жϡ�

�ں�����һ��ȱʡ�Ĺ������߳�events/n(n��ʾCPU�����)������ʹ�ã�����ʹ���ں��ṩ�Ĺ������̣߳�Ҳ�����Լ�������������n���������̡߳�

�����ǵ�work�Ƚϸ���ʱ��һ���Լ�����һ���������̣߳��������ں�ȱʡ�Ĺ������̵߳������������ڼ���״̬��

�������е�ʹ�÷��������ʹ���ں�ȱʡ�Ĺ������߳�events/n��

���Ⱦ�̬����DECLARE_WORK���߶�̬����INIT_WORKһ��������Ȼ�󽫸ù����ŵ�events/n��ȥִ�м��ɣ�schedule_work();/schedule_delayed_work;

���ʹ���Լ������Ĺ������̣߳�

��������/n���������̣߳�create_singlethread_workqueue();/create_workqueue();

Ȼ���ύ�������������߳�ȥִ�У�queue_work();/queue_delayed_work();



�š��ο�����
1��Linux kernel development
2��Linux device driver
3�������ں��Ŷӣ�http://kernel.meizu.com/linux-interrupt.html
4�����ѿƼ���http://www.wowotech.net/sort/irq_subsystem


