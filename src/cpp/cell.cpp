#include "sysinc.h"
#include "qtinc.h"
#include "brainfuck.h"
#include "cell.h"

Cell::Cell(size_t index, QHBoxLayout* l)
{
	group_box = new QGroupBox;
	group_box->setGeometry(QRect(9, 9, 15000, 200));
	QSizePolicy size_policy(QSizePolicy::Preferred, QSizePolicy::Preferred);
	group_box->setSizePolicy(size_policy);
   group_box->setAlignment(Qt::AlignCenter);
	group_box->setTitle(QString("#%1").arg(index));

	//value_label = new QLabel(group_box);
	//value_label->setText("0");
	//value_label->setGeometry(QRect(20, 50, 25, 8));

	lcd_number = new QLCDNumber(group_box);
	lcd_number->move(9, 9);
	lcd_number->setObjectName(QStringLiteral("lcd_number"));
	lcd_number->setDigitCount(2);
	lcd_number->setMode(QLCDNumber::Hex);
	lcd_number->setProperty("intValue", QVariant(0));

   lcd_number->show();
	group_box->show();
	//value_label->show();

	l->addWidget(group_box);
}

Cell::~Cell()
{
	std::cout << "cell destructor called" << std::endl;
	delete lcd_number;
	delete group_box;
}
//TODO: Find way to upüdate cells

void Cell::SetValue(int val)
{
	//value_label->setText(QString("%1").arg(val));
	lcd_number->setProperty("intValue", QVariant(val));
}

void Cell::Hide()
{
	group_box->hide();
	lcd_number->hide();
}
