#ifndef __MAINWINDOW_H
#define __MAINWINDOW_H

#include "build/mainwindow.ui.h"
#include "qtinc.h"

class MainWindow: public QMainWindow, public Ui::MainWindow
{
	Q_OBJECT;

public:
	MainWindow();
	virtual ~MainWindow();
	QWidget* value_widget;
	QWidget* index_widget;

public slots:
	void OnActionOpen();
	void OnActionSave();
	void OnExecuteClicked();
	void OnStopClicked();
};

#endif //__MAINWINDOW_H
