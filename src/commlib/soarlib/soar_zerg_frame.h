
#ifndef SOARING_LIB_SERVER_APP_FRAME_H_
#define SOARING_LIB_SERVER_APP_FRAME_H_

#include "soar_enum_define.h"
#include "soar_service_info.h"
#include "soar_frame_command.h"
#include "soar_error_code.h"

#pragma pack (1)


/*!
* @brief      FRAME��ѡ���ֽڵ�UNION�ṹ
*             
*/
struct _ZERG_FRAME_OPTION
{
public:

    //frame_option_��ͷ24��BIT��Ϊѡ���ֶ�,,
    unsigned int         inner_option_: 24;

    //��4BIT��Ϊ�汾��ʶ
    unsigned int         frame_version_: 8;
};



/*!
* @brief      Zerg�������䴫����Ϣ��ͨ��֡ͷ
*             
*/
class SOARING_EXPORT Zerg_App_Frame
{
public:

    //֡������,��frame_option_�ֶ�ʹ��
    enum PET_APPFRAME_OPTION
    {
        //-----------------------------------------------------------------
        //��16λ�����ڲ�������

        //
        DESC_DEFUALT             = 0x0,

        //�����ȼ���û��ʹ�ã�
        DESC_HIGH_PRIORITY       = 0x1,

        //ĳ������֡����ʧ��,֪ͨ����ķ���
        DESC_SEND_ERROR          = 0x2,

        //�������ʧ��,�ظ����Է���
        DESC_SEND_FAIL_RECORD    = 0x4,
        //�������ʧ��,֪ͨ�����Ӧ�ý���
        DESC_SNDPRC_NOTIFY_APP   = 0x8,

        //������ͳɹ���,ֱ�ӶϿ����ӣ����ڲ���TCP�Ķ�����
        DESC_SNDPRC_CLOSE_PEER   = 0x10,

        //�ڰ���׷�ӵ�¼KEY
        DESC_APPEND_SESSION_KEY  = 0x20,

        //�ڰ���׷�ӵ�¼ip
        DESC_APPEND_LOGIN_IP     = 0x40,

        //Ĭ�ϵ�ͨѶ֡����TCP�ģ���������ֱ�ʾ���֡��UDP��
        DESC_UDP_FRAME           = 0x80,

        //�����TCP��֡,��ʵĬ����TCP��֡,������ʵû��ʹ��
        DESC_TCP_FRAME           = 0x100,

        //-----------------------------------------------------------------
        //��16λ�����ⲿ������,8λ������
        DESC_MONITOR_TRACK       = 0x10000,

        //FRAME�����������û�ǩ��
        DESC_HEAD_WITH_SIGNATURE = 0x20000,

        //֡�����ݲ��ü���
        DESC_SESSION_ENCRYPT     = 0x40000,

        //�����ĳЩ����ü��ܽ��д��������ڼ������ĳЩ����������ܵ��������
        DESC_SPECIAL_NO_ENCRYPT  = 0x80000,

        //APPFram�İ汾V1
        DESC_V1_VERSION          = 0x1000000,
        //APPFram�İ汾V2�����ڻ���������һ��
        DESC_V2_VERSION          = 0x2000000,
    };

    //�ڲ�ѡ������������,�ڲ�ѡ��������俴��������ͨѶ��������ҵ�������ǰ�ɼ���
    static const unsigned int INNER_OPTION_MASK = 0xFFFF;
    //�ⲿѡ������+�汾�ŵ�����
    static const unsigned int OUTER_OPTION_MASK = 0xFFFF0000;

public:

    //��ͷ���ߴ�,
    static const size_t LEN_OF_APPFRAME_HEAD = 50;

    //APPFAME�汾V1
    static const unsigned char TSS_APPFRAME_V1 = 1;

    //---------------------------------------------------------------------------
    //FRAME��һЩ���Ȳ���,

