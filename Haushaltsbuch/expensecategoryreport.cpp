#include "expensecategoryreport.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QTableWidget>
#include <QHeaderView>
#include <QChart>
#include <QChartView>
#include <QPieSeries>
#include <QPieSlice>
#include "budgetoverviewreport.h"

using namespace std;



// Konstruktor
ExpenseCategoryReport::ExpenseCategoryReport(TransactionController* transactionController)
    : m_transactionController(transactionController) {
}

void ExpenseCategoryReport::generateReport(QWidget* container, const QDate& startDate, const QDate& endDate) {
    QVBoxLayout* layout = qobject_cast<QVBoxLayout*>(container->layout());


   
    // Titel hinzufügen
    QLabel* titleLabel = new QLabel(tr("Ausgaben nach Kategorie"), container);
    titleLabel->setAlignment(Qt::AlignCenter);
    QFont titleFont;
    titleFont.setPointSize(14);
    titleFont.setBold(true);
    titleLabel->setFont(titleFont);
    layout->addWidget(titleLabel);

    // Zeitraum-Label
    QLabel* dateRangeLabel = new QLabel(
        tr("Zeitraum: %1 - %2")
        .arg(startDate.toString("dd.MM.yyyy"))
        .arg(endDate.toString("dd.MM.yyyy")),
        container);
    dateRangeLabel->setAlignment(Qt::AlignCenter);
    layout->addWidget(dateRangeLabel);

    // Daten abrufen
    QMap<QString, double> expensesByCategory = m_transactionController->getExpensesByCategory(startDate, endDate);
    double totalExpense = m_transactionController->getTotalExpense(startDate, endDate);

    // Prüfen, ob Daten vorhanden sind
    if (expensesByCategory.isEmpty() || totalExpense <= 0) {
        QLabel* noDataLabel = new QLabel(tr("Keine Ausgaben im ausgewählten Zeitraum."), container);
        noDataLabel->setAlignment(Qt::AlignCenter);
        layout->addWidget(noDataLabel);
        return;
    }

    // Gesamtausgaben anzeigen
    QLabel* totalExpenseLabel = new QLabel(
        tr("Gesamtausgaben: %1 \u20AC").arg(totalExpense, 0, 'f', 2),
        container);
    totalExpenseLabel->setAlignment(Qt::AlignCenter);
    QFont totalFont;
    totalFont.setBold(true);
    totalExpenseLabel->setFont(totalFont);
    layout->addWidget(totalExpenseLabel);

    // Tabelle erstellen
    QTableWidget* table = new QTableWidget(container);
    table->setColumnCount(3);
    table->setHorizontalHeaderLabels(QStringList() << tr("Kategorie") << tr("Betrag") << tr("Anteil"));
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    table->verticalHeader()->setVisible(false);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    table->setAlternatingRowColors(true);

    // Daten sortieren (absteigend nach Betrag)
    QList<QPair<QString, double>> sortedExpenses;
    for (auto it = expensesByCategory.begin(); it != expensesByCategory.end(); ++it) {
        sortedExpenses.append(qMakePair(it.key(), it.value()));
    }

    std::sort(sortedExpenses.begin(), sortedExpenses.end(),
        [](const QPair<QString, double>& a, const QPair<QString, double>& b) {
            return a.second > b.second;
        });

    // Zeilen hinzufügen
    table->setRowCount(sortedExpenses.size());
    int row = 0;

    // Daten für das Kreisdiagramm
    QPieSeries* series = new QPieSeries();

    // "Sonstige" Kategorie für kleine Anteile
    double otherAmount = 0.0;
    int smallCategoriesCount = 0;

    for (const auto& expense : sortedExpenses) {
        QString category = expense.first;
        double amount = expense.second;
        double percentage = (amount / totalExpense) * 100;

        // Kategorie
        QTableWidgetItem* categoryItem = new QTableWidgetItem(category);
        table->setItem(row, 0, categoryItem);

        // Betrag
        QTableWidgetItem* amountItem = new QTableWidgetItem(QString("%1 \u20AC").arg(amount, 0, 'f', 2));
        amountItem->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
        table->setItem(row, 1, amountItem);

        // Prozentsatz
        QTableWidgetItem* percentageItem = new QTableWidgetItem(QString("%1%").arg(percentage, 0, 'f', 1));
        percentageItem->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
        table->setItem(row, 2, percentageItem);

        // Daten für das Kreisdiagramm
        // Kategorien mit weniger als 3% werden zu "Sonstige" zusammengefasst
        if (percentage >= 3.0) {
            QPieSlice* slice = series->append(category, amount);
            slice->setLabelVisible(true);
            slice->setLabelPosition(QPieSlice::LabelOutside);
            slice->setLabel(QString("%1: %2%").arg(category).arg(percentage, 0, 'f', 1));

            // Für bessere Visualisierung explodieren wir die größten Scheiben leicht
            if (row < 3) {
                slice->setExploded(true);
                slice->setExplodeDistanceFactor(0.1);
            }
        }
        else {
            otherAmount += amount;
            smallCategoriesCount++;
        }

        row++;
    }

    // "Sonstige" Kategorie zum Diagramm hinzufügen, wenn vorhanden
    if (smallCategoriesCount > 0) {
        double otherPercentage = (otherAmount / totalExpense) * 100;
        QPieSlice* otherSlice = series->append(tr("Sonstige (%1)").arg(smallCategoriesCount), otherAmount);
        otherSlice->setLabelVisible(true);
        otherSlice->setLabelPosition(QPieSlice::LabelOutside);
        otherSlice->setLabel(QString("%1: %2%").arg(tr("Sonstige")).arg(otherPercentage, 0, 'f', 1));
        otherSlice->setBrush(QColor(150, 150, 150));
    }

    layout->addWidget(table);

    // Kreisdiagramm erstellen
    QChart* chart = new QChart();
    chart->setTitle(tr("Ausgabenverteilung"));
    chart->setAnimationOptions(QChart::SeriesAnimations);
    chart->addSeries(series);
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignRight);

    // Chart-View erstellen und hinzufügen
    QChartView* chartView = new QChartView(chart, container);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setMinimumHeight(350);

    layout->addWidget(chartView);

    // Abstand am Ende hinzufügen
    layout->addStretch();

    // Optional: Hinweise hinzufügen
    QLabel* noteLabel = new QLabel(tr("Hinweis: Kategorien unter 3% werden als 'Sonstige' zusammengefasst."), container);
    noteLabel->setAlignment(Qt::AlignCenter);
    noteLabel->setStyleSheet("color: gray; font-style: italic;");
    layout->addWidget(noteLabel);
}