/********************************************************************************
** Form generated from reading UI file 'clipboardmemory.ui'
**
** Created by: Qt User Interface Compiler version 6.5.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CLIPBOARDMEMORY_H
#define UI_CLIPBOARDMEMORY_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ClipBoardMemory
{
public:
    QWidget *centralwidget;
    QDialogButtonBox *buttonBox;
    QPushButton *Previous;
    QPushButton *Next;
    QTextBrowser *Text;
    QPushButton *Copy;
    QPushButton *Clear;
    QPushButton *Stop;
    QPushButton *Start;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *ClipBoardMemory)
    {
        if (ClipBoardMemory->objectName().isEmpty())
            ClipBoardMemory->setObjectName("ClipBoardMemory");
        ClipBoardMemory->resize(404, 315);
        centralwidget = new QWidget(ClipBoardMemory);
        centralwidget->setObjectName("centralwidget");
        buttonBox = new QDialogButtonBox(centralwidget);
        buttonBox->setObjectName("buttonBox");
        buttonBox->setGeometry(QRect(240, 250, 166, 24));
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        Previous = new QPushButton(centralwidget);
        Previous->setObjectName("Previous");
        Previous->setGeometry(QRect(0, 10, 80, 24));
        Previous->setMouseTracking(false);
        Previous->setTabletTracking(false);
        Next = new QPushButton(centralwidget);
        Next->setObjectName("Next");
        Next->setGeometry(QRect(0, 50, 80, 24));
        Next->setMouseTracking(false);
        Next->setTabletTracking(false);
        Text = new QTextBrowser(centralwidget);
        Text->setObjectName("Text");
        Text->setGeometry(QRect(95, 0, 311, 241));
        Copy = new QPushButton(centralwidget);
        Copy->setObjectName("Copy");
        Copy->setGeometry(QRect(0, 90, 80, 24));
        Copy->setMouseTracking(false);
        Copy->setTabletTracking(false);
        Clear = new QPushButton(centralwidget);
        Clear->setObjectName("Clear");
        Clear->setGeometry(QRect(0, 130, 80, 24));
        Clear->setMouseTracking(false);
        Clear->setTabletTracking(false);
        Stop = new QPushButton(centralwidget);
        Stop->setObjectName("Stop");
        Stop->setGeometry(QRect(0, 210, 80, 24));
        Stop->setMouseTracking(false);
        Stop->setTabletTracking(false);
        Start = new QPushButton(centralwidget);
        Start->setObjectName("Start");
        Start->setGeometry(QRect(0, 170, 80, 24));
        Start->setMouseTracking(false);
        Start->setTabletTracking(false);
        ClipBoardMemory->setCentralWidget(centralwidget);
        menubar = new QMenuBar(ClipBoardMemory);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 404, 21));
        ClipBoardMemory->setMenuBar(menubar);
        statusbar = new QStatusBar(ClipBoardMemory);
        statusbar->setObjectName("statusbar");
        ClipBoardMemory->setStatusBar(statusbar);

        retranslateUi(ClipBoardMemory);

        QMetaObject::connectSlotsByName(ClipBoardMemory);
    } // setupUi

    void retranslateUi(QMainWindow *ClipBoardMemory)
    {
        ClipBoardMemory->setWindowTitle(QCoreApplication::translate("ClipBoardMemory", "ClipBoardMemory", nullptr));
        Previous->setText(QCoreApplication::translate("ClipBoardMemory", "Previous", nullptr));
        Next->setText(QCoreApplication::translate("ClipBoardMemory", "Next", nullptr));
        Copy->setText(QCoreApplication::translate("ClipBoardMemory", "Copy", nullptr));
        Clear->setText(QCoreApplication::translate("ClipBoardMemory", "Clear", nullptr));
        Stop->setText(QCoreApplication::translate("ClipBoardMemory", "Stop", nullptr));
        Start->setText(QCoreApplication::translate("ClipBoardMemory", "Start", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ClipBoardMemory: public Ui_ClipBoardMemory {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CLIPBOARDMEMORY_H
