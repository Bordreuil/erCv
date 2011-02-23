from pylab import *

for i in arange(1,6):
    base='laser_prototypage_wep_curveCgal_'
    try:
        X=loadtxt(base+str(i)+'.txt')
        loaded= True
    except:
        loaded = False
    im=imread('../example_laser_prototypage_'+str(i)+'.png')
    figure(i)
    imshow(im)
    print im.shape
    hold('on')
    if (loaded):
        for x in X:
            plot(x[::2],x[1::2],linewidth=2,color='red')
    #plot(X[:,0],X[:,1],color='red',linewidth=2)

   
   

show()
