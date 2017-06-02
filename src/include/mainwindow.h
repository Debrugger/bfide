#ifndef __MAINWINDOW_H
#define __MAINWINDOW_H

#include "sysinc.h"
#include "build/mainwindow.ui.h"
#include "brainfuck.h"
#include "cell.h"
#include "bfgui.h"

extern bool stop;

class MainWindow: public QMainWindow, public Ui::MainWindow
{
	Q_OBJECT;
	QWidget* value_widget; //did we need those?
	QWidget* index_widget;

	Bfgui* brainfuck;
	void StepByStep(Bfgui*, std::vector<Brainfuck::Command>* parsed);
	void SaveFile(QString fn);
	void HighlightCell(size_t index);

public:
	MainWindow();
	virtual ~MainWindow();

public slots:
	void OnActionOpen();
	void OnActionSave();
	void OnActionSaveAs();
	void OnExecuteClicked();
	void OnStopClicked();
};

#endif //__MAINWINDOW_H
