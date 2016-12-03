#ifndef __EXTERNAL_SCRIPT_H
#define __EXTERNAL_SCRIPT_H

#include <qapplication.h>
#include <QtGui>

#ifdef CREATE_IMPROC_LIB
#define SCRIPT_LIB_FUNC  Q_DECL_EXPORT
#else
#define SCRIPT_LIB_FUNC Q_DECL_IMPORT
#endif

#ifdef _WIN32
#define PREFIX extern "C" SCRIPT_LIB_FUNC
#else
#define PREFIX extern "C"
#endif


class SCRIPT_LIB_FUNC Osignal : public QObject
{
    Q_OBJECT
public:
    explicit Osignal(QTabWidget *t,QObject *parent=0);
    Osignal();
signals:
    void msg_Pumped();
public slots:
    void got_msg_Pumped()
    {
        emit msg_Pumped();
    }
};


class SCRIPT_LIB_FUNC Oscope : public QObject
{
    Q_OBJECT
public:
    explicit Oscope(QTabWidget *t,QObject *parent=0);
    Oscope();
signals:
    void msg_Pumped();
    void extPlotReq();
public slots:
    void do_plot();
    void set_x_size(unsigned short len);
    void set_y_size(unsigned short len);
};

class SCRIPT_LIB_FUNC ExternSig : public QObject
{
    Q_OBJECT
public:
    ExternSig();
signals:
    void msg_Pumped();
public slots:
    void got_msg_Pumped()
    {
        emit msg_Pumped();
    }
};

#define WMSG_LEN      50
#define WMSG_STR_LEN  1024
#define NUM_TIMER     5

typedef struct ScriptWinMsg
{
    unsigned short wm;
    unsigned short wmlPar;
    unsigned short wmwPar;
    union
    {
        char  wmsg_cStr[WMSG_STR_LEN];
        float wFltVal[WMSG_LEN];
    };
} ScriptWinMsg;

struct WinMsgQ
{
    volatile unsigned short wmsg_Arr[WMSG_LEN];
    volatile unsigned short wmsg_lPar[WMSG_LEN];
    volatile unsigned short wmsg_wPar[WMSG_LEN];
    union
    {
        char  wmsg_cStr[WMSG_STR_LEN][WMSG_LEN];
        volatile float wFltVal[WMSG_LEN];
    };
    volatile unsigned short wmsg_Head;
    volatile unsigned short wmsg_Tail;
    volatile unsigned short wmsg_Len;
};

#define WM_USER_MSG           (0x400)
#define WM_LED                (WM_USER_MSG+1)
#define WM_MSG                (WM_USER_MSG+2)
#define WM_GRAPH              (WM_USER_MSG+3)
#define WM_WIN_DIS_FRAME1     (WM_USER_MSG+4)
#define WM_WIN_DIS_FRAME2     (WM_USER_MSG+5)
#define WM_WIN_DIS_FRAME3     (WM_USER_MSG+6)
#define WM_WIN_DIS_FRAME4     (WM_USER_MSG+7)
#define WM_WIN_DIS_FRAME5     (WM_USER_MSG+8)
#define WM_FEED_R_X_Y         (WM_USER_MSG+9)
#define WM_STATUS_MSG         (WM_USER_MSG+10)
#define WM_SCROLL_MSG         (WM_USER_MSG+11)
#define WM_TIMER_MSG          (WM_USER_MSG+12)

#define WM_BOXT               (WM_USER_MSG+13)
#define WM_BOXR               (WM_USER_MSG+14)
#define WM_BOXF               (WM_USER_MSG+15)
#define WM_BANNER             (WM_USER_MSG+16)
#define WM_CLEAR_MSG          (WM_USER_MSG+17)
#define WM_APPEND_MSG         (WM_USER_MSG+18)
#define WM_CAL_MSG            (WM_USER_MSG+19)
#define WM_CAL_LED            (WM_USER_MSG+20)
#define WM_INFO_MSG           (WM_USER_MSG+21)

#define WM_WIN_DIS_IMG1       (WM_USER_MSG+22)
#define WM_WIN_DIS_IMG2       (WM_USER_MSG+23)
#define WM_WIN_DIS_IMG3       (WM_USER_MSG+24)
#define WM_WIN_DIS_IMG4       (WM_USER_MSG+25)
#define WM_WIN_DIS_IMG5       (WM_USER_MSG+26)
#define WM_WIN_DIS_IMG6       (WM_USER_MSG+27)
#define WM_CLEAR_LOG          (WM_USER_MSG+28)
#define WM_LOG                (WM_USER_MSG+29)

