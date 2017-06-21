#include "sysinc.h"
#include "qtinc.h"
#include "brainfuck.h"
#include "cell.h"
#include "bfgui.h"
#include "exec_thread.h"
#include "mainwindow.h"

QString filename;
bool stop;

MainWindow::MainWindow()
{
	stop = false;
	exec_thread_started = false;
	setupUi(this);
	terminal_edit->setReadOnly(true);
	input_edit->setReadOnly(true);
	connect(action_open, SIGNAL(triggered()), this, SLOT(OnActionOpen()));
	connect(action_save, SIGNAL(triggered()), this, SLOT(OnActionSave()));
	connect(action_save_as, SIGNAL(triggered()), this, SLOT(OnActionSaveAs()));
	connect(button_exec, SIGNAL(clicked()), this, SLOT(OnExecuteClicked()));
	connect(button_stop, SIGNAL(clicked()), this, SLOT(OnStopClicked()));
	value_layout->setAlignment(Qt::AlignTop);
	index_layout->setAlignment(Qt::AlignTop);
   button_next->setEnabled(false);
	button_stop->setEnabled(false);
	setWindowTitle("bfide");
	brainfuck = new Bfgui(terminal_edit, input_edit, index_layout, value_layout);
}

MainWindow::~MainWindow()
{
}

void MainWindow::OnExecuteClicked()
{
	Cmdvec parsed = Brainfuck::Parse(main_edit->toPlainText().toStdString());
	brainfuck->Reset();
	stop = false;
	button_stop->setEnabled(true);

	if (!step_checkbox->isChecked())	
	{
		QThread* exec_thread = new QThread;
		executer = new Executer(brainfuck, parsed);
		connect(executer, SIGNAL(Done()), exec_thread, SLOT(quit()));
		connect(exec_thread, SIGNAL(started()), executer, SLOT(Exec()));
		connect(button_stop, SIGNAL(clicked()), exec_thread, SLOT(quit()));
		connect(executer, SIGNAL(Done()), executer, SLOT(deleteLater()));
		connect(executer, SIGNAL(Done()), this, SLOT(OnExecDone()));
		connect(exec_thread, SIGNAL(finished()), exec_thread, SLOT(deleteLater()));
		button_exec->setEnabled(false);
		exec_thread->start();
		exec_thread_started = true;
	}
	else
		StepByStep(brainfuck, &parsed);
	button_stop->setEnabled(false);
	button_exec->setEnabled(true);
}

void MainWindow::OnExecDone()
{
	printf("Exec thread emitted done\n");
	button_exec->setEnabled(true);
	delete exec_thread;
}

void MainWindow::OnStopClicked()
{
	printf("onstopclicked\n");
	stop = true;
	if (exec_thread_started) { exec_thread->quit(); delete exec_thread; }
	button_stop->setEnabled(false);
	button_next->setEnabled(false);
	button_exec->setEnabled(true);
}

void MainWindow::StepByStep(Bfgui* b, Cmdvec* p)
{
	size_t i = 0;
	b->ClearCells();
	button_exec->setEnabled(false);
	button_next->setEnabled(true);
	while (i < p->size() && !stop)
	{
		i = Brainfuck::Execute(b, p, i);
		QEventLoop l;
		QWidget::connect(button_next, SIGNAL(clicked()), &l, SLOT(quit()));
		l.exec();
	}	
	button_next->setEnabled(false);
}


void MainWindow::OnActionOpen()
{
	filename = QFileDialog::getOpenFileName(this, tr("Open source file"), getenv("HOME"), tr("Brainfuck source file (*.b)")); 
	QFile file(filename);
	file.open((QFile::ReadOnly | QFile::Text));
	QTextStream in(&file);
	main_edit->setPlainText(in.readAll());
 	statusBar()->showMessage(filename); 
	setWindowTitle("bfide - " + filename);
}

void MainWindow::OnActionSave()
{
	if (filename == "")
		filename = QFileDialog::getSaveFileName(this, tr("Save source file"), getenv("HOME"), tr("Brainfuck source file (*.b)")); 

	SaveFile(filename);
}

void MainWindow::OnActionSaveAs()
{
	filename = QFileDialog::getSaveFileName(this, tr("Save source file"), getenv("HOME"), tr("Brainfuck source file (*.b)"));

	SaveFile(filename); 
}

void MainWindow::SaveFile(QString fn)
{
	QFile file(fn);
	file.open((QFile::ReadWrite | QFile::Text));
	//file.clear();
	QTextStream out(&file);
	out << main_edit->toPlainText();
	qDebug() << "saved as " << fn;

 	statusBar()->showMessage(fn); 
	setWindowTitle("bfide - " + fn);
}
