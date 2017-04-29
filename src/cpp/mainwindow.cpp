#include "sysinc.h"
#include "qtinc.h"
#include "mainwindow.h"
#include "cell.h"
#include "brainfuck.h"

QString filename;

MainWindow::MainWindow()
{
	setupUi(this);
	terminal_edit->setReadOnly(true);
	input_edit->setReadOnly(true);
	connect(action_open, SIGNAL(triggered()), this, SLOT(OnActionOpen()));
	connect(action_save, SIGNAL(triggered()), this, SLOT(OnActionSave()));
	connect(button_exec, SIGNAL(clicked()), this, SLOT(OnExecuteClicked()));
	connect(button_stop, SIGNAL(clicked()), this, SLOT(OnStopClicked()));

	//value_widget = new QWidget(scrollAreaWidgetContents);
	//value_widget->setObjectName(QStringLiteral("value_widget"));
	//value_layout->setWidget(value_widget);

	//index_widget = new QWidget(scrollAreaWidgetContents);
	//index_widget->setObjectName(QStringLiteral("index_widget"));
	//index_layout->setWidget(index_widget);

	setWindowTitle("bfide");
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
	main_edit->setPlainText(in.readAll());
 	statusBar()->showMessage(filename); 
	setWindowTitle("bfide - " + filename);
}

void MainWindow::OnActionSave()
{
	if (filename == "")
		filename = QFileDialog::getSaveFileName(this, tr("Open source file"), getenv("HOME"), tr("Brainfuck source file (*)")); 
	QFile file(filename);
	file.open((QFile::ReadWrite | QFile::Text));
	QTextStream out(&file);
	out << main_edit->toPlainText();
}

void MainWindow::OnExecuteClicked()
{
	Brainfuck brainfuck;
	std::vector<Command> parsed = brainfuck.Parse(main_edit->toPlainText().toStdString());

	//for (unsigned int i = 0; i < parsed.size(); i++)
	//	std::cout << "Command " << parsed[i].type << std::endl;
	//std::cout << "nb commands: " << parsed.size();

	brainfuck.ExecuteAll(parsed);
}

void MainWindow::OnStopClicked()
{
}
