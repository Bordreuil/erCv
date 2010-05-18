import sys
sys.path.append('../../libs')
from PyerCv import *

rect=CvRect();
rect.x =20;rect.y=160;rect.width=230;rect.height=75;
cerc= erCerc(20,210,5);
p1  = erSmootP(BLUR,7)
p2  = erSmootP(GAUSSIAN,5);
cann= erCannyP(355,355);
adp = erAdThrP(THRESH_BINARY,AM_MEAN,50,14,255);

an=erMacroDropAnalysis("peo","peo")
an.defineParameters(rect,cerc,p1,p2,cann,adp)
an.doIt("imageExemple_1.bmp")
