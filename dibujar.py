import string
import numpy
import scipy
from pylab import *
from scipy.optimize import curve_fit
from scipy.linalg import *

for i in range(10):

    #prepara los archivos uno a uno para ser leidos 
    dibujar = numpy.loadtxt(str(i)+'Data.dat')
    x = dibujar[:,1]
    y = dibujar[:,2]
    z = dibujar[:,3]
    
    #grafica x vs y
    plot(x, y)
    xlabel('x')
    ylabel('y')
    title(str(i)+'Plano_x,y')
    savefig(str(i)+'Plano_x,y.pdf')
    close()
    
    #grafica x vs z
    plot(x, z)
    xlabel('x')
    ylabel('z')
    title(str(i)+'Plano_x,z')
    savefig(str(i)+'Plano_x,z.pdf')
    close()
    
    #grafica y vs z 
    plot(y, z)
    xlabel('y')
    ylabel('z')
    title(str(i)+'Plano_y,z')
    savefig(str(i)+'Plano_y,z.pdf')
    close()

