#ifndef __MAINWINDOW_H
#define __MAINWINDOW_H

#include "build/mainwindow.ui.h"

class MainWindow: public QMainWindow, public Ui::MainWindow
{
	Q_OBJECT;
public:
	MainWindow();
	virtual ~MainWindow();

public slots:
	void OnActionOpen();
	void OnActionSave();
	void OnExecuteClicked();
};

#endif //__MAINWINDOW_H
