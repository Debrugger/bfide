#include "sysinc.h"
#include "qtinc.h"
#include "brainfuck.h"
#include "cell.h"
#include "bfgui.h"

//TODO: first cell hidden on execute (Reset() is called)
//no new cells are created
Bfgui::Bfgui(QPlainTextEdit* _out_edit, QLineEdit* _in_edit, QVBoxLayout* _il, QVBoxLayout* _vl) : out_edit(_out_edit), in_edit(_in_edit), il(_il), vl(_vl)
{
	printf("constructing bfgui objext\n");
	cell_boxes.push_back(new Cell(cell_boxes.size(), il, vl));
	cell_boxes[0]->SetHighlighted(true);
}

Bfgui::~Bfgui()
{
}

void Bfgui::ExecuteAll(Cmdvec* c)
{
	size_t i = 0;
	try { while ((i = Execute(c, i)) < c->size() && !stop); }
	catch (Brainfuck::OffLimits)
	{
		std::cout << "Tried to execute off limit command. Exiting." << std::endl;
		exit(1);
	}
}

int Bfgui::GetInput()
{
	printf("input called\n");
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
	printf("Output called\n");
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
	cell_boxes[CurrentCell()]->SetHighlighted(false);
	cell_boxes[CurrentCell() - 1]->SetHighlighted(true);
}

void Bfgui::OnIncVal()
{
	OnDecVal();
}

void Bfgui::OnDecVal()
{
	printf("ondecval called, assigning value %d to cell %d\n", CellValue(CurrentCell()), CurrentCell());
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
