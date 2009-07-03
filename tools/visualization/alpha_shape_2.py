from pylab import *

def alpha_shape_2(fichierpts,fichier,fichieralpha):
    pts=load(fichierpts)
    plot(pts[:,0],pts[:,1],'o')
    hold('on')
    ptscv=load(fichier)
    plot(ptscv[:,0],ptscv[:,1],'s')
    hold('on')
    x=load(fichieralpha)
    for i in range(x.shape[0]):
        plot([x[i,0],x[i,2]],[x[i,1],x[i,3]])
        hold('on')
    grid('on')
    show()
