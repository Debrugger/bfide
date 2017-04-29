#ifndef __CELL_H
#define __CELL_H
#include "qtinc.h"

class Cell: public QWidget
{
	Q_OBJECT;
	QLabel* index_label;
	QLabel* value_label;

	public:
	Cell(size_t, QVBoxLayout*, QVBoxLayout*);
	~Cell();
	void SetValue(int);
	void Hide();
};

#endif //__CELL_H
