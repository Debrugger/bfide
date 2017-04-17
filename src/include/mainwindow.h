#ifndef __MAINWINDOW_H
#define __MAINWINDOW_H

#include "build/mainwindow.ui.h"

class MainWindow: public QMainWindow, public Ui::MainWindow
{
public:
	MainWindow();
	virtual ~MainWindow();
};

#endif //__MAINWINDOW_H
