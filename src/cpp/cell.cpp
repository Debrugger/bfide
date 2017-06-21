#include "sysinc.h"
#include "qtinc.h"
#include "cell.h"

Cell::Cell(size_t _index, QVBoxLayout* il, QVBoxLayout* vl)
{
	index = _index;
	index_label = new QLabel();
	index_label->setText(QString("%1").arg(index));
	index_label->setGeometry(0, 0, 25, 8);
	index_label->setTextFormat(Qt::RichText);
	il->addWidget(index_label);

	value = 0;
	value_label = new QLabel();
	value_label->setText(QString(value));
	value_label->setGeometry(QRect(0, 0, 25, 8));
	value_label->setTextFormat(Qt::RichText);
	vl->addWidget(value_label);

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
	value = val;
	if (highlighted)
		value_label->setText(QString("<b>%1</b>").arg(val));
	else
		value_label->setText(QString("%1").arg(val));
}

void Cell::SetHighlighted(bool b)
{
	if (b)
	{
		highlighted = true;
		index_label->setText("<b>" + QString::number(index) + "</b>");
		value_label->setText("<b>" + QString::number(value) + "</b>");
	}
	else
	{
		highlighted = false;
      index_label->setText(QString::number(index));
		value_label->setText(QString::number(value));
	}
}

void Cell::Hide()
{
	value_label->hide();
	index_label->hide();
}
