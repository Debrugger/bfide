#ifndef __BFGUI_H
#define __BFGUI_H

extern bool stop;

class Bfgui : public Brainfuck::BrainfuckInterpreter
{
public:
	Bfgui();
	~Bfgui();

	int GetInput(QLineEdit* edit);
	void Output(char c, QPlainTextEdit* edit);
	void ExecuteAll(Cmdvec c);
};

#endif //__BFGUI_H
