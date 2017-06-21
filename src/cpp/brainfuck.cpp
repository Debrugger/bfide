#include "sysinc.h"
#include "brainfuck.h"

Brainfuck::State::State()
{
	current_cell = 0;
}

Brainfuck::State::~State()
{
}

void Brainfuck::State::Output(char c)
{
	std::cout << c;
}

int Brainfuck::State::GetInput()
{
	std::string s;
	std::cin >> s;
	char c = s[0];
	return static_cast<int>(c);
}

std::vector<Brainfuck::Command> Brainfuck::Parse(std::string code)
{
	using Brainfuck::Command;
	std::unordered_map<char, CommandType> command_table = { {'+', ADD}, {'-', SUB}, {'>', INC}, {'<', DEC}, {'[', BRO}, {']', BRC}, {'.', PUT}, {',', GET} };
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

size_t Brainfuck::Execute(State* s, std::vector<Command>* c, size_t index)
{
	if (index > c->size())
		throw OffLimits();
	Command command = c->at(index);
	if (!s->cells.size()) s->cells.push_back(0);
   int* curr_val = &(s->cells[s->current_cell]);
	bool br = false;

	switch (command.type)
	{
		case ADD:
			if (*curr_val == 255)
				*curr_val = 0;
			else (*curr_val)++;
			s->OnIncVal();
			break;

		case SUB:
			if (!*curr_val)
				*curr_val = 255;
			else (*curr_val)--;
			s->OnDecVal();
			break;

		case INC:
			if (s->current_cell == s->cells.size() - 1)
				s->cells.resize(s->cells.size() + 1);
			s->current_cell++;
			s->OnIncPtr();
			break;

		case DEC:
			if (!s->current_cell)
				break;
			else
			{
				s->current_cell--;
				s->OnDecPtr();
			}
			break;

		case PUT:
			s->Output(static_cast<char>(*curr_val));
			break;

		case GET:
			*curr_val = s->GetInput();
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
