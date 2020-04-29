#include <iostream>

using namespace std;
const double eps = 0.00001;


double f(double x1, double x2) {
	return x1*x1-2*x1+2*x2*x2-32*x2+134.5;
}


int main () {
	cout<<"\nNelder-Mid:\n"<<endl;
	double x[7][5];
	double s;
	int a, b, c, it=0;
	x[0][0] = 1;
	x[0][1] = -6;
	x[1][0] = 0;
	x[1][1] = 8;
	x[2][0] = -13;
	x[2][1] = 14;
 
	do {
	it++;
	a = 0;
	b = 0;
	c = 0;
	double max = f(x[0][0], x[0][1]);
	double min = f(x[0][0], x[0][1]);
	for (int k = 1; k <= 2; k ++) {
		if (f(x[k][0], x[k][1]) < min) {
		   min = f(x[k][0], x[k][1]);
		   b = k;
		}
	    if (f(x[k][0], x[k][1]) > max) {
		   max = f(x[k][0], x[k][1]);
		   a = k;
	    }
    }
	max = f(x[0][0], x[0][1]);
	for (int k = 1; k <= 2; k ++) {
	   if ((f(x[k][0], x[k][1]) > max) && (k != a)) {
		   max = f(x[k][0], x[k][1]);
		   c = k;
	   }
    }
	x[3][0] = (x[0][0] + x[1][0] + x[2][0] - x[a][0]) / 2;
	x[3][1] = (x[0][1] + x[1][1] + x[2][1] - x[a][1]) / 2;


   for (int i = 0; i < 2; i++)
		x[4][i] = 2 * x[3][i] - x[a][i];

   if (f(x[4][0], x[4][1]) < f(x[b][0], x[b][1])) {
	   x[5][0] = x[3][0] + 2 * (x[4][0] - x[3][0]);
	   x[5][1] = x[3][1] + 2 * (x[4][1] - x[3][1]);

	   if (f(x[5][0], x[5][1]) < f(x[b][0], x[b][1])) {
		   x[a][0] = x[5][0];
		   x[a][1] = x[5][1];
	   } else {
		   x[a][0] = x[4][0];
		   x[a][1] = x[4][1];
	   }
   } else
		if (f(x[4][0], x[4][1]) > f(x[c][0], x[c][1])) {
		   if (!(f(x[4][0], x[4][1]) > f(x[a][0], x[a][1]))) {
			   x[a][0] = x[4][0];
			   x[a][1] = x[4][1];
		   }
		   x[6][0] = x[3][0] + 0.5 * (x[a][0] - x[3][0]);
		   x[6][1] = x[3][1] + 0.5 * (x[a][1] - x[3][1]);
		   if (!(f(x[6][0], x[6][1]) > f(x[a][0], x[a][1]))) {
			   x[a][0] = x[6][0];
			   x[a][1] = x[6][1];
		   }
		   else {
			   for (int k = 0; k < 2; k++) {
				   x[k][0] = x[k][0] + 0.5 * (x[k][0] - x[b][0]);
				   x[k][1] = x[k][1] + 0.5 * (x[k][1] - x[b][1]);
			   }
		   }
	}
   else {
	   x[a][0] = x[4][0];
	   x[a][1] = x[4][1];
   }
   float s1 = 0, s2 = 0;
   for (int k = 0; k < 3; k++) {
	   s1 += f(x[k][0], x[k][1]);
	   s2 += f(x[k][0], x[k][1]) * f(x[k][0], x[k][1]);
   }
   s = s2 - s1 * s1 / 3;
   s /= 3;  
   min = f(x[0][0], x[0][1]);
   for (int k = 1; k <= 2; k++) {
	   if (f(x[k][0], x[k][1]) < min) {
		   min = f(x[k][0], x[k][1]);
		   b = k;
	   }
   }
   } while (s > eps);

   cout<<"Tochka min: ("<<x[3][0]<<" , "<<x[3][1]<<")"<<endl;
   cout<<"Kolichestvo iteratsiy: "<<it<<endl;
   return 0;
}
