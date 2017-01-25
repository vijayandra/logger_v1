#include <QMainWindow>
#include <QtGui>
#include <QColorDialog>
#include <qapplication.h>
#include <qmainwindow.h>
#include <QtNetwork>
#include <qtoolbar.h>
#include <qcombobox.h>
#include <qwwled.h>

#include "images/connect.xpm"
#include "images/disconnect.xpm"
#include "images/sd.xpm"
#include "images/run.xpm"
#include "images/startscript.xpm"
#include "images/boot.xpm"
#include "images/script_red.xpm"
#include "images/script_grn.xpm"
#include "images/script_yel.xpm"
#include "images/oscilloscope.xpm"

#include "heartbeat.h"
#include "scratch_pad.h"

#include "ext_script.h"
extern "C"
{
#include "srv_coap.h"
#include "enc_coap.h"
#include "ep_mem.h"
#include "ep_file.h"
#include "ep_device.h"
#include "ep_rtc.h"
#include "ep_adc.h"
#include "ep_dac.h"
#include "ep_7020.h"
#include "ep_scratch.h"
#include "ep_direct.h"
#include "ep_scratch.h"
#include "ep_cmds.h"
}

HeartBeat::HeartBeat()
{
    printf("starting listerner \n");
    tBar          = new QToolBar();
    editor        = new CodeEditor(0);
    iExtern       = new IWExtern(this);
    adc_obj       = new ADC_class(this);

    s_pad1        = new ScratchPad(this);
    s_pad2        = new ScratchPad(this);
    s_pad3        = new ScratchPad(this);


    //i_udp=new LRN_cs("192.168.0.8",5683);
    reinit_done=false;

#ifdef ZSERIAL
    p_lrn=new SERIAL_cs(0,this);
#else
    p_lrn=new LRN_io("10.38.180.185",5683,this);
#endif
    iMode=0;

    p_lrn->start();

    createActions();
    //createMenus();
    createToolBars();
    createStatusBar();
    createTabWidget();
    //createDockWindows();

    setWindowTitle(tr("Data Logger"));
    //msgPump=new MsgPump();
    ext_msgPump=new ExternSig();
    mem_obj    = new MemRw_class(0,1000,this);
    file_obj   = new FileRw_class(this);
    rtc_obj    = new RTC_pp(this);
    scratch_obj= new SCRATCH_pp(this);
    sensor_obj = new SENSOR_pp(this);

    timerHeartBeat = new QTimer(this);

    connect(p_lrn, SIGNAL(hwPokeSignalWithIP(QString)),this,SLOT(FoundDataLoggerHWString(QString)));
    connect(p_lrn, SIGNAL(got_valid_coap(scoap_packet_t &)),this,SLOT(route_pkt(scoap_packet_t &)));


    connect(mem_obj, SIGNAL(push_trigger(unsigned char *,unsigned short)),this,SLOT(post_coap(unsigned char *,unsigned short)));
    connect(file_obj,SIGNAL(push_trigger(unsigned char *,unsigned short)),this,SLOT(post_coap(unsigned char *,unsigned short)));
    connect(this,SIGNAL(push_trigger(unsigned char *,unsigned short)),this,SLOT(post_coap(unsigned char *,unsigned short)));
    connect(rtc_obj,SIGNAL(push_trigger(unsigned char *,unsigned short)),this,SLOT(post_coap(unsigned char *,unsigned short)));
    connect(scratch_obj,SIGNAL(push_trigger(unsigned char *,unsigned short)),this,SLOT(post_coap(unsigned char *,unsigned short)));
    connect(sensor_obj,SIGNAL(push_trigger(unsigned char *,unsigned short)),this,SLOT(post_coap(unsigned char *,unsigned short)));

    connect(file_obj, SIGNAL(progress(qint64,qint64)),this,SLOT(update_progress(qint64,qint64)));
    connect(this,SIGNAL(sig_pushFile(const QString &)),file_obj,SLOT(slot_pushFile(const QString &)));
    connect(this,SIGNAL(sig_pullFile(const QString &)),file_obj,SLOT(slot_pullFile(const QString &)));

    connect(timerHeartBeat, SIGNAL(timeout()), this, SLOT(HeartBeatTimerSyncSlot()));
    connect(timerHeartBeat, SIGNAL(timeout()), mem_obj, SLOT(heartbeat_pulse()));
    connect(timerHeartBeat, SIGNAL(timeout()), file_obj,SLOT(heartbeat_pulse()));

    //alarmTimer.setInterval(1);
    //connect(&alarmTimer, SIGNAL(timeout()), this, SLOT(test_write()));
    //alarmTimer.start();
    //connect(runLED, SIGNAL(clicked()),this,SLOT(slotEditAutoExecScriptC()));
    connect(&timer,SIGNAL(timeout()),this,SLOT(timerExpired()));
    connect(&delayRAMCodeTimer,SIGNAL(timeout()),this,SLOT(delayRAMCodeTimerrExpired()));
    connect(d_ram_script, SIGNAL(toggled(bool)),this,SLOT(slotEditAutoExecScriptC(bool)));
    connect(d_run_script,SIGNAL(toggled(bool)), this, SLOT(slot_Run_Script_In_Hardware(bool)));
    connect(d_format, SIGNAL(toggled(bool)),this,SLOT(slot_FormatSDCard()));
    connect(d_reboot, SIGNAL(toggled(bool)),this,SLOT(slot_Reboot()));
    /////////////

    connect(d_ini_script,SIGNAL(toggled(bool)), this, SLOT(slot_Edit_OR_PUSH_INI(bool)));
    connect(d_autoexec_script,SIGNAL(toggled(bool)), this, SLOT(slot_Edit_OR_PUSH_C_Script(bool)));

    connect(sendButton, SIGNAL(clicked()),this,SLOT(browse_and_send()));
    connect(getButton, SIGNAL(clicked()),this,SLOT(getFile()));


    connect(this,SIGNAL(sig_script_load_and_run()),this,SLOT(slot_script_load_and_run()));
    connect(this,SIGNAL(sig_script_run()),this,SLOT(slot_script_run()));

    connect(editor, SIGNAL(code_edit_text_changed()), this, SLOT(update_code_buffer()));


    connect(mem_obj, SIGNAL(comm_start()), this, SLOT(comm_start()));
    connect(mem_obj, SIGNAL(comm_end()), this, SLOT(comm_end()));
    connect(file_obj, SIGNAL(comm_start()), this, SLOT(comm_start()));
    connect(file_obj, SIGNAL(comm_end()), this, SLOT(comm_end()));


    connect(ext_msgPump, SIGNAL(msg_Pumped()),SIGNAL(msg_Pumped()));
    connect(this, SIGNAL(msg_Pumped()),SLOT(msg_PumpedRcvd()));


    connect(this,SIGNAL(SIG_SCRATCH1(ioTxtGrpthExchStrct &)),s_pad1,SLOT(process_slot(ioTxtGrpthExchStrct &)));
    connect(p_lrn,SIGNAL(SIG_GUI_UPDATE(ioTxtGrpthExchStrct &)),s_pad1,SLOT(process_slot(ioTxtGrpthExchStrct &)));
    connect(p_lrn,SIGNAL(SIG_GUI_UPDATE(ioTxtGrpthExchStrct &)),this,SLOT(GUI_UPDATE(ioTxtGrpthExchStrct &)));
}


