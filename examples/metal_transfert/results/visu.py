from pylab import *
import os,re,sys

nls  = os.listdir('.')  # comme un ls est recupere l ensemble des fichiers
ndep = 32             # numero de depart de l image a visualiser

for n,f in enumerate(nls[::2]):   # pour chaque fichier du rpertoire
    n*=2
    if f.endswith('.seg'):        # qui termine par .seg
        try:
            x=loadtxt(f)
        except:
            x=array([],'f')
        taille=x.shape       # taille de la matrice lu dans le .seg apriori n x 2
        # Ce qui a ete charge avec le loadtxt doit avoir une taille plus grande que 0
        if taille[0] > 0 and len(taille) > 0:
            figure(n)
            fichier='../../pictures/metal_transfert/schia_08072009_2_0'+str(ndep+n)+'.bmp'  # nom de base du fichier image
            print fichier
            im=imread(fichier)
            imshow(im,origin='lower')
            hold('on')
            # Ici pour chaque indice de colonne on vient tracer 
            # le contour ferme
            for i in range(taille[0]):
                plot(x[i,::2],255-x[i,1::2],color='white',linewidth=2)
                hold('on')
            savefig('prueba_2_'+str(n)+'.png')  # On sauvegarde le fichier en .png
axis('equal')
show()
