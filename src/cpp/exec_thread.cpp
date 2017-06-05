#include "sysinc.h"
#include "qtinc.h"
//#include "brainfuck.h"
//#include "cell.h"
//#include "bfgui.h"
#include "exec_thread.h"

void Executer::Exec()
{
	size_t i = 0; 
	try { while ((i = Brainfuck::Execute(b, c, i)) < c->size()); }
	catch (Brainfuck::OffLimits)
	{
		std::cout << "Tried to execute off limit command. Exiting." << std::endl;
		exit(1);
	}
	emit Done();
}
