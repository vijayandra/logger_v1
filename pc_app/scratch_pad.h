#ifndef _SCRATCH_VIEWER_H
#define _SCRATCH_VIEWER_H

#include <QPlainTextEdit>
#include <QObject>
#include "shared_struct.h"

QT_BEGIN_NAMESPACE
class QPaintEvent;
class QResizeEvent;
class QSize;
class QWidget;
QT_END_NAMESPACE


//![codeeditordefinition]

class ScratchPad : public QPlainTextEdit
{
    Q_OBJECT

public:
    ScratchPad(QWidget *parent = 0);
    char buffer[4095];
    unsigned char iMode;

    ioTxtGrpthExchStrct iGuiUpdate;

    void lineNumberAreaPaintEvent(QPaintEvent *event);
    int  lineNumberAreaWidth();
    void setFileName(QString sfileName);


protected:

    void resizeEvent(QResizeEvent *event);

public slots:
    void saveFile();
    void process_slot(ioTxtGrpthExchStrct &s);

private:
    QString sfileName;
signals:
    void code_edit_text_changed();
};

//![codeeditordefinition]
//![extraarea]

#endif
