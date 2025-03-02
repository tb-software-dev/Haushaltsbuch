#pragma once

#include <QMainWindow>
#include <QtSql>
#include <QMessageBox>
#include <QStandardItemModel>

QT_BEGIN_NAMESPACE

namespace Ui
{
	class MainWindow;
}

QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
	Q_OBJECT


public:
	// 
	MainWindow(QWidget* parent = nullptr);
	~MainWindow();


private slots:

	//


private:
	//
	Ui::MainWindow* ui;




};