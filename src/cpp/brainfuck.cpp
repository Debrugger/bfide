#include "sysinc.h"
#include "qtinc.h"
#include "brainfuck.h"

std::unordered_map<char, Type> command_table = { {'+', ADD}, {'-', SUB}, {'>', INC}, {'<', DEC}, {'[', BRO}, {']', BRC}, {'.', PUT}, {',', GET} };

Brainfuck::Brainfuck()
{
	current_cell = 0;
	cells.resize(current_cell+1);
}

std::vector<Command> Brainfuck::Parse(std::string code)
{
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
				std::cout << "Size of commands: " << commands.size() << std::endl;
				break;
			case '[':
				command.type = command_table[c];
				commands.push_back(command);
				brackets.push_back(commands.size() - 1); //push index pf bracket onto bracket stack
				std::cout << "opening bracket found, pushing_back index: " << commands.size() - 1 << std::endl;
				break;
			case ']':
				command.type = command_table[c];
				if (brackets.size() == 0) //means diff number of open and close brackets
					throw(BrMismatch);
				else
				{
					command.matching_bracket = brackets.back(); //matching opening bracket is the last on the stack
					std::cout << "matching opening bracket: " << command.matching_bracket << std::endl;
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

int Brainfuck::Execute(std::vector<Command> c, size_t index)
{
	Command command = c[index];
   int* curr_val = &cells[current_cell];
	bool br = false;

	switch (command.type)
	{
		case ADD:
			std::cout << "add" << std::endl;
			if (*curr_val == 255)
				*curr_val = 0;
			else (*curr_val)++;
			break;

		case SUB:
			std::cout << "sub" << std::endl;
			if (!*curr_val)
				*curr_val = 255;
			else (*curr_val)--;
			break;

		case INC:
			std::cout << "inc" << std::endl;
			if (current_cell == cells.size() - 1)
				cells.resize(cells.size() + 1);
			current_cell++;
			break;

		case DEC:
			std::cout << "dec" << std::endl;
			if (!current_cell)
			{
				break;
			}
			else current_cell--;
			break;

		case PUT:
			std::cout << "put" << std::endl;
			Output(static_cast<char>(*curr_val));
			break;

		case GET:
			std::cout << "get" << std::endl;
			*curr_val = GetInput();
			break;

		case BRO:
			std::cout << "bro" << std::endl;
			br = true;
			if (*curr_val == 0)
				return command.matching_bracket + 1;
			else return index + 1;
			break;

		case BRC:
			std::cout << "brc" << std::endl;
			br = true;
			std::cout << "*curr_val: " << *curr_val << std::endl;
			std::cout << "index: " << index << std::endl;
			std::cout << "matching bracket: " << command.matching_bracket << std::endl;

         if (*curr_val == 0)
				return index + 1;
			else return command.matching_bracket + 1;
			break;

		default:
			throw (UnknownCommand);
	}
	if (!br)
		return index + 1;
	return -1;
}

void Brainfuck::ExecuteAll(std::vector<Command> commands)
{
	size_t i = 0;
	while (i < commands.size())
	{
		i = Execute(commands, i);
		std::cout << i << std::endl;
	} 
}

void Brainfuck::Output(char c)
{
	std::cout << "Output called" << std::endl;
	std::cout << "output character: " << c << std::endl;
}

int Brainfuck::GetInput()
{
	return 'C';
}
