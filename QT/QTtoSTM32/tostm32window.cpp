//串口链接32
//配置串口
//发送命令控制


#include "tostm32window.h"
#include "ui_tostm32window.h"
#include <QDebug>
#include <QDateTime>
toStm32Window::toStm32Window(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::toStm32Window)
{
    ui->setupUi(this);
    count = 0;
    serial = new QSerialPort;
    //读函数的信号槽
    QObject::connect(serial, &QSerialPort::readyRead, this, &toStm32Window::serial_readyRead);
    m_pModel = new QStandardItemModel(ui->tableView);//实例化模型，并且指定模型依赖的控件
    //将数据模型设置到表对象上
    ui->tableView->setModel(m_pModel);
    //tableview 歌单头部
    QStringList fonts;
    fonts << "温度" << "湿度" << "光照" << "电位"<<"时间";
    m_pModel->setHorizontalHeaderLabels(fonts);

    //数据库
    pSql = new SqliteOperator;
    pSql->open_db();
    pSql->creat_table();
    // 设置对齐方式为居中对齐
    ui->label->setAlignment(Qt::AlignCenter);
    ui->label_2->setAlignment(Qt::AlignCenter);
    ui->label_3->setAlignment(Qt::AlignCenter);
    ui->label_4->setAlignment(Qt::AlignCenter);
    ui->lineEdit->setAlignment(Qt::AlignCenter);
    ui->lineEdit_2->setAlignment(Qt::AlignCenter);
    ui->lineEdit_3->setAlignment(Qt::AlignCenter);
    ui->lineEdit_4->setAlignment(Qt::AlignCenter);
    ui->lineEdit_5->setAlignment(Qt::AlignCenter);
}
//进入下一级窗口时，保存本窗口为上一级窗口
void toStm32Window::setComebackWindow(QWidget *pWindow)
{
    this->pComebackWindow = pWindow;
}



toStm32Window::~toStm32Window()
{
    delete ui;
}

void toStm32Window::on_pushButton_clicked()
{
    //是OPEN时，代表没有打开串口
    if(ui->pushButton->text() == QString("OPEN"))
    {
        // 获取计算机中有效的端口号，然后将端口号的名称给端口选择控件
        //QSerialPortInfo::availablePorts()的返回值为QList<QSerialPortInfo> 每一个可用端口组成的容器
        foreach(const QSerialPortInfo &info,QSerialPortInfo::availablePorts())
        {
            serial->setPort(info);
            if(serial->open(QIODevice::ReadWrite))      // 以读写方式打开串口
            {                            // 在对象中设置串口
                qDebug() << "串口打开成功";
                qDebug()<<"serialPortName:"<<info.portName();
                serial->close();                        // 关闭
            }
            else
            {
                qDebug() << "串口打开失败，请重试";
            }
         }
        // 参数配置，波特率V
        serial->setBaudRate(QSerialPort::Baud115200);
        // 校验位，校验默认选择无
        serial->setParity(QSerialPort::NoParity);
        // 数据位，数据位默认选择8位
        serial->setDataBits(QSerialPort::Data8);
        // 停止位，停止位默认选择1位
        serial->setStopBits(QSerialPort::OneStop);
        // 控制流，默认选择无
        serial->setFlowControl(QSerialPort::NoFlowControl);

        //改变按钮上的文本
         ui->pushButton->setText("CLOSE");
         qDebug()<<serial->portName();

         bool isSerialOpen = serial->open(QIODevice::ReadWrite);
         serial->setDataTerminalReady(true);
         serial->setReadBufferSize(3);
         if (!isSerialOpen) {
         qDebug()<< QString("Failed to open serial port:")  << serial->errorString();
         serial->clearError();

         }
         else
         {
          qDebug()<< QString("The serial port is open: ") ;
         }
         ui->lineEdit_5->setText("连接成功,并采集数据");
    }
    else
    {
        ui->lineEdit_5->setText("断开连接");
        ui->pushButton->setText("OPEN");
        serial->close();
    }

}
QString toStm32Window::hexStrToStr(const QString &hexStr)
{
    QString s1 = hexStr;
    s1.remove(QRegExp("\\s"));  // 去除空格
    QByteArray ba = QByteArray::fromHex(s1.toLocal8Bit());
    return QString::fromLocal8Bit(ba);
}


