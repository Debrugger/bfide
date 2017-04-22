#include "sysinc.h"
#include "qtinc.h"
#include "brainfuck.h"
#include "cell.h"

Cell::Cell(size_t index, QHBoxLayout* l)
{
	group_box = new QGroupBox;
	index_label = new QLabel(group_box);
	index_label->setText(QString("%1").arg(index));

	group_box->show();
	index_label->show();

	l->addWidget(group_box);
}

Cell::~Cell()
{
	delete group_box;
	delete index_label;
}
//TODO: Find way to upüdate cells
