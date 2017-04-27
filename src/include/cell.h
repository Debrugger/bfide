#ifndef __CELL_H
#define __CELL_H
#include "qtinc.h"

class Cell: public QWidget
{
	Q_OBJECT;
	QLabel* value_label;

	public:
	Cell(size_t, QHBoxLayout*);
	~Cell();
	void SetValue(int);
	void Hide();
};

#endif //__CELL_H
