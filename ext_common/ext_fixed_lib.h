#ifndef __EXTERNAL_FIXED_H
#define __EXTERNAL_FIXED_H

#include <qapplication.h>
#include <QtGui>
#include <QImage>
#include <QPixmap>
#include "options.h"
#include "comm_protocol.h"
#include "commandlist.h"

#ifdef CREATE_IMPROC_LIB
#define IMPROC_LIB_FUN  Q_DECL_EXPORT
#else
#define IMPROC_LIB_FUN Q_DECL_IMPORT
#endif

#ifdef _WIN32
#define PREFIX extern "C" IMPROC_LIB_FUN
#else
#define PREFIX extern "C"
#endif

class IMPROC_LIB_FUN Osignal : public QObject
{
    Q_OBJECT
public:
    explicit Osignal(QTabWidget *t,QObject *parent=0);
    Osignal();
signals:
    void msg_Pumped();
public slots:
};


class IMPROC_LIB_FUN Oscope : public QObject
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

class IMPROC_LIB_FUN ExternSig : public QObject
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



#define PIVAL 3.1415f

#define BW_IMAGE  0
#define COL_IMAGE 1

#define N_CL_BUFF 12
#define N_BW_BUFF 12
#define N_PLOT_ARR 1280

#define MAJOR_FIXED_LIB_VER 3
#define MINOR_FIXED_LIB_VER 6

#define SCOSETTINGS_SENT  0x01
#define SCOSETTINGS_RESET 0x02

#define MIN_ARRAY_SIZE              25
#define FULL_ARRAY_SIZE             2048
#define USER_ARRAY_SIZE             2048
#define MAX_DATA_PKT_SIZE           2048

#define IW_WHITE       0
#define IW_BLACK       1
#define IW_RED         2
#define IW_DARKRED     3
#define IW_GREEN       4
#define IW_DARKGREEN   5
#define IW_BLUE        6
#define IW_DARKBLUE    7
#define IW_CYAN        8
#define IW_DARKCYAN    9
#define IW_MAGENTA     10
#define IW_DARKMAGENTA 11

#define IW_YELLOW      12
#define IW_DARKYELLOW  13
#define IW_GRAY        14
#define IW_DARKGRAY    15
#define IW_LIGHTGRAY   16
#define IW_TRANSPARENT 17


#define CLK_DIV_001  0
#define CLK_DIV_002  1
#define CLK_DIV_004  2
#define CLK_DIV_008  3
#define CLK_DIV_016  4
#define CLK_DIV_032  8
#define CLK_DIV_064  6
#define CLK_DIV_256  7


enum QQCol
{
    Qt_red=0,
    Qt_green,
    Qt_blue,
    Qt_cyan,
    Qt_magenta,
    Qt_gray,
    Qt_yellow,
    Qt_darkRed,
    Qt_darkGreen,
    Qt_darkBlue,
    Qt_darkCyan,
    Qt_darkMagenta,
    Qt_darkGray,
    Qt_darkYellow,
    Qt_black,
    Qt_lightGray
};

enum
{
    SCAN_STATE_CAPTURE=1,
    SCAN_STATE_PROCESS,
    SCAN_STATE_BLOB_0,
    SCAN_STATE_BLOB_1,
    SCAN_STATE_BLOB_2,
    SCAN_STATE_BLOB_3,
    SCAN_STATE_BLOB_4,
    SCAN_STATE_BLOB_5,
    SCAN_STATE_BLOB_6,
    SCAN_STATE_BLOB_7,
    SCAN_STATE_DONE
};


typedef struct
{
    float x[1024];
    float y1[1024];
    float y2[1024];
} plot_shared_data;

typedef struct
{
    unsigned short blob_size_min;
    unsigned short blob_size_max;
    unsigned short exp_time;
    unsigned short blob_threshold;
} target_plate_struct;

enum
{
    __IW_Sin=0,
    __IW_Cos,
    __IW_Square,
    __IW_Rect1,
    __IW_Rect2,
    __IW_Triangle,
    __IW_Sawtooth1,
    __IW_Sawtooth2,
    __IW_Spike,
    __IW_Raw,
    __IW_Nosig=0x80
};


typedef struct SIG
{
    unsigned short waveForm;
    unsigned short symm;
    unsigned short max;
    unsigned short min;
    unsigned short noise;
    unsigned short gain;
    unsigned short offset;
} SIG;

typedef struct Sig_Settings
{
    SIG Ch1;
    SIG Ch2;

    unsigned short  activeChannel;
    unsigned short  currChannel;
    unsigned short  numFreq;
    unsigned short  numPoint;

    unsigned short  tmr;
    unsigned short  tmrdiv;

    unsigned short  adjust_Max;
    unsigned short  adjust_Min;
//} Sig_Settings;
} Sig_Settings  __attribute__ ((aligned(16)));



