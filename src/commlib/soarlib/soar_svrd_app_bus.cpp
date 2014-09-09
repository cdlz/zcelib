#include "soar_predefine.h"
#include "soar_zerg_frame.h"
#include "soar_svrd_app_bus.h"
#include "soar_zerg_mmappipe.h"
#include "soar_error_code.h"

Comm_SvrdApp_BUS::Comm_SvrdApp_BUS() :
    Comm_Svrd_Appliction(),
    nonctrl_recv_buffer_(NULL)
{
    nonctrl_recv_buffer_ = new (Zerg_App_Frame::MAX_LEN_OF_APPFRAME) Zerg_App_Frame();
}

Comm_SvrdApp_BUS::~Comm_SvrdApp_BUS()
{
    //�ͷ���Դ
    if (nonctrl_recv_buffer_)
    {
        delete nonctrl_recv_buffer_;
        nonctrl_recv_buffer_ = NULL;
    }
}

//���к���
int Comm_SvrdApp_BUS::on_run()
{
    ZLOG_INFO("======================================================================================================");
    ZLOG_INFO("[framework] app %s class [%s] run_instance start.",
        get_app_basename(),
        typeid(*this).name());

    //����N�κ�,����SELECT�ĵȴ�ʱ����
    const unsigned int LIGHT_IDLE_SELECT_INTERVAL = 128;
    //����N�κ�,SLEEP��ʱ����
    const unsigned int HEAVY_IDLE_SLEEP_INTERVAL = 10240;

    //microsecond
    // 64λtlinux��idle��ʱ�����̫�̻ᵼ��cpu����
    const int LIGHT_IDLE_INTERVAL_MICROSECOND = 10000;
    const int HEAVY_IDLE_INTERVAL_MICROSECOND = 100000;

    /// һ���������FRAME����
    static const size_t MAX_ONCE_PROCESS_FRAME = 2048;

    //
    size_t size_io_event = 0 , size_timer_expire  = 0;

    size_t prc_frame = 0, idle = 0, proc_data_num = 0;

    ZCE_Time_Value select_interval(0, 0);

    ZCE_Timer_Queue *time_queue = ZCE_Timer_Queue::instance();
    ZCE_Reactor *reactor = ZCE_Reactor::instance();

    for (; app_run_;)
    {
        //�����յ�������
        popfront_recvpipe(MAX_ONCE_PROCESS_FRAME, prc_frame);

        size_timer_expire = time_queue->expire();

        //���û�д����κ�֡
        // �����ܵ��İ�����Ҫ�������������˵���ܵ��Ѿ�����
        if (prc_frame < MAX_ONCE_PROCESS_FRAME && size_timer_expire <= 0 && proc_data_num <= 0)
        {
            ++idle;
        }
        else
        {
            idle = 0;
        }

        // �����ѭ��̫�����װ׺ĵ粻��̼
        // ����������˯�����ʱ����100����
        // ���ֻҪ�ڴ�ܵ���С>=100�������ϵͳ��������*ÿ�����ֽ���
        // ����˯���Ժ��ܹ������������ݶ������ڹܵ�����������
        // ����ϵͳ������Դ���ã���ô������������������������
        // ������1Gbit���㣬��ܵ��ٽ��СΪ1Gbit-per(S)/8/10��12MByte���ټ��Ϲܵ��������ڴ�ṹռ��
        // ����Ϊ16MByteҲ�����ԣ�����ֻҪ�ܵ���С����16MByteӦ�þͶ���ס��
        // ��������Ͳ��ÿ�����ô����ˡ�
        if (idle < LIGHT_IDLE_SELECT_INTERVAL)
        {
            continue;
        }
        //������кܶ�,��Ϣһ��,�����ȽϿ��У������SELECT�൱��Sleep��
        else if (idle >= HEAVY_IDLE_SLEEP_INTERVAL)
        {
            select_interval.usec(HEAVY_IDLE_INTERVAL_MICROSECOND);
        }
        //else �൱�� else if (idle >= LIGHT_IDLE_SELECT_INTERVAL)
        else
        {
            select_interval.usec(LIGHT_IDLE_INTERVAL_MICROSECOND);
        }

        //
        reactor->handle_events(&select_interval, &size_io_event);
    }

    ZLOG_INFO("[framework] app %s class [%s] run_instance end.",
              get_app_basename(),
              typeid(*this).name());
    return 0;
}

//�ӹܵ�����ȡһ�����ݽ��д���
int Comm_SvrdApp_BUS::popfront_recvpipe(size_t max_prc,size_t &proc_frame)
{
    int ret = 0;

    //һ�δ�������������
    for (proc_frame = 0;
         zerg_mmap_pipe_->is_empty_bus(Zerg_MMAP_BusPipe::RECV_PIPE_ID) == false
         && proc_frame < max_prc;
         ++proc_frame)
    {
        //
        ret = zerg_mmap_pipe_->pop_front_recvpipe(nonctrl_recv_buffer_);

        if (ret !=  0)
        {
            return 0;
        }

        DEBUGDUMP_FRAME_HEAD(nonctrl_recv_buffer_, "FROM RECV PIPE FRAME", RS_DEBUG);

        //����һ���յ�������
        ret = process_recv_appframe(nonctrl_recv_buffer_);

        //
        if (ret !=  0)
        {
            continue;
        }
    }

    //
    return 0;
}