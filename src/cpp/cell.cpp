#include "sysinc.h"
#include "qtinc.h"
#include "brainfuck.h"
#include "cell.h"

Cell::Cell(size_t index, QVBoxLayout* il, QVBoxLayout* vl)
{
	value_label = new QLabel();
	value_label->setText("0");
	value_label->setGeometry(QRect(0, 0, 25, 8));
	vl->addWidget(value_label);

	index_label = new QLabel();
	index_label->setText(QString("%1").arg(index));
	index_label->setGeometry(0, 0, 25, 8);
	il->addWidget(index_label);

	index_label->show();
	value_label->show();
}

Cell::~Cell()
{
	Hide();
	delete value_label;
	delete index_label;
}

void Cell::SetValue(int val)
{
	value_label->setText(QString("%1").arg(val));
}

void Cell::Hide()
{
	value_label->hide();
	index_label->hide();
}