typedef struct SCO
{
    int gain;
    int offset;
} SCO;

typedef struct Sco_Settings
{
    SCO Ch1;
    SCO Ch2;

    unsigned short  activeChannel;
    unsigned short  currChannel;
    unsigned short  triggerSource;
    unsigned short  triggerType;
    unsigned short  triggerVoltage;

    unsigned short  enMarker;
    unsigned short  HorTop;
    unsigned short  HorBot;
    unsigned short  VerLeft;
    unsigned short  VerRight;

    unsigned short  numFreq;
    unsigned short  numPoint;

    unsigned short  tmr;
    unsigned short  tmrdiv;

} Sco_Settings __attribute__ ((aligned(16)));

typedef union
{
    unsigned char buff[64];
    struct
    {
        unsigned short hSignature;
        unsigned short hMode;
        unsigned char  buff[60];
    } gen;

    struct
    {
        unsigned short hSignature;
        unsigned short hMode;
        unsigned short hCRC;
        Sco_Settings   emb_sco;

    } _sco;

    struct
    {
        unsigned short hSignature;
        unsigned short hMode;
        unsigned short hCRC;
        Sig_Settings   emb_sig;
    } _sig;

    struct
    {
        unsigned short hSignature;
        unsigned short hMode;
        unsigned short hSMode;
        unsigned short hAction;
        unsigned char  portNum;
        unsigned char  hArg;

        unsigned short hS1Mode;
        unsigned short hS2Mode;

        unsigned char  hC1Arg;
        unsigned char  hC2Arg;
        unsigned char  hC3Arg;
        unsigned char  hC4Arg;
        unsigned char  hC5Arg;
        unsigned char  hC6Arg;

        unsigned long  hL1Arg;
        float          hL2Arg;
        unsigned long  hL3Arg;

        volatile unsigned char  h_buff[32];
    } _ext;

    struct
    {
        unsigned short hSignature;
        unsigned short hMode;
        unsigned short hSMode;
        unsigned short hAction;
        unsigned char  portNum;
        unsigned char  hArg;

        unsigned short hFreq;
        unsigned char uc1Type;
        unsigned char uc2Type;

        float    minCh1;
        float    maxCh1;

        float    minCh2;
        float    maxCh2;

        volatile unsigned char  h_buff[34];
    } _esig;

    struct
    {
        unsigned short main_32[16];
        unsigned short status_32[16];
    } STATUS;

    struct
    {
        unsigned char buff[64];
    } USRAW;

    struct
    {
        char buff[64];
    } RAW;

    struct
    {
        unsigned short hSignature;
        unsigned short hMainMode;
        char buff[60];
    } QuickMode;

    struct
    {
        unsigned short hSignature;
        unsigned short hMode;
        unsigned short hEnabledChannel;

        unsigned short hGainA;
        unsigned short hGainB;

        unsigned short hTriggerSource;
        unsigned short hTriggerVoltage;
        unsigned short hNumSampleSize;
        unsigned short hNumSampleRate;

        unsigned short hIntermittent;
        unsigned short hIntermittent_Interval;

        unsigned short hus_CRC;
        unsigned char buff[40];
    } Scope;

    struct
    {
        unsigned short hSignature;
        unsigned short hMode;

        unsigned short hEnabledChannel;

        unsigned short hGainA;
        unsigned short hGainB;

        unsigned short hTriggerSource;
        unsigned short hTriggerVoltage;
        unsigned short hNumSampleSize;
        unsigned short hNumSampleRate;

        unsigned short hIntermittent;
        unsigned short hIntermittent_Interval;

        unsigned short hus_CRC;
        unsigned char buff[40];
    } Signal;


    struct
    {
        unsigned short hSignature;
        unsigned short hMode;

        unsigned short hEnabledChannel;

        unsigned short chAI2C_Mode;
        unsigned short chBI2C_Mode;

        unsigned short chAI2C_ExMode;
        unsigned short chBI2C_ExMode;

        unsigned short chAI2C_Addr;
        unsigned short chBI2C_Addr;

        unsigned short chAI2C_Speed;
        unsigned short chBI2C_Speed;


        unsigned short hTriggerSource;
        unsigned short hTriggerVoltage;
        unsigned short hNumSampleSize;
        unsigned short hNumSampleRate;

        unsigned short hIntermittent;
        unsigned short hIntermittent_Interval;

        unsigned short hus_CRC;
        unsigned short hus_Reserve;
    } I2C;


    struct
    {
        unsigned short hSignature;
        unsigned short hMode;

    } IN_CAP;

    struct
    {
        unsigned short hSignature;
        unsigned short hMode;

    } Freq_Capture;

    struct
    {
        unsigned short hCurrMode;
        unsigned short hCurrentADC1;
        unsigned short hCurrentADC2;
        unsigned short hSignalIndex_Filler;
        unsigned short hSignalIndex_Emptier;
        unsigned short hGestimated_FTime;
        unsigned short hGestimated_ETime;

        unsigned short hFilling_Index01;
        unsigned short hFilling_Index02;
        unsigned short hFilling_Ended01;
        unsigned short hFilling_Ended02;

        unsigned short hVersion_Info;
        unsigned short hVersion_Major;
        unsigned short hVersion_Minor;

        unsigned short hVersion_DaMo;
        unsigned short hVersion_Year;
        unsigned short hVersion_Time;

        unsigned char hTarget_01_ended;
        unsigned char hTarget_01_started;
        unsigned char hTarget_01_fill_started;

        unsigned char hTarget_02_ended;
        unsigned char hTarget_02_started;
        unsigned char hTarget_02_fill_started;

        unsigned char hTail_Chaser;
        unsigned char hAttempt;
        char buff[22];
    } QSTATUS;

} Mode_Frame  __attribute__ ((aligned(16)));