    //frame_appdata_����󳤶�
#if defined    HUGE_LEN_OF_APPFRAME
    static const size_t MAX_LEN_OF_APPFRAME  = 256 * 1024;
#elif defined  LARGE_LEN_OF_APPFRAME
    static const size_t MAX_LEN_OF_APPFRAME  = 128 * 1024;
#elif defined  MIDDLE_LEN_OF_APPFRAME
    static const size_t MAX_LEN_OF_APPFRAME  = 32 * 1024;
#elif defined  TINY_LEN_OF_APPFRAME
    static const size_t MAX_LEN_OF_APPFRAME  = 16 * 1024;
#else

    //Ĭ�ϵ���󳤶���64K
    //Ϊʲô����64K��ԭ�������ǵ�UPD����󳤶����������������������ĳ��ȱȽ�����.
    static const size_t MAX_LEN_OF_APPFRAME  = 64 * 1024;
#endif

    //TEA���ܺ����ӵĳ���,UPD���������鷳�Լ���೤�����Ƶ�����
    static const size_t LEN_OF_TEA_REMAIN_ROOM = 17;

    //FRAME����󳤶�,���ݸ����ط��ĳ��ȶ��õ�
    static const size_t MAX_LEN_OF_APPFRAME_DATA = MAX_LEN_OF_APPFRAME - LEN_OF_APPFRAME_HEAD - LEN_OF_TEA_REMAIN_ROOM;

    //
    static const size_t MAX_LEN_OF_TEA_APPDATA = MAX_LEN_OF_APPFRAME_DATA + LEN_OF_TEA_REMAIN_ROOM;

public:

    //����ͨѶ������,����ռ�,����֡ͷ�ĳ���.
    unsigned int            frame_length_;

    union
    {
        unsigned int        frame_option_;
        //
        _ZERG_FRAME_OPTION   inner_option_;
    };

    //������ �����ֻ��Ƿ��ڰ�ͷ�ȽϺ�,
    unsigned int            frame_command_;

    //UIN    �û�QQ����,
    unsigned int            frame_uin_;

    //���ͺͽ��յķ�����Ӧ��ҲҪ��д

    //���ͷ���,�������ͷ��������ͣ����ͷ��������,û�б�ţ����߲��Ƿ�����д0
    SERVICES_ID             send_service_;
    //���ܷ�����
    SERVICES_ID             recv_service_;
    //����������
    SERVICES_ID             proxy_service_;

    //����ID,�����������������Ϊһ����ʾ������ķ���������backfill_trans_id_�ֶη���,
    unsigned int            transaction_id_;
    //����������ߵ�����ID,
    unsigned int            backfill_trans_id_;

    //ҵ��ID��GAMEID�����ڱ�ʶ��Ϸ�ڲ�ID
    unsigned int            app_id_;

    union
    {
        //�������кţ��ƻ�ֻ��ͨѶ����,��ʱû����
        unsigned int       send_serial_number_;
        //�����ߵ�IP��ַ���ڲ�ʹ��
        unsigned int       send_ip_address_;

    };

    //frame_appdata_ ��һ���䳤�ȵ��ַ������б�ʾ,
#ifdef ZCE_OS_WINDOWS
#pragma warning ( disable : 4200)
#endif
    char                 frame_appdata_[];
#ifdef ZCE_OS_WINDOWS
#pragma warning ( default : 4200)
#endif

public:
    //���캯������Ҷ������õ�.
    Zerg_App_Frame(unsigned int cmd = CMD_INVALID_CMD,
                   unsigned int lenframe = LEN_OF_APPFRAME_HEAD,
                   unsigned int frameoption = DESC_V1_VERSION);

    //���캯��,����,�ͻ��˳�ʼ��,
    Zerg_App_Frame(unsigned int cmd,
                   unsigned int lenframe,
                   unsigned int uin,
                   unsigned short sndsvrtype,
                   unsigned short rcvsvctype,
                   unsigned int frameoption = DESC_V1_VERSION);

    //���캯��,���ڷ��͸�һ���Ǵ���������
    Zerg_App_Frame(unsigned int cmd,
                   unsigned int lenframe,
                   unsigned int uin,
                   const SERVICES_ID sndsvr,
                   SERVICES_ID rcvsvc,
                   unsigned int frameoption = DESC_V1_VERSION);

