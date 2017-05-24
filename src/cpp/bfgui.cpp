#include "sysinc.h"
#include "qtinc.h"
#include "brainfuck.h"
#include "bfgui.h"

Bfgui::Bfgui()
{
}

Bfgui::~Bfgui()
{
}

void Bfgui::ExecuteAll(Cmdvec c)
{
	size_t i = 0;
	while ((i = Execute(c, i)) < c.size() - 1 && !stop);
}

int Bfgui::GetInput(QLineEdit* edit)
{
   edit->setReadOnly(false);
	QString s;
	QEventLoop loop;
	QWidget::connect(edit, SIGNAL(editingFinished()), &loop, SLOT(quit()));
	loop.exec();

   int ret = static_cast<int>(edit->text().at(0).toLatin1());
	edit->setReadOnly(true);
	edit->clear();
	return ret;
}

void Bfgui::Output(char c, QPlainTextEdit* edit)
{
	QString s;
  	s = c;
	edit->moveCursor(QTextCursor::End);
	edit->textCursor().insertText(s);
}
