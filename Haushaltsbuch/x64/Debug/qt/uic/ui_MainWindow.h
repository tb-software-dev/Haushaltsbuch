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
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableView>
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
    QWidget *transactionsTab;
    QVBoxLayout *verticalLayout_2;
    QGroupBox *dateRangeGroup;
    QHBoxLayout *horizontalLayout;
    QLabel *startDateLabel;
    QDateEdit *startDateEdit;
    QLabel *endDateLabel;
    QDateEdit *endDateEdit;
    QPushButton *filterButton;
    QSpacerItem *horizontalSpacer;
    QTableView *transactionsTable;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *addTransactionButton;
    QPushButton *editTransactionButton;
    QPushButton *deleteTransactionButton;
    QSpacerItem *horizontalSpacer_2;
    QWidget *budgetTab;
    QVBoxLayout *verticalLayout_3;
    QTableView *budgetTable;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *addBudgetButton;
    QPushButton *editBudgetButton;
    QSpacerItem *horizontalSpacer_3;
    QWidget *reportsTab;
    QVBoxLayout *verticalLayout_4;
    QGroupBox *reportConfigGroup;
    QHBoxLayout *horizontalLayout_4;
    QLabel *reportTypeLabel;
    QComboBox *reportTypeComboBox;
    QLabel *reportStartDateLabel;
    QDateEdit *reportStartDateEdit;
    QLabel *reportEndDateLabel;
    QDateEdit *reportEndDateEdit;
    QPushButton *generateReportButton;
    QSpacerItem *horizontalSpacer_4;
    QScrollArea *reportScrollArea;
    QWidget *reportContainer;
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
        transactionsTab = new QWidget();
        transactionsTab->setObjectName("transactionsTab");
        verticalLayout_2 = new QVBoxLayout(transactionsTab);
        verticalLayout_2->setObjectName("verticalLayout_2");
        dateRangeGroup = new QGroupBox(transactionsTab);
        dateRangeGroup->setObjectName("dateRangeGroup");
        horizontalLayout = new QHBoxLayout(dateRangeGroup);
        horizontalLayout->setObjectName("horizontalLayout");
        startDateLabel = new QLabel(dateRangeGroup);
        startDateLabel->setObjectName("startDateLabel");

        horizontalLayout->addWidget(startDateLabel);

        startDateEdit = new QDateEdit(dateRangeGroup);
        startDateEdit->setObjectName("startDateEdit");
        startDateEdit->setCalenderPopup(true);

        horizontalLayout->addWidget(startDateEdit);

        endDateLabel = new QLabel(dateRangeGroup);
        endDateLabel->setObjectName("endDateLabel");

        horizontalLayout->addWidget(endDateLabel);

        endDateEdit = new QDateEdit(dateRangeGroup);
        endDateEdit->setObjectName("endDateEdit");
        endDateEdit->setCalendarPopup(true);

        horizontalLayout->addWidget(endDateEdit);

        filterButton = new QPushButton(dateRangeGroup);
        filterButton->setObjectName("filterButton");

        horizontalLayout->addWidget(filterButton);

        horizontalSpacer = new QSpacerItem(0, 0, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        verticalLayout_2->addWidget(dateRangeGroup);

        transactionsTable = new QTableView(transactionsTab);
        transactionsTable->setObjectName("transactionsTable");
        transactionsTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
        transactionsTable->setSelectionBehavior(QAbstractItemView::SelectRows);
        transactionsTable->setSortingEnabled(true);
        transactionsTable->verticalHeader()->setVisible(false);

        verticalLayout_2->addWidget(transactionsTable);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        addTransactionButton = new QPushButton(transactionsTab);
        addTransactionButton->setObjectName("addTransactionButton");

        horizontalLayout_2->addWidget(addTransactionButton);

        editTransactionButton = new QPushButton(transactionsTab);
        editTransactionButton->setObjectName("editTransactionButton");

        horizontalLayout_2->addWidget(editTransactionButton);

        deleteTransactionButton = new QPushButton(transactionsTab);
        deleteTransactionButton->setObjectName("deleteTransactionButton");

        horizontalLayout_2->addWidget(deleteTransactionButton);

        horizontalSpacer_2 = new QSpacerItem(0, 0, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);


        verticalLayout_2->addLayout(horizontalLayout_2);

        tabWidget->addTab(transactionsTab, QString());
        budgetTab = new QWidget();
        budgetTab->setObjectName("budgetTab");
        verticalLayout_3 = new QVBoxLayout(budgetTab);
        verticalLayout_3->setObjectName("verticalLayout_3");
        budgetTable = new QTableView(budgetTab);
        budgetTable->setObjectName("budgetTable");
        budgetTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
        budgetTable->setSelectionBehavior(QAbstractItemView::SelectRows);
        budgetTable->verticalHeader()->setVisible(false);

        verticalLayout_3->addWidget(budgetTable);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        addBudgetButton = new QPushButton(budgetTab);
        addBudgetButton->setObjectName("addBudgetButton");

        horizontalLayout_3->addWidget(addBudgetButton);

        editBudgetButton = new QPushButton(budgetTab);
        editBudgetButton->setObjectName("editBudgetButton");

        horizontalLayout_3->addWidget(editBudgetButton);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_3);


        verticalLayout_3->addLayout(horizontalLayout_3);

        tabWidget->addTab(budgetTab, QString());
        reportsTab = new QWidget();
        reportsTab->setObjectName("reportsTab");
        verticalLayout_4 = new QVBoxLayout(reportsTab);
        verticalLayout_4->setObjectName("verticalLayout_4");
        reportConfigGroup = new QGroupBox(reportsTab);
        reportConfigGroup->setObjectName("reportConfigGroup");
        horizontalLayout_4 = new QHBoxLayout(reportConfigGroup);
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        reportTypeLabel = new QLabel(reportConfigGroup);
        reportTypeLabel->setObjectName("reportTypeLabel");

        horizontalLayout_4->addWidget(reportTypeLabel);

        reportTypeComboBox = new QComboBox(reportConfigGroup);
        reportTypeComboBox->addItem(QString());
        reportTypeComboBox->addItem(QString());
        reportTypeComboBox->addItem(QString());
        reportTypeComboBox->setObjectName("reportTypeComboBox");

        horizontalLayout_4->addWidget(reportTypeComboBox);

        reportStartDateLabel = new QLabel(reportConfigGroup);
        reportStartDateLabel->setObjectName("reportStartDateLabel");

        horizontalLayout_4->addWidget(reportStartDateLabel);

        reportStartDateEdit = new QDateEdit(reportConfigGroup);
        reportStartDateEdit->setObjectName("reportStartDateEdit");
        reportStartDateEdit->setCalendarPopup(true);

        horizontalLayout_4->addWidget(reportStartDateEdit);

        reportEndDateLabel = new QLabel(reportConfigGroup);
        reportEndDateLabel->setObjectName("reportEndDateLabel");

        horizontalLayout_4->addWidget(reportEndDateLabel);

        reportEndDateEdit = new QDateEdit(reportConfigGroup);
        reportEndDateEdit->setObjectName("reportEndDateEdit");
        reportEndDateEdit->setCalendarPopup(true);

        horizontalLayout_4->addWidget(reportEndDateEdit);

        generateReportButton = new QPushButton(reportConfigGroup);
        generateReportButton->setObjectName("generateReportButton");

        horizontalLayout_4->addWidget(generateReportButton);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_4);


        verticalLayout_4->addWidget(reportConfigGroup);

        reportScrollArea = new QScrollArea(reportsTab);
        reportScrollArea->setObjectName("reportScrollArea");
        reportScrollArea->setWidgetResizable(true);
        reportContainer = new QWidget();
        reportContainer->setObjectName("reportContainer");
        reportContainer->setGeometry(QRect(0, 0, 744, 371));
        reportScrollArea->setWidget(reportContainer);

        verticalLayout_4->addWidget(reportScrollArea);

        tabWidget->addTab(reportsTab, QString());

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
        actionUeber->setText(QCoreApplication::translate("MainWindow", "\303\234ber...", nullptr));
        dateRangeGroup->setTitle(QCoreApplication::translate("MainWindow", "Zeitraum", nullptr));
        startDateLabel->setText(QCoreApplication::translate("MainWindow", "Von:", nullptr));
        endDateLabel->setText(QCoreApplication::translate("MainWindow", "Bis:", nullptr));
        filterButton->setText(QCoreApplication::translate("MainWindow", "Filtern", nullptr));
        addTransactionButton->setText(QCoreApplication::translate("MainWindow", "Hinzuf\303\274gen", nullptr));
        editTransactionButton->setText(QCoreApplication::translate("MainWindow", "Bearbeiten", nullptr));
        deleteTransactionButton->setText(QCoreApplication::translate("MainWindow", "L\303\266schen", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(transactionsTab), QCoreApplication::translate("MainWindow", "Transaktionen", nullptr));
        addBudgetButton->setText(QCoreApplication::translate("MainWindow", "Hinzuf\303\274gen", nullptr));
        editBudgetButton->setText(QCoreApplication::translate("MainWindow", "Bearbeiten", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(budgetTab), QCoreApplication::translate("MainWindow", "Budget", nullptr));
        reportConfigGroup->setTitle(QCoreApplication::translate("MainWindow", "Berichtseinstellungen", nullptr));
        reportTypeLabel->setText(QCoreApplication::translate("MainWindow", "Berichtstyp:", nullptr));
        reportTypeComboBox->setItemText(0, QCoreApplication::translate("MainWindow", "Einnahmen/Ausgaben", nullptr));
        reportTypeComboBox->setItemText(1, QCoreApplication::translate("MainWindow", "Ausgaben nach Kategorie", nullptr));
        reportTypeComboBox->setItemText(2, QCoreApplication::translate("MainWindow", "Budget-\303\234bersicht", nullptr));

        reportStartDateLabel->setText(QCoreApplication::translate("MainWindow", "Von:", nullptr));
        reportEndDateLabel->setText(QCoreApplication::translate("MainWindow", "Bis:", nullptr));
        generateReportButton->setText(QCoreApplication::translate("MainWindow", "Bericht erstellen", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(reportsTab), QCoreApplication::translate("MainWindow", "Bericht erstellen", nullptr));
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
