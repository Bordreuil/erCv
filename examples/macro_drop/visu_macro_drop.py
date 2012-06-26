from pylab import *

im=imread('imageExemple_1.bmp')
X=loadtxt('macroDrop_erCvAnalysis/macroDrop_mcr_curvCV_1.txt')
imshow(im,origin='lower')
plot(X[:,0],im.shape[0]-X[:,1])
show()
