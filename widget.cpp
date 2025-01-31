#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    _socket = new QUdpSocket(this);
    _socket->bind(4000);
    connect(_socket,SIGNAL(readyRead()),this,SLOT(readData()));
}

Widget::~Widget()
{
    delete ui;
}

void Widget::readData()
{
    if(!_socket->hasPendingDatagrams())
        return;
    int size = _socket->pendingDatagramSize();
    char *buffer = new char[size];
    _socket->readDatagram(buffer,size);
    QString Str(buffer);
    ui->Txt_Recive->appendPlainText(Str);
}