typedef struct
{
    unsigned short  currTriggerSelection;
    unsigned short  lastTriggerSelection;
    char            sig_file[255];
    unsigned short  currScoChannel;
    unsigned short  currSigChannel;
    unsigned short  csvTimeCol;
    unsigned short  csvSigCol1;
    unsigned short  csvSigCol2;
    float           csv_Sig1Gain;
    float           csv_Sig2Gain;
    float           csv_Sig1Off;
    float           csv_Sig2Off;


    unsigned short  sco_Brush01Thick;
    unsigned int    sco_Brush01Color;
    unsigned short  sco_Brush02Thick;
    unsigned int    sco_Brush02Color;
    unsigned int    bg_sco_color;

    unsigned short  sig_Brush01Thick;
    unsigned int    sig_Brush01Color;
    unsigned short  sig_Brush02Thick;
    unsigned int    sig_Brush02Color;
    unsigned int    bg_sig_color;

    unsigned int    currAppTab;

} App_Settings __attribute__ ((aligned(16)));

typedef struct DllSetting
{
    unsigned short target01_started;
    unsigned short target01_ended;

    unsigned short target02_started;
    unsigned short target02_ended;

    unsigned short fill01_started;
    unsigned short fill02_started;

    unsigned short fill01_done;
    unsigned short fill02_done;

    unsigned short empty01_index;
    unsigned short empty02_index;

    unsigned short filling_now;
    unsigned short sending_now;
    unsigned short tail_Chaser;

    //Trans_IO_Pkt   *senderPtr;
    unsigned char  send_ep_num;
} DllSetting  __attribute__ ((aligned(16)));

typedef struct
{
    volatile unsigned int _portANum;
    volatile unsigned int _portBNum;
    volatile unsigned int _portCNum;
    volatile unsigned int _portDNum;

    volatile unsigned int _portA_Status;
    volatile unsigned int _portB_Status;
    volatile unsigned int _portC_Status;
    volatile unsigned int _portD_Status;

    volatile unsigned int _portA_Baud;
    volatile unsigned int _portB_Baud;
    volatile unsigned int _portC_Baud;
    volatile unsigned int _portD_Baud;

    volatile unsigned int _portA_Dbg;
    volatile unsigned int _portB_Dbg;
    volatile unsigned int _portC_Dbg;
    volatile unsigned int _portD_Dbg;

} Uart_Setting __attribute__ ((aligned(16)));



enum QBoxType
{
    CBOX_TARGET=0,
    CBOX_REF,
    CBOX_DEVICE,
    CBOX_INTERNAL,
    CBOX_INFO,
    CBOX_C40_CNT,
    CBOX_C40_OFF,
    CBOX_C45_CNT,
    CBOX_C45_OFF,
    CBOX_C56_CNT,
    CBOX_C56_OFF,
    CONN_LED,
    TARGET_LED,
    CBOX_SCOPE,
    CBOX_LCD,
    DEVICE_LED
};

#define MODE_NONE      0
#define ROI_CIRCLE     1
#define ROI_RECTANGLE  2
#define BLOB_SIZE      3
#define BLOB_THRESHOLD 4

#define NUMBER_OF_RS232_PORTS 2
#define LEN_OF_STR 100

