#include "sysinc.h"
#include "qtinc.h"
#include "bfgui.h"
#include "cell.h"

Bfgui::Bfgui(QPlainTextEdit* _out_edit, QLineEdit* _in_edit, QVBoxLayout* _il, QVBoxLayout* _vl) : out_edit(_out_edit), in_edit(_in_edit), il(_il), vl(_vl)
{
	cell_boxes.push_back(new Cell(cell_boxes.size(), il, vl));
	cell_boxes[0]->SetHighlighted(true);
}

Bfgui::~Bfgui()
{
}

int Bfgui::GetInput()
{
   in_edit->setReadOnly(false);
	QString s;
	QEventLoop loop;
	QWidget::connect(in_edit, SIGNAL(editingFinished()), &loop, SLOT(quit()));
	loop.exec();

   int ret = static_cast<int>(in_edit->text().at(0).toLatin1());
	in_edit->setReadOnly(true);
	in_edit->clear();
	return ret;
}

void Bfgui::Output(char c)
{
	printf("outputting %c\n", c);
	QString s;
  	s = c;
	out_edit->moveCursor(QTextCursor::End);
	out_edit->textCursor().insertText(s);
}

void Bfgui::OnIncPtr()
{      
	size_t sz = cell_boxes.size();

	if (CurrentCell() + 1 > sz)
	{
		cell_boxes.push_back(new Cell(CurrentCell(), il, vl));
	}
	cell_boxes[CurrentCell()]->SetHighlighted(true);
	cell_boxes[CurrentCell() - 1]->SetHighlighted(false);
}

void Bfgui::OnDecPtr()
{
	cell_boxes[CurrentCell()]->SetHighlighted(true);
	cell_boxes[CurrentCell() + 1]->SetHighlighted(false);
}

void Bfgui::OnIncVal()
{
	OnDecVal();
}

void Bfgui::OnDecVal()
{
	cell_boxes[CurrentCell()]->SetValue(CellValue(CurrentCell()));
}

void Bfgui::ClearCells()
{
   for (auto i = cell_boxes.begin(); i != cell_boxes.end(); i++)
		delete *i;
	cell_boxes.clear();
	cell_boxes.push_back(new Cell(0, il, vl));
}

void Bfgui::Reset()
{
	ClearCells();
	current_cell = 0;
	cells.clear();
	out_edit->clear();
}