    //���캯��,���ڷ��͸�һ������������
    Zerg_App_Frame(unsigned int cmd,
                   unsigned int lenframe,
                   unsigned int uin,
                   const SERVICES_ID &sndsvr,
                   const SERVICES_ID &proxy,
                   unsigned short rcvsvc,
                   unsigned int frameoption = DESC_V1_VERSION);

    //��������
    ~Zerg_App_Frame();

    //Assign =�������
    Zerg_App_Frame &operator = (const Zerg_App_Frame &other);

    //�Ƿ����ڲ�����������
    inline bool is_internal_process(bool &bsenderr);
    //�Ƿ���ͨ�ŷ���������������
    inline bool is_zerg_processcmd();

    //�����ڲ���ѡ����Ϣ
    inline void clear_inner_option();
    //�������е�ѡ������
    inline void clear_all_option();

    //��֡ͷ�����е�unsigned short,unsigned intת��Ϊ������
    void framehead_encode();
    //��֡ͷ�����е�unsigned short,unsigned intת��Ϊ������
    void framehead_decode();

    //��ʼ��V1�汾�İ�ͷ,����������0
    void init_framehead(unsigned int lenframe,
                        unsigned int option = 0,
                        unsigned int cmd = 0);

    //��䷢��SVR��Ϣ
    void set_send_svcid(unsigned short svrtype, unsigned int svrid);
    //��䷢��SVR��Ϣ
    void set_recv_svcid(unsigned short svrtype, unsigned int svrid);
    //������SVR��Ϣ
    void set_proxy_svcid(unsigned short svrtype, unsigned int svrid);

    //��д���еķ�����Ϣ,
    void set_all_svcid(const SERVICES_ID &rcvinfo, const SERVICES_ID &sndinfo, const SERVICES_ID &proxyinfo);

    //���AppData���ݵ�APPFrame
    int fill_appdata(const size_t szdata, const char *vardata);

    //����Rcv ,Snd SvrInfo
    void exchange_rcvsnd_svcid();
    //����Rcv ,Snd SvrInfo,prochandle
    void exchange_rcvsnd_svcid(Zerg_App_Frame &exframe );
    //����ذ�ͷ
    void fillback_appframe_head(Zerg_App_Frame &exframe );

    //Cloneһ��APP FRAME
    Zerg_App_Frame *CloneAppFrame() const;
    //
    void CloneAppFrame(Zerg_App_Frame *clone_frame) const;
    //
    void CloneFrameHead(Zerg_App_Frame *clone_frame) const;

    //Dumpͷ����DATA��������
    void dump_appframe_info(std::ostringstream &strstream) const;
    //Dump���е�������Ϣ,һ���ֽ��ֽڵĸ�����,
    void dump_appframe_data(std::ostringstream &strstream) const;
    //Dump���ݰ�ͷ�е���Ҫ��Ϣ����,
    void dump_appframe_head(std::ostringstream &strstream) const;

    //���APPFRAME��ͷ����Ϣ
    void dumpoutput_framehead(const char *outstr,
                              ZCE_LOG_PRIORITY log_priority) const;
    //���APPFRAME��β����Ϣ
    void dumpoutput_frameinfo(const char *outstr,
                              ZCE_LOG_PRIORITY log_priority)  const;

    //ȡ��֡�ĳ���
    inline size_t get_appframe_len() const;
    //ȡ��֡���ݵĳ���
    inline size_t get_frame_datalen() const;

    //TDR AppCode����,szframe_appdataΪframe_appdata_��buffer����,���frame_appdata_Ϊһ������,ʹ�ô˺���
    template<class T> int appdata_encode(
        size_t szframe_appdata,
        const T &info,
        size_t data_start = 0,
        size_t *sz_code = NULL);

    //TDR AppCode����,
    template<class T> int appdata_decode(
        T &info,
        size_t data_start = 0,
        size_t *sz_code = NULL) const;

