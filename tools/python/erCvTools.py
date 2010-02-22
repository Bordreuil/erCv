import sys
import os
import re
from pylab import *

def erGetBadImagesNumber(name_anal):
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

def erGetAllImagesNumber(name_analysis,name_image):
    all_images_number=[]
    ls=os.listdir('.')
    for f in ls:
        if (f.startswith(name_analysis) and f.endswith(name_image[-3:])):
            res=re.split("_|\.",f)
            all_images_number.append(res[1])
    return all_images_number

def erCleanDir(name_analysis):
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

def erGetBaseImage(name_image):
    """
    permet d avoir le nom sans l extension ni les numero 
    """
    res = re.split("_",name_image)
    base ="_".join(res[:-1])
    base+='_'
    return base
def erLoadImage(image):
    """
    permet de charger une image 
    retourne une paire:
    - booleen pour savoir si ca ete charge
    - une image
    """
    test = True
    try:
        im=imread(image)
    except:
        print 'Probleme avec le fichier:',image
        im   = None
        test = False
    return test,im
def erTransformPoints(x):
    taille   = x.shape
    X        = zeros((taille[0]+1,taille[1]),'f')
    X[:-1,:] = x
    X[-1,:]  = x[0,:]
    return X
def erTransformSegmentsToClosedList(x):
    
    X=[]
    Y=[]
    try:
        for x1,y1,x2,y2 in x:
            x1inX = x1 in X;y1inY = y1 in Y
            x2inX = x2 in X;y2inY = y2 in Y
            if(x1inX and y1inY and (not (x2inX or y2inY))):
                x1i =X.index(x1);X.insert(x1i+1,x2);Y.insert(x1i+1,y2)
            if(x2inX and y2inY and (not (x1inX or y1inY))):
                x2i =X.index(x2);X.insert(x2i+1,x1);Y.insert(x2i+1,y1)  
            if(not x1inX and not y1inY and not x2inX ans not y2inY):
                X.append(x1);X.append(x2);Y.append(y1);Y.append(y2)
    except:
        print 'Error : erTransformSegmentsToClosedList() : x ne contient pas des segments'
        sys.exit()
    return array([X,Y],'f')
def erLoadCurve(curve,type='asItIs'):
    """
    permet de charger une courbe 
    Doit pouvoir afficher des points mais aussi
    transformer une fichier de segments en points ordonnes
    Si type = 'pointsToClose' on suppose que l on veut fermer la liste de points
    Si type = 'segmentsToList' on suppose le contour forme de segments
    TOTEST
    """
    x=[]
    test=True
    try:
        x=loadtxt(curve)
    except:
        print 'Probleme avec le fichier:',curve
        x=[]
        test=False
    if type='asIsIt':
        pass
    elif type=='pointsToClose':
        x=erTransformPoints(x)
    elif type='segmentsToList':
        x=erTransformSegmentsToClosedList(x)
    else:
        print "erLoadCurve : prevue uniquement pour type ='pointsToClose' ou 'segmentsToList' ou 'asIsIt'"
    return test,x

def erLoadImageAndCurve(name_analysis,base_image,number,format='bmp',type='points'):
    """
    permet de charger une image et une courbe a un temps donne
    si l une des deux n a pas ete charge, la premiere sortie sera fausse
    """
    fich     = name_analysis+'_curve_'+number+'.txt'
    imag     = base_image+number+'.'+format
    loadc,x  = erLoadCurve(fich,type)
    loadi,im = erLoadImage(imag)
    return loadc*loadi,im,x

def erPlotImageAndCurve(x,im,figure_number=1):
    """
    permet de tracer une courbe et une image sur le meme graphe
    """
    figure(figure_number)
    imshow(im,origin='lower')
    hold('on')
    plot(x[:,0],255-x[:,1],linewidth=2,color='white')
