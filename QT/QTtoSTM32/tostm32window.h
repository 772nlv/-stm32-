#ifndef TOSTM32WINDOW_H
#define TOSTM32WINDOW_H

#include <QMainWindow>
#include <QtSerialPort/QSerialPort>         // 提供访问串口的功能
#include <QtSerialPort/QSerialPortInfo>   // 提供系统中存在的串口信息
#include <QStandardItemModel>
#include "sqliteoperator.h"
namespace Ui {
class toStm32Window;
}

class toStm32Window : public QMainWindow
{
    Q_OBJECT

public:
    explicit toStm32Window(QWidget *parent = nullptr);
    ~toStm32Window();
    void setComebackWindow(QWidget * pWindow);
    QString hexStrToStr(const QString &hexStr);
private slots:
    void on_pushButton_clicked();

    void serial_readyRead();

    void on_LED_Ctr_clicked();


    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_comboBox_activated(const QString &arg1);

private:
    Ui::toStm32Window *ui;
    //指向返回窗口的指针
    QWidget *pComebackWindow;
    //串口助手
    QSerialPort *serial;
    //数据模型 导入tableview
    QStandardItemModel *m_pModel;
    //读取数据的次数
    int count;
    //读取数据收集
    QVector<QString> databuff;
    //数据库
    SqliteOperator *pSql;
};

#endif // TOSTM32WINDOW_H
