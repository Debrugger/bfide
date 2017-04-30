#ifndef __MAINWINDOW_H
#define __MAINWINDOW_H

#include "build/mainwindow.ui.h"
#include "qtinc.h"

class Brainfuck;
struct Command;
extern bool stop;

class MainWindow: public QMainWindow, public Ui::MainWindow
{
	Q_OBJECT;

public:
	MainWindow();
	virtual ~MainWindow();
	QWidget* value_widget;
	QWidget* index_widget;
	void StepByStep(Brainfuck*, std::vector<Command>* parsed);
	void SaveFile(QString fn);

public slots:
	void OnActionOpen();
	void OnActionSave();
	void OnActionSaveAs();
	void OnExecuteClicked();
	void OnStopClicked();
};

#endif //__MAINWINDOW_H
