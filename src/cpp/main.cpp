#include "sysinc.h"
#include "qtinc.h"

#include "mainwindow.h"
#include "globals.h"

MainWindow* mw;

int main(int argc, char* argv[])
{
	QApplication* app;
	app = new QApplication(argc, argv);
	mw = new MainWindow;

	mw->show();
	return app->exec();
}
