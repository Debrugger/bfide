#include "sysinc.h"
#include "qtinc.h"
#include "brainfuck.h"
#include "mainwindow.h"
#include "globals.h"

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
				//std::cout << "Size of commands: " << commands.size() << std::endl;
				break;
			case '[':
				command.type = command_table[c];
				commands.push_back(command);
				brackets.push_back(commands.size() - 1); //push index pf bracket onto bracket stack
				//std::cout << "opening bracket found, pushing_back index: " << commands.size() - 1 << std::endl;
				break;
			case ']':
				command.type = command_table[c];
				if (brackets.size() == 0) //means diff number of open and close brackets
					throw(BrMismatch);
				else
				{
					command.matching_bracket = brackets.back(); //matching opening bracket is the last on the stack
					//std::cout << "matching opening bracket: " << command.matching_bracket << std::endl;
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

   if (!cell_boxes.size())
	{
		cell_boxes.push_back(new Cell(0, mw->index_layout, mw->value_layout));
	}

	switch (command.type)
	{
		case ADD:
			if (*curr_val == 255)
				*curr_val = 0;
			else (*curr_val)++;
			cell_boxes[current_cell]->SetValue(*curr_val);
			break;

		case SUB:
			if (!*curr_val)
				*curr_val = 255;
			else (*curr_val)--;
			cell_boxes[current_cell]->SetValue(*curr_val);
			break;

		case INC:
			if (current_cell == cells.size() - 1)
			{
				cells.resize(cells.size() + 1);
				cell_boxes.push_back(new Cell(current_cell + 1, mw->index_layout, mw->value_layout));
			}
			current_cell++;
			break;

		case DEC:
			if (!current_cell)
			{
				break;
			}
			else current_cell--;
			break;

		case PUT:
			Output(static_cast<char>(*curr_val));
			break;

		case GET:
			*curr_val = GetInput();
			cell_boxes[current_cell]->SetValue(*curr_val);
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
			//throw (UnknownCommand);
	}
	if (!br)
		return index + 1;
	return -1;
}

void Brainfuck::ClearCells()
{
   for (auto it : cell_boxes)
	{
		it->Hide();
		delete it;
	}
	cell_boxes.clear(); 
}

void Brainfuck::ExecuteAll(std::vector<Command> commands)
{
	stop = false;
   ClearCells();
	size_t i = 0;

	mw->terminal_edit->clear();
	mw->button_exec->setEnabled(false);
	mw->button_stop->setEnabled(true);
	while (i < commands.size() && !stop)
	{
		std::cout << "Executed " << i;
		i = Execute(commands, i);
		//std::cout << ", next " << i << std::endl;
		if (i < 0)
		{
			mw->statusBar()->showMessage("Error executing code.");
			break;
		}
	}
	//std::cout << "Out of execall loop at command " << i << "loop condition is " << (i < commands.size()) << std::endl;
	mw->button_exec->setEnabled(true);
	mw->button_stop->setEnabled(false);
}

void Brainfuck::Output(char c)
{
	//std::cout << "Output called" << std::endl;
	std::cout << c;
	QString s;
	s = c;
	mw->terminal_edit->moveCursor(QTextCursor::End);
	mw->terminal_edit->textCursor().insertText(s);
}

int Brainfuck::GetInput()
{
   mw->input_edit->setReadOnly(false);
	QString s;
	QEventLoop loop;
	QWidget::connect(mw->input_edit, SIGNAL(editingFinished()), &loop, SLOT(quit()));
	loop.exec();

   int ret = static_cast<int>(mw->input_edit->text().at(0).toLatin1());
	mw->input_edit->setReadOnly(true);
	mw->input_edit->clear();
	return ret;
}
