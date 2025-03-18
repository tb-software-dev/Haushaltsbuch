#include "incomeexpensereport.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QGroupBox>
#include <QFormLayout>
#include <QChart>
#include <QChartView>
#include <QBarSeries>
#include <QBarSet>
#include <QBarCategoryAxis>
#include <QValueAxis>
#include <QMessageBox>
#include <QWidget>
#include <QTextCodec>
#include <QLocale>


QLocale locale(QLocale::German, QLocale::Germany);

IncomeExpenseReport::IncomeExpenseReport(TransactionController* transactionController)
    : m_transactionController(transactionController) 
{

}

void IncomeExpenseReport::generateReport(QWidget* container, const QDate& startDate, const QDate& endDate)
{
    //
    

    QVBoxLayout* layout = qobject_cast<QVBoxLayout*>(container->layout());

    // Titel hinzufügen
    QLabel* titleLabel = new QLabel(tr("Einnahmen und Ausgaben"));
    titleLabel->setAlignment(Qt::AlignCenter);
    QFont titleFont = titleLabel->font();
    titleFont.setPointSize(14);
    titleFont.setBold(true);
    titleLabel->setFont(titleFont);
    layout->addWidget(titleLabel);

    // Zeitraum-Label
    QLabel* dateRangeLabel = new QLabel(
        tr("Zeitraum: %1 - %2")
        .arg(startDate.toString("dd.MM.yyyy"))
        .arg(endDate.toString("dd.MM.yyyy")));
    dateRangeLabel->setAlignment(Qt::AlignCenter);
    layout->addWidget(dateRangeLabel);

    // Daten abrufen
    double totalIncome = m_transactionController->getTotalIncome(startDate, endDate);
    double totalExpense = m_transactionController->getTotalExpense(startDate, endDate);
    double balance = totalIncome - totalExpense;

    // Zusammenfassung
    QGroupBox* summaryGroup = new QGroupBox(tr("Zusammenfassung"));
    QFormLayout* summaryLayout = new QFormLayout(summaryGroup);

    QLabel* incomeLabel = new QLabel(QString("%1 \u20AC").arg(totalIncome, 0, 'f', 2));
    incomeLabel->setStyleSheet("color: green;");
    summaryLayout->addRow(tr("Gesamteinnahmen:"), incomeLabel);

    QLabel* expenseLabel = new QLabel(QString("%1 \u20AC").arg(totalExpense, 0, 'f', 2));
    expenseLabel->setStyleSheet("color: red;");
    summaryLayout->addRow(tr("Gesamtausgaben:"), expenseLabel);

    QLabel* balanceLabel = new QLabel(QString("%1 \u20AC").arg(balance, 0, 'f', 2));
    balanceLabel->setStyleSheet(balance >= 0 ? "color: green;" : "color: red;");
    summaryLayout->addRow(tr("Saldo:"), balanceLabel);

    // Sparrate berechnen
    if (totalIncome > 0)
    {
        double savingsRate = (balance > 0) ? (balance / totalIncome) * 100 : 0;
        QLabel* savingsRateLabel = new QLabel(QString("%1 %").arg(savingsRate, 0, 'f', 1));
        savingsRateLabel->setStyleSheet(savingsRate >= 0 ? "color: green;" : "color: red;");
        summaryLayout->addRow(tr("Sparrate:"), savingsRateLabel);
    }

    layout->addWidget(summaryGroup);

    // Diagramm erstellen
    QChart* chart = new QChart();
    chart->setTitle(tr("Einnahmen vs. Ausgaben"));
    chart->setAnimationOptions(QChart::SeriesAnimations);

    // Daten für dass Balkendiagramm
    QBarSet* incomeSet = new QBarSet(tr("Einnahmen"));
    incomeSet->append(totalIncome);
    incomeSet->setColor(QColor(0, 128, 0));

    QBarSet* expenseSet = new QBarSet(tr("Ausgaben"));
    expenseSet->append(totalExpense);
    expenseSet->setColor(QColor(128, 0, 0));

    QBarSeries* series = new QBarSeries();
    series->append(incomeSet);
    series->append(expenseSet);

    chart->addSeries(series);

    // Achsen konfigurieren
    QStringList categories;
    categories << QString::fromUtf8("Transaktionen");

    QBarCategoryAxis* axisX = new QBarCategoryAxis();
    axisX->append(categories);
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    QValueAxis* axisY = new QValueAxis();
    axisY->setRange(0, qMax(totalIncome, totalExpense) * 1.1);
    axisY->setLabelFormat(QStringLiteral("%d €"));
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    // Legende konfigurieren
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);

    // Chart-View erstellen und hinzufügen
    QChartView* chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setMinimumHeight(300);

    layout->addWidget(chartView);

    // Optional: Zusätzliche Informationen hinzufügen
    QLabel* noteLabel = new QLabel(tr("Hinweis: Alle Transaktionen sind in Euro angegeben."));
    noteLabel->setAlignment(Qt::AlignCenter);
    noteLabel->setStyleSheet("color: gray; font-style: italic;");
    layout->addWidget(noteLabel);

    // Abstand am Ende hinzufügen
    layout->addStretch();

}