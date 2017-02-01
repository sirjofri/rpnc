#ifndef MYCALC_H
#define MYCALC_H
#define TYPE int

class mycalc;

#include <string>
#ifdef __unix__
#include "cview.h"
#endif

class mycalc
{
private:
	TYPE c_x;
	TYPE c_y;
	TYPE c_z;
	TYPE c_a;
	TYPE c_rotate_pop();
	void c_rotate_push();
#ifdef __unix__
	cview *v;
#endif
public:
	TYPE c_get_x();
	TYPE c_get_y();
	TYPE c_get_z();
	void c_push(TYPE x);
	TYPE c_pop();
	void add();
	void add(TYPE y);
	void sub();
	void sub(TYPE y);
	void mul();
	void mul(TYPE y);
	void div();
	void div(TYPE y);
#ifdef __unix__
	void reg(cview *v);
	std::string get_display();
#endif
};

#endif