void HeartBeat::HeartBeatTimerSyncSlot()
{

}


void HeartBeat::route_pkt(scoap_packet_t &pkt)
{
#define  IS_URI_MATCH(X) ((strncmp(X,(char *)pkt.opts[0].buf.p,pkt.opts[0].buf.len))==0)
    static unsigned short i=0;
    static unsigned short j=0;
    static unsigned short m=0;

    if(IS_URI_MATCH(ADC_URI))
    {
        unsigned short crc=1234;
        io_ADC_DAC_Exchng gluData;
        //adc_obj->route_msg(DEV_VERSION_URI,pkt);
        memcpy(&gluData,pkt.payload.p,sizeof(io_ADC_DAC_Exchng));
        for(i=0; i<MAX_ADC_DAC_DATA_IN_PKT; i++)
        {
            xCh1_Array[m]=(float )gluData.ch1[i]/1000;
            xCh2_Array[m]=(float )gluData.ch2[i]/1000;
            crc+=gluData.ch1[i];
            crc+=gluData.ch2[i];
            m++;
            if(m>2000) m=0;
        }
        if(crc==gluData.crc)
        {
            printf("crc OK\r\n");
        }
        else
        {
            printf("crc not OK\r\n");
        }
        fflush(stdout);
        oscope->do_plot();
    }
    else if(IS_URI_MATCH(DEV_VERSION_URI))
    {
        mem_obj->route_msg(DEV_VERSION_URI,pkt);
    }
    else if(IS_URI_MATCH(RW_MEM_ADDR_URI))
    {
        mem_obj->process_incomming_pkt(pkt);
    }
    else if(IS_URI_MATCH(RTC_URI))
    {
        rtc_obj->process_incomming_pkt(pkt);
    }
    else if(IS_URI_MATCH(RTC_TEMP_URI))
    {
        sensor_obj->process_incomming_pkt(pkt);
    }
    else if(IS_URI_MATCH(RTC_HUMD_URI))
    {
        sensor_obj->process_incomming_pkt(pkt);
    }
    else if(IS_URI_MATCH(RW_MEM_URI))
    {
        //mem_obj->route_msg(RW_MEM_URI,pkt);
        mem_obj->process_incomming_pkt(pkt);
    }
    else if(IS_URI_MATCH(FILE_OPEN_URI))
    {
        file_obj->route_msg(FILE_OPEN_URI,pkt);
    }
    else if(IS_URI_MATCH(FILE_CLOSE_URI))
    {
        file_obj->route_msg(FILE_CLOSE_URI,pkt);
    }
    else if(IS_URI_MATCH(FILE_WRITE_URI))
    {
        file_obj->route_msg(FILE_WRITE_URI,pkt);
    }
    else if(IS_URI_MATCH(FILE_READ_URI))
    {
        file_obj->route_msg(FILE_READ_URI,pkt);
    }
    else if(IS_URI_MATCH(FILE_POS_URI))
    {
        file_obj->route_msg(FILE_POS_URI,pkt);
    }
    else if(IS_URI_MATCH(FILE_FORMAT_URI))
    {
        printf("file formatted\r\n");
        fflush(stdout);
    }
    else if(IS_URI_MATCH(FILE_REBOOT_URI))
    {
        printf("Reboot Issued\r\n");
        fflush(stdout);
    }
    else if(IS_URI_MATCH(SCRATCH_URI))
    {
        memcpy(&iGuiUpdate,pkt.payload.p,pkt.payload.len);

        switch(iGuiUpdate.guiDest.tWin)
        {
        case IW_SCRATCH1:
            Q_EMIT SIG_SCRATCH1(iGuiUpdate);
            tabWidget->setCurrentIndex(0);

            break;

        case IW_SCRATCH2:

            Q_EMIT SIG_SCRATCH2(iGuiUpdate);
            tabWidget->setCurrentIndex(1);

            break;

        case IW_SCRATCH3:
            Q_EMIT SIG_SCRATCH3(iGuiUpdate);

            break;

        case IW_RS485:
            Q_EMIT SIG_RS485(iGuiUpdate);

            break;

        case IW_UART2:
            Q_EMIT SIG_UART2(iGuiUpdate);

            break;

        case IW_UART3:
            Q_EMIT SIG_UART3(iGuiUpdate);

            break;

        case IW_UART23:
            Q_EMIT SIG_UART23(iGuiUpdate);

            break;

        default:
            break;

        }
    }
#undef  IS_URI_MATCH
}

