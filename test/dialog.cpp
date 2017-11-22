#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_home_clicked()
{
    QByteArray data;
    QString r,c,t;

    r = ui->row->text();
    c = ui->column->text();
    t = "\x1B[" + r + ";" + c + "H";
    data = t.toLocal8Bit();

    emit outData(data);
}

void Dialog::on_start_clicked()
{
    QByteArray data = "\r行首";

    emit outData(data);
}

void Dialog::on_up_clicked()
{
    QByteArray data = "\x1B[A";

    emit outData(data);
}

void Dialog::on_down_clicked()
{
    QByteArray data = "\x1B[B";

    emit outData(data);
}

void Dialog::on_left_clicked()
{
    QByteArray data = "\x1B[C";

    emit outData(data);
}

void Dialog::on_right_clicked()
{
    QByteArray data = "\x1B[D";

    emit outData(data);
}

void Dialog::on_reset_clicked()
{
    QByteArray data = "\x1B[0myes";

    emit outData(data);
}

void Dialog::on_color_clicked()
{
    QByteArray data;
    QString b,f,t;

    b = ui->back->currentText();
    f = ui->fore->currentText();
    t = "\x1B[" + b + ";" + f + "mtest";
    data = t.toLocal8Bit();

    emit outData(data);
}

void Dialog::on_lend_clicked()
{
    QByteArray data = "\x1B[K";

    emit outData(data);
}

void Dialog::on_lstart_clicked()
{
    QByteArray data = "\x1B[1K";

    emit outData(data);
}

void Dialog::on_lentire_clicked()
{
    QByteArray data = "\x1B[2K";

    emit outData(data);
}

void Dialog::on_ldown_clicked()
{
    QByteArray data = "\x1B[J";

    emit outData(data);
}

void Dialog::on_lup_clicked()
{
    QByteArray data = "\x1B[1J";

    emit outData(data);
}

void Dialog::on_screen_clicked()
{
    QByteArray data = "\x1B[2J";

    emit outData(data);
}

void Dialog::on_crlf_clicked()
{
    QByteArray data = "\x0D\x0Alala";

    emit outData(data);
}

void Dialog::on_nl_clicked()
{
    QByteArray data = "\r\n";

    emit outData(data);
}

void Dialog::on_test1_clicked()
{
    char ch[] ={0x0D, 0x0A,
                  0x1B, 0x5B, 0x31, 0x3B, 0x31, 0x48, 0x1B, 0x5B, 0x30, 0x4A,
                  0x0D, 0x70, 0x72, 0x6F, 0x63, 0x20, 0x20, 0x20, 0x20, 0x20,
                  0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x2F, 0x70, 0x72,
                  0x6F, 0x63, 0x20, 0x20, 0x20, 0x70, 0x72, 0x6F, 0x63, 0x20,
                  0x20, 0x20, 0x20, 0x64, 0x65, 0x66, 0x61, 0x75, 0x6C, 0x74,
                  0x73, 0x20, 0x20, 0x20, 0x20, 0x30, 0x20, 0x20, 0x20, 0x30,
                  0x0A, 0x0D, 0x73, 0x79, 0x73, 0x66, 0x73, 0x20, 0x20, 0x20,
                  0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x2F, 0x73,
                  0x79, 0x73, 0x20, 0x20, 0x20, 0x20, 0x73, 0x79, 0x73, 0x66,
                  0x73, 0x20, 0x20, 0x20, 0x64, 0x65, 0x66, 0x61, 0x75, 0x6C,
                  0x74, 0x73, 0x20, 0x20, 0x20, 0x20, 0x30, 0x20, 0x20, 0x20,
                  0x30, 0x0A, 0x0D, 0x7E, 0x0A, 0x0D, 0x7E, 0x0A, 0x0D, 0x7E,
                  0x0A, 0x0D, 0x7E, 0x0A, 0x0D, 0x7E, 0x0A, 0x0D, 0x7E, 0x0A, 0x0D,
                  0x7E, 0x0A, 0x0D, 0x7E, 0x0A, 0x0D, 0x7E, 0x0A, 0x0D, 0x7E,
                  0x0A, 0x0D, 0x7E, 0x0A, 0x0D, 0x7E, 0x0A, 0x0D, 0x7E, 0x0A, 0x0D,
                  0x7E, 0x0A, 0x0D, 0x7E, 0x0A, 0x0D, 0x7E, 0x0A, 0x0D, 0x7E, 0x0A, 0x0D,
                  0x7E, 0x0A, 0x0D, 0x7E, 0x0A, 0x0D, 0x7E, 0x0A, 0x0D, 0x7E,
                  0x1B, 0x5B, 0x31, 0x3B, 0x31, 0x48, 0x1B, 0x5B, 0x32, 0x34, 0x3B, 0x31, 0x48,
                  0x1B, 0x5B, 0x30, 0x4B,
                  0x2D, 0x20, 0x66, 0x73, 0x74, 0x61, 0x62, 0x20, 0x31, 0x2F, 0x32, 0x20,
                  0x35, 0x30, 0x25, 0x1B, 0x5B, 0x31, 0x3B, 0x31, 0x48,
                  0x00
                 };

    QByteArray data = ch;

    emit outData(data);
}

