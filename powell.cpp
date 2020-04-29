#include <iostream>
#include <cmath>

using namespace std;

double alpha=0,a,b,eps=0.0001,x1,x2,x21,x22,s1,s2,x11,x12;
double alph, h_sv=16, c, d, e, alp;
double alpha1,alpha2, alpha3, alphamin, al, f1, f2, f3, denom, razn1, razn2, h=0.1;
int iter=0;

double func (double x1, double x2){
	return x1*x1-2*x1+2*x2*x2-32*x2+134.5;
}

double f(double alpha){
	return (x1+alpha*s1)*(x1+alpha*s1)-2*(x1+alpha*s1)+2*(x2+alpha*s2)*(x2+alpha*s2)-32*(x2+alpha*s2)+134.5;
}

void Svenn (double alpha) { 
	c=f(alpha-abs(h_sv));
	d=f(alpha);
	e=f(alpha+abs(h_sv));
	if (c<d&&d<e) h_sv=-h_sv;
		while (!(c>=d&&d<=e)){	
			alpha=alpha+h_sv/2;
			c=f(alpha-abs(h_sv));
			d=f(alpha);
			e=f(alpha+abs(h_sv));	
			}
		a=alpha-abs(h_sv);
		b=alpha+abs(h_sv);
}
	
double kvadr_interpol (double alpha) {	
	alpha1=(a+b)/2;
	do {
		alpha2=alpha1+h;
		if (f(alpha1)>f(alpha2)) alpha3=alpha1+2*h;
		else alpha3=alpha1-h;
		
		f1=f(alpha1);
		f2=f(alpha2);
		f3=f(alpha3);
				
		denom=(alpha2-alpha3)*f1+(alpha3-alpha1)*f2+(alpha1-alpha2)*f3;
		if (f1<=f2&&f1<=f3) alphamin = alpha1;
		if (f2<=f1&&f2<=f3) alphamin = alpha2;
		if (f3<=f1&&f3<=f2) alphamin = alpha3;
		
		if (denom == 0) {
			alpha1 = alphamin;
			f1=f(alpha1);
			}
			
		al=0.5*((alpha2*alpha2-alpha3*alpha3)*f1+(alpha3*alpha3-alpha1*alpha1)*f2+(alpha1*alpha1-alpha2*alpha2)*f3)/denom;
					
		razn1=abs(f(alphamin)-f(al));
		razn2=abs(alphamin-al);
		if (razn1>=eps && razn2>=eps) {
			if (alpha1<=al && alpha3>=al) {
			if (f(alphamin)<f(al)) alpha1=alphamin;
			else alpha1=al;
		} else {
			alpha1=al;
			}	
		}
		} while (razn1>=eps && razn2>=eps);
	return al;	
}

void Powel(){
	iter++;
	s1=0;
	s2=1;	
	Svenn(alpha);
	alp=kvadr_interpol(alpha);	
	x11=x1+alp*s1;
	x12=x2+alp*s2;
   
    s1=1;
	s2=0;	
	x1=x11;
	x2=x12;
	Svenn(alpha);
	alp=kvadr_interpol(alpha);	
	x21=x1+alp*s1;
    x22=x2+alp*s2; 
   
    s1=0;
	s2=1;	
	x1=x21;
	x2=x22;	
	Svenn(alpha);
	alp = kvadr_interpol(alpha);
	x21=x1+alp*s1;
    x22=x2+alp*s2;
    
    if(func(2*x21-x11,2*x22-x12)>=func(x11,x12)){ 
    	x1=x21;
    	x2=x22;    	
	}else{
		s1=x21-x11;
		s2=x22-x12;		
		Svenn(alpha);
		alp=kvadr_interpol(alpha);	
		x21=x1+alp*s1;
    	x22=x2+alp*s2;
    	
		if(abs(func(x21,x22)-func(x1,x2))>=eps){
			x1=x21;
			x2=x22;    	
			Powel();
		} else {
			x1=x21;
			x2=x22;
			}
	}	
}

int main () {		
	cout<<"\nPowell:\n"<<endl;
	x1=-13;
	x2=14;
	cout<<"Nachalnaya tochka: ("<<x1<<" , "<<x2<<")"<<endl;
	s1=0;
	s2=1;
	Powel();
	cout<<"Tochka minimuma: ("<<x1<<" , "<<x2<<")"<<endl;
	cout<<"Kolichestvo iteratsiy: "<<iter<<endl;
	return 0;
	}

