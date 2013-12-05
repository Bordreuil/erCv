# -*- coding: utf-8 -*-

# Copyright Universite Montpellier 2/CNRS 
# Contributor(s) : 
#         Julien Chapuis
#         Cyril Bordreuil
# Contact: cyril.bordreuil@univ-montp2.fr
# 
# This software is a computer program whose purpose is to [describe
#  functionalities and technical features of your software].
#
# This software is governed by the CeCILL license under French law and
# abiding by the rules of distribution of free software.  You can  use, 
# modify and/ or redistribute the software under the terms of the CeCILL
# license as circulated by CEA, CNRS and INRIA at the following URL
# "http://www.cecill.info". 
#
# As a counterpart to the access to the source code and  rights to copy,
# modify and redistribute granted by the license, users are provided only
# with a limited warranty  and the software's author,  the holder of the
# economic rights,  and the successive licensors  have only  limited
# liability. 
#
# In this respect, the user's attention is drawn to the risks associated
# with loading,  using,  modifying and/or developing or reproducing the
# software by the user in light of its specific status of free software,
# that may mean  that it is complicated to manipulate,  and  that  also
# therefore means  that it is reserved for developers  and  experienced
# professionals having in-depth computer knowledge. Users are therefore
# encouraged to load and test the software's suitability as regards their
# requirements in conditions enabling the security of their systems and/or 
# data to be ensured and,  more generally, to use and operate it in the 
# same conditions as regards security. 
# 
# The fact that you are presently reading this means that you have had
# knowledge of the CeCILL license and that you accept its terms.


from mplwidget        import *
from erParamsGUI.erParamsWidget   import *
from erDirControl     import *
from PyQt4.QtCore     import *
from PyQt4.QtGui      import *
from erCv             import *
from BAME.io.cineFile import *
from qrc_resources    import *
import numpy,time,os,sys
from pylab import *
FICHIER_IMAGE_TEMP="/tmp/ercv.png"
## @defgroup GUI GUI
## Ce module decrit quelques fonctions avec des users interfaces
## @addtogroup GUI
##@{
# @brief Under construction


#wpa.defineParameters( rect, whi, p1, p2, cann, dil, thr, templ, alp);
class erWeldPoolParamsWidget(QWidget):
    def __init__(self,parent=None):
        super(erWeldPoolParamsWidget,self).__init__(parent)
        layout=QVBoxLayout()
        self._rec = erRectWidget()
        layout.addWidget(self._rec)
        self._wb = erWhiteBlobWidget()
        layout.addWidget(self._wb)
        self._sp1 = erSmootWidget(default='BLUR')
        layout.addWidget(self._sp1)
        self._sp2 = erSmootWidget(default='MEDIAN')
        layout.addWidget(self._sp2)
        self._cann=erCannyWidget()
        layout.addWidget(self._cann)   
        self._dil =erDilateWidget()
        layout.addWidget(self._dil)
        self._thr = erThresholdWidget()
        layout.addWidget(self._thr)
        self._temp = erTemplateWidget()
        layout.addWidget(self._temp)
        self._alp = erAlphaShapeWidget()
        layout.addWidget(self._alp)
        self.setLayout(layout)
    def erParams(self):
        return [self._rec.erParam(),
                self._wb.erParam(),
                self._sp1.erParam(),
                self._sp2.erParam(),
                self._cann.erParam(),
                self._dil.erParam(),
                self._thr.erParam(),
                self._temp.erParam(),
                self._alp.erParam()]
    def roi(self):
        return self._rec.erParam()
    def roiTempl(self):
        return self._temp.erParam().rectan
    def setRoi(self,x,y,w,h):
        self._rec.setRoi(x,y,w,h)
    def setErThreshold(self,thr):
        self._thr.setErParam(thr)
    def setErSmooth1(self,p1):
        self._sp1.setErParam(p1)
    def setErSmooth2(self,p1):
        self._sp2.setErParam(p1)
    def setErCanny(self,p1):
        self._cann.setErParam(p1)
    def setErTemplate(self,p1):
        self._temp.setErParam(p1)
    def setErAlpha(self,alp):
        self._alp.setErParam(alp)
    def setErDilate(self,dil):
        self._dil.setErParam(dil)

