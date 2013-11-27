import sys
sys.path.append('../../lib/erCv')

from PyerCv import *
from pylab import *
rect    = CvRect();
rect.x  = 138;rect.y=71;rect.width=261;rect.height=281;
whi     = erWhitBP  ( 150, 150, 5, 100);
p1      = erSmootP (BLUR,9)
p2      = erSmootP(MEDIAN,7);
cann    = erCannyP (500,500);
dil     = erDilatP(2); 
thr     = erThresP(THRESH_BINARY_,121,255); 
rec_tem = CvRect();
rec_tem.x = 231; rec_tem.y = 254; rec_tem.width = 5; rec_tem.height = 5;
templ   = erTemplP(SQDIFF_NORMED, rec_tem, True); 
alp     = erAlphaP(1);
wpa     = erWeldPoolAnalysis("bain_move_python");
wpa.defineCalibration("calibration_source.jpg","calibration_target.bmp");
wpa.defineParameters( rect, whi, p1, p2, cann, dil, thr, templ, alp);
img_base="../pictures/gtaw_for_edward_0";
i_dep = 587
for i in arange(0,20):
    im = img_base+str(i_dep+i*20)+'.bmp'
    wpa.doIt(im)
    print '------image:',im
