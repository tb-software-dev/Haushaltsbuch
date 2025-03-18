#include "mainwindow.h"
#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <QLibraryInfo>
#include <QSettings>
#include <QDir>
#include <QTextCodec>

int main(int argc, char* argv[])
{
	// Setze UTF-8 als Standardkodierung
	


	// QApplication erstellen
	QApplication app(argc, argv);

	// Anwendungsinformationen setzen
	QApplication::setApplicationName("Haushaltsbuch");
	QApplication::setApplicationVersion("1.0");

	// Lokalisierung einrichten
	QTranslator qtTranslator;
	qtTranslator.load(QLocale::system(), "qt", "_",
		QLibraryInfo::path(QLibraryInfo::TranslationsPath));
	app.installTranslator(&qtTranslator);

	//


	// Standardeinstellungen festlegen , für den ersten Start
	QSettings settings;
	if (!settings.contains("firstRun"))
	{
		settings.setValue("firstRun", false);
		settings.setValue("defaultCurrency", "€");
		settings.setValue("defaultStartMonth", 1);		// Januar


		// Beispielkategorien für neue Benutzer
		QStringList defaultCategories;
		defaultCategories << "Lebensmittel" << "Wohnen" << "Transport"
			<< "Unterhaltung" << "Gesundheit" << "Bildung" << "Sonstiges";
		settings.setValue("defaultCategories", defaultCategories);
	}


	// Prüfen, ob das Datenverzeichnis existiert, andernfalls erstellen
	QDir dataDir(QDir::homePath() + "/.haushaltsbuch");
	if (!dataDir.exists()) {
		dataDir.mkpath(".");
	}

	// Hauptfenster erstellen und anzeigen
	MainWindow mainWindow;
	mainWindow.show();

	// Anwendung ausführen und Rückgabecode zurückgeben
	return app.exec();


}


