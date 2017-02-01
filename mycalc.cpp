#include "mycalc.h"
#ifdef __unix__
#include "cview.h"
#endif
#include <iostream>
#define TYPE int

TYPE mycalc::c_get_x()
{
	return this->c_x;
}

TYPE mycalc::c_get_y()
{
	return this->c_y;
}

TYPE mycalc::c_get_z()
{
	return this->c_z;
}

void mycalc::c_push(TYPE x)
{
	this->c_rotate_push();
	this->c_x = x;
}

TYPE mycalc::c_pop()
{
	return this->c_rotate_pop();
}

TYPE mycalc::c_rotate_pop()
{
	TYPE buf = this->c_x;
	this->c_x = this->c_y;
	this->c_y = this->c_z;
	this->c_z = 0;
	return buf;
}

void mycalc::c_rotate_push()
{
	this->c_z = this->c_y;
	this->c_y = this->c_x;
}

void mycalc::add()
{
	this->add(this->c_rotate_pop());
}

void mycalc::add(TYPE y)
{
	this->c_x += y;
}

void mycalc::sub()
{
	this->sub(this->c_rotate_pop());
}

void mycalc::sub(TYPE y)
{
	this->c_x -= y;
}

void mycalc::mul()
{
	this->mul(this->c_rotate_pop());
}

void mycalc::mul(TYPE y)
{
	this->c_x *= y;
}

void mycalc::div()
{
	this->div(this->c_rotate_pop());
}

void mycalc::div(TYPE y)
{
	this->c_x /= y;
}

#ifdef __unix__
void mycalc::reg(cview *v)
{
	this->v = v;
}

std::string mycalc::get_display()
{
	std::string display = std::to_string(c_x) + " " + std::to_string(c_y) + " " + std::to_string(c_z);
	return display;
}
#endif
