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
## knowledge of the CeCILL license and that you accept its terms.
import string
import numpy
from   erCvTools import *

ER_TOLER_GEO = 1.e-3

class erGeometryDropletInformation:
    def __init__(self,incTime,cnb,x,y,area,princ_x,princ_y,fit):
        self._incTime = incTime
        self._cnb     = cnb
        self._x       = x
        self._y       = y
        self._area    = area
        self._princ_x = princ_x
        self._princ_y = princ_y
        self._fit     = fit
    def incTime(self):
        return self._incTime
    def contour(self):
        return self._cnb
    def x(self):
        return self._x
    def y(self):
        return self._y
    def area(self):
        return self._area
    def princ_x(self):
        return self._princ_x
    def princ_y(self):
        return self._princ_y
    def fit(self):
        return self._fit

def erReadGeometryFile(fichier):
    lignes = open(fichier,'r').readlines()
    geoChar = []
    for ligne in lignes[1:]:
        res = string.split(ligne)
        ind = erGetImageNumber(res[0])
        cnb = erGetContourNumber(res[1])
        geoChar.append(erGeometryDropletInformation(int(ind),
                                                    int(cnb),
                                                  float(res[2]),
                                                  float(res[3]),
                                                  float(res[4]),
                                                  float(res[5]),
                                                  float(res[6]),
                                                  float(res[7])))
    return geoChar

def erFilterGeometry(geoChar,filtre):
    geoFiltr=[]
    for geo in geoChar:
        if filtre(geo):
            geoFiltr.append(geo)
    return geoFiltr


# This function was copied from scipy
# http://www.scipy.org/Cookbook/SignalSmooth
def scipySmooth(x,window_len=11,window='hanning'):
    """smooth the data using a window with requested size.
    
    This method is based on the convolution of a scaled window with the signal.
    The signal is prepared by introducing reflected copies of the signal 
    (with the window size) in both ends so that transient parts are minimized
    in the begining and end part of the output signal.
    
    input:
        x: the input signal 
        window_len: the dimension of the smoothing window; should be an odd integer
        window: the type of window from 'flat', 'hanning', 'hamming', 'bartlett', 'blackman'
            flat window will produce a moving average smoothing.

    output:
        the smoothed signal
        
    example:

    t=linspace(-2,2,0.1)
    x=sin(t)+randn(len(t))*0.1
    y=smooth(x)
    
    see also: 
    
    numpy.hanning, numpy.hamming, numpy.bartlett, numpy.blackman, numpy.convolve
    scipy.signal.lfilter
 
    TODO: the window parameter could be the window itself if an array instead of a string   
    """

    if x.ndim != 1:
        raise ValueError, "smooth only accepts 1 dimension arrays."

    if x.size < window_len:
        raise ValueError, "Input vector needs to be bigger than window size."


    if window_len<3:
        return x


    if not window in ['flat', 'hanning', 'hamming', 'bartlett', 'blackman']:
        raise ValueError, "Window is on of 'flat', 'hanning', 'hamming', 'bartlett', 'blackman'"


    s=numpy.r_[x[window_len-1:0:-1],x,x[-1:-window_len:-1]]
    #print(len(s))
    if window == 'flat': #moving average
        w=numpy.ones(window_len,'d')
    else:
        w=eval('numpy.'+window+'(window_len)')

    y=numpy.convolve(w/w.sum(),s,mode='valid')
    return y

class erPoint:
    """
    
    """
    def __init__(self,x,y):
        self.__x  = x
        self.__y  = y
    def x(self):
        return self.__x
    def y(self):
        return self.__y

    def __eq__(self,other):
        return abs(self.x()-other.x()) < ER_TOLER_GEO and abs(self.y()-other.y()) < ER_TOLER_GEO

def erSmoothContour(X,window_len=6,window='hanning'):
    xx=scipySmooth(X[:,0],window_len=window_len,window=window)
    yy=scipySmooth(X[:,1],window_len=window_len,window=window)
    list_points = []
    for i in range(len(xx)):
        pt = erPoint(xx[i],yy[i])
        if pt not in list_points: # Mauvais test
            list_points.append(pt)
    X = zeros((len(list_points),2),'float')
    for i,pt in enumerate(list_points):
        X[i,0] = pt.x()
        X[i,1] = pt.y()
    return X

def erCurvilinearAbscissa(X):
    if X.shape[1] != 2:
        raise ValueError('Shape array must have 2 in second dimension')
    dx = [0.]+list(diff(X[:,0]))
    dy = [0.]+list(diff(X[:,1]))
    ds = map(lambda x,y:sqrt(x**2.+y**2.),dx,dy)
    s  = add.accumulate(ds)
    return s



def erMeanCurvatures(X,distance=5,debut=0,fini=0):
    meanCurvatures=[]
    for i in arange(debut,fini):
        deb = i-distance
        fin = i+distance
        if deb < 0:
            deb=0
            fin+=distance
        if fin > X.shape[0]:
            fin = X.shape[0]
            deb-=distance

        a = polyfit(X[deb:fin,0],X[deb:fin,1],2)
        meanCurvatures.append(a[0])
    return array(meanCurvatures,'f')
def erCircleInterpolation(p,x,y):
    return (x-p[0])**2.+(y-p[1])**2.-p[2]**2.
def erParabolicInterpolation(p,x,y):
    funct = y-p[0]*x**2.-p[1]*x-p[2]
    return funct
def erLinearInterpolation(p,x,y):
    return y-p[0]*x-p[1]
def erFmin(X,funct):
    pass
    
    
