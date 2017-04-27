#include "sysinc.h"
#include "qtinc.h"
#include "brainfuck.h"
#include "cell.h"

Cell::Cell(size_t index, QHBoxLayout* l)
{
	value_label = new QLabel(group_box);
	value_label->setText("0");
	value_label->setGeometry(QRect(20, 50, 25, 8));

	//value_label->show();

	l->addWidget(group_box);
}

Cell::~Cell()
{
	std::cout << "cell destructor called" << std::endl;
}

void Cell::SetValue(int val)
{
	value_label->setText(QString("%1").arg(val));
}

void Cell::Hide()
{
}
