#include "QTermWidget.h"

#include <QApplication>

QTermWidget::QTermWidget(QWidget *parent):
    QTermScreen(parent)
{
    m_Mode = 0;
    setAcceptDrops(false);
}

void QTermWidget::putData(const QByteArray &data)
{
    if (data.size() == 0)
        return;

    for (int i = 0; i < data.size(); i ++)
    {
        recvChar(data[i]);
    }

    flushText();
}

void QTermWidget::recvChar(char ch)
{
    switch (m_Mode)
    {
    case 2:
    {
        switch (ch)
        {
        case 'A':
        case 'B':
        case 'C':
        case 'D':
        case 'H':
        {
            m_Mode = 0;
            moveCursor(ch);
        }break;
        case 'J':
        case 'K':
        {
            m_Mode = 0;

            eraseText(ch);
        }break;
        case 'm':
        {
            m_Mode = 0;
            setDisplay();
        }break;
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
        case ';':
        {
            m_Param.push_back(ch);
        }break;
        case '?':
        {
            m_Mode = 3;
        }break;
        default:
        {
            m_Mode = 0;
        }break;
        }
    }break;
    case 1:
    {
        switch (ch)
        {
        case '[':
        {
            m_Mode = 2;
        }break;
        default:
        {
            m_Mode = 0;
        }break;
        }
    }break;
    case 3:
    {
        switch (ch)
        {
        case '0':
        case '1':
        {}break;
        case 'h':
        {
            m_Mode = 0;
        }break;
        }
    }break;
    default:
    {
        switch (ch)
        {
        case '\e':
        {
            m_Mode = 1;
            m_Param.clear();
            flushText();
        }break;
        case 0x0D:
        {
            flushText();
            CursorStartOfLine();
        }break;
        case 0x0A:
        {
            flushText();
            CursorNewLine();
        }break;
        case 0x08:
        {
            flushText();
            CursorLeft();
        }break;
        case 0x07:
        {
            QApplication::beep();
        }break;
        default:
        {
            m_Text.push_back(ch);
        }break;
        }
    }break;
    }
}

void QTermWidget::mousePressEvent(QMouseEvent *e)
{
    Q_UNUSED(e)
    setFocus();
}

void QTermWidget::keyPressEvent(QKeyEvent *e)
{
    QByteArray byte;

    switch (e->key())
    {
    case Qt::Key_Backspace:
        byte[0] = 0x08;
        break;
    case Qt::Key_Left:
        byte[0] = 0x1B; byte[1] = 0x5B, byte[2] = 0x44;
        break;
    case Qt::Key_Right:
        byte[0] = 0x1B; byte[1] = 0x5B, byte[2] = 0x43;
        break;
    case Qt::Key_Up:
        byte[0] = 0x1B; byte[1] = 0x5B, byte[2] = 0x41;
        break;
    case Qt::Key_Down:
        byte[0] = 0x1B; byte[1] = 0x5B, byte[2] = 0x42;
        break;
    case Qt::Key_Enter:
        break;
    case Qt::Key_Return:
    default:
        byte = e->text().toLocal8Bit();
        break;
    }

    if (byte.size() != 0)
    {
        emit outData(byte);
    }
}

void QTermWidget::parseParam(QVector <int> &param, int np, int defval)
{
    if (m_Param.isEmpty())
    {
        for (int i = 0; i < np; i ++)
        {
            param.push_back(defval);
        }
        return;
    }

    m_Param.append(';');

    QString tmp;
    for (int i = 0; i < m_Param.count(); i ++)
    {
        QChar ch = m_Param.at(i);

        if (ch == ';')
        {
            int v;

            v = tmp.toInt();
            param.push_back(v);
            tmp.clear();
            continue;
        }
        tmp.push_back(ch);
    }
}

void QTermWidget::eraseText(char cmd)
{
    QVector <int> p;

    parseParam(p);
    if (cmd == 'J')
    {
        switch (p[0])
        {
        case 0:
        {
            EraseDown();
        }break;
        case 1:
        {
            EraseUp();
        }break;
        case 2:
        {
            EraseScreen();
        }break;
        }
    }
    else
    {
        switch (p[0])
        {
        case 0:
        {
            EraseEndOfLine();
        }break;
        case 1:
        {
            EraseStartOfLine();
        }break;
        case 2:
        {
            EraseEntireLine();
        }break;
        }
    }
}

void QTermWidget::setDisplay()
{
    QVector <int> p;

    parseParam(p);

    for(int i = 0; i < p.count(); i ++)
    {
        int v = p[i];

        switch (v)
        {
        case 0:
        {
            DisplayReset();
        }break;
        default:
        {
            if (v >= 30 && v <= 37)
            {
                QColor c = GetColor(v - 30);
                DisplayForeground(c);
            }
            if (v >= 40 && v <= 47)
            {
                QColor c = GetColor(v - 40);
                DisplayBackground(c);
            }
        }break;
        }
    }
}

void QTermWidget::flushText()
{
    if (m_Text.size())
    {
        SelectRight(m_Text.size());
        insertPlainText(m_Text);
        m_Text.clear();
    }
}

void QTermWidget::moveCursor(char cmd)
{
    QVector <int> p;

    parseParam(p, 2, 1);

    switch (cmd)
    {
    case 'A':
        CursorUp(p[0]);
        break;
    case 'B':
        CursorDown(p[0]);
        break;
    case 'C':
        CursorLeft(p[0]);
        break;
    case 'D':
        CursorRight(p[0]);
        break;
    case 'H':
        CursorPosition(p[0], p[1]);
        break;
    }
}

void QTermWidget::debug(const QByteArray &data)
{
    QString str;

    for (int i = 0; i < data.size(); i ++)
    {
        QString tmp;
        str += tmp.sprintf("0x%02X, ", (unsigned char)(data.data()[i]));
    }

    qDebug(str.toStdString().data());
}