#define WM_WIN_PLOT_C1        (WM_USER_MSG+30)
#define WM_WIN_PLOT_C2        (WM_USER_MSG+31)
#define WM_WIN_PLOT_C3        (WM_USER_MSG+32)

#define WM_WIN_APC_BOX        (WM_USER_MSG+33)
#define WM_TIMER_STOP_MSG     (WM_USER_MSG+34)
#define WM_WIN_SAVE_IMG       (WM_USER_MSG+35)
#define WM_HW_CONNECTED       (WM_USER_MSG+36)
#define WM_HW_NOTCONNECTED    (WM_USER_MSG+37)
#define WM_RECP_SCO           (WM_USER_MSG+38)
#define WM_RECP_SIG           (WM_USER_MSG+39)

#define WM_APP_LOADER         (WM_USER_MSG+42)
#define WM_APP_COMOK          (WM_USER_MSG+43)
#define WM_APP_FILEOK         (WM_USER_MSG+44)
#define WM_APP_PROGRESS       (WM_USER_MSG+45)
#define WM_APP_DOWNOK         (WM_USER_MSG+46)
#define WM_APP_PYTHON         (WM_USER_MSG+47)

#define WM_CRV_T1             (WM_USER_MSG+48)
#define WM_CRV_T2             (WM_USER_MSG+49)
#define WM_CRV_T3             (WM_USER_MSG+50)
#define WM_CRV_T4             (WM_USER_MSG+51)
#define WM_CRV_T5             (WM_USER_MSG+52)
#define WM_CRV_T6             (WM_USER_MSG+53)

#define WM_SET_IMG_TAB        (WM_USER_MSG+55)
#define WM_CIMG_DISPLAY       (WM_USER_MSG+56)
#define WM_GIMG_DISPLAY       (WM_USER_MSG+57)

#define WMTM_LOG_MSG          (WM_USER_MSG+58)
#define WMTM_STATUS_MSG       (WM_USER_MSG+59)
#define WMTM_STATUS_GRAPH     (WM_USER_MSG+60)
#define WMTM_BOX_MSG          (WM_USER_MSG+61)
#define WMTM_LED_MSG          (WM_USER_MSG+62)
#define WMTM_TAB_MSG          (WM_USER_MSG+63)
#define WMTM_ARRIVED_MSG      (WM_USER_MSG+64)

#define WM_SIGNAL_TAB         (WM_USER_MSG+65)
#define WM_SCOPE_TAB          (WM_USER_MSG+66)
#define WM_PLUGIN_TAB         (WM_USER_MSG+67)

#define WM_SCOPE_PROGR        (WM_USER_MSG+68)
#define WM_SCOPE_READY        (WM_USER_MSG+69)
#define WM_SCOPE_PARTREADY        (WM_USER_MSG+70)
#define WM_SCOPE_START        (WM_USER_MSG+71)
#define WM_BOOT_START         (WM_USER_MSG+72)
#define WM_LCD_DEC            (WM_USER_MSG+73)
#define WM_LCD_HEX            (WM_USER_MSG+74)

PREFIX double x_Axis[11200];
PREFIX double xCh1_Array[11200];
PREFIX double xCh2_Array[11200];
PREFIX double signal_FIX_A[11200];
PREFIX double signal_FIX_B[11200];
PREFIX double xAxis_Array[4095];

PREFIX unsigned short TransmitTag();
PREFIX unsigned short WaitTag(unsigned short mSleep);
PREFIX int            lStart(void);
PREFIX bool           lStop(void);

PREFIX void           OnStart();
PREFIX void           OnStartIP();
PREFIX void           OnExit();

PREFIX void           _script_wait(int iwait_time);
PREFIX void           _script_version();
PREFIX unsigned short _script_wait_cmd(int iwait_time);
PREFIX unsigned short _gpio_rcmd(unsigned short i);
PREFIX unsigned short _gpio_wcmd(unsigned short i,unsigned short j);
PREFIX unsigned short __test_write(unsigned char *chptr,unsigned char len);
PREFIX unsigned short __test_read(unsigned char *chptr,unsigned char len);

