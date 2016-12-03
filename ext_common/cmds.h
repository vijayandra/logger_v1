#ifndef _OSCOPE_CMDS_H
#define _OSCOPE_CMDS_H


enum
{
    MEM_C_SRC=0,
    MEM_UART1_RX=1,
    MEM_UART1_TX=2,
    MEM_UART2_RX=3,
    MEM_UART2_TX=4,
    MEM_UART3_RX=5,
    MEM_UART3_TX=6,
    MEM_ADC=7,
    MEM_DAC=8,
    MEM_I2C=9,
    MEM_FIL=10
};

enum
{
    INOCMD=0,
    ICHANGE_TAB,
    IUSER_TAB,
    ISCOPE_CTRL,
    ISIGNAL_CTRL,
    IINPUT_CAP,
    IOUTPUT_CAP,
    II2C_MASTER,
    IUART_WRITE,
    IUART_READ,
    ILED_CTRL,
    IGPIO_READ,
    IGPIO_WRITE,
    IGRAPH_CTRL,
    ITAG_CTRL=0xEE
};


enum
{
    NOCMD=0,
    CHANGE_TAB,
    CAPTURE_IMG,
    PROCESS_IMG,
    RUN_FILTER,
    APPLY_MASK,
    CAPTURE_N,
    CAPTURE_N_AVG,
    VIEW_BUFFER,
    GRAPH_CTRL,
    DOMATH,
    DOTHRESHOLD,
    INVERTIMG,
    COL2GRAY,
    DO_SIFT
};

#define SCRIPT_PACKET_SIZE 56
typedef union
{
    char           _ch_buff[SCRIPT_PACKET_SIZE];
    unsigned char  _uc_buff[SCRIPT_PACKET_SIZE];

    struct
    {
        unsigned short TMR;
        unsigned short TMRDIV;
        unsigned short numElem;
        unsigned short actChnl;
        unsigned char  buff[50];
    } scope;

    struct
    {
        unsigned short TMR;
        unsigned short TMRDIV;
        unsigned short numElem;

        unsigned short sig1type;
        unsigned short sig1max;
        unsigned short sig1min;

        unsigned short sig2type;
        unsigned short sig2max;
        unsigned short sig2min;

        unsigned char  buff[38];
    } signal;

    struct
    {
        unsigned short tabNum;
        unsigned char  ledNum;
        unsigned char  ledColor;
        unsigned char  plotNum;
        unsigned char  plotPar;
        char           msg[20];
        unsigned char  buff[30];
    } tab;

} ModeData  __attribute__ ((aligned(4)));


#define SCRIPT_NET_PACKET_SIZE 1424
typedef union
{
    char           _ch_buff[SCRIPT_NET_PACKET_SIZE];
    unsigned char  _uc_buff[SCRIPT_NET_PACKET_SIZE];

    struct
    {
        unsigned short TMR;
        unsigned short TMRDIV;
        unsigned short numElem;
        unsigned short actChnl;
        unsigned char  buff[50];
    } scope;

    struct
    {
        unsigned short TMR;
        unsigned short TMRDIV;
        unsigned short numElem;

        unsigned short sig1type;
        unsigned short sig1max;
        unsigned short sig1min;

        unsigned short sig2type;
        unsigned short sig2max;
        unsigned short sig2min;

        unsigned char  buff[38];
    } signal;

    struct
    {
        unsigned short tabNum;
        unsigned char  ledNum;
        unsigned char  ledColor;
        unsigned char  plotNum;
        unsigned char  plotPar;
        char           msg[20];
        unsigned char  buff[30];
    } tab;

} ModeNetData  __attribute__ ((aligned(4)));



#endif
