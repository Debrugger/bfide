#include "sysinc.h"
#include "brainfuck.h"


Brainfuck::Interpreter::Interpreter()
{
	current_cell = 0;
}

Brainfuck::Interpreter::~Interpreter()
{
}

std::vector<Brainfuck::Command> Brainfuck::Interpreter::Parse(std::string code)
{
	using Brainfuck::Command;
	std::vector<Command> commands;
	std::vector<size_t> brackets;

	for (char& c : code)
	{
		Command command;
		switch (c)
		{
			case '+':
			case '-':
			case '>':
			case '<':
			case '.':
			case ',':
				command.type = command_table[c];
				commands.push_back(command);
				break;
			case '[':
				command.type = command_table[c];
				commands.push_back(command);
				brackets.push_back(commands.size() - 1); //push index pf bracket onto bracket stack
				break;
			case ']':
				command.type = command_table[c];
				if (brackets.size() == 0) //means diff number of open and close brackets
					throw BrMismatch();
				else
				{
					command.matching_bracket = brackets.back(); //matching opening bracket is the last on the stack
					brackets.pop_back();
					commands[command.matching_bracket].matching_bracket = commands.size() - 1; //give the opening bracket its matching one too
				}
				commands.push_back(command);
				break;

			default:
				break;
		}
	}

	return commands;
}

size_t Brainfuck::Interpreter::Execute(std::vector<Command>* c, size_t index)
{
	if (index > c->size())
		throw OffLimits();
	Command command = c->at(index);
	if (!cells.size()) cells.push_back(0);
   short int* curr_val = &cells[current_cell];
	bool br = false;

	switch (command.type)
	{
		case ADD:
			if (*curr_val == 255)
				*curr_val = 0;
			else (*curr_val)++;
			OnIncVal();
			break;

		case SUB:
			if (!*curr_val)
				*curr_val = 255;
			else (*curr_val)--;
			OnDecVal();
			break;

		case INC:
			if (current_cell == cells.size() - 1)
				cells.resize(cells.size() + 1);
			current_cell++;
			OnIncPtr();
			break;

		case DEC:
			if (!current_cell)
				break;
			else
			{
				current_cell--;
				OnDecPtr();
			}
			break;

		case PUT:
			Output(static_cast<char>(*curr_val));
			break;

		case GET:
			*curr_val = GetInput();
			break;

		case BRO:
			br = true;
			if (*curr_val == 0)
				return command.matching_bracket + 1;
			else return index + 1;
			break;

		case BRC:
			br = true;

         if (*curr_val == 0)
				return index + 1;
			else return command.matching_bracket + 1;
			break;

		default:
			return -1;
	}
	if (!br)
		return index + 1;
	return -1;
}

void Brainfuck::Interpreter::Output(char c)
{
	std::cout << c;
}

int Brainfuck::Interpreter::GetInput()
{
	std::string s;
	std::cin >> s;
	char c = s[0];
	return static_cast<int>(c);
}
