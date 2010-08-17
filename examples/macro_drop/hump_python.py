import sys
sys.path.append('../../libs')
from PyerCv import *

rect=CvRect();
rect.x =121;rect.y=110;rect.width=814;rect.height=220;
cerc= erCerc(135,293,25);
p1  = erSmootP(BLUR,7)
p2  = erSmootP(MEDIAN,5);
cann= erCannyP(355,355);
adp = erAdThrP(THRESH_BINARY,AM_MEAN,49,119,255);

an=erMacroDropAnalysis("hump","hump")
an.defineParameters(rect,cerc,p1,p2,cann,adp)
an.doIt("hump_1.bmp")
an.doIt("hump_2.bmp")
an.doIt("hump_3.bmp")
