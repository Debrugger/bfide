#ifndef __MAINWINDOW_H
#define __MAINWINDOW_H

#include "build/mainwindow.ui.h"
#include "qtinc.h"

class MainWindow: public QMainWindow, public Ui::MainWindow
{
	Q_OBJECT;

   QWidget* cell_widget;

public:
	MainWindow();
	virtual ~MainWindow();
	QHBoxLayout* cell_layout;

public slots:
	void OnActionOpen();
	void OnActionSave();
	void OnExecuteClicked();
	void OnStopClicked();
};

#endif //__MAINWINDOW_H
