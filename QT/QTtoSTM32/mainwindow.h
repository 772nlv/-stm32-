#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "sqliteoperator.h"
#include "regiwindow.h"
#include "tostm32window.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::MainWindow *ui;
    //数据库
    SqliteOperator *pSql;
    //注册界面
    RegiWindow *pRegiWindow;
    toStm32Window *pStm32Window;
};
#endif // MAINWINDOW_H