struct INI_Settings_RS232
{
    unsigned short nInterfaceActive;
    unsigned short nTempSensor;
    unsigned short nTempComPort;
    unsigned long  nTempBaud;
    unsigned long  nCurrentIndex;
    unsigned long  nEmulateCam;
    unsigned long  nDebugChannel;

    char           strnCurrMAC[LEN_OF_STR];
    char           strnStrtMAC[LEN_OF_STR];
    char           strnLeftMAC[LEN_OF_STR];
    char           strnUsedMAC[LEN_OF_STR];

    unsigned short nActive[NUMBER_OF_RS232_PORTS];
    unsigned short nPortNum[NUMBER_OF_RS232_PORTS];
    char           strnPortType[NUMBER_OF_RS232_PORTS][LEN_OF_STR]; // FIXME Later
    unsigned short nChnlNum[NUMBER_OF_RS232_PORTS];
    unsigned long  nBaudRate[NUMBER_OF_RS232_PORTS];

};


struct p_str
{
    float x[1024];
    float y1[1024];
    float y2[1024];
};

struct node
{
    // X, Y and Z coordinates
    float x;
    float y;
    float min_x;
    float min_y;
    float max_x;
    float max_y;
    float area;
    float par;

    // color information
    unsigned char r;
    unsigned char g;
    unsigned char b;

    node *next;   // the reference to the next node
};

#define WMSG_LEN      50
#define WMSG_STR_LEN  1024
#define NUM_TIMER     5

#define FGROUP 0x01
#define CGROUP 0x02
#define TGROUP 0x03
#define RGROUP 0x04
#define DGROUP 0x05
#define IGROUP 0x06

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

#define BOX_ID_01 1
#define BOX_ID_02 2
#define BOX_ID_03 3
#define BOX_ID_04 4
#define BOX_ID_05 5
#define BOX_ID_06 6
#define BOX_ID_07 7
#define BOX_ID_08 8
#define BOX_ID_09 9
#define BOX_ID_10 10
#define BOX_ID_11 11


#define BOX_APC_IEEE_ADRR     12
#define BOX_APC_OLDMAC_ADRR   13
#define BOX_APC_HW_VERSION    14
#define BOX_APC_BOOTLOADER    15
#define BOX_APC_SERIAL_NUMBER 16
#define BOX_APC_MFG_DATE      17
#define BOX_APC_MAC_ADDR      18
#define BOX_APC_INDEX_ADDR    19

enum {  LED1=0,
        LED2,
        LED3,
        LED4,
        LED5,
        LED6,
     };

enum {  RED=0,
        GREEN,
        BLUE,
        CYAN,
        MAGENTA,
        GRAY,
        YELLOW,
        DARKRED,
        DARKGREEN,
        DARKBLUE,
        DARKCYAN,
        DARKMAGENTA,
        DARKGRAY,
        DARKYELLOW,
        BLACK,
        LIGHTGRAY,
        LIGHTCYAN,
        WHITE
     };

#define BLACK       0x0F
#define LIGHTCYAN   0x10

PREFIX void fn_NewMaskCircle(int i,int x,int y,int r);
PREFIX void calStats(unsigned char inImg,short x,short y,short r,double *mn,double *sd,double *minV,double *maxV);
PREFIX void fn_cutROI_White(unsigned char i);
PREFIX void fnPaintCanvas(unsigned char thr,unsigned char inImg,unsigned char crbnPltImg);
PREFIX void fn_Merge2Images(unsigned char j,unsigned char k);
PREFIX int fn_exp_abs(unsigned short abs_exp_time);
PREFIX int fn_DeltaExpCap_Image(short int delta_exp);
PREFIX unsigned short fn_usMountSDCard(unsigned short uartNum);
PREFIX void fn_ProcessDirectory();
PREFIX void fn_SaveImage(unsigned short wPar,unsigned short lPar);
PREFIX void fn_SaveImageHDD(void);
PREFIX void fn_HistEqualization(void);
PREFIX int fn_CaptureImage_Process(void);
PREFIX int fn_CaptureBotImage_Process(void);
PREFIX unsigned short usOpenComPorts(void);
PREFIX void vInitTimer(void);
PREFIX unsigned short usOpenTimer(unsigned char iTimerIndex, unsigned short iTimerVal, unsigned short lPar);
PREFIX unsigned short usOpenRtimer(unsigned char iTimerIndex, unsigned short iTimerVal, unsigned short lPar);
PREFIX unsigned short usCloseTimer(unsigned char iTimerIndex);
PREFIX unsigned short usCloseComPorts(void);
PREFIX void UartTransmit(unsigned short uartNum,const unsigned char *buff,unsigned short len);
PREFIX unsigned short UartReceive(unsigned short uartNum,unsigned char *buff,unsigned short len);
PREFIX unsigned short UartReceiveUntil(unsigned short uartNum,unsigned char *buff, unsigned char c, unsigned short len);
PREFIX int fn_LoadIniFile(void);
PREFIX int fn_SaveIniFile(void);
PREFIX unsigned short usTestComPorts(unsigned char nPortNum, unsigned long bdRate);
PREFIX unsigned short usTestLoopBack(unsigned char *resArr);
PREFIX unsigned short usAPC_Cal(void);
PREFIX unsigned short usAPCP_Cal(void);
PREFIX void usPushWinQ(unsigned short winMsg,unsigned short wPar,unsigned short lPar, float fVal);
PREFIX unsigned char usPullWinQ(unsigned short &winMsg,unsigned short &wPar,unsigned short &lPar, float &fVal);
PREFIX void usPushStrWinQ(unsigned short winMsg,unsigned short wPar,unsigned short lPar,char *str);