void HeartBeat::slot_Run_Script_In_Hardware(bool x)
{
    //unsigned short len;
    //len=coap_pc_req(buff,COAP_METHOD_GET,"cscript",NULL,0);
    //Q_EMIT push_trigger(buff,len);

    iMode=3;
    if(timer.isActive())
    {
        timer.stop();
        d_ini_script->setChecked(false);
        printf("BAT Load and RUN\n");
        Q_EMIT sig_script_run();
    }
    else
    {
        timer.setInterval(550);
        timer.setSingleShot(true);
        timer.start();
    }

}

void HeartBeat::slot_Edit_OR_PUSH_INI(bool x)
{
    iMode=1;
    if(timer.isActive())
    {
        timer.stop();
        d_ini_script->setChecked(false);
        printf("INI Single Click\n");
        Q_EMIT sig_pushFile("autoexec.ini");
    }
    else
    {
        timer.setInterval(550);
        timer.setSingleShot(true);
        timer.start();
    }
}

void HeartBeat::slot_Edit_OR_PUSH_C_Script(bool x)
{
    iMode=2;

    if(timer.isActive())
    {
        timer.stop();
        d_autoexec_script->setChecked(false);
        Q_EMIT sig_pushFile("autoexec.c");
        printf("C Script Single Click\n");
    }
    else
    {
        timer.setInterval(550);
        timer.setSingleShot(true);
        timer.start();
    }
}

