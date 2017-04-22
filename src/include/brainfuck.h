#ifndef __BRAINFUCK_H
#define __BRAINFUCK_H

enum Type
{
	ADD, SUB, INC, DEC, BRO, BRC, PUT, GET
};

struct Command
{
	size_t matching_bracket;
	Type type;
};

class Brainfuck
{
	const int BrMismatch = 100;
	const int OffLimits = 200;
	const int UnknownCommand = 300;
	std::vector<int> cells;
	size_t current_cell;

public:
	Brainfuck();

	std::vector<Command> Parse(std::string);
	int Execute(std::vector<Command>, size_t); //returns the index of the next command to execute
	void ExecuteAll(std::vector<Command>);
	void Output(char);
	int GetInput();
	size_t CurrentCell() 			{ return current_cell; };
	size_t NbCells() 					{ return cells.size(); };
	int CellValue(size_t index)   { return cells.at(index); };
};


#endif //__BRAINFUCK_H
