#include <iostream>
#define _USE_MATH_DEFINES 
#include <cmath>
#include <ctime>

using namespace std;

double func (double x1, double x2){
return x1*x1-2*x1+2*x2*x2-32*x2+134.5;
}

int main () {
	double alpha;
	double x10, x20, x11, x21, h=1, eps=0.01;
	int it=0;
	x10=-13;
	x20=14;
	cout<<"Startovaya tochka: "<<"("<<x10<<" , "<<x20<<")"<<endl<<endl;
	srand(time( 0 ));
	alpha=(M_PI*rand())/180;
	x11=x10+h*cos(alpha);
	
	x21=x20+h*sin(alpha);
	while (h>eps){
		it++;
		while (func(x11,x21)>=func(x10,x20)) { 
			h*=0.7;
			alpha=(M_PI*rand())/180;
			x10=x11;
			x20=x21;
			x11=x10+h*cos(alpha);
			x21=x20+h*sin(alpha);
		}
		while (func(x11,x21)<func(x10,x20)){
			h*=1.3;
			x10=x11;
			x20=x21;
			x11=x10+h*cos(alpha);
			x21=x20+h*sin(alpha);
			}
	}
	cout<<"Tochka min: "<<"("<<x11<<" , "<<x21<<")"<<endl<<endl;
	cout<<"Kolichestvo iteratsiy: "<<it<<endl;
	return 0;
	}