PREFIX unsigned char start_CtrlFunction();
PREFIX void          startRemoteAccess(void *p,unsigned short ms);
PREFIX void          register_CtrlFunction(void (*p)(int));

PREFIX void          _start_server_ip(void *a);
PREFIX void          _stop_server_ip();
PREFIX int           _start_client_ip(void *a);
PREFIX void          _stop_client_ip();
PREFIX int           _is_server_alive(int ms);
PREFIX void          _cl_encode_msg(unsigned short cnstMsg,unsigned char *buff);
PREFIX void          _cl_wait_done();

PREFIX void          _cl_tc_encode_msg(unsigned short cnstMsg,unsigned char *buff);
PREFIX void          _cl_tc_wait_done();
PREFIX void          _cl_net_tc_encode_msg(unsigned short cnstMsg,unsigned char *buff);
PREFIX void          _cl_net_tc_wait_done();

PREFIX unsigned char test_start_CtrlFunction();
PREFIX void          test_startRemoteAccess(void *p,unsigned short ms);
PREFIX void          test_register_CtrlFunction(void (*p)(int));

PREFIX int           millisleep(unsigned long ms);

PREFIX unsigned short usCommandStatus(unsigned short cmdx);
PREFIX unsigned char  lPushTag(char cmdx,unsigned char *ucbuff,unsigned char len);
PREFIX unsigned short lPullTag(unsigned char *ucbuff);
PREFIX unsigned char  lusPushTag(char cmdx,unsigned short lm);

#if 0
PREFIX unsigned short Enc_Net_Frame(CNetFrame *cf,unsigned short cmdx,unsigned char token,void *p,unsigned short cSize);
PREFIX void Copy_Net_Frame(CNetFrame *csrc,CNetFrame *cdst);
PREFIX void Register_Net_Handler(void (*FuncPtr)(void));
PREFIX unsigned short isNetPktValid(CNetFrame *cf);
PREFIX unsigned short lEnc_Net_Frame_Buffer(CNetFrame *cf,unsigned char cmdx,unsigned char token,void *p,unsigned short cSize);
#endif

PREFIX unsigned char  lNetPushTag(char cmdx,unsigned char *ucbuff,unsigned short len);
PREFIX unsigned short lNetPullTag(unsigned char *ucbuff);
PREFIX unsigned char  lusNetPushTag(char cmdx,unsigned short lm);
PREFIX unsigned short usGetString(QString s,char *buffer);


PREFIX void          _script_signal(unsigned short   numPoint,  \
                                    unsigned short   tmr,       \
                                    unsigned short   tmrdiv,    \
                                    unsigned short   h1Type,    \
                                    unsigned short   h2Type,    \
                                    unsigned short   ch1Max,    \
                                    unsigned short   ch1Min,    \
                                    unsigned short   ch2Max,    \
                                    unsigned short   ch2Min);

PREFIX void vInitRing(unsigned char index,unsigned char *buffer, short buffer_size);
PREFIX void vRingWrite(unsigned char index,void *vdata, short len);
PREFIX unsigned short usRingRead(unsigned char index,void *vdata, short *len);
PREFIX unsigned short usRingReadFast(unsigned char index);
PREFIX void vRingWriteFast(unsigned char index, unsigned char ch);
PREFIX unsigned char usPullStrWinHLQ(unsigned short &winMsg,unsigned char *ucArr,float &fVal,char *str);
PREFIX unsigned char usPullStrWinQ(unsigned short &winMsg,unsigned short &wPar,unsigned short &lPar,float &fVal,char *str);

PREFIX int tcp_server_start(unsigned short port);
PREFIX int tftp_put(char *saddr,unsigned short port,char *file);
PREFIX int tftp_get(char *saddr,unsigned short port,char *file);

PREFIX void run_cscript(const char *script,unsigned short len);
//PREFIX void transmit_pkt(CNetFrame &cfrm);
PREFIX void ExecuteScript1(bool x);
PREFIX void ExecuteScript2(bool x);
PREFIX void ExecuteScript3(bool x);
PREFIX void ExecuteScript4(bool x);
PREFIX void ExecuteScript5(bool x);
PREFIX void ExecuteCoap1(bool x);
PREFIX ExternSig *createWidget1();
PREFIX Oscope    *createWidget2();
PREFIX Osignal   *createWidget3();

#if _WIN32
PREFIX void RegisterWin(HWND hwnd);
#else
PREFIX void RegisterWin(int hwnd);
#endif

#endif