PREFIX void usPushStrWinHLQ(unsigned short winMsg,unsigned char *ucArr,char *str);
PREFIX unsigned char usPullStrWinHLQ(unsigned short &winMsg,unsigned char *ucArr,float &fVal,char *str);

PREFIX unsigned char usPullStrWinQ(unsigned short &winMsg,unsigned short &wPar,unsigned short &lPar,float &fVal,char *str);
PREFIX unsigned short UartRxPending(unsigned short uartNum);
PREFIX unsigned short UartTxPending(unsigned short uartNum);
PREFIX void UartClearAll(unsigned short uartNum);
PREFIX unsigned short UartRxTail(unsigned short uartNum);
PREFIX void vInitUSB(void);
PREFIX void vCloseUSB(void);
PREFIX void probe_Cam(unsigned char active);
PREFIX void close_Cam(void);
PREFIX unsigned char ReadNovolum2(unsigned char numUart,unsigned short *pot, float *t, float *max, float *min,unsigned short *dir);
PREFIX int i_Process(unsigned short i);
PREFIX int n_Process(unsigned short i);
PREFIX void fn_ROI_Image_Process();
PREFIX void fn_ROI_Image0();
PREFIX void fn_gBlob_Counting();
PREFIX void process_c1_LED();
PREFIX void process_c2_LED();
PREFIX void fn_nBlob_Counting();
PREFIX void fn_Blob_Counting();
PREFIX int fn_Manual_Place_Circle(int x,int y, int r);
PREFIX int fn_Manual_Place_Rect(int x,int y,int xl,int yl);
PREFIX void fn_Hough_Image_Process();
PREFIX unsigned short fn_VersionInfo();
PREFIX unsigned char usInitializeCalibration();
PREFIX void SetCameraMode(unsigned char active);

PREFIX void init_spline(unsigned short spCnt);
PREFIX void exit_spline();
PREFIX void push_spline(double *X,double *Y);
PREFIX double pull_spline(double xi);

PREFIX int cb_Reset(void);
PREFIX int cb_GetCB(unsigned short num, unsigned char *cow, unsigned char *bull);
PREFIX void cb_Init_Master(void);
PREFIX unsigned short cb_Master(void);
PREFIX int cb_Filter(unsigned short num, unsigned char cow, unsigned char bull);
PREFIX int cb_Pick_One(void);
PREFIX int cb_Random_Num(void);
PREFIX int cb_Check_Num(unsigned short nNum, unsigned char sp_Num[4]);
PREFIX void cb_Find_CB(unsigned short nNum1,unsigned short nNum2, unsigned char *b, unsigned char *c);
PREFIX int cb_New_Num(void);
PREFIX int cb_Seed(void);
PREFIX void fn_OCR_Read(void);
PREFIX void fn_QR_Read(void);
PREFIX void fn_Blur(void);
PREFIX int  ext_main();
PREFIX int  fn_focus();
PREFIX int  fn_exp();
PREFIX void test(void);
PREFIX void SB_SendHandshake();
PREFIX int  fn_Image_Scanner(void);
PREFIX bool polynomialfit(int nElem, int degree, double *dx, double *dy, double *store);
PREFIX double eval_poly(double *pl,short len,double xi);

// External Commands
PREFIX void           Copy_Frame(CFrame *csrc,CFrame *cdst);
PREFIX unsigned short cf2_uc(CFrame *cfrm,unsigned char *ldBuff);
PREFIX unsigned short Add_Frame_Buffer(CFrame *cf,const unsigned char *buffer,unsigned short cSize);
PREFIX void           Print_Enc_Msg(CFrame *cf);
PREFIX unsigned short isValid(CFrame *cf);
PREFIX void           probe_Archive(unsigned char active);
PREFIX void           fn_LoadArchine(unsigned char i);