    //����Output CDR�е�Msg,Block����,szframe_appdataΪframe_appdata_��buffer����,���frame_appdata_Ϊһ������,ʹ�ô˺���
    //ssize_t CopyCDRMsgBlock(size_t szframe_appdata,const ACE_OutputCDR& outcdr );
    //���AppFrameΪһ��ǡ�ó��ȵ�Frame,�����Ѿ���д,ʹ�ô˺���,
    //ssize_t CopyCDRMsgBlock(const ACE_OutputCDR& outcdr);

    //ȡ��IP��ַ��Ϣ
    unsigned int get_send_ip() const;

    //-----------------------------------------------------------------------------------
    //FRAME�����ݽ���TEA�㷨���ܽ��ܵĺ�������֪��Jovi����ΪɶҪд��STATIC�ģ��Ǻ�
    //APPDATA��������
    int appframe_encrypt(const char *session_key,
                         size_t data_start = 0);
    //APPDATA���ݽ���,
    int appframe_decrypt(const char *session_key,
                         size_t data_start = 0);

    //��APPDATA��������,�������ݱ��浽����Zerg_App_Frame��
    int appframe_encrypt(const char *session_key,
                         Zerg_App_Frame *dest_frame,
                         size_t data_start = 0);
    //��APPDATA���ݽ���,�������ݱ���������һ��Zerg_App_Frame��
    int appframe_decrypt(const char *session_key,
                         Zerg_App_Frame *dest_frame,
                         size_t data_start = 0);

public:

    //
    static Zerg_App_Frame *FillDatainAppFrame(const size_t szdata, const char *vardata);

    //����New����
    static void   *operator new (size_t , size_t lenframe = LEN_OF_APPFRAME_HEAD);
    //������delte��������ͨ��������ʵû��ʲô����,
    static void operator delete(void *ptrframe, size_t );

    //ֱ��ʹ��һ��buf��Ϊ�����
    //static ssize_t CopyCDRMsgBlock(char *buf,size_t szbuf,const ACE_OutputCDR& outcdr);

    //���APPFRAME��ͷ����Ϣ
    static void dumpoutput_framehead(const Zerg_App_Frame *proc_frame,
                                     const char *outstr,
                                     ZCE_LOG_PRIORITY log_priority);
    //���APPFRAME��β����Ϣ
    static void dumpoutput_frameinfo(const Zerg_App_Frame *proc_frame ,
                                     const char *outstr,
                                     ZCE_LOG_PRIORITY log_priority);

    //--------------------------------------------------------------------------
    //FRAME�����ݽ���TEA�㷨���ܽ��ܵĺ�����STATIC��������֪��Jovi����ΪɶҪд��STATIC�ģ��Ǻ�
    //����ǩ����
    static void signature_construct(Zerg_App_Frame *&proc_frame, unsigned int uin, const char *pSignature, size_t len);

};

#pragma pack ()

//�����ڲ���ѡ����Ϣ
inline void Zerg_App_Frame::clear_inner_option()
{
    frame_option_ &=  OUTER_OPTION_MASK;
}
//�������е�ѡ������
inline void Zerg_App_Frame::clear_all_option()
{
    frame_option_ = 0;
}

//�õ�֡���ܳ���
inline size_t Zerg_App_Frame::get_appframe_len() const
{
    return frame_length_;
}
//�õ�֡ͷ�ܳ���
inline  size_t Zerg_App_Frame::get_frame_datalen() const
{
    return frame_length_ - LEN_OF_APPFRAME_HEAD;
}

//�õ������ߵ�IP��ַ,�����ֽ���ģ�
inline unsigned int Zerg_App_Frame::get_send_ip() const
{
    return send_ip_address_;
}

//�Ƿ���ͨ�ŷ���������������
inline bool Zerg_App_Frame::is_zerg_processcmd()
{
    if (frame_command_ >= ZERG_COMMAND_BEGIN && frame_command_ <= ZERG_COMMAND_END)
    {
        return true;
    }

    return false;
}