class erWeldPoolSetter(QMainWindow):
    def __init__(self,parent=None):
        super(erWeldPoolSetter,self).__init__(parent)
        #-----------------------------------------------------
        #
        #  Variables
        #
        #-----------------------------------------------------
        self._erAnal = erWeldPoolAnalysis("test","test")
        self._erAnal.setWhiteBlobDetection(False)
        self._im     = None
        self._inc    = 0
        #-----------------------------------------------------
        #
        #  Settings
        #
        #-----------------------------------------------------
        settings = QSettings()
        self.restoreGeometry(settings.value("Geometry").toByteArray())
 
        #------------------------------------------------------
        #
        #  Help Menu
        #
        #------------------------------------------------------
        helpMenu        = self.menuBar().addMenu("Help")
        aboutAction     = self._createAction("About",self._about,
                                           None,None,"")
        authorAction    = self._createAction("Authors",self._authors,None,None,"")
        self._addActions(helpMenu,(aboutAction,authorAction,))
        #-------------------------------------------------------
        #
        #   ToolBars
        #
        #-------------------------------------------------------
        manageToolBar = self.addToolBar("Manage File")
        manageToolBar.setObjectName("manageToolBar")
        self._erFileCine    = erFileWidget(text='Cine File to treat:')
        manageToolBar.addWidget(self._erFileCine)
        self.connect(self._erFileCine,SIGNAL("fileChanged"),self._openCine)
        self._reverseButton = QCheckBox("Reverse")
        self.connect(self._reverseButton,  SIGNAL('stateChanged(int)'),self._showImage)
        self._slider  = QSlider(Qt.Horizontal)
        self.connect(self._slider,SIGNAL('valueChanged(int)'),self._loadCine)
        manageToolBar.addWidget(self._reverseButton)
        manageToolBar.addWidget(self._slider)       
        self.setWindowTitle("erWeldPool ConSol")
        
        paramToolBar = QToolBar()
        paramToolBar.setObjectName("erParamToolBar")
        self.addToolBar(Qt.BottomToolBarArea,paramToolBar)

        self._params = erWeldPoolParamsWidget()
        paramToolBar.addWidget(self._params)
        self._roiButton = QPushButton('Define ROI')
        self._applyButton = QPushButton('Apply')
        self.connect(self._applyButton,SIGNAL('clicked()'),self._doIt)
        self.connect(self._roiButton,SIGNAL('clicked()'),self._defineROI)

        paramToolBar.addWidget(self._roiButton)
        paramToolBar.addWidget(self._applyButton)

        self._label=QLabel()
        self.setCentralWidget(self._label)
        self.restoreState(settings.value("State").toByteArray())
    def _about(self):
        QMessageBox.about(self,"About erWeldPoolSetter",
                          """<p> Copyright &copy; LMGC-AS.
                                 All right reserved.
                             <p>This application can be used to analyse experimental test.
                             <p>Version : %s - Date : %s """ % ('1.1.0','05.12.2013'))
    def _authors(self):
        QMessageBox.about(self,"Authors of ercv:",
                          """<p> buddha ercv : Cyril Bordreuil cyril.bordreuil@univ-montp2.fr
                             <p> arhat ercv : Edward Romero physicienfou@hotmail.com""")

    def _addActions(self,target,actions):
        for action in actions:
            if action is None:
                target.addSeparator()
            else:
                target.addAction(action)

    def _createAction(self,text,slot=None,shortcut=None,icon=None,
                      tip=None,checkable=False,signal="triggered()"):
        action = QAction(text,self)
        if icon is not None:
           action.setIcon(QIcon(":%s.png" % icon))
        if tip is not None:
           action.setToolTip(tip)
           action.setStatusTip(tip)
        if shortcut is not None:
           action.setShortcut(shortcut)
        if slot is not None:
           self.connect(action,SIGNAL(signal),slot)
        if checkable:
           action.setCheckable(True)
        return action
    def _defineROI(self):
        self._loadCine()

    def _openCine(self):
        fname=self._erFileCine.get()
        self._cin=cineFile(fname)
        self._im = self._cin[0]
        self._params.setRoi(0,0,self._im.shape[0],self._im.shape[1])
        self._slider.setRange(0,self._cin.imageCount())
        self._slider.setTickPosition(3)
        imsave(FICHIER_IMAGE_TEMP,self._im,cmap='gray')
        self._showImage()
    def _loadCine(self):
 
        roi = self._params.roi()
        self._im = self._cin[self._slider.value()][roi.x:roi.x+roi.width,roi.y:roi.y+roi.height]
        rtpl = self._params.roiTempl()
        #print rtpl.x,rtpl.y,rtpl.width,rtpl.height
        self._im[rtpl.x:rtpl.x+rtpl.width,rtpl.y-1:rtpl.y+1] = 255
        self._im[rtpl.x-1:rtpl.x+1,rtpl.y:rtpl.y+rtpl.height] = 255
        self._im[rtpl.x:rtpl.x+rtpl.width,rtpl.y+rtpl.height-1:rtpl.y+rtpl.height+1] = 255
        self._im[rtpl.x+rtpl.width-1:rtpl.x+rtpl.width+1,rtpl.y:rtpl.y+rtpl.height] = 255
        self._im[rtpl.x:rtpl.x+rtpl.width,rtpl.y+1:rtpl.y+2] = 0
        self._im[rtpl.x+1:rtpl.x+2,rtpl.y:rtpl.y+rtpl.height] =0
        self._im[rtpl.x:rtpl.x+rtpl.width,rtpl.y+rtpl.height+1:rtpl.y+rtpl.height+2] = 0
        self._im[rtpl.x+rtpl.width+1:rtpl.x+rtpl.width+2,rtpl.y:rtpl.y+rtpl.height] = 0
        imsave(FICHIER_IMAGE_TEMP,self._im,cmap='gray') 
       
        self._showImage()
    def _showImage(self):  
        self._inc+=1
 
        inter= QPixmap(FICHIER_IMAGE_TEMP)
        if self._reverseButton.isChecked():
                trans=QTransform()
                trans.rotate(180)
                self._image = inter.transformed(trans)
        else:
                self._image=inter
        self._label.setPixmap(self._image)
    def _doIt(self):
        params = self._params.erParams()
        re = params[0]
        rect = CvRect();rect.x = re.y;rect.y=re.x;rect.width=re.height;rect.height=re.width
        #self._erAnal.defineParameters(rect,
        self._erAnal.defineParameters( rect, 
                                       params[1],
                                       params[2],
                                       params[3],
                                       params[4],
                                       params[5],
                                       params[6],
                                       params[7],
                                       params[8],
                                       )
        self._applyAnalysis()
    def _applyAnalysis(self):
        self._im = self._cin[self._slider.value()]
        self._erAnal.doItNumPy(self._im,"cineviewer_ercv_0.bmp")
        output_name=self._erAnal.output_name
        try:
             X=loadtxt(output_name+'_curveCgal_0.txt')
             #figure()
             for xx in X:
                    xX = map(int,xx[::2])
                    yY = map(int,xx[1::2])
                    #plot(xX,yY)
                    for ii in range(len(xX)): 
                        x = xX[ii]
                        y = yY[ii]
                        for i in range(3):
                            for j in range(3):
                                if (y-i+2 > 0 and y-i+2<self._im.shape[0] and x-j+2 >0 and x-j+2 < self._im.shape[1]):
                                 self._im[y-i+2,x-j+2]=0
             show()
        except IOError:
             print '--Aucun contour detecte....'
        roi = self._params.roi()

        imsave(FICHIER_IMAGE_TEMP,self._im[roi.x:roi.x+roi.width,roi.y:roi.y+roi.height],cmap='gray')
        self._showImage()
    def closeEvent(self,event):
        settings = QSettings()
        settings.setValue("Geometry",QVariant(self.saveGeometry()))
        settings.setValue("State",QVariant(self.saveState()))
    def setFileToTreat(self,fichier):
        self._erFileCine.set(fichier)
    def setParams(self,p1,p2,thr,cann,dil,temp,alp):
        self._params.setErThreshold(thr)
        self._params.setErSmooth1(p1)
        self._params.setErSmooth2(p2)
        self._params.setErCanny(cann)
        self._params.setErDilate(dil)
        self._params.setErTemplate(temp)
        self._params.setErAlpha(alp)
