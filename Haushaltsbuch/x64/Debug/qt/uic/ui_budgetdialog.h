/********************************************************************************
** Form generated from reading UI file 'budgetdialog.ui'
**
** Created by: Qt User Interface Compiler version 6.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BUDGETDIALOG_H
#define UI_BUDGETDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_BudgetDialog
{
public:
    QVBoxLayout *verticalLayout;
    QFormLayout *formLayout;
    QLabel *categoryLabel;
    QComboBox *categoryComboBox;
    QLabel *amountLabel;
    QDoubleSpinBox *amountSpinBox;
    QSpacerItem *verticalSpacer;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *BudgetDialog)
    {
        if (BudgetDialog->objectName().isEmpty())
            BudgetDialog->setObjectName("BudgetDialog");
        BudgetDialog->resize(350, 150);
        verticalLayout = new QVBoxLayout(BudgetDialog);
        verticalLayout->setObjectName("verticalLayout");
        formLayout = new QFormLayout();
        formLayout->setObjectName("formLayout");
        categoryLabel = new QLabel(BudgetDialog);
        categoryLabel->setObjectName("categoryLabel");

        formLayout->setWidget(0, QFormLayout::LabelRole, categoryLabel);

        categoryComboBox = new QComboBox(BudgetDialog);
        categoryComboBox->setObjectName("categoryComboBox");
        categoryComboBox->setEditable(true);

        formLayout->setWidget(0, QFormLayout::FieldRole, categoryComboBox);

        amountLabel = new QLabel(BudgetDialog);
        amountLabel->setObjectName("amountLabel");

        formLayout->setWidget(1, QFormLayout::LabelRole, amountLabel);

        amountSpinBox = new QDoubleSpinBox(BudgetDialog);
        amountSpinBox->setObjectName("amountSpinBox");
        amountSpinBox->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        amountSpinBox->setDecimals(2);
        amountSpinBox->setMaximum(1000000.000000000000000);

        formLayout->setWidget(1, QFormLayout::FieldRole, amountSpinBox);


        verticalLayout->addLayout(formLayout);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        buttonBox = new QDialogButtonBox(BudgetDialog);
        buttonBox->setObjectName("buttonBox");
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(BudgetDialog);
        QObject::connect(buttonBox, &QDialogButtonBox::accepted, BudgetDialog, qOverload<>(&QDialog::accept));
        QObject::connect(buttonBox, &QDialogButtonBox::rejected, BudgetDialog, qOverload<>(&QDialog::reject));

        QMetaObject::connectSlotsByName(BudgetDialog);
    } // setupUi

    void retranslateUi(QDialog *BudgetDialog)
    {
        BudgetDialog->setWindowTitle(QCoreApplication::translate("BudgetDialog", "Budget bearbeiten", nullptr));
        categoryLabel->setText(QCoreApplication::translate("BudgetDialog", "Kategorie:", nullptr));
        amountLabel->setText(QCoreApplication::translate("BudgetDialog", "Budgetbetrag (\342\202\254):", nullptr));
        amountSpinBox->setSuffix(QCoreApplication::translate("BudgetDialog", " \342\202\254", nullptr));
    } // retranslateUi

};

namespace Ui {
    class BudgetDialog: public Ui_BudgetDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BUDGETDIALOG_H
