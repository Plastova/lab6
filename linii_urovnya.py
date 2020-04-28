import pylab
import numpy as np
import matplotlib.pyplot as plt

	
def makeData():
	x = np.arange(-15, 15, 0.1)
	y = np.arange(-5, 20, 0.1)
	xgrid, ygrid = np.meshgrid(x, y)
	zgrid = xgrid*xgrid - 2*xgrid + 2*ygrid*ygrid-32*ygrid+134.5
	return xgrid, ygrid, zgrid

try:
	if __name__ == '__main__':
		x, y, z = makeData()
		pylab.contour(x, y, z,levels = 15)
		pylab.minorticks_on()
		pylab.grid(color="blue", which="major", linewidth=1)
		pylab.grid(color="blue", which="minor", linestyle=":", linewidth=0.5)
		data=np.loadtxt ("points.txt")
		plt.plot(data[:,0], data[:,1],color='red')
		plt.gcf().canvas.set_window_title("Pokoordinatniy spusk")
		data=np.loadtxt ("points.txt")
		plt.plot(data[:,0], data[:,1],'ro')
		pylab.show()
except BaseException:
	print("fail ne nayden")
	