void HeartBeat::delayRAMCodeTimerrExpired()
{
    //printf(c_code_data);
    //fflush(stdout);
    mem_obj->slot_sendScriptC_Code(c_code_data);
    /* time to send code to hardware */


}

void HeartBeat::timerExpired()
{
    if(iMode==1)
    {
        editor->setMode(0);
        editor->setFileName("autoexec.ini");
        editor->show();
        editor->setWindowTitle(QObject::tr("AutoExec.INI"));
        iMode=0;
    }
    else if(iMode==2)
    {
        editor->setMode(0);
        editor->setFileName("autoexec.c");
        editor->show();
        editor->setWindowTitle(QObject::tr("AutoExec.C"));
        iMode=0;
    }
    else if(iMode==3)
    {
        editor->setMode(0);
        iMode=0;
        Q_EMIT sig_script_run();
    }
    else if(iMode==4)
    {
        QString fileName("autoexec.c");
        iMode=4;
        if (!fileName.isEmpty())
        {
            QFile file(fileName);
            if (!file.open(QFile::ReadOnly))
            {
                return;
            }

            QByteArray data = file.readAll();
            if(data.size()<4095)
                memcpy(c_code_data,data.data(),data.size());
            else
                memcpy(c_code_data,data.data(),4095);

            delayRAMCodeTimer.setInterval(550);
            delayRAMCodeTimer.setSingleShot(true);
            delayRAMCodeTimer.start();
        }
    }

    //if(d_ini_script->isChecked())

    fflush(stdout);
}

//coapUDP=new CoAPComm(oscope_id->itemText(0));

void HeartBeat::PushRTCTimeSlot()
{

}

void HeartBeat::autoExecScriptSlot()
{
    QDesktopServices desk;
    //desk.openUrl(QUrl("file://HeartBeat.cpp"));
    desk.openUrl(QUrl("mainwindow.cpp"));
}

void HeartBeat::newScriptSlot()
{
    QTreeWidget *rem_Filelist;
    rem_Filelist = new QTreeWidget;

    rem_Filelist->setEnabled(false);
    rem_Filelist->setRootIsDecorated(false);
    rem_Filelist->setHeaderLabels(QStringList() << tr("Name") << tr("Size")  << tr("Time"));

    rem_Filelist->header()->setStretchLastSection(true);
    rem_Filelist->setEnabled(true);
    rem_Filelist->style()->pixelMetric(QStyle::PM_ScrollBarExtent);

    rem_Filelist->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    rem_Filelist->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

    QList<QTreeWidgetItem *> items;
    for (int i = 0; i < 1; ++i)
    {
        items.append(new QTreeWidgetItem((QTreeWidget*)0, QStringList(QString("item: %1").arg(i))));
        rem_Filelist->insertTopLevelItems(0, items);
    }

    for(int i=0; i<5; i++)
    {
        //rem_Filelist->resizeColumnToContents(i);
    }
    printf("new script \n");
    fflush(stdout);
    rem_Filelist->show();
}

