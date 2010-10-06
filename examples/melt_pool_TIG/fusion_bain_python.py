import sys
sys.path.append('../../libs')

from PyerCv import *

rect = CvRect();
rect.x=158;rect.y=121;rect.width=225;rect.height=225;

whi =erWhitBP( 150, 150, 5, 100);
p1=erSmootP(BLUR,5); p2=erSmootP(MEDIAN,5);
cann=erCannyP(500,500);
dil=erDilatP(1); 
thr=erThresP(_THRESH_BINARY,200,255); 
rec_tem=CvRect()
rec_tem.x = 9; rec_tem.y = 208; rec_tem.width = 8; rec_tem.height = 8;
templ=erTemplP(SQDIFF_NORMED, rec_tem, true); 
alp=erAlphaP(1);
wpa=erWeldPoolAnalysis("full_bain_1_py");

wpa.defineCalibration("calibration_source.jpg","calibration_target.bmp");
wpa.defineParameters( rect, whi, p1, p2, cann, dil, thr, templ, alp);

wpa.doIt( "example_full_bain_1.bmp");
wpa.doIt( "example_full_bain_2.bmp");
wpa.doIt( "example_full_bain_3.bmp");
#erSmootP p12(BLUR,7), p22(MEDIAN,7);
#erThresP thr2(_THRESH_BINARY,215,255); 
#wpa.defineParameters( rect, whi, p12, p22, cann, dil, thr2, templ, alp);
#wpa.doIt( "example_full_bain_4.bmp");
