from pylab import *

for i in arange(1,7,1):
    im=imread('imageExemple_'+str(i)+'.bmp')
    figure(i)
    imshow(im,origin='lower')
    hold('on')
    X=loadtxt('peo_erCvAnalysis/peo_mtl_curveCgal_'+str(i)+'.txt')
    for i in range(X.shape[0]):
        plot(X[i,::2],255-X[i,1::2],'w',linewidth=2)
        hold('on')


show()

