#include <iostream>
#include "mycalc.h"
#ifdef __unix__
#include "cview.h"
#endif

using namespace std;

// returns true if it should not exit
bool calculate(string op, mycalc* mc)
{
	switch(op[0])
	{
	case '=':
		break;
	case 'q':
		return false;
	case '/':
		mc->div();
		break;
	case '*':
		mc->mul();
		break;
	case '-':
		mc->sub();
		break;
	case '+':
		mc->add();
		break;
	default:
		mc->c_push(stoi(op));
	}
	return true;
}

void output(mycalc* mc)
{
	std::cout<< "  X: "<<mc->c_get_x()<<std::endl
	         << "  Y: "<<mc->c_get_y()<<std::endl
	         << "  Z: "<<mc->c_get_z()<<std::endl;
}

int main(int argc, char *argv[])
{
	mycalc *my_calc = new mycalc();

#ifdef __unix__
	if(argc < 2)
	{
		cview *v = new cview(my_calc);

		my_calc->reg(v);

		delete v;
	} else {
#endif
		string op = "="; //deprecates exit on first run
		
		while(calculate(op, my_calc))
		{
			output(my_calc);
			cout<<"Input: ";
			cin>>op;
		}

#ifdef __unix__
	}
#endif

	delete my_calc;
	
	cout<<"Exited."<<endl;

	return 0;
}