void HeartBeat::createActions()
{
    connLED    = new QwwLed(Qt::darkGray, QwwLed::Circular,this);
    connLED->setMinimumSize(30,30);

    d_connect = new QAction(QIcon(icon_connect), "Connect", this);
    d_connect->setShortcut(tr("C-C"));
    d_connect->setCheckable(true);

#if 0
    newScript = new QAction(QIcon(":/images/new.png"), tr("&New \"C\" Script"), this);
    newScript->setShortcuts(QKeySequence::New);
    newScript->setStatusTip(tr("Create a new form letter"));
    connect(newScript, SIGNAL(triggered()), this, SLOT(newScriptSlot()));

    autoExecScript = new QAction(QIcon(":/images/new.png"), tr("&AutoExec \"C\" Script"), this);
    autoExecScript->setShortcuts(QKeySequence::New);
    autoExecScript->setStatusTip(tr("Create a new form letter"));
    connect(autoExecScript, SIGNAL(triggered()), this, SLOT(autoExecScriptSlot()));
#endif

    rtcClock = new QAction(QIcon(":/images/rtc.png"), tr("&Sync RTC Clock"), this);
    rtcClock->setShortcuts(QKeySequence::New);
    rtcClock->setStatusTip(tr("Create a new form letter"));
    connect(rtcClock, SIGNAL(triggered()), this, SLOT(PushRTCTimeSlot()));

    saveAct = new QAction(QIcon(":/images/save.png"), tr("&Save..."), this);
    saveAct->setShortcuts(QKeySequence::Save);
    saveAct->setStatusTip(tr("Save the current form letter"));
    connect(saveAct, SIGNAL(triggered()), this, SLOT(save()));

#if 0
    printAct = new QAction(QIcon(":/images/print.png"), tr("&Print..."), this);
    printAct->setShortcuts(QKeySequence::Print);
    printAct->setStatusTip(tr("Print the current form letter"));
    connect(printAct, SIGNAL(triggered()), this, SLOT(print()));


    undoAct = new QAction(QIcon(":/images/undo.png"), tr("&Undo"), this);
    undoAct->setShortcuts(QKeySequence::Undo);
    undoAct->setStatusTip(tr("Undo the last editing action"));
    connect(undoAct, SIGNAL(triggered()), this, SLOT(undo()));

    quitAct = new QAction(tr("&Quit"), this);
    quitAct->setShortcuts(QKeySequence::Quit);
    quitAct->setStatusTip(tr("Quit the application"));
    connect(quitAct, SIGNAL(triggered()), this, SLOT(close()));

    aboutAct = new QAction(tr("&About"), this);
    aboutAct->setStatusTip(tr("Show the application's About box"));
    connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));

    aboutQtAct = new QAction(tr("About &Qt"), this);
    aboutQtAct->setStatusTip(tr("Show the Qt library's About box"));
    connect(aboutQtAct, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
#endif
}

