// $NAME <mak191@zips.uakron.edu>

#include "machine.hpp"

#include <map>
#include <iostream>
#include <sstream>


// Returns the op code found in the first n characters of s. Throws an 
// exception if the operation name is invalid.
static int get_op(String const& s)
{
	// A lookup table that maps from strings to opcodes.
	static std::map<String, int> ops{
		{ "push", push_op },
		{ "pop", pop_op },
		{ "copy", copy_op },
		{ "add", add_op },
		{ "sub", sub_op },
		{ "mul", mul_op },
		{ "div", div_op },
		{ "rem", rem_op },
		{ "print", print_op },
		{ "read", read_op },
		{ "halt", halt_op },
	};

	auto iter = ops.find(s);
	if (iter == ops.end()) {
		String msg = "no such opcode '" + s + "'";
		//throw std::runtime_error(msg);
		exit(-1);
	}
	return iter->second;
}


int get_arg(String const& s)
{
	if (s.empty())
		return 0;
	else
		return stoi(s);
}


Machine::Machine(std::istream& is)
{
	// Parse instructions from input.
	while (is) {
		String s;
		if (!getline(is, s))
			break;

		// Search for a ';', indicating a comment and strip that from the line.
		std::size_t k = s.find(';');
		if (k != -1)
			s = s.substr(0, k);

		// Skip empty lines.
		if (s.empty())
			continue;

		// Parse out the opcode and operand.
		int n = s.find(" \t\n\0");
		String opstr = s.substr(0, n);
		String argstr;
		int m = s.find("0123456789", n + 1);
		if (n != -1)
			argstr = s.substr(m, s.find(" \t\n\0"));



		int op = get_op(opstr);
		int arg = get_arg(argstr);
		Instruction ins(op, arg);
		prog.push_back(ins);
	}
}


void Machine::run()
{
	// Start the pc at the first instruction.
	pc = 0;

	while (pc != prog.size()) {

		// Get the next instruction.
		Instruction ins = fetch();

		// "Decode" and execute the instruction.
		switch (ins.op) {
		case push_op:
			push(ins.arg);
			break;
		case pop_op:
			pop();
			break;
		case copy_op:
			copy();
			break;
		case add_op:
			add();
			break;
		case sub_op:
			sub();
			break;
		case mul_op:
			mul();
			break;
		case div_op:
			div();
			break;
		case rem_op:
			rem();
			break;
		case print_op:
			print();
			break;
		case read_op:
			read();
			break;
		case halt_op:
			halt();
			break;
		}
	}
}


Instruction Machine::fetch()
{
	return prog[pc++];
}


int Machine::top() 
{
	// TODO: Implement me!
	return o_stack.top();
	throw std::logic_error("not implemented");
}


void Machine::push(int n)
{
	// TODO: Implement me!
	o_stack.push_back(n);
	throw std::logic_error("not implemented");
}


int Machine::pop()
{
	// TODO: Implement me!
	return o_stack.pop_back();
	throw std::logic_error("not implemented");
}


void Machine::copy()
{
	// TODO: Implement me!
	o_stack.push_back(o_stack.top());
	throw std::logic_error("not implemented");
}


void Machine::add()
{
	// TODO: Implement me!
	o_stack.push_back(o_stack.pop_back() + o_stack.pop_back());
	throw std::logic_error("not implemented");
}


void Machine::sub()
{
	// TODO: Implement me!
	o_stack.push_back((o_stack.pop_back() * (-1)) + o_stack.pop_back());
	throw std::logic_error("not implemented");
}


void Machine::mul()
{
	// TODO: Implement me!
	o_stack.push_back(o_stack.pop_back() * o_stack.pop_back());
	throw std::logic_error("not implemented");
}


void Machine::div()
{
	// TODO: Implement me!
	int one = o_stack.pop_back();
	int two = o_stack.pop_back();
	o_stack.push_back(two / one);
	throw std::logic_error("not implemented");
}


void Machine::rem()
{
	// TODO: Implement me!
	int one = o_stack.pop_back();
	int two = o_stack.pop_back();
	o_stack.push_back(two % one);
	throw std::logic_error("not implemented");
}


void Machine::print()
{
	// TODO: Implement me!
	std::cout << o_stack.pop_back();
	throw std::logic_error("not implemented");
}


void Machine::read()
{
	// TODO: Implement me!
	int input;
	std::cin >> input;
	o_stack.push_back(input);
	throw std::logic_error("not implemented");
}


void Machine::halt()
{
	pc = prog.size();
}