void toStm32Window::serial_readyRead()
{
    if(count == 10)
    {
        QString temp = databuff[0]+databuff[1]+"℃";
        QString humi = databuff[2]+databuff[3]+"%";
        QString light = databuff[7] + databuff[8];
        QString poten = databuff[4]+databuff[5]+databuff[6]+"V";
        qDebug()<<temp<<" "<<humi<<" "<<light<<" "<<poten;
        // 获取系统当前时间
        QDateTime currentDateTime = QDateTime::currentDateTime();
        int temp_value = databuff[0].toInt();
        qDebug()<<temp_value;
        // 输出当前时间
        QString currentTime = currentDateTime.toString("yyyy-MM-dd hh:mm:ss");
        qDebug() << "当前时间：" << currentTime;

        //把表单内容设置为数据信息
        m_pModel->appendRow(QList<QStandardItem *>()<< new QStandardItem(temp)<< new QStandardItem(humi)
        << new QStandardItem(light)<< new QStandardItem(poten)<< new QStandardItem(currentTime));
        ui->lineEdit->setText(temp);
        ui->lineEdit_2->setText(humi);
        ui->lineEdit_3->setText(poten);
        ui->lineEdit_4->setText(light);

        //把数据存入数据库
        QString sql = QString("INSERT INTO DATA VALUES('%1','%2','%3','%4','%5')")
                .arg(temp).arg(humi).arg(light).arg(poten).arg(currentTime);
         pSql->normalFunc(sql);
        count = 0;
        QVector<QString>().swap(databuff);
    }
    //从接收缓冲区中读取数据
    QByteArray buffer = serial->readAll();
    QString data = QString(buffer);
    QStringList parts = data.split("  ", QString::SkipEmptyParts); // 跳过空字符串
    for(int i = 0;i<parts.size();i++)
    {
        databuff.append(parts.at(i));
        qDebug()<<parts.at(i);
    }
    count++;
}

//开灯LED1
void toStm32Window::on_LED_Ctr_clicked()
{
    if(ui->LED_Ctr->text() == QString("LED1_ON"))
    {
        QByteArray data ="open led1";
        serial->write(data);
        qDebug() <<serial ;
        ui->LED_Ctr->setText("LED1_OFF");
        ui->lineEdit_5->setText("open LED1 success!");
    }
    else
    {
        QByteArray data ="close led1";
        serial->write(data);
        qDebug() <<serial ;
        ui->LED_Ctr->setText("LED1_ON");
        ui->lineEdit_5->setText("close LED1 success!");
    }

}


//LED2
void toStm32Window::on_pushButton_2_clicked()
{
    if(ui->pushButton_2->text() == QString("LED2_ON"))
    {
        QByteArray data ="open led2";
        serial->write(data);
        qDebug() <<serial ;
        ui->pushButton_2->setText("LED2_OFF");
        ui->lineEdit_5->setText("open LED2 success!");
    }
    else
    {
        QByteArray data ="close led2";
        serial->write(data);
        qDebug() <<serial ;
        ui->pushButton_2->setText("LED2_ON");
    ui->lineEdit_5->setText("close LED2 success!");
    }
}

//BEEP
void toStm32Window::on_pushButton_3_clicked()
{
    if(ui->pushButton_3->text() == QString("BEEP_ON"))
    {
        QByteArray data ="open beep";
        serial->write(data);
        qDebug() <<serial ;
        ui->pushButton_3->setText("BEEP_OFF");
        ui->lineEdit_5->setText("open beep success!");
    }
    else
    {
        QByteArray data ="close beep";
        serial->write(data);
        qDebug() <<serial ;
        ui->pushButton_3->setText("BEEP_ON");
        ui->lineEdit_5->setText("close beep success!");
    }
}

void toStm32Window::on_comboBox_activated(const QString &arg1)
{
    if(arg1 == "     FAN_ON")
    {
        QByteArray data ="open fan";
        serial->write(data);
        qDebug() <<serial ;
        ui->lineEdit_5->setText("open fan success!");
    }
    if(arg1 == "     FAN_OFF")
    {
        QByteArray data ="close fan";
        serial->write(data);
        qDebug() <<serial ;
        ui->lineEdit_5->setText("close fan success!");
    }
    if(arg1 == "     FAN LOW")
    {
        QByteArray data ="low fan";
        serial->write(data);
        qDebug() <<serial ;
        ui->lineEdit_5->setText("lowed fan success!");
    }
    if(arg1 == "     FAN MIDDLE")
    {
        QByteArray data ="middle fan";
        serial->write(data);
        qDebug() <<serial ;
        ui->lineEdit_5->setText("middled fan success!");
    }
    if(arg1 == "     FAN FAST")
    {
        QByteArray data ="fast fan";
        serial->write(data);
        qDebug() <<serial ;
        ui->lineEdit_5->setText("fasted fan success!");
    }
}
