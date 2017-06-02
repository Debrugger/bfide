#include "sysinc.h"
#include "qtinc.h"
#include "brainfuck.h"
#include "cell.h"
#include "bfgui.h"
#include "mainwindow.h"
#include "globals.h"

MainWindow* mw;
std::vector<Cell*> cell_boxes;

int main(int argc, char* argv[])
{
	QApplication* app;
	app = new QApplication(argc, argv);
	mw = new MainWindow;

	mw->show();
	return app->exec();
}
