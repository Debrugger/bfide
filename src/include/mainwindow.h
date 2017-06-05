#ifndef __MAINWINDOW_H
#define __MAINWINDOW_H

#include "sysinc.h"
#include "build/mainwindow.ui.h"
#include "cell.h"
#include "brainfuck.h"

class Bfgui;
class Executer;
class MainWindow: public QMainWindow, public Ui::MainWindow
{
	Q_OBJECT;

	Bfgui* brainfuck;
	Executer* executer;
	QThread* exec_thread;
	bool stop;
	bool exec_thread_started;
	void StepByStep(Bfgui*, std::vector<Brainfuck::Command>* parsed);
	void SaveFile(QString fn);
	void HighlightCell(size_t index);

public:
	MainWindow();
	virtual ~MainWindow();

public slots:
	void OnExecDone();
	void OnActionOpen();
	void OnActionSave();
	void OnActionSaveAs();
	void OnExecuteClicked();
	void OnStopClicked();
};

#endif //__MAINWINDOW_H
