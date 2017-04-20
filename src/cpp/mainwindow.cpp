#include "sysinc.h"
#include "qtinc.h"
#include "mainwindow.h"

QString filename;

MainWindow::MainWindow()
{
	setupUi(this);
	terminal_edit->setReadOnly(true);
	connect(action_open, SIGNAL(triggered()), this, SLOT(OnActionOpen()));
	connect(action_save, SIGNAL(triggered()), this, SLOT(OnActionSave()));
}

MainWindow::~MainWindow()
{
}

void MainWindow::OnActionOpen()
{
	filename = QFileDialog::getOpenFileName(this, tr("Open source file"), getenv("HOME"), tr("Brainfuck source file (*)")); 
	QFile file(filename);
	file.open((QFile::ReadOnly | QFile::Text));
	QTextStream in(&file);
	main_edit->setText(in.readAll());
}

void MainWindow::OnActionSave()
{
	if (filename == "")
		filename = QFileDialog::getSaveFileName(this, tr("Open source file"), getenv("HOME"), tr("Brainfuck source file (*)")); 
	QFile file(filename);
	file.open((QFile::ReadWrite | QFile::Text));
	QTextStream out(&file);
	out << "placeholder";
}
