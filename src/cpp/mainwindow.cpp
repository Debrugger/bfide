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
	cell_widget = new QWidget;
	cell_widget->setGeometry(QRect(10, 470, 981, 91));
	cell_layout = new QHBoxLayout(cell_widget);
	cell_layout->setObjectName(QStringLiteral("cell_layout"));
	cell_layout->setSizeConstraint(QLayout::SetMaximumSize);

	cell_scroll_area->setWidget(cell_widget);
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