//��������Ƿ����ڲ���������
inline bool  Zerg_App_Frame::is_internal_process(bool &bsenderr)
{
    bsenderr = false;

    if (frame_command_ >= INTERNAL_COMMAND_BEGIN && frame_command_ <= INTERNAL_COMMAND_END)
    {
        return true;
    }

    if (frame_option_ & DESC_SEND_ERROR)
    {
        bsenderr = true;
        return true;
    }

    return false;
}

/******************************************************************************************
Author          : Yunfeiyang  Date Of Creation: 2007��3��12��
Function        : Zerg_App_Frame::appdata_decode
Return          : template<class T> int
Parameter List  :
  Param1: size_t szframe_appdata FRAME��APPDATA�����ݳ��ȣ�ע�ⲻ������APPFRMAE�ĳ���
  Param2: const T& info          ���������
  Param3: size_t data_start      ��DATA���ĵڼ���λ�ÿ�ʼ������ݣ�Ĭ��Ϊ0
  Param4: size_t *sz_code        �����ϵ��������ݳ��ȣ�����һ��ָ��õ����ȣ�Ĭ��ΪNULL,��ʾ������
Description     : frame_appdata_�ı��뺯��
Calls           :
Called By       :
Other           :
Modify Record   :
******************************************************************************************/
template<class T>
int Zerg_App_Frame::appdata_encode(size_t szframe_appdata,
                                   const T &info,
                                   size_t data_start,
                                   size_t *sz_code)
{
    size_t use_len = 0;
    int ret = info.pack(frame_appdata_ + data_start,
                        szframe_appdata - data_start, &use_len);

    if (ret == 0 && sz_code != NULL)
    {
        *sz_code = use_len;
    }

    if (ret != 0)
    {
        return SOAR_RET::ERROR_CDR_ENCODE_FAIL;
    }

    // ����frame�ĳ���
    frame_length_
        = (unsigned int)(data_start + use_len + LEN_OF_APPFRAME_HEAD);
    return SOAR_RET::SOAR_RET_SUCC;
}

/******************************************************************************************
Author          : Sailzeng <sailerzeng@gmail.com>  Date Of Creation: 2007��3��12��
Function        : Zerg_App_Frame::appdata_decode
Return          : template<class T> int
Parameter List  :
  Param1: T& info           ����ת���Ľṹ
  Param2: size_t data_start ��DATA���ĵڼ���λ�ÿ�ʼ�������ݣ�Ĭ��Ϊ0
  Param3: size_t *sz_code   �����ϵ��������ݳ��ȣ�����һ��ָ��õ����ȣ�Ĭ��ΪNULL,��ʾ������
Description     : frame_appdata_�Ľ��뺯��
Calls           :
Called By       :
Other           :
Modify Record   :
******************************************************************************************/
template<class T>
int Zerg_App_Frame::appdata_decode(  T &info,
                                     size_t data_start,
                                     size_t *sz_code) const
{
    size_t use_len = 0;

    // frame_length_������frameͷ�����ݵģ�����Ҫ����
    int ret = info.unpack(frame_appdata_ + data_start,
                          frame_length_ - data_start - LEN_OF_APPFRAME_HEAD, &use_len);

    if (ret == 0 && sz_code != NULL)
    {
        //���Ҫ�õ��������ݵĳ���
        *sz_code = use_len;
    }

    if (ret != 0)
    {
        return SOAR_RET::ERROR_CDR_ENCODE_FAIL;
    }

    return SOAR_RET::SOAR_RET_SUCC;
}

//�ܺ�ʱ�Ĳ�����ע��ʹ��Ƶ��
#if defined _DEBUG || defined DEBUG
#define DEBUGDUMP_FRAME_HEAD(x,y,z)      Zerg_App_Frame::dumpoutput_framehead(x,y,z);
#define DEBUGDUMP_FRAME_INFO(x,y,z)      Zerg_App_Frame::dumpoutput_frameInfo(x,y,z)
#else
#define DEBUGDUMP_FRAME_HEAD(x,y,z)
#define DEBUGDUMP_FRAME_INFO(x,y,z)
#endif

#endif //SOARING_LIB_SERVER_APP_FRAME_H_
