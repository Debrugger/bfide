#ifndef __CELL_H
#define __CELL_H
#include "qtinc.h"

class Cell: public QWidget
{
	Q_OBJECT;
	QGroupBox* group_box;
	QLabel* value_label;
	QLCDNumber* lcd_number;

	public:
	Cell(size_t, QHBoxLayout*);
	~Cell();
	void SetValue(int);
	void Hide();
};

#endif //__CELL_H
