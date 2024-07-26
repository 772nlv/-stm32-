/********************************************************************************
** Form generated from reading UI file 'tostm32window.ui'
**
** Created by: Qt User Interface Compiler version 5.9.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TOSTM32WINDOW_H
#define UI_TOSTM32WINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QTableView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_toStm32Window
{
public:
    QWidget *centralwidget;
    QPushButton *pushButton;
    QPushButton *LED_Ctr;
    QTableView *tableView;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QComboBox *comboBox;
    QLineEdit *lineEdit_5;
    QSplitter *splitter_2;
    QLineEdit *lineEdit;
    QLineEdit *lineEdit_2;
    QLineEdit *lineEdit_4;
    QLineEdit *lineEdit_3;
    QSplitter *splitter_3;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;

    void setupUi(QMainWindow *toStm32Window)
    {
        if (toStm32Window->objectName().isEmpty())
            toStm32Window->setObjectName(QStringLiteral("toStm32Window"));
        toStm32Window->resize(871, 665);
        centralwidget = new QWidget(toStm32Window);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(10, 220, 161, 61));
        LED_Ctr = new QPushButton(centralwidget);
        LED_Ctr->setObjectName(QStringLiteral("LED_Ctr"));
        LED_Ctr->setGeometry(QRect(10, 310, 161, 51));
        tableView = new QTableView(centralwidget);
        tableView->setObjectName(QStringLiteral("tableView"));
        tableView->setGeometry(QRect(190, 210, 671, 351));
        pushButton_2 = new QPushButton(centralwidget);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(10, 380, 161, 51));
        pushButton_3 = new QPushButton(centralwidget);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));
        pushButton_3->setGeometry(QRect(10, 440, 161, 51));
        comboBox = new QComboBox(centralwidget);
        comboBox->setObjectName(QStringLiteral("comboBox"));
        comboBox->setGeometry(QRect(10, 510, 161, 51));
        lineEdit_5 = new QLineEdit(centralwidget);
        lineEdit_5->setObjectName(QStringLiteral("lineEdit_5"));
        lineEdit_5->setGeometry(QRect(20, 580, 831, 71));
        lineEdit_5->setStyleSheet(QStringLiteral("font: 75 18pt \"Arial\";"));
        splitter_2 = new QSplitter(centralwidget);
        splitter_2->setObjectName(QStringLiteral("splitter_2"));
        splitter_2->setGeometry(QRect(210, 140, 641, 61));
        splitter_2->setOrientation(Qt::Horizontal);
        lineEdit = new QLineEdit(splitter_2);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        splitter_2->addWidget(lineEdit);
        lineEdit_2 = new QLineEdit(splitter_2);
        lineEdit_2->setObjectName(QStringLiteral("lineEdit_2"));
        splitter_2->addWidget(lineEdit_2);
        lineEdit_4 = new QLineEdit(splitter_2);
        lineEdit_4->setObjectName(QStringLiteral("lineEdit_4"));
        splitter_2->addWidget(lineEdit_4);
        lineEdit_3 = new QLineEdit(splitter_2);
        lineEdit_3->setObjectName(QStringLiteral("lineEdit_3"));
        splitter_2->addWidget(lineEdit_3);
        splitter_3 = new QSplitter(centralwidget);
        splitter_3->setObjectName(QStringLiteral("splitter_3"));
        splitter_3->setGeometry(QRect(210, 120, 641, 20));
        splitter_3->setOrientation(Qt::Horizontal);
        label = new QLabel(splitter_3);
        label->setObjectName(QStringLiteral("label"));
        splitter_3->addWidget(label);
        label_2 = new QLabel(splitter_3);
        label_2->setObjectName(QStringLiteral("label_2"));
        splitter_3->addWidget(label_2);
        label_3 = new QLabel(splitter_3);
        label_3->setObjectName(QStringLiteral("label_3"));
        splitter_3->addWidget(label_3);
        label_4 = new QLabel(splitter_3);
        label_4->setObjectName(QStringLiteral("label_4"));
        splitter_3->addWidget(label_4);
        label_5 = new QLabel(centralwidget);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(20, 10, 191, 191));
        label_5->setStyleSheet(QStringLiteral("image: url(:/png/AUTO_Icon.png);"));
        label_6 = new QLabel(centralwidget);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(240, 30, 571, 61));
        label_6->setStyleSheet(QStringLiteral("font: 75 italic 36pt \"Arial\";"));
        toStm32Window->setCentralWidget(centralwidget);

        retranslateUi(toStm32Window);

        QMetaObject::connectSlotsByName(toStm32Window);
    } // setupUi

    void retranslateUi(QMainWindow *toStm32Window)
    {
        toStm32Window->setWindowTitle(QApplication::translate("toStm32Window", "MainWindow", Q_NULLPTR));
        pushButton->setText(QApplication::translate("toStm32Window", "OPEN", Q_NULLPTR));
        LED_Ctr->setText(QApplication::translate("toStm32Window", "LED1_ON", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("toStm32Window", "LED2_ON", Q_NULLPTR));
        pushButton_3->setText(QApplication::translate("toStm32Window", "BEEP_ON", Q_NULLPTR));
        comboBox->clear();
        comboBox->insertItems(0, QStringList()
         << QApplication::translate("toStm32Window", "     FAN_ON", Q_NULLPTR)
         << QApplication::translate("toStm32Window", "     FAN_OFF", Q_NULLPTR)
         << QApplication::translate("toStm32Window", "     FAN LOW", Q_NULLPTR)
         << QApplication::translate("toStm32Window", "     FAN MIDDLE", Q_NULLPTR)
         << QApplication::translate("toStm32Window", "     FAN FAST", Q_NULLPTR)
        );
        label->setText(QApplication::translate("toStm32Window", "\345\275\223\345\211\215\346\270\251\345\272\246", Q_NULLPTR));
        label_2->setText(QApplication::translate("toStm32Window", "\345\275\223\345\211\215\346\271\277\345\272\246", Q_NULLPTR));
        label_3->setText(QApplication::translate("toStm32Window", "\345\275\223\345\211\215\345\205\211\347\205\247", Q_NULLPTR));
        label_4->setText(QApplication::translate("toStm32Window", "\345\275\223\345\211\215\347\224\265\344\275\215", Q_NULLPTR));
        label_5->setText(QString());
        label_6->setText(QApplication::translate("toStm32Window", "Welcome Home", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class toStm32Window: public Ui_toStm32Window {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TOSTM32WINDOW_H
