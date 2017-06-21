#ifndef __CELL_H
#define __CELL_H
#include "qtinc.h"

class Cell: public QWidget
{
	Q_OBJECT;
	size_t index;
	int value;
	bool highlighted;

	public:
	QLabel* index_label;
	QLabel* value_label;
	Cell(size_t, QVBoxLayout* il, QVBoxLayout* vl);
	~Cell();
	void SetValue(int);
	void SetHighlighted(bool);
	void Hide();
};

#endif //__CELL_H
