#ifndef __CELL_H
#define __CELL_H
#include "qtinc.h"

class Cell: public QWidget
{
	Q_OBJECT;
	QGroupBox* group_box;
	QLabel* index_label;
	public:
	Cell(size_t, QHBoxLayout*);
	~Cell();
};

#endif //__CELL_H
