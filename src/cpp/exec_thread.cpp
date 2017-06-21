#include "sysinc.h"
#include "exec_thread.h"

void Executer::Exec()
{
	printf("in exec thread\n");
	qDebug() << "PID: " << thread();
	size_t i = 0; 
	//std::cout << "c->size() = " << c->size();
	//printf("%d\n", c->at(c->size() - 1));
	try { while ((i = Brainfuck::Execute(b, &c, i)) < c.size()); }
	catch (Brainfuck::OffLimits)
	{
		std::cout << "Tried to execute off limit command. Exiting." << std::endl;
		exit(1);
	}
	emit Done();
}
