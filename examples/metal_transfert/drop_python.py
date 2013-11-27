import sys
sys.path.append('../../libs')
from PyerCv import *
from numpy import arange

an=erMetalTransfertAnalysis("peo","peo")
#zone d etudes
rect=CvRect();
rect.x =100;rect.y=120;rect.width=70;rect.height=70;

# Premier jeu de parametres
p1  = erSmootP(BLUR,3)
p2  = erSmootP(GAUSSIAN,9);
cann= erCannyP(355,355);
adp = erAdThrP(THRESH_BINARY,AM_MEAN,51,11,255);
alp = erAlphaP(1.)

# Immediatrement apres le detachement on a un jeu de parametres
an.defineParameters(rect,p1,p2,cann,adp,alp)
an.doIt("imageExemple_1.bmp")

# On change pour les images en vol
p1  = erSmootP(BLUR,7)
p2  = erSmootP(GAUSSIAN,7);
adp = erAdThrP(THRESH_BINARY,AM_MEAN,51,17,255);
alp = erAlphaP(2.)
an.defineParameters(rect,p1,p2,cann,adp,alp)
for i in arange(2,7,1):
    an.doIt("imageExemple_"+str(i)+".bmp")
