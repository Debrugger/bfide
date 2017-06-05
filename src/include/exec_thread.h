#ifndef __EXEC_THREAD_H
#define __EXEC_THREAD_H

#include "sysinc.h"
#include "qtinc.h"
#include "bfgui.h"

typedef std::vector<Brainfuck::Command> Cmdvec ;

class Executer : public QObject
{
	Q_OBJECT;
	Bfgui* b;
	Cmdvec* c;

public:
	Executer(Bfgui* _b, Cmdvec* _c) : b(_b), c(_c) {};
public slots:
	void Exec();

signals:
	void Done();
};

#endif //__EXEC_THREAD_H
