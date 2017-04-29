#include "sysinc.h"
#include "qtinc.h"
#include "brainfuck.h"
#include "mainwindow.h"

QString filename;

MainWindow::MainWindow()
{
	setupUi(this);
	terminal_edit->setReadOnly(true);
	input_edit->setReadOnly(true);
	connect(action_open, SIGNAL(triggered()), this, SLOT(OnActionOpen()));
	connect(action_save, SIGNAL(triggered()), this, SLOT(OnActionSave()));
	connect(action_save_as, SIGNAL(triggered()), this, SLOT(OnActionSaveAs()));
	connect(button_exec, SIGNAL(clicked()), this, SLOT(OnExecuteClicked()));
	connect(button_stop, SIGNAL(clicked()), this, SLOT(OnStopClicked()));

	//value_widget = new QWidget(scrollAreaWidgetContents);
	//value_widget->setObjectName(QStringLiteral("value_widget"));
	//value_layout->setWidget(value_widget);

	//index_widget = new QWidget(scrollAreaWidgetContents);
	//index_widget->setObjectName(QStringLiteral("index_widget"));
	//index_layout->setWidget(index_widget);
	value_layout->setAlignment(Qt::AlignTop);
	index_layout->setAlignment(Qt::AlignTop);

	setWindowTitle("bfide");
}

MainWindow::~MainWindow()
{
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
	file.clear();
	QTextStream out(&file);
	out << main_edit->toPlainText();
	qDebug() << "saved as " << fn;

 	statusBar()->showMessage(fn); 
	setWindowTitle("bfide - " + fn);
}

void MainWindow::OnExecuteClicked()
{
	Brainfuck brainfuck;
	std::vector<Command> parsed = brainfuck.Parse(main_edit->toPlainText().toStdString());

	if (!step_checkbox->isChecked())	
	{
		brainfuck.ExecuteAll(parsed);
		std::cout << "executing all" << std::endl;
	}
	else
		StepByStep(&brainfuck, &parsed);
}

void MainWindow::OnStopClicked()
{
}

void MainWindow::StepByStep(Brainfuck* b, std::vector<Command>* p)
{
	size_t i = 0;
	b->ClearCells();
	while (i < p->size())
	{
		i = b->Execute(*p, i);
		QEventLoop l;
		QWidget::connect(button_next, SIGNAL(clicked()), &l, SLOT(quit()));
		l.exec();
	}	
}
