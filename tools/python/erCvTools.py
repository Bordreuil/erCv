## Copyright Universite Montpellier 2/CNRS 
## Contributor(s) : 
##         Edward Romero 
##         Cyril Bordreuil
## Contact: cyril.bordreuil@univ-montp2.fr
## 
## This software is a computer program whose purpose is to [describe
##  functionalities and technical features of your software].
##
## This software is governed by the CeCILL license under French law and
## abiding by the rules of distribution of free software.  You can  use, 
## modify and/ or redistribute the software under the terms of the CeCILL
## license as circulated by CEA, CNRS and INRIA at the following URL
## "http://www.cecill.info". 
##
## As a counterpart to the access to the source code and  rights to copy,
## modify and redistribute granted by the license, users are provided only
## with a limited warranty  and the software's author,  the holder of the
## economic rights,  and the successive licensors  have only  limited
## liability. 
##
## In this respect, the user's attention is drawn to the risks associated
## with loading,  using,  modifying and/or developing or reproducing the
## software by the user in light of its specific status of free software,
## that may mean  that it is complicated to manipulate,  and  that  also
## therefore means  that it is reserved for developers  and  experienced
## professionals having in-depth computer knowledge. Users are therefore
## encouraged to load and test the software's suitability as regards their
## requirements in conditions enabling the security of their systems and/or 
## data to be ensured and,  more generally, to use and operate it in the 
## same conditions as regards security. 
## 
## The fact that you are presently reading this means that you have had
## knowledge of the CeCILL license and that you accept its terms

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
    all_images_number=[ ]
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

def erGetImageNumber(fichier):
    res = re.split("_|\.",fichier)
    return res[-2]

def erGetBaseImage(name_image):
    """
    permet d avoir le nom sans l extension ni les numero 
    """
    res = re.split("_",name_image)
    base ="_".join(res[:-1])
    base+='_'
    return base

