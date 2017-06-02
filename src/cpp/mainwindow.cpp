#include "sysinc.h"
#include "qtinc.h"
#include "brainfuck.h"
#include "cell.h"
#include "bfgui.h"
#include "mainwindow.h"
#include "globals.h"

QString filename;
bool stop;

MainWindow::MainWindow()
{
	stop = false;
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
	using namespace Brainfuck;
	Cmdvec parsed = brainfuck->Parse(main_edit->toPlainText().toStdString());
	brainfuck->Reset();
	stop = false;
	button_stop->setEnabled(true);

	if (!step_checkbox->isChecked())	
	{
		button_exec->setEnabled(false);
		brainfuck->ExecuteAll(&parsed);
		button_exec->setEnabled(true);
	}
	else
		StepByStep(brainfuck, &parsed);
	button_stop->setEnabled(false);
}

void MainWindow::OnStopClicked()
{
	printf("onstopclicked\n");
	brainfuck->stop = true;
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
		i = b->Execute(p, i);
		QEventLoop l;
		QWidget::connect(button_next, SIGNAL(clicked()), &l, SLOT(quit()));
		l.exec();
	}	
	button_exec->setEnabled(true);
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
