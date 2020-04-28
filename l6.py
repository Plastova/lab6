from __future__ import print_function
from scipy.optimize import minimize_scalar
import numpy as np
import pylab
import matplotlib.pyplot as plt

def f(x1,x2):
	return x1*x1-2*x1+2*x2*x2-32*x2+134.5

def f1(x):
	return x*x-2*x+2*x2_fixed*x2_fixed-32*x2_fixed+134.5

def f2(x):
	return x1_fixed*x1_fixed-2*x1_fixed+2*x*x-32*x+134.5; 

x1=[]
x2=[]

def pokoord_spusk():
	eps=0.0001
	global it,x1,x2,x1_fixed,x2_fixed
	
	x1_fixed_0 = x1_fixed
	x2_fixed_0 = x2_fixed
	x1.append(x1_fixed)
	x2.append(x2_fixed)
	print("nachalnaya tochka: (",x1_fixed,";",x2_fixed,")")
	print()
	while True:	
		res = minimize_scalar(f1,method='brent')
		x1_fixed = res.x
		it+=1
		x1.append(x1_fixed)
		x2.append(x2_fixed)
		print("promezhutochnaya tochka: (",x1_fixed,";",x2_fixed,")")	
		x1_fixed_0 = x1_fixed;	
		res = minimize_scalar(f2,method='brent')
		x2_fixed = res.x
		it+=1
		x1.append(x1_fixed)
		x2.append(x2_fixed)
		print("promezhutochnaya tochka: (",x1_fixed,";",x2_fixed,")")	
		x2_fixed_0 = x2_fixed;	
		if abs(f(x1_fixed,x2_fixed)-f(x1_fixed_0,x2_fixed_0))<eps:
			break
	
	x1.append(x1_fixed)
	x2.append(x2_fixed)	
	print()	
	print("tochka min: (",x1_fixed,";",x2_fixed,")")
	print("min znachenie funktsii:", f(x1_fixed,x2_fixed))
	
it=0		
x1_fixed = -11
x2_fixed = 14
pokoord_spusk()
print("kolichestvo iteratsiy:",it)

def makeData():
	x = np.arange(-15, 15, 0.1)
	y = np.arange(-5, 20, 0.1)
	xgrid, ygrid = np.meshgrid(x, y)	
	zgrid = xgrid*xgrid - 2*xgrid + 2*ygrid*ygrid-32*ygrid+134.5
	return xgrid, ygrid, zgrid

if __name__ == '__main__':
	x, y, z = makeData()
	pylab.contour(x, y, z,levels = 15)
	pylab.minorticks_on()
	pylab.grid(color="blue", which="major", linewidth=1)
	pylab.grid(color="blue", which="minor", linestyle=":", linewidth=0.5)
	plt.gcf().canvas.set_window_title("Pokoordinatniy spusk")
	plt.plot (x1,x2,'ro')
	plt.plot (x1,x2,color='red')
	pylab.show()