PREFIX bool  fn_StopExecutionThread();
PREFIX bool  fn_StartExecutionThread();

PREFIX int   fn_SoftReset();
PREFIX int   fn_InitBufferPool();
PREFIX int   millisleep(unsigned long ms);
PREFIX short fn_RawCommands(unsigned short uartNum,void *sbuff,unsigned short len);
PREFIX int   fn_TestMessgae(unsigned char uartNum);
PREFIX int   fn_SoftReset();
PREFIX int   fn_LoadAutoExec();
PREFIX int   fn_CreateTestFile();

PREFIX int   fn_MountDisk();
PREFIX int   fn_UnMountDisk();
PREFIX int   fn_kFindFile(char *fName,char *fDir);
PREFIX int   fn_GetMountStatus();
PREFIX int   fn_RunAutoExec();
PREFIX void  Calc_Signal_Settings(unsigned char chnl,const Sig_Settings *s1);

PREFIX bool  Load_UART_Settings(void);
PREFIX bool  Load_Signal_Settings(volatile Sig_Settings *s);
PREFIX void  Save_Signal_Settings(volatile Sig_Settings *s);

PREFIX bool  Load_App_Settings(volatile App_Settings *s);
PREFIX bool  Save_App_Settings(volatile App_Settings *s);

PREFIX void  Push_Signal_Settings(const Sig_Settings *s);
PREFIX void  Push_Scope_Settings(const Sco_Settings *s);
PREFIX unsigned char Val_Scope_Settings(const Sco_Settings *s);
PREFIX void  Pull_Signal_Settings(Sig_Settings *s);
PREFIX void  Pull_Scope_Settings(Sco_Settings *s);
PREFIX bool  Load_Scope_Settings(Sco_Settings *s);
PREFIX void  Save_Scope_Settings(Sco_Settings *s);
PREFIX void  Signal_Settings_CopySettings(const Sig_Settings s,Sig_Settings *s1);
PREFIX void  Scope_Settings_CopySettings(const Sco_Settings s,Sco_Settings *s1);
PREFIX bool  Validate_Signal_Settings(Sig_Settings *s);
PREFIX bool  Validate_Scope_Settings(Sco_Settings *s);
PREFIX void  Apply_Signal_Settings(const Sig_Settings *s);
PREFIX void  Val_Signal_Settings(void);
PREFIX void  fnSingleShotMainImproc(void);
PREFIX void  fnFindGradient(void);
PREFIX unsigned short UartReceiveCFrame(unsigned short uartNum,CFrame *cfrm);
PREFIX bool  UartTransmitCFrame(unsigned short uartNum,CFrame *cfrm);
PREFIX bool UartTransmitCFrameRetry(unsigned short uartNum,CFrame *cfrm,unsigned short attempts);
//PREFIX ring_buffer_t *UartTxRingPtr(unsigned short uartNum);
//PREFIX ring_buffer_t *UartRxRingPtr(unsigned short uartNum);
PREFIX void Register_Handler(void (*FuncPtr)(void));
PREFIX int capture_hdr_input(unsigned char tFrames);
PREFIX void Cmd_Task(void);
PREFIX bool PushCFrame(unsigned short uartNum,CFrame *cfrm);
PREFIX bool PushCCFrame(unsigned short uartNum,CFrame *cfrm);
PREFIX unsigned short PullCFrame(unsigned short uartNum,CFrame *cfrm);
PREFIX unsigned short PullCCFrame(unsigned short uartNum,CFrame *cfrm);

PREFIX bool PushRawBuffer(unsigned short uartNum,void *rawData,unsigned short len);
PREFIX unsigned short PullRawBuffer(unsigned short uartNum,void *rawData);
PREFIX unsigned short InitCStack(void);
PREFIX unsigned short csRunScrFile(char *nfile);
PREFIX unsigned short csCleanStack(void);

