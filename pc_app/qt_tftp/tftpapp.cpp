#include "tftpapp.h"
#include "ui_tftpapp.h"

TFTPApp::TFTPApp(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TFTPApp)
{
    ui->setupUi(this);
    qRegisterMetaType<rqCode>("rqCode");
    client = NULL;
}

TFTPApp::~TFTPApp()
{
    delete ui;
}

void TFTPApp::on_pbStartStopServer_pressed()
{
}

void TFTPApp::on_pbPut_pressed()
{
//    toggleClientButtons(false);

    if(client == NULL)
    {
        client = new TFTPClient(ui->leIPHost->text(), (qint16)ui->spPort->value(),
                                ui->leFileName->text(),this);
//        connect(client, SIGNAL(workerDone()), this, SLOT(workerDone()));
    }
    else
    {
        client->setReqInfo(ui->leIPHost->text(), (qint16)ui->spPort->value(),
                           ui->leFileName->text());
    }
//    connect(client, SIGNAL(workerDone(bool)), this, SLOT(workerDone()));
    client->putFile();
}

void TFTPApp::on_pbGet_pressed()
{
//    toggleClientButtons(false);

    if(client == NULL)
    {
        client = new TFTPClient(ui->leIPHost->text(), (qint16)ui->spPort->value(),
                                ui->leFileName->text(), this);
    }
    else
    {
        client->setReqInfo(ui->leIPHost->text(), (qint16)ui->spPort->value(),
                           ui->leFileName->text());
    }
    client->getFile();
}

void TFTPApp::on_pbStopClient_pressed()
{
    if(client != NULL)
    {
        client->stopTransfer();
    }
//    toggleClientButtons(true);
}

void TFTPApp::toggleClientButtons(bool val)
{
    ui->pbGet->setEnabled(val);
    ui->pbPut->setEnabled(val);
    ui->pbStopClient->setEnabled(!val);
}

void TFTPApp::workerDone()
{
    toggleClientButtons(true);
}
