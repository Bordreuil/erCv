from pylab import *

im=imread('hump_1.bmp')
X=loadtxt('hump_erCvAnalysis/hump_mcr_curvCV_1.txt')
imshow(im,origin='lower')
plot(X[:,0],im.shape[0]-X[:,1])
show()