PREFIX void I2CBusAction(unsigned char BusNum,unsigned char busAction);
PREFIX void I2CBusSpeed(unsigned char BusNum,unsigned long clkSpeed);
PREFIX void I2CBusWrite(unsigned char BusNum,unsigned char *icdata,unsigned char len);
PREFIX void I2CBusRead(unsigned char BusNum,unsigned char len);
PREFIX void I2CBusStatus(unsigned char BusNum);
PREFIX void TTLUART_Speed(unsigned char BusNum,unsigned long baudSpeed);
PREFIX void TTLUART_Read(unsigned char BusNum,unsigned char len);
PREFIX void TTLUART_Write(unsigned char BusNum,unsigned char *icdata,unsigned char len);
PREFIX void TTLGPIO_Init(unsigned char gpioNum,unsigned long mask);
PREFIX void TTLGPIO_Write(unsigned char gpioNum,unsigned long gpdata,unsigned long mask);
PREFIX void TTLGPIO_Read(unsigned char gpioNum,unsigned long mask);
PREFIX void InitPWM(unsigned char chnl,unsigned long freq,unsigned long gran);
PREFIX void Regulate_PWM(unsigned char chnl,unsigned long nCnt);
PREFIX void InitINCAP(unsigned char chnl,unsigned long tfreq,unsigned long gran);
PREFIX void ReadFresh_INCAP(unsigned char chnl);
PREFIX void InitAutoDataFields(unsigned char *ucData,unsigned char ucLen);
PREFIX void ReadSingleAutoData(void);
PREFIX void StartAutoDataMode(void);
PREFIX void pushSnapShotDAC(unsigned char chnlNum,unsigned short cnt);
PREFIX void pullSnapShotADC(unsigned char chnlNum);
PREFIX unsigned char PushArbitrtyWaveForm(unsigned char chnl,float *poly,unsigned char polyLen,unsigned short expndlen);
PREFIX bool Poly2Signal(int nElem,unsigned short *sig,double *coeff);
PREFIX bool Signal2Poly(int nElem,unsigned short *dy, double *store);

PREFIX int GUI_PUTC(unsigned char ch);
PREFIX int GUI_PUTS(char *ch,unsigned short len);

PREFIX int cb_stdout(unsigned char _tr);
PREFIX int cb_load(void *memPtr,unsigned short memLen);
PREFIX int cb_unload(void);
PREFIX int cb_run(char *ScrName,char *SourceStr);
PREFIX unsigned char RequestRead(unsigned short mem_len,unsigned short waitTime);
PREFIX unsigned short CreateMgrCmd(unsigned short cmdx,unsigned short autoRepeat,void *pArg);
PREFIX unsigned short mgr2hw_cmd(unsigned short cmdx);
PREFIX unsigned short hw2mgr_cmd(unsigned short cmdx);
PREFIX int fn_InitCmdQ();
PREFIX unsigned short didLastCmdComplete(unsigned short cmdx);
PREFIX unsigned char i2c_start(unsigned char chnl);
PREFIX unsigned char i2c_addr(unsigned char chnl,unsigned char sladdr);
PREFIX unsigned char i2c_clk(unsigned char chnl,unsigned short freq);
PREFIX unsigned char i2c_write(unsigned char chnl,unsigned short dataLen,unsigned char *arrData);
PREFIX unsigned char i2c_read(unsigned char chnl,unsigned short dataLen,unsigned char *arrData);
PREFIX unsigned char i2c_start(unsigned char chnl);
PREFIX unsigned char i2c_restart(unsigned char chnl);
PREFIX unsigned char i2c_stop(unsigned char chnl);
PREFIX void i2c_scan(unsigned char chnl,unsigned char *addr,unsigned char *len,unsigned char minAdr,unsigned char maxAdr);
PREFIX int led_switch(unsigned short ledNum,unsigned short sAction);
PREFIX int gpio_read(unsigned short gpioNum);
PREFIX void gpio_write(unsigned short gpioNum,unsigned char action);
PREFIX int guiled_switch(unsigned short tabNum,unsigned short ledNum,unsigned short color);
PREFIX int gui_switch_tab(unsigned short tabNum);
PREFIX int fn_PluginIPServer();
PREFIX unsigned short usCommandStatus(unsigned short cmdx);

PREFIX unsigned char  lPushTag(char cmdx,unsigned char *ucbuff,unsigned char len);
PREFIX unsigned short lPullTag(unsigned char *ucbuff);
PREFIX unsigned char  lNetPushTag(char cmdx,unsigned char *ucbuff,unsigned short len);
PREFIX unsigned short lNetPullTag(unsigned char *ucbuff);

PREFIX unsigned char  lusPushTag(char cmdx,unsigned short lm);
unsigned short lEnc_Frame_Buffer(CFrame *cf,unsigned char cmdx,unsigned char token,void *p,unsigned short cSize);

PREFIX unsigned short usScoGetActiveChannl();
PREFIX unsigned short usScoGetNumPoints();
PREFIX unsigned short TransmitTag();
PREFIX unsigned short WaitTag(unsigned short mSleep);
PREFIX int  lStart(void);
PREFIX bool lStop(void);

