/********************************************************************************
** Form generated from reading UI file 'transactiondialog.ui'
**
** Created by: Qt User Interface Compiler version 6.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TRANSACTIONDIALOG_H
#define UI_TRANSACTIONDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_TransactionDialog
{
public:
    QVBoxLayout *verticalLayout;
    QGroupBox *typeGroupBox;
    QHBoxLayout *horizontalLayout;
    QRadioButton *incomeRadioButton;
    QRadioButton *expenseRadioButton;
    QFormLayout *formLayout;
    QLabel *dateLabel;
    QDateEdit *dateEdit;
    QLabel *amountLabel;
    QDoubleSpinBox *amountSpinBox;
    QLabel *categoryLabel;
    QComboBox *categoryComboBox;
    QLabel *descriptionLabel;
    QTextEdit *descriptionTextEdit;
    QSpacerItem *verticalSpacer;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *TransactionDialog)
    {
        if (TransactionDialog->objectName().isEmpty())
            TransactionDialog->setObjectName("TransactionDialog");
        TransactionDialog->resize(400, 350);
        verticalLayout = new QVBoxLayout(TransactionDialog);
        verticalLayout->setObjectName("verticalLayout");
        typeGroupBox = new QGroupBox(TransactionDialog);
        typeGroupBox->setObjectName("typeGroupBox");
        horizontalLayout = new QHBoxLayout(typeGroupBox);
        horizontalLayout->setObjectName("horizontalLayout");
        incomeRadioButton = new QRadioButton(typeGroupBox);
        incomeRadioButton->setObjectName("incomeRadioButton");
        incomeRadioButton->setChecked(false);

        horizontalLayout->addWidget(incomeRadioButton);

        expenseRadioButton = new QRadioButton(typeGroupBox);
        expenseRadioButton->setObjectName("expenseRadioButton");
        expenseRadioButton->setChecked(true);

        horizontalLayout->addWidget(expenseRadioButton);


        verticalLayout->addWidget(typeGroupBox);

        formLayout = new QFormLayout();
        formLayout->setObjectName("formLayout");
        dateLabel = new QLabel(TransactionDialog);
        dateLabel->setObjectName("dateLabel");

        formLayout->setWidget(0, QFormLayout::LabelRole, dateLabel);

        dateEdit = new QDateEdit(TransactionDialog);
        dateEdit->setObjectName("dateEdit");
        dateEdit->setCalendarPopup(true);

        formLayout->setWidget(0, QFormLayout::FieldRole, dateEdit);

        amountLabel = new QLabel(TransactionDialog);
        amountLabel->setObjectName("amountLabel");

        formLayout->setWidget(1, QFormLayout::LabelRole, amountLabel);

        amountSpinBox = new QDoubleSpinBox(TransactionDialog);
        amountSpinBox->setObjectName("amountSpinBox");
        amountSpinBox->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        amountSpinBox->setDecimals(2);
        amountSpinBox->setMaximum(1000000.000000000000000);

        formLayout->setWidget(1, QFormLayout::FieldRole, amountSpinBox);

        categoryLabel = new QLabel(TransactionDialog);
        categoryLabel->setObjectName("categoryLabel");

        formLayout->setWidget(2, QFormLayout::LabelRole, categoryLabel);

        categoryComboBox = new QComboBox(TransactionDialog);
        categoryComboBox->setObjectName("categoryComboBox");
        categoryComboBox->setEditable(true);

        formLayout->setWidget(2, QFormLayout::FieldRole, categoryComboBox);

        descriptionLabel = new QLabel(TransactionDialog);
        descriptionLabel->setObjectName("descriptionLabel");

        formLayout->setWidget(3, QFormLayout::LabelRole, descriptionLabel);

        descriptionTextEdit = new QTextEdit(TransactionDialog);
        descriptionTextEdit->setObjectName("descriptionTextEdit");
        descriptionTextEdit->setMaximumSize(QSize(16777215, 100));

        formLayout->setWidget(3, QFormLayout::FieldRole, descriptionTextEdit);


        verticalLayout->addLayout(formLayout);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        buttonBox = new QDialogButtonBox(TransactionDialog);
        buttonBox->setObjectName("buttonBox");
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(TransactionDialog);
        QObject::connect(buttonBox, &QDialogButtonBox::accepted, TransactionDialog, qOverload<>(&QDialog::accept));
        QObject::connect(buttonBox, &QDialogButtonBox::rejected, TransactionDialog, qOverload<>(&QDialog::reject));

        QMetaObject::connectSlotsByName(TransactionDialog);
    } // setupUi

    void retranslateUi(QDialog *TransactionDialog)
    {
        TransactionDialog->setWindowTitle(QCoreApplication::translate("TransactionDialog", "Transaktion", nullptr));
        typeGroupBox->setTitle(QCoreApplication::translate("TransactionDialog", "Transaktionstyp", nullptr));
        incomeRadioButton->setText(QCoreApplication::translate("TransactionDialog", "Einnahme", nullptr));
        expenseRadioButton->setText(QCoreApplication::translate("TransactionDialog", "Ausgabe", nullptr));
        dateLabel->setText(QCoreApplication::translate("TransactionDialog", "Datum:", nullptr));
        amountLabel->setText(QCoreApplication::translate("TransactionDialog", "Betrag (\342\202\254):", nullptr));
        amountSpinBox->setSuffix(QCoreApplication::translate("TransactionDialog", " \342\202\254", nullptr));
        categoryLabel->setText(QCoreApplication::translate("TransactionDialog", "Kategorie:", nullptr));
        descriptionLabel->setText(QCoreApplication::translate("TransactionDialog", "Beschreibung:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class TransactionDialog: public Ui_TransactionDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TRANSACTIONDIALOG_H
