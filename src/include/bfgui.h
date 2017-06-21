#ifndef __BFGUI_H
#define __BFGUI_H

#include "qtinc.h"
#include "brainfuck.h"

class Cell;
class Bfgui : public QObject, public Brainfuck::State 
{
	Q_OBJECT;
	std::vector<Cell*> cell_boxes;

	void OnIncPtr();
	void OnDecPtr();
	void OnIncVal();
	void OnDecVal();

	QPlainTextEdit* out_edit;
	QLineEdit* in_edit;
	QVBoxLayout* il;
	QVBoxLayout* vl;

public:
	Bfgui(QPlainTextEdit* _out_edit, QLineEdit* _in_edit, QVBoxLayout* _il, QVBoxLayout* _vl);
	virtual ~Bfgui();

	int GetInput();
	virtual void Output(char c);
	//virtual void ExecuteAll(Cmdvec* c);
	virtual void ClearCells();
	void Reset();
};

#endif //__BFGUI_H