def mainErWeldPoolSetter(fichier=None,*params):
       app   = QApplication([])
       app.setOrganizationName("LMGC/UMR5508/UM2")
       app.setOrganizationDomain("http://www.lmgc.univ-montp2.fr")
       app.setApplicationName("erCv ConSol")
       pixmap = QPixmap(":bame.png")
       splash = QSplashScreen(pixmap, Qt.WindowStaysOnTopHint)
       splash.setMask(pixmap.mask()) 
       splash.show()
       splash.showMessage((u'Starting erWeldPoolSetter...'), Qt.AlignRight | Qt.AlignBottom,Qt.red)
       # make sure Qt really display the splash screen
       app.processEvents()
       frame = erWeldPoolSetter()
       frame.setFileToTreat(fichier)
       p1=params[0]
       p2=params[1]
       cann=params[2]
       dil=params[3]
       templ=params[4]
       alp=params[5]
       frame.setParams(p1,p2,thr,cann,dil,templ,alp)
       splash.finish(frame)

       frame.show()

       app.exec_()

if __name__=="__main__":
    fichier = sys.argv[1]
    thr   = erThresP(THRESH_BINARY_INV_,5,50);
    p1    = erSmootP(BLUR,1);
    p2    = erSmootP(MEDIAN,5);
    cann  = erCannyP(500,500);
    dil   = erDilatP(2)
    rec_tem=CvRect()
    rec_tem.x = 253; rec_tem.y = 253; rec_tem.width = 7; rec_tem.height = 7;
    templ = erTemplP(SQDIFF_NORMED, rec_tem, True);
    alp   = erAlphaP(1);
    mainErWeldPoolSetter(fichier,p1,p2,cann,dil,templ,alp)
                    
##@}