PREFIX void OnStart();
PREFIX void OnStartIP();
PREFIX void OnExit();

PREFIX void    _script_wait(int iwait_time);
PREFIX void    _script_version();
PREFIX unsigned short _script_wait_cmd(int iwait_time);
PREFIX unsigned short _gpio_rcmd(unsigned short i);
PREFIX unsigned short _gpio_wcmd(unsigned short i,unsigned short j);
PREFIX unsigned short __test_write(unsigned char *chptr,unsigned char len);
PREFIX unsigned short __test_read(unsigned char *chptr,unsigned char len);
PREFIX unsigned char start_CtrlFunction();

PREFIX void _fill_signal(unsigned char chnl,unsigned short currentPlotSize,unsigned short typeWave,unsigned short minH,unsigned short maxH);

PREFIX void startRemoteAccess(void *p,unsigned short ms);
PREFIX void register_CtrlFunction(void (*p)(int));
PREFIX void _start_server_ip(void *a);
PREFIX void _stop_server_ip();


PREFIX void test_register_CtrlFunction(void (*p)(int));
PREFIX void test_startRemoteAccess(void *p,unsigned short ms);
PREFIX unsigned char test_start_CtrlFunction();

PREFIX void _start_tc_server_ip(void *p);
PREFIX int  _start_tc_client_ip(void *a);
PREFIX void _stop_tc_client_ip();
PREFIX void _cl_tc_wait_done();
PREFIX void _cl_tc_encode_msg(unsigned short cnstMsg,unsigned char *buff);


PREFIX int  _start_client_ip(void *a);
PREFIX void _stop_client_ip();
PREFIX void _cl_encode_msg(unsigned short cnstMsg,unsigned char *buff);
PREFIX void _cl_wait_done();

PREFIX int  _is_server_alive(int ms);
PREFIX void _script_signal(unsigned short   numPoint,  \
                           unsigned short   tmr,       \
                           unsigned short   tmrdiv,    \
                           unsigned short   h1Type,    \
                           unsigned short   h2Type,    \
                           unsigned short   ch1Max,    \
                           unsigned short   ch1Min,    \
                           unsigned short   ch2Max,    \
                           unsigned short   ch2Min);


PREFIX bool PushRawFrame(unsigned short uartNum,void *vbuff,unsigned short len);
PREFIX unsigned short PullRawFrame(unsigned short uartNum,unsigned char *vbuff);
PREFIX void set_raw_mode(unsigned short mMode);
PREFIX unsigned short get_raw_mode();
PREFIX void run_cscript(const char *script,unsigned short len);
PREFIX unsigned short usGetString(QString s,char *buffer);

//PREFIX unsigned char open_device(unsigned short vid,unsigned short pid);
//PREFIX void write_device(unsigned char *buffer, int bufflen);
//PREFIX unsigned short read_device(unsigned char *buffer, int bufflen);

//#include <hw/hw.h>
PREFIX int tcp_server_start(unsigned short port);
PREFIX void transmit_pkt(CNetFrame &cfrm);
PREFIX int tftp_put(char *saddr,unsigned short port,char *file);
PREFIX int tftp_get(char *saddr,unsigned short port,char *file);

PREFIX void _SetCurrTab(int);
PREFIX void _App_Sleep(int);
PREFIX void _Scope(int actChnl,int Timer,int TimerDiv,int numElem);
PREFIX void _Signal(int sig1type,int sig2type,int sig1min,int sig1max,int sig2min,int sig2max,int TMR,int TMRDIV,int numElem);
PREFIX void _BannerMsg(unsigned short wPar,unsigned short lPar,const char *str);
PREFIX void  _LED(int ledNum,int ledColor);
PREFIX void  _LCD_DEC(int lcdNum1,int lcdNum2);
PREFIX void  _LCD_HEX(int lcdNum1,int lcdNum2);

PREFIX void vInitRing(unsigned char index,unsigned char *buffer, short buffer_size);
PREFIX void vRingWrite(unsigned char index,void *vdata, short len);
PREFIX unsigned short usRingRead(unsigned char index,void *vdata, short *len);
PREFIX unsigned short usRingReadFast(unsigned char index);
PREFIX void vRingWriteFast(unsigned char index, unsigned char ch);

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

#define FIX_EXTERN PREFIX
#include "global_vars.h"

#define CV_IMAGE_ELEMX(image,row,col)  (((unsigned char *)((image)->imageData + (image)->widthStep*(row)))[(col)])
#define APP_INI_FILE_NAME       "iw_settings.ini"
#define USER_INI_USERFILE_NAME  "user_settings.ini"

#endif
