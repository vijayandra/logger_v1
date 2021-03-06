#include <QCoreApplication>
#include <iostream>
#include <stdio.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <unistd.h>
#include <QMutex>
#include <QThread>

#include "console.h"

using namespace std;

//#define EXAMPLE_SIGNAL
//#define EXAMPLE_SCOPE
//#define GPIO_CTRL
//#define EXAMPLE_I2C

extern "C"
{
#include "srv_coap.h"
    int coap_request(unsigned char *buff,uint8_t k);
    int coap_decode(unsigned char *buff,unsigned short len);
}

#define PORT 5683

int main(int argc, char **argv)
{
    int n, rc;
    int fd;
    uint8_t buf[4096];
    int len;

    QCoreApplication app(argc, argv);
    QStringList arguments = app.arguments();
    arguments.takeFirst();      // remove the first argument, which is the program's name
    if (arguments.isEmpty())
    {
    }

    Console *cmd=new Console();

    cmd->append(arguments);

    QObject::connect(cmd, SIGNAL(finished()), &app, SLOT(quit()));
    app.exec();

    return 0;
}