void HeartBeat::createToolBars()
{
    fileToolBar = addToolBar(tr("File"));
    fileToolBar->addWidget(connLED);
    fileToolBar->addAction(d_connect);
    //fileToolBar->addAction(newScript);
    fileToolBar->addAction(rtcClock);
    //fileToolBar->addAction(autoExecScript);
    //fileToolBar->addAction(saveAct);
    //fileToolBar->addAction(printAct);

    d_ram_script = new QAction(QIcon(script_yel_xpm), "Single Click (Push)/Double Click(Edit)", tBar);
    d_ram_script->setCheckable(true);
    fileToolBar->addAction(d_ram_script);

    d_run_script = new QAction(QIcon(":/images/go.png"), tr("&Run \"C\" Script"), tBar);
    d_run_script->setCheckable(true);
    fileToolBar->addAction(d_run_script);


    //runLED    = new QwwLed(Qt::yellow, QwwLed::Circular,this);
    //runLED->setMinimumSize(30,30);
    //fileToolBar->addWidget(runLED);

    //editToolBar = addToolBar(tr("Edit"));
    //editToolBar->addAction(undoAct);

    commLED    = new QwwLed(Qt::darkGray, QwwLed::Circular,this);
    commLED->setMinimumSize(30,30);
    fileToolBar->addWidget(commLED);


    sendButton = new QPushButton(tr("Send"),this);
    fileToolBar->addWidget(sendButton);

    lineEdit=new QLineEdit(this);
    lineEdit->setFixedWidth(100);

    getButton = new QPushButton(tr("Get"),this);
    fileToolBar->addWidget(getButton);


    fileToolBar->addWidget(lineEdit);

    oscope_id = new QComboBox(this);

    //oscope_id->setProperty(AdjustToContents);
    //oscope_id->setMinimumContentsLength(12);
    oscope_id->setEditable(true);
    oscope_id->setSizeAdjustPolicy(QComboBox::AdjustToContents);

    fileToolBar->addWidget(oscope_id);

    //oscope_id->setIcon(QIcon(oscilloscope));
    //_led3    = new QwwLed(Qt::darkGray, QwwLed::Circular,this);
    //fileToolBar->addWidget(_led3);

    d_ini_script = new QAction(QIcon(script_red), "INI", tBar);
    d_ini_script->setCheckable(true);

    d_autoexec_script = new QAction(QIcon(script_grn_xpm), "AutoExec", tBar);
    d_autoexec_script->setCheckable(true);

    //fileToolBar->addWidget(rem_Filelist);
    fileToolBar->addAction(d_ini_script);
    fileToolBar->addAction(d_autoexec_script);


    d_format = new QAction(QIcon(":/images/format.png"), tr("&Format SD Card"), tBar);
    d_format->setCheckable(true);
    fileToolBar->addAction(d_format);

    d_reboot = new QAction(QIcon(":/images/reboot.png"), tr("&Reboot"), tBar);
    d_reboot->setCheckable(true);
    fileToolBar->addAction(d_reboot);
}

//! [8]
void HeartBeat::createStatusBar()
{
    statusBar()->showMessage(tr("Ready"));
}
//! [8]

void HeartBeat::createTabWidget()
{
    tabWidget    = new QTabWidget(this);
    setCentralWidget(tabWidget);

    tabWidget->addTab(s_pad1, tr("s pad1"));
    tabWidget->addTab(s_pad2, tr("s pad2"));
    tabWidget->addTab(s_pad3, tr("s pad3"));
    tabWidget->addTab(editor,  tr("\"Edit\" autoexec.c \"C\""));
    tabWidget->addTab(iExtern, tr("\"Extern\""));
    oscope       = new Oscope(tabWidget,this);
    osignal      = new Osignal(tabWidget,this);

    //connect(this,SIGNAL(do_plot()),oscope,SLOT(do_plot));

    //tabWidget->addTab(oscope);
}

void HeartBeat::comm_start()
{
    commLED->setColor(Qt::red);
}

void HeartBeat::comm_end()
{
    commLED->setColor(Qt::yellow);
}

//! [9]
void HeartBeat::createDockWindows()
{
    QDockWidget *dock = new QDockWidget(tr("UART1RX"), this);
    dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    textEdit1 = new QTextEdit(dock);
    dock->setWidget(textEdit1);

    addDockWidget(Qt::RightDockWidgetArea, dock);
    //viewMenu->addAction(dock->toggleViewAction());

    dock = new QDockWidget(tr("UART2RX"), this);
    textEdit2 = new QTextEdit(dock);
    dock->setWidget(textEdit2);

    addDockWidget(Qt::LeftDockWidgetArea, dock);
    //viewMenu->addAction(dock->toggleViewAction());
}

bool HeartBeat::eventFilter(QObject *object, QEvent *e)
{
    if ( e->type() == QEvent::Resize )
    {
        //const QSize &size = ((QResizeEvent *)e)->size();
        //lineEdit->setText("*******");

    }

    return HeartBeat::eventFilter(object, e);
}

void HeartBeat::closeEvent(QCloseEvent *event)
{
    //if (maybeSave()) {
    if (true)
    {
        //writeSettings();
        event->accept();
    }
    else
    {
        event->ignore();
    }
}


