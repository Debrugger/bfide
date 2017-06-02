#ifndef __BRAINFUCK_H
#define __BRAINFUCK_H

namespace Brainfuck
{
	enum CommandType
	{
		ADD, SUB, INC, DEC, BRO, BRC, PUT, GET
	};

	struct Command
	{
		size_t matching_bracket;
		CommandType type;
	};
	class OffLimits{};

	class Interpreter
	{
		class BrMismatch{};
		class UnknownCommand{};

		protected:
		std::vector<short> cells;
		size_t current_cell;
		std::unordered_map<char, CommandType> command_table = { {'+', ADD}, {'-', SUB}, {'>', INC}, {'<', DEC}, {'[', BRO}, {']', BRC}, {'.', PUT}, {',', GET} };
		virtual void Output(char);
		virtual int GetInput();
		virtual void OnIncPtr() = 0;
		virtual void OnDecPtr() = 0;
		virtual void OnIncVal() = 0;
		virtual void OnDecVal() = 0;

		public:
		Interpreter();
		virtual ~Interpreter();
		std::vector<Brainfuck::Command> Parse(std::string);
		size_t Execute(std::vector<Brainfuck::Command>*, size_t); //returns the index of the next command to execute
		size_t CurrentCell() 			{ return current_cell; };
		size_t NbCells() 					{ return cells.size(); };
		int CellValue(size_t index)   { return cells.at(index); };
		bool stop;
	};
}

typedef std::vector<Brainfuck::Command> Cmdvec ;
#endif //__BRAINFUCK_H
