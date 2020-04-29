#include <iostream>
using namespace std;
double x1, x2, xb1, xb2,xpb1,xpb2,rpb,xp1,xp2, x11,x12,rb,r,r1;
double h=1, eps=0.0001;
	

double func (double &x1, double &x2){
	return x1*x1-2*x1+2*x2*x2-32*x2+134.5;
	}

void issled (int n){
	if (n==1) x11=x1+h;
	if (n==2) x12=x2+h;
	r1=func(x11,x12);
	if (r1<r) {
		x1=x11;
		x2=x12;
		r=r1;
	} else {
		if (n==1) x11=x1-h;
		if (n==2) x12=x2-h;
		r1=func(x11,x12);
		if (r1<r) {
			x1=x11;
			x2=x12;
			r=r1;
		}
	}	
}

int main() {	
	cout<<"\nHooke-Jeeves:\n"<<endl;
	int it=0;
	x1=-13; 
	x2=14;
	xb1=x1;
	xb2=x2;
	cout<<"Startovaya tochka: ("<<xb1<<" , "<<xb2<<")"<<endl;
	rb=func(xb1,xb2);
	
	while (h>eps){
		it++;
		x1=xb1;
		x2=xb2;
		r=rb;
		x11=x1;
		x12=x2;
		issled(1);
		issled(2);
		if (r < rb){
			while (1){
				xpb1=xb1;
				xpb2=xb2;
				rpb=rb;
				xb1=x1;
				xb2=x2;
				rb=r;
			
				xp1=xpb1+2*(xb1-xpb1);
				xp2=xpb2+2*(xb2-xpb2);
				
				x1=xp1;
				x2=xp2;
				x11=x1;
				x12=x2;
				
				issled(1);
				issled(2);
				if (r>=rb){
					break;
				}
			}	
		}
	h=h/10;
	}	
	cout<<"Tochka min: ("<<xb1<<" , "<<xb2<<")"<<endl;
	cout<<"Kolichestvo iteratsiy: "<<it<<endl;			
	return 0;
}
