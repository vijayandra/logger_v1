#include <QtGui>

#include "shared_struct.h"
#include "scratch_pad.h"

void ScratchPad::process_slot(ioTxtGrpthExchStrct &s)
{
    if(s.guiDest.cmdTxt==IW_CLEAR_SCREEN)
    {

    }
    //else if(s.guiDest.cmdTxt==IW_APPEND_TEXT)

    if(s.guiDest.pInfo==IW_PLAIN_TEXT)
    {
        memcpy(buffer,s.hex_data_buffer,s.guiDest.lenTxt);
        buffer[s.guiDest.lenTxt]='\0';

        this->moveCursor (QTextCursor::End);
        this->insertPlainText (buffer);
        this->moveCursor (QTextCursor::End);
    }
    else if(s.guiDest.pInfo==IW_HEX_DUMP)
    {

    }
    else if(s.guiDest.pInfo==IW_HEX_DUMP_WITH_0x)
    {

    }
    else if(s.guiDest.pInfo==IW_LED)
    {

    }
    else if(s.guiDest.pInfo==IW_STATUS)
    {

    }
    else if(s.guiDest.pInfo==IW_BANNER)
    {

    }
    else if(s.guiDest.pInfo==IW_GRAPH)
    {

    }
}

void ScratchPad::setFileName(QString sfile)
{
    QFile file(sfile);

    sfileName=sfile;

    if (file.open(QFile::ReadOnly | QFile::Text))
    {
        QTextStream in(&file);
        this->setPlainText(in.readAll());
    }
}

void ScratchPad::saveFile()
{
    QFile file(sfileName);
    if (!file.open(QFile::WriteOnly | QFile::Text))
    {
        return;
    }

    QTextStream out(&file);
    out << this->toPlainText();
}

ScratchPad::ScratchPad(QWidget *parent) : QPlainTextEdit(parent)
{
    QTextDocument *doc = this->document();
    QFont font = doc->defaultFont();
    font.setFamily("Courier New");
    font.setBold(true);
    doc->setDefaultFont(font);


    //connect(this, SIGNAL(blockCountChanged(int)), this, SLOT(updateLineNumberAreaWidth(int)));
    //connect(this, SIGNAL(cursorPositionChanged()), this, SLOT(highlightCurrentLine()));
    //connect(this, SIGNAL(textChanged()), this, SLOT(saveFile()));

}

//![constructor]

//![extraAreaWidth]

int ScratchPad::lineNumberAreaWidth()
{
    int digits = 1;
    int max = qMax(1, blockCount());
    while (max >= 10)
    {
        max /= 10;
        ++digits;
    }

    int space = 3 + fontMetrics().width(QLatin1Char('9')) * digits;

    return space;
}

//![extraAreaWidth]

//![slotUpdateExtraAreaWidth]


void ScratchPad::resizeEvent(QResizeEvent *e)
{
    QPlainTextEdit::resizeEvent(e);

    QRect cr = contentsRect();
}
