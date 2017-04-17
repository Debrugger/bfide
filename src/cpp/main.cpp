#include "sysinc.h"
#include "qtinc.h"

#include "mainwindow.h"

int main(int argc, char* argv[])
{
	QApplication* app;
	MainWindow* mw;
	app = new QApplication(argc, argv);
	mw = new MainWindow;

	mw->show();
	return app->exec();
}
