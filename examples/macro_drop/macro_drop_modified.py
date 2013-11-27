import sys
sys.path.append('../../libs')
from PyerCv import *

rect=CvRect();
rect.x =20;rect.y=160;rect.width=230;rect.height=75;
cerc= erCerc(20,210,5);
p1  = erSmootP(BLUR,3)
p2  = erSmootP(GAUSSIAN,3);
cann= erCannyP(355,355);
adp = erAdThrP(THRESH_BINARY,AM_MEAN,51,14,255);

an  = erMacroDropAnalysis("macroDrop_modified","macroDrop_modified")
an.defineParameters(rect,cerc,p1,p2,cann,adp)
an.doIt("imageExemple_1.bmp")
