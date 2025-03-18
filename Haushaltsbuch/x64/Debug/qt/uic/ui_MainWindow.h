/********************************************************************************
** Form generated from reading UI file 'MainWindow.ui'
**
** Created by: Qt User Interface Compiler version 6.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionExportieren;
    QAction *actionImportieren;
    QAction *actionBeenden;
    QAction *actionEinstellungen;
    QAction *actionUeber;
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QTabWidget *tabWidget;
    QMenuBar *menubar;
    QMenu *menuDatei;
    QMenu *menuBearbeiten;
    QMenu *menuHilfe;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 600);
        actionExportieren = new QAction(MainWindow);
        actionExportieren->setObjectName("actionExportieren");
        actionImportieren = new QAction(MainWindow);
        actionImportieren->setObjectName("actionImportieren");
        actionBeenden = new QAction(MainWindow);
        actionBeenden->setObjectName("actionBeenden");
        actionEinstellungen = new QAction(MainWindow);
        actionEinstellungen->setObjectName("actionEinstellungen");
        actionUeber = new QAction(MainWindow);
        actionUeber->setObjectName("actionUeber");
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName("verticalLayout");
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName("tabWidget");

        verticalLayout->addWidget(tabWidget);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 22));
        menuDatei = new QMenu(menubar);
        menuDatei->setObjectName("menuDatei");
        menuBearbeiten = new QMenu(menubar);
        menuBearbeiten->setObjectName("menuBearbeiten");
        menuHilfe = new QMenu(menubar);
        menuHilfe->setObjectName("menuHilfe");
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuDatei->menuAction());
        menubar->addAction(menuBearbeiten->menuAction());
        menubar->addAction(menuHilfe->menuAction());
        menuDatei->addAction(actionExportieren);
        menuDatei->addAction(actionImportieren);
        menuDatei->addSeparator();
        menuDatei->addAction(actionBeenden);
        menuBearbeiten->addAction(actionEinstellungen);
        menuHilfe->addAction(actionUeber);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Haushaltsbuch", nullptr));
        actionExportieren->setText(QCoreApplication::translate("MainWindow", "Exportieren...", nullptr));
        actionImportieren->setText(QCoreApplication::translate("MainWindow", "Importieren...", nullptr));
        actionBeenden->setText(QCoreApplication::translate("MainWindow", "Beenden", nullptr));
        actionEinstellungen->setText(QCoreApplication::translate("MainWindow", "Einstellungen...", nullptr));
        actionUeber->setText(QCoreApplication::translate("MainWindow", "Uber...", nullptr));
        menuDatei->setTitle(QCoreApplication::translate("MainWindow", "Datei", nullptr));
        menuBearbeiten->setTitle(QCoreApplication::translate("MainWindow", "Bearbeiten", nullptr));
        menuHilfe->setTitle(QCoreApplication::translate("MainWindow", "Hilfe", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
