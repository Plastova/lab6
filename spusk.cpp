#include <iostream>
#include <cmath>
#include <fstream>
using namespace std;
double x1_fixed,x2_fixed, left_border, right_border, eps=0.0001;

double func (double x1, double x2){
	return x1*x1-2*x1+2*x2*x2-32*x2+134.5;
	}

	
double test_f(int n, double x){
	if (n==1) return x*x-2*x+2*x2_fixed*x2_fixed-32*x2_fixed+134.5;
	if (n==2) return x1_fixed*x1_fixed-2*x1_fixed+2*x*x-32*x+134.5; 
	}
	
double kvadr_interpol (double a, double b, double h, int n) {
	double x1,x2,x3, xmin, x, f1, f2, f3, denom, razn1, razn2;
	int it=0;
	x1=(a+b)/2;
	do {
		it++;
		x2=x1+h;
		if (test_f(n,x1)>test_f(n,x2)) x3=x1+2*h;
		else x3=x1-h;
		
		f1=test_f(n,x1);
		f2=test_f(n,x2);
		f3=test_f(n,x3);
		
		denom=(x2-x3)*f1+(x3-x1)*f2+(x1-x2)*f3;
		if (f1<=f2&&f1<=f3) xmin = x1;
		if (f2<=f1&&f2<=f3) xmin = x2;
		if (f3<=f1&&f3<=f2) xmin = x3;
		
		if (denom == 0) {
			x1 = xmin;
			f1=test_f(n,x1);
			}
			
		x=0.5*((x2*x2-x3*x3)*f1+(x3*x3-x1*x1)*f2+(x1*x1-x2*x2)*f3)/denom;
					
		razn1=abs(test_f(n,xmin)-test_f(n,x));
		razn2=abs(xmin-x);
		if (razn1>=eps && razn2>=eps) {
			if (x1<=x && x3>=x) {
			if (test_f(n,xmin)<test_f(n,x)) x1=xmin;
			else x1=x;
		} else {
			x1=x;
			}	
		}
		} while (razn1>=eps && razn2>=eps);
	cout<<"Kvadratichnaya interpolytsiya: kolichestvo iteratsiy="<<it<<endl;
	cout<<endl;
	return x;
}


void Svenn (double x0, double h,int n){
	double a, b, c;
	int it =0;
	a=test_f(n,x0-abs(h));
	b=test_f(n,x0);
	c=test_f(n,x0+abs(h));
	if (a<=b&&b>=c) cout<<"Error: funktsiya ne unimodalna v okrestnosti tochki x0."<<endl;
	if (a<b&&b<c) h=-h;
	while (!(a>=b&&b<=c)){
		it++;
		x0=x0+h/2;
		a=test_f(n,x0-abs(h));
		b=test_f(n,x0);
		c=test_f(n,x0+abs(h));		
		}
	left_border=x0-abs(h);
	right_border=x0+abs(h);
	cout<<"Metod Svenna: kolichestvo iteratsiy="<<it<<endl;
	}
	
void pokoord_spusk () {
	int it=0;
	double x1_fixed_0, x2_fixed_0;
	ofstream fout;
	fout.open("points.txt");
	fout<<x1_fixed<<" "<<x2_fixed<<endl;
	x1_fixed_0 = x1_fixed;
	x2_fixed_0 = x2_fixed;
	do {
		Svenn (x1_fixed,1,1);
		x1_fixed = kvadr_interpol (left_border, right_border, 0.1,1);
		fout<<x1_fixed<<" "<<x2_fixed<<endl;
		it++;	
		x1_fixed_0 = x1_fixed;	
		Svenn (x2_fixed,1,2);
		x2_fixed = kvadr_interpol (left_border, right_border, 0.1,2);
		fout<<x1_fixed<<" "<<x2_fixed<<endl;
		it++;
		x2_fixed_0 = x2_fixed;
		}while (abs(func(x1_fixed,x2_fixed)-func(x1_fixed_0,x2_fixed_0))>=eps);

	cout<<"\nPokoordinatniy spusk: kolichestvo iteratsiy="<<it<<endl;
	cout<<"\nMinimum funktsii: "<<func(x1_fixed,x2_fixed)<<endl;
	cout<<"Tochka min: x1="<<x1_fixed<<" x2="<<x2_fixed<<endl;	
	
	fout.close();
	}


int main () {
	x1_fixed = -13;
	x2_fixed = 14; 
	pokoord_spusk ();
	return 0;
	}

