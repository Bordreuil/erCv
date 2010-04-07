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
    """
    permet d obtenir tous les numeros d images associes
    a l image de base
    """
    all_images_number=[]
    result=os.path.split(name_analysis)
    ls=os.listdir(result[0])
    for f in ls:
        if ( f.startswith(result[1]) and (f.endswith(name_image[-3:]) or f.endswith('png'))):
            res = re.split("_|\.",f)
            largo = len(res)
            all_images_number.append( res[largo-2])
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