void HeartBeat::FoundDataLoggerHWString(QString s)
{
    bool found=false;
    int i;

    unsigned short len;
    /* device ping received, ask version info */

    for(i = 0u; i < oscope_id->count(); i++ )
    {
        QString s1=oscope_id->itemText(i);
        if(s==s1) found=true;
    }

    if(!found)
    {
        oscope_id->addItem(s);
        connLED->setColor(Qt::green);

        timerHeartBeat->start(10);

        len=coap_pc_req(buff,COAP_METHOD_GET,"device/version",NULL,0);
        p_lrn->push_msg(buff,len,1);
    }

}

void HeartBeat::slotEditAutoExecScriptC(bool n)
{
    //editor=new CodeEditor("autoexec.c");
    if(timer.isActive())
    {
        iMode=0;
        timer.stop();

        editor->setMode(1);
        editor->setFileName("autoexec.c");
        editor->show();
        editor->setWindowTitle(QObject::tr("AutoExec.C"));
        tabWidget->setCurrentIndex(3);
    }
    else
    {
        timer.setInterval(550);
        timer.setSingleShot(true);
        timer.start();
        iMode=4;
    }
}

void HeartBeat::update_progress(qint64 currPos,qint64 endPos)
{
    char buff[80];
    if(endPos==0)
    {
        sprintf(buff,"A%d",currPos);
        lineEdit->setText(buff);
    }
    else
    {
        sprintf(buff,"P%d",100*currPos/endPos);
        lineEdit->setText(buff);
    }
}

void HeartBeat::getFile()
{
    if(((lineEdit->text()).size())>0)
    {
        fileName=lineEdit->text();
        Q_EMIT sig_pullFile(fileName);
        printf("file name\n");
        fflush(stdout);
    }

}

void HeartBeat::browse_and_send()
{
    QFileDialog::Options options;
    QString selectedFilter;
    fileName = QFileDialog::getOpenFileName(this,
                                            tr("QFileDialog::getOpenFileName()"),
                                            "",
                                            tr("All Files (*);;INI Files (*.ini);;C Files (*.c);;C Files (*.log)"),
                                            &selectedFilter,
                                            options);

    if (!fileName.isEmpty())
    {
        Q_EMIT sig_pushFile(fileName);
    }
}

void HeartBeat::slot_script_load_and_run()
{
    unsigned short len;
    len=coap_pc_req(buff,COAP_METHOD_PUT,"cscript",NULL,0);
    Q_EMIT push_trigger(buff,len);

}

void HeartBeat::slot_script_run()
{
    unsigned short len;
    len=coap_pc_req(buff,COAP_METHOD_GET,"cscript",NULL,0);
    Q_EMIT push_trigger(buff,len);
}

HeartBeat::~HeartBeat()
{
    fflush(stdout);
    delete tBar;
    delete editor;
    delete p_lrn;
    delete ext_msgPump;
}

void HeartBeat::msg_PumpedRcvd()
{
    commonMsgHandle();
}

void HeartBeat::GUI_UPDATE(ioTxtGrpthExchStrct &)
{
    printf("run-->%s\n",__FUNCTION__);
    fflush(stdout);
}

void HeartBeat::commonMsgHandle(void)
{
    unsigned short winMsg,wPar,lPar;
    //unsigned char  ucArr[4];
    float fVal;
    char        strMsg[1023];

    //while(usPullStrWinHLQ(winMsg,ucArr,fVal,strMsg))
    while(usPullStrWinQ(winMsg,wPar,lPar,fVal,strMsg))
    {
        switch(winMsg)
        {
        case WM_BANNER:
        case WM_CLEAR_MSG:
        case WM_APPEND_MSG:
        case WM_LED:
        case WM_LCD_HEX:
        case WM_LCD_DEC:

        default:

            break;
        }
    }
}

void HeartBeat::slot_FormatSDCard()
{
    unsigned short len;
    printf("format SD card clicked\r\n");
    fflush(stdout);
    len=coap_pc_req(buff,COAP_METHOD_PUT,"sdformat",NULL,0);
    Q_EMIT push_trigger(buff,len);
}

void HeartBeat::slot_Reboot()
{
    unsigned short len;
    len=coap_pc_req(buff,COAP_METHOD_PUT,"reboot",NULL,0);
    Q_EMIT push_trigger(buff,len);
}
