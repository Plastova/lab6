#include<iostream>
#include<cmath>

using namespace std;

double func (double x1, double x2){
	return x1*x1-2*x1+2*x2*x2-32*x2+134.5;
}

double f(double x1,double x2,double alpha,double s1,double s2){
	return (x1+alpha*s1)*(x1+alpha*s1)-2*(x1+alpha*s1)+2*(x2+alpha*s2)*(x2+alpha*s2)-32*(x2+alpha*s2)+134.5;
}

double alpha=0,a,b,eps=0.01,x1,x2,new_x1,new_x2,S11,S12,S21,S22;	
double a11,a12,a21,a22,b11,b12,b21,b22;
double m1, m2, alph1, alph2, x21, x22,m11, m12, m21,m22;
double alpha1,alpha2, alpha3, alphamin, al, f1, f2, f3, denom, razn1, razn2, h=0.1;
int k=1, j=1, iter=0;
double h_sv=1, c, d, e;


void Svenn(double s1,double s2){
	h_sv=1;
	c=f(m1,m2,alpha-abs(h_sv),s1,s2);
	d=f(m1,m2,alpha,s1,s2);
	e=f(m1,m2,alpha+abs(h_sv),s1,s2);
	if (c<d&&d<e) h_sv=-h_sv;
		while (!(c>=d&&d<=e)){	
			alpha=alpha+h_sv/2;
			c=f(m1,m2,alpha-abs(h_sv),s1,s2);
			d=f(m1,m2,alpha,s1,s2);
			e=f(m1,m2,alpha+abs(h_sv),s1,s2);	
			}
		a=alpha-abs(h_sv);
		b=alpha+abs(h_sv);
}

void kvadr_interpol (double s1,double s2) {
	h=0.1;
	alpha1=(a+b)/2;
	do {		
		alpha2=alpha1+h;
		if (f(m1,m2,alpha1,s1,s2)>f(m1,m2,alpha2,s1,s2)) alpha3=alpha1+2*h;
		else alpha3=alpha1-h;
		
		f1=f(m1,m2,alpha1,s1,s2);
		f2=f(m1,m2,alpha2,s1,s2);
		f3=f(m1,m2,alpha3,s1,s2);
		
		denom=(alpha2-alpha3)*f1+(alpha3-alpha1)*f2+(alpha1-alpha2)*f3;
		if (f1<=f2&&f1<=f3) alphamin = alpha1;
		if (f2<=f1&&f2<=f3) alphamin = alpha2;
		if (f3<=f1&&f3<=f2) alphamin = alpha3;
		
		if (denom == 0) {
			alpha1 = alphamin;
			f1=f(m1,m2,alpha1,s1,s2);
			}
			
		al=0.5*((alpha2*alpha2-alpha3*alpha3)*f1+(alpha3*alpha3-alpha1*alpha1)*f2+(alpha1*alpha1-alpha2*alpha2)*f3)/denom;
					
		razn1=abs(f(m1,m2,alphamin,s1,s2)-f(m1,m2,al,s1,s2));
		razn2=abs(alphamin-al);
		if (razn1>=eps && razn2>=eps) {
			if (alpha1<=al && alpha3>=al) {
			if (f(m1,m2,alphamin,s1,s2)<f(m1,m2,al,s1,s2)) alpha1=alphamin;
			else alpha1=al;
		} else {
			alpha1=al;
			}	
		}
		} while (razn1>=eps && razn2>=eps);
	alpha = al;
}

void rozenbrok (){
	iter++;
	m1=x1; m2=x2; 

	Svenn(S11,S12);
	kvadr_interpol(S11,S12);
	alph1=alpha;
	m21=m1+alph1*S11; 
	m22=m2+alph1*S12; 

	m1=m21; m2=m22;
	Svenn(S21,S22);
	kvadr_interpol(S21,S22);
	alph2=alpha;
	m21=m1+alph2*S21; 
	m22=m2+alph2*S22;

	x21=m21;
	x22=m22;

	if (sqrt(pow(x21-x1,2)+pow(x22-x2,2))<eps){
		cout<<"Tochka minimuma: ("<<x21<<" , "<<x22<<")"<<endl;
		cout<<"Kolichestvo iteratsiy: "<<iter<<endl;
		} else {
			k=k+1;
			if (alph1==0) {a11=S11; a12=S12;}
				else {
					a11=alph1*S11+alph2*S21;
					a12=alph1*S12+alph2*S22;
					}
			
			if (alph2==0) {a21=S21; a22=S22;}
				else {
					a21=alph2*S21;
					a22=alph2*S22;
					}
			b11=a11; 
			b12=a12;
			
			b21=a21-S11*(a11*S11+a12*S12);
			b22=a22-S21*(a11*S11+a12*S12);
			
			S11=b11/sqrt(b11*b11+b12*b12);
			S12=b12/sqrt(b11*b11+b12*b12);
			
			S21=b21/sqrt(b21*b21+b22*b22);
			S22=b22/sqrt(b21*b21+b22*b22);
			
			x1=x21;
			x2=x22;
			rozenbrok ();
			}
}

 
int main (){	
	cout<<"\nRozenbrok:\n"<<endl;
	x1=-13;
	x2=14;
	cout<<"Nachalnaya tochka: ("<<x1<<" , "<<x2<<")"<<endl;	
	S11=0;
	S12=1;	
	S21=1;
	S22=0;
	
	rozenbrok ();	
	return 0;
} 
 
 
 
 
 
 
 
 
 
 
 



