/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QComboBox *comboBoxRegione;
    QTableWidget *tableRegione;
    QLabel *labelRegione;
    QWidget *widget_chart_maschi;
    QWidget *widget;
    QMenuBar *menuBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1122, 819);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        comboBoxRegione = new QComboBox(centralWidget);
        comboBoxRegione->setObjectName(QString::fromUtf8("comboBoxRegione"));
        comboBoxRegione->setGeometry(QRect(840, 30, 121, 22));
        comboBoxRegione->setEditable(false);
        tableRegione = new QTableWidget(centralWidget);
        if (tableRegione->columnCount() < 3)
            tableRegione->setColumnCount(3);
        if (tableRegione->rowCount() < 8)
            tableRegione->setRowCount(8);
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        font.setStrikeOut(false);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        __qtablewidgetitem->setTextAlignment(Qt::AlignCenter);
        __qtablewidgetitem->setFont(font);
        tableRegione->setItem(0, 0, __qtablewidgetitem);
        QFont font1;
        font1.setBold(true);
        font1.setWeight(75);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        __qtablewidgetitem1->setTextAlignment(Qt::AlignCenter);
        __qtablewidgetitem1->setFont(font1);
        tableRegione->setItem(0, 1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        __qtablewidgetitem2->setTextAlignment(Qt::AlignCenter);
        __qtablewidgetitem2->setFont(font1);
        tableRegione->setItem(0, 2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableRegione->setItem(7, 0, __qtablewidgetitem3);
        tableRegione->setObjectName(QString::fromUtf8("tableRegione"));
        tableRegione->setGeometry(QRect(20, 70, 301, 691));
        tableRegione->setLayoutDirection(Qt::LeftToRight);
        tableRegione->setAutoFillBackground(false);
        tableRegione->setFrameShape(QFrame::NoFrame);
        tableRegione->setFrameShadow(QFrame::Sunken);
        tableRegione->setLineWidth(1);
        tableRegione->setShowGrid(true);
        tableRegione->setWordWrap(true);
        tableRegione->setCornerButtonEnabled(false);
        tableRegione->setRowCount(8);
        tableRegione->setColumnCount(3);
        tableRegione->horizontalHeader()->setVisible(false);
        tableRegione->horizontalHeader()->setDefaultSectionSize(100);
        tableRegione->horizontalHeader()->setHighlightSections(true);
        tableRegione->horizontalHeader()->setMinimumSectionSize(39);
        tableRegione->verticalHeader()->setVisible(false);
        tableRegione->verticalHeader()->setHighlightSections(true);
        labelRegione = new QLabel(centralWidget);
        labelRegione->setObjectName(QString::fromUtf8("labelRegione"));
        labelRegione->setGeometry(QRect(100, 30, 161, 31));
        QFont font2;
        font2.setPointSize(16);
        font2.setBold(false);
        font2.setWeight(50);
        labelRegione->setFont(font2);
        widget_chart_maschi = new QWidget(centralWidget);
        widget_chart_maschi->setObjectName(QString::fromUtf8("widget_chart_maschi"));
        widget_chart_maschi->setGeometry(QRect(390, 80, 711, 351));
        widget = new QWidget(centralWidget);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(390, 440, 711, 321));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1122, 21));
        MainWindow->setMenuBar(menuBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        comboBoxRegione->setCurrentText(QString());

        const bool __sortingEnabled = tableRegione->isSortingEnabled();
        tableRegione->setSortingEnabled(false);
        QTableWidgetItem *___qtablewidgetitem = tableRegione->item(0, 0);
        ___qtablewidgetitem->setText(QApplication::translate("MainWindow", "Et\303\240", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableRegione->item(0, 1);
        ___qtablewidgetitem1->setText(QApplication::translate("MainWindow", "Maschi", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableRegione->item(0, 2);
        ___qtablewidgetitem2->setText(QApplication::translate("MainWindow", "Femmine", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableRegione->item(7, 0);
        ___qtablewidgetitem3->setText(QApplication::translate("MainWindow", "Totale", nullptr));
        tableRegione->setSortingEnabled(__sortingEnabled);

        labelRegione->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
