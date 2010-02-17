import sys
import os
import re
from pylab import *

def get_bad_images_number(name_anal):
    """
    permet de connaitre les images qui ne sont pas bonnes
    Les images ou le contour n a pas ete detecte se trouve
    dans name_anal+'_imagesOUT.txt'
    """
    file=name_anal+'_imagesOUT.txt'
    bad_images_number=[]
    fid=open(file,'r')
    for ligne in fid.readlines():
        if len(ligne) > 1:
            res=re.split("_|\.",ligne)
            bad_images_number.append(res[5])
    return bad_images_number

def get_all_images_number(name_analysis,name_image):
    all_images_number=[]
    ls=os.listdir('.')
    for f in ls:
        if (f.startswith(name_analysis) and f.endswith(name_image[-3:])):
            res=re.split("_|\.",f)
            all_images_number.append(res[1])
    return all_images_number

def clean_dir(name_analysis):
    """
    permet d enlever tous les fichiers d analyse portant
    deja un nom  d analyse existante.
    Au passage recree le fichier name_analysis+'_imagesOUT.txt'
    """
    ls=os.listdir('.')
    for f in ls:
        if name_analysis in f:
            os.remove(f)
    fid=open(name_analysis+'_imagesOUT.txt','w')
    fid.close()

def get_base_image(name_image):
    """
    permet d acoir le nom sans l extension ni les numero 
    """
    res = re.split("_",name_image)
    base ="_".join(res[:-1])
    base+='_'
    return base
def load_image(image):
    test=True
    try:
        im=imread(image)
    except:
        print 'Probleme avec le fichier:',image
        im=None
        test=False
    return test,im
def load_curve(curve):
    x=[]
    test=True
    try:
        x=load(curve)
    except:
        print 'Probleme avec le fichier:',curve
        x=[]
        test=False
    return test,x

def load_image_and_curve(name_analysis,base_image,number,format='bmp'):
    """
    permet de charger une image et une courbe a un temps donne
    si l une des deux n a pas ete charge, la premiere sortie sera fausse
    """
    fich = name_analysis+'_curve_'+number+'.txt'
    imag = base_image+number+'.'+format
    loadc,x = load_curve(fich)
    loadi,im = load_image(imag)
    return loadc*loadi,im,x

def plot_image_and_curve(x,im):
    """
    permet de tracer une courbe et une image sur le meme graphe
    """
    figure()
    imshow(im,origin='lower')
    hold('on')
    plot(x[:,0],255-x[:,1],linewidth=2,color='white')
