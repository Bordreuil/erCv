from erCv import *

an=erCreatisAnalysis("peo","peo")
#zone d etudes
rect=CvRect();
rect.x =0;rect.y=0;rect.width=350;rect.height=166;

# Premier jeu de parametres
p1  = erSmootP(BLUR,1)
p2  = erSmootP(GAUSSIAN,1);
cann= erCannyP(255,255);
adp = erAdThrP(THRESH_BINARY,AM_MEAN,51,11,255);
alp = erAlphaP(1.)

# Immediatrement apres le detachement on a un jeu de parametres
an.defineParameters(rect,p1,p2,cann,adp,alp)
an.setOutputIntermediateImages(True)
from pylab import imread
im = imread('head_test_0.bmp')
imz = im[:,:,2]
imz=imz.astype('int16')
an.doItNumPy(imz,'test_0.bmp')
#an.doIt('head_test_0.bmp')