void Dialog::on_test2_clicked()
{
    char ch[] =
    {
        0x0D, 0x0A,
#if 1
        0x1B, 0x5B, 0x3F, 0x31, 0x30, 0x34, 0x39, 0x68,
#endif
        0x1B, 0x5B, 0x31, 0x3B, 0x31, 0x48,
        0x1B, 0x5B, 0x4A,
        0x1B, 0x5B, 0x32, 0x3B, 0x31, 0x48, 0x7E,
#if 1
        0x1B, 0x5B, 0x33, 0x3B, 0x31, 0x48, 0x7E,
        0x1B, 0x5B, 0x34, 0x3B, 0x31, 0x48, 0x7E,
        0x1B, 0x5B, 0x35, 0x3B, 0x31, 0x48, 0x7E,

        0x1B, 0x5B, 0x36, 0x3B, 0x31, 0x48, 0x7E,
        0x1B, 0x5B, 0x37, 0x3B, 0x31, 0x48, 0x7E,
        0x1B, 0x5B, 0x38, 0x3B, 0x31, 0x48, 0x7E,
        0x1B, 0x5B, 0x39, 0x3B, 0x31, 0x48, 0x7E,
        0x1B, 0x5B, 0x31, 0x30, 0x3B, 0x31, 0x48, 0x7E,
        0x1B, 0x5B, 0x31, 0x31, 0x3B, 0x31, 0x48, 0x7E,
        0x1B, 0x5B, 0x31, 0x32, 0x3B, 0x31, 0x48, 0x7E,
        0x1B, 0x5B, 0x31, 0x33, 0x3B, 0x31, 0x48, 0x7E,
        0x1B, 0x5B, 0x31, 0x34, 0x3B, 0x31, 0x48, 0x7E,
        0x1B, 0x5B, 0x31, 0x35, 0x3B, 0x31, 0x48, 0x7E,
        0x1B, 0x5B, 0x31, 0x36, 0x3B, 0x31, 0x48, 0x7E,
        0x1B, 0x5B, 0x31, 0x37, 0x3B, 0x31, 0x48, 0x7E,
        0x1B, 0x5B, 0x31, 0x38, 0x3B, 0x31, 0x48, 0x7E,
        0x1B, 0x5B, 0x31, 0x39, 0x3B, 0x31, 0x48, 0x7E,
        0x1B, 0x5B, 0x32, 0x30, 0x3B, 0x31, 0x48, 0x7E,
        0x1B, 0x5B, 0x32, 0x31, 0x3B, 0x31, 0x48, 0x7E,
        0x1B, 0x5B, 0x32, 0x32, 0x3B, 0x31, 0x48, 0x7E,
        0x1B, 0x5B, 0x32, 0x33, 0x3B, 0x31, 0x48, 0x7E,
#endif

#if 1
        0x1B, 0x5B, 0x31, 0x3B, 0x31, 0x48,
        0x1B, 0x5B, 0x32, 0x34, 0x3B, 0x31, 0x48,
        0x1B, 0x5B, 0x4B, 0x2D, 0x20, 0x65, 0x65, 0x20, 0x5B, 0x4D, 0x6F, 0x64, 0x69, 0x66, 0x69, 0x65, 0x64, 0x5D, 0x20, 0x31, 0x2F, 0x31, 0x20, 0x31, 0x30, 0x30, 0x25,
        0x1B, 0x5B, 0x31, 0x3B, 0x31, 0x48,
#endif
        0x00
    };

    QByteArray data = ch;

    emit outData(data);
}

void Dialog::on_test3_clicked()
{
    char ch[] =
    {
        0x0D, 0x0A,
        0x1B, 0x5B, 0x31, 0x3B, 0x31, 0x48,
        0x1B, 0x5B, 0x30, 0x4A,
        0x0D,
        0x70, 0x72, 0x6F, 0x63, 0x20, 0x20, 0x20, 0x20, 0x20,
        0x1B, 0x5B, 0x31, 0x3B, 0x31, 0x48,
        0x00
    };

    QByteArray data = ch;

    emit outData(data);
}

void Dialog::on_cn_clicked()
{
    QByteArray data = "cn中文\n";

    emit outData(data);
}

void Dialog::on_add_clicked()
{
    QByteArray data = "\ncnaaddddddddd";

    emit outData(data);
}

void Dialog::on_pushButton_clicked()
{
    char ch[] =
    {
        0x1B, 0x5B, 0x31, 0x3B, 0x33, 0x34, 0x6D, 0x73, 0x68, 0x61, 0x72, 0x65,
        0x1B, 0x5B, 0x30, 0x6D, 0x0D, 0x0A,
        0x1B, 0x5B, 0x31, 0x3B, 0x33, 0x34, 0x6D, 0x77, 0x77, 0x77,
        0x1B, 0x5B, 0x30, 0x6D, 0x0D, 0x0A,
        0x5B, 0x72, 0x6F, 0x6F, 0x74, 0x40, 0x51, 0x54, 0x3A, 0x2F, 0x75, 0x73, 0x72, 0x5D, 0x23, 0x20, 0x0D, 0x0A,
        0x00
    };

    QByteArray data = ch;

    emit outData(data);
}
