from pylab import *
import os,re,sys

nls=os.listdir('.')
ndep=1601

for n,f in enumerate(nls[::2]):
    n*=2
    if f.endswith('.seg'):
        try:
            x=load(f)
        except:
            x=array([],'f')
        taille=x.shape

        if taille[0] > 0 and len(taille) > 0:
            figure(n)
            fichier='../../pictures/mcr_07092009_5_0'+str(ndep+n)+'.bmp'
            print fichier
            im=imread(fichier)
            imshow(im,origin='lower')
            hold('on')
            for i in range(taille[0]):
                plot(x[i,::2],255-x[i,1::2],color='white',linewidth=2)
                hold('on')
            savefig('transfert_'+str(n)+'.png')
axis('equal')
show()
