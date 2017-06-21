#ifndef __BRAINFUCK_H
#define __BRAINFUCK_H

#include "sysinc.h"

namespace Brainfuck
{
	enum CommandType { ADD, SUB, INC, DEC, BRO, BRC, PUT, GET };
	struct Command
	{
		size_t matching_bracket;
		CommandType type;
	};

	class State
	{
		protected:
		std::vector<int> cells;
		size_t current_cell;
		virtual void Output(char);
		virtual int GetInput();
		virtual void OnIncPtr() = 0;
		virtual void OnDecPtr() = 0;
		virtual void OnIncVal() = 0;
		virtual void OnDecVal() = 0;

		public:
		State();
		virtual ~State();
		size_t CurrentCell() 			{ return current_cell; };
		size_t NbCells() 					{ return cells.size(); };
		int CellValue(size_t index)   { return cells.at(index); };

		friend size_t Execute(State* s, std::vector<Brainfuck::Command>*, size_t);
	};

	std::vector<Brainfuck::Command> Parse(std::string);
	size_t Execute(State* s, std::vector<Brainfuck::Command>*, size_t);


	class OffLimits{};
	class BrMismatch{};
	class UnknownCommand{};

}

typedef std::vector<Brainfuck::Command> Cmdvec ;
#endif //__BRAINFUCK_H
