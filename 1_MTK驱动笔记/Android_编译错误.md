
```c

vendor/mediatek/proprietary/hardware/mtkcam/acdk/entry_mdk/entry_mdk.cpp:99: error: undefined reference to '__android_log_print'
vendor/mediatek/proprietary/hardware/mtkcam/acdk/entry_mdk/entry_mdk.cpp:118: error: undefined reference to '__android_log_print'
vendor/mediatek/proprietary/hardware/mtkcam/acdk/entry_mdk/entry_mdk.cpp:145: error: undefined reference to '__android_log_print'
vendor/mediatek/proprietary/hardware/mtkcam/acdk/entry_mdk/entry_mdk.cpp:172: error: undefined reference to '__android_log_print'
�����Android.mk�м��ϣ�LOCAL_SHARED_LIBRARIES += libcutils


vendor/mediatek/proprietary/hardware/mtkcam/acdk/entry_mdk/entry_mdk.cpp:95: error: undefined reference to 'dlopen'
vendor/mediatek/proprietary/hardware/mtkcam/acdk/entry_mdk/entry_mdk.cpp:98: error: undefined reference to 'dlerror'
vendor/mediatek/proprietary/hardware/mtkcam/acdk/entry_mdk/entry_mdk.cpp:114: error: undefined reference to 'dlsym'
vendor/mediatek/proprietary/hardware/mtkcam/acdk/entry_mdk/entry_mdk.cpp:117: error: undefined reference to 'dlerror'
�����Android.mk�м��ϣ�LOCAL_SHARED_LIBRARIES += libdl


vendor/ageing/stress/stress.cpp:48: error: undefined reference to 'ui_fill'
vendor/ageing/stress/stress.cpp:49: error: undefined reference to 'ui_flip'
vendor/ageing/stress/stress.cpp:52: error: undefined reference to 'ui_color'
vendor/ageing/stress/stress.cpp:53: error: undefined reference to 'ui_fb_width'
vendor/ageing/stress/stress.cpp:53: error: undefined reference to 'ui_fb_height'
vendor/ageing/stress/stress.cpp:53: error: undefined reference to 'ui_fill'
vendor/ageing/stress/stress.cpp:54: error: undefined reference to 'ui_flip'
collect2: error: ld returned 1 exit status
�����Android.mk�м��ϣ�LOCAL_STATIC_LIBRARIES += libminiui



target Executable: factory (out/target/product/top8321_fgemmc/obj/EXECUTABLES/factory_intermediates/LINKED/factory)
vendor/mediatek/proprietary/factory/src/test/ftm_btdemo.cpp:369: error: undefined reference to 'OSSocketInitClientBt(TW_OSSocketDomain, OS_bt_callbacks_t*)'
vendor/mediatek/proprietary/factory/src/test/ftm_btdemo.cpp:384: error: undefined reference to 'OSSocketInitServerBt(TW_OSSocketDomain, OS_bt_callbacks_t*)'
collect2: error: ld returned 1 exit status
�������OSSocket.h����ӣ�
int OSSocketInitServerBt(TW_OSSocketDomain domain, OS_bt_callbacks_t * os_bt_callbacks_t);
int OSSocketInitClientBt(TW_OSSocketDomain domain, OS_bt_callbacks_t * os_bt_callbacks_t);



���뱨��
make:����Ŀ¼'/work2/1-POS/MB416/MB416_factory'
target Executable: testclock (out/target/product/top8321_fgemmc/obj/EXECUTABLES/testclock_intermediates/LINKED/testclock)
vendor/USDK/libusdk/clock/test.cpp:276: error: undefined reference to 'property_set'
collect2: error: ld returned 1 exit status
make: *** [out/target/product/top8321_fgemmc/obj/EXECUTABLES/testclock_intermediates/LINKED/testclock] ���� 1
make:�뿪Ŀ¼��/work2/1-POS/MB416/MB416_factory��

�����
Android.mk�����  LOCAL_SHARED_LIBRARIES := libcutils
���������ͷ�ļ��� #include <cutils/properties.h>



����send dataʧ�ܣ�
I/AEE/AED (  851): backtrace:
I/AEE/AED (  851):     #00 pc 0003de88  /system/lib/libc.so (sendto+20)
I/AEE/AED (  851):     #01 pc 00017be1  /system/lib/libc.so (send+8)
I/AEE/AED (  851):     #02 pc 00011da1  /system/lib/libusdk.so (OSSend+44)
I/AEE/AED (  851):     #03 pc 00058305  /system/bin/factory
I/AEE/AED (  851):     #04 pc 0005367f  /system/bin/factory
I/AEE/AED (  851):     #05 pc 0004264d  /system/bin/factory (main+1744)
I/AEE/AED (  851):     #06 pc 00012471  /system/lib/libc.so (__libc_init+44)
I/AEE/AED (  851):     #07 pc 00043f90  /system/bin/factory
E/        (  237): [TAG] fail to send data to fd: 0.  len=-1
ԭ������bondedʧ������ġ�



target Executable: factory (out/target/product/top8321_fgemmc/obj/EXECUTABLES/factory_intermediates/LINKED/factory)
vendor/mediatek/proprietary/factory/src/test/ftm_btdemo.cpp:195: error: undefined reference to 'BtSspReply(unsigned char*, int, int, int)'
collect2: error: ld returned 1 exit status
make: *** [out/target/product/top8321_fgemmc/obj/EXECUTABLES/factory_intermediates/LINKED/factory] ���� 1
ԭ����ΪC������û�� bool ���͡�



client bt����AEE����
Abort message: 'FORTIFY_SOURCE: memcpy: prevented write past end of buffer. Calling abort()
#08 pc 000113d5  /system/lib/libusdk.so (_ZL38bt_remote_device_properties_callback_t11bt_status_tP11bt_bdaddr_tiP13bt_property_t+252)
�����
��λ��bt_remote_device_properties_callback_t()������memcpy����
��
uint8_t uuid[16];
memcpy((uint8_t *)uuid, (uint8_t *)ptr->val, len);
�ĳɣ�
uint8_t uuid[128];
memcpy(uuid, (uint8_t *)ptr->val, len);


```

