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


from mplwidget     import *
from erDirControl  import *
from PyQt4.QtCore  import *
from PyQt4.QtGui   import *
from erCv          import *
from BAME.io.cineFile import *
from qrc_resources import *
import numpy,time,os
from pylab import *
FICHIER_IMAGE_TEMP="/tmp/ercv.png"
## @defgroup GUI GUI
## Ce module decrit quelques fonctions avec des users interfaces
## @addtogroup GUI
##@{
# @brief Under construction


class erRectWidget(QWidget):
     def __init__(self,parent=None,default='BLUR'):
        super(erRectWidget,self).__init__(parent)
        layout = QVBoxLayout()
        layout1 = QHBoxLayout()
        layout1.addWidget(QLabel('x:'))
        self._x = QSpinBox();self._x.setRange(0,1000)
        layout1.addWidget(self._x)
        layout1.addWidget(QLabel('y:'))
        self._y = QSpinBox();self._y.setRange(0,1000)
        layout1.addWidget(self._y)
        layout2 = QHBoxLayout()
        layout2.addWidget(QLabel('width:'))
        self._width = QSpinBox();self._width.setRange(0,1000)
        layout2.addWidget(self._width)
        layout2.addWidget(QLabel('height:'))

        self._height = QSpinBox();self._height.setRange(0,1000)
        layout2.addWidget(self._height)
        layout.addLayout(layout1)
        layout.addLayout(layout2)
        self.setLayout(layout)
     def erParam(self):
         rect       =  CvRect()
         rect.x     = int(self._x.value())
         rect.y     = int(self._y.value())
         rect.width = int(self._width.value())
         rect.height= int(self._height.value()) 
         return rect
     def setRoi(self,x,y,w,h):
         self._x.setValue(x)
         self._y.setValue(y)
         self._width.setValue(w)
         self._height.setValue(h)
class erSmootWidget(QWidget):
    def __init__(self,parent=None,default='BLUR'):
        super(erSmootWidget,self).__init__(parent)
        self._comboType = QComboBox()
        smt=SmoothType.names.keys()
        self._comboType.addItems(smt)
        self._comboType.setCurrentIndex(smt.index(default))
        layout = QHBoxLayout()
        layout.addWidget(QLabel('Smooth Filter Type:'))
        layout.addWidget(self._comboType)
        layout.addWidget(QLabel('Smooth zone :'))
        self._valueROI = QSpinBox()
        self._valueROI.setValue(5)
        layout.addWidget(self._valueROI)
        self.setLayout(layout)
    def erParam(self):
        size = int(self._valueROI.value())
        tipe = self._comboType.currentText()
        return erSmootP(SmoothType.names[str(self._comboType.currentText())],size)
class erCannyWidget(QWidget):
    def __init__(self,parent=None):
        super(erCannyWidget,self).__init__(parent)

        layout = QHBoxLayout()

        layout.addWidget(QLabel('Canny Threshold 1:'))
        self._value1 = QSpinBox()
        self._value1.setRange(1,255)
        self._value1.setValue(255)
        layout.addWidget(self._value1)
        layout.addWidget(QLabel('Canny Threshold 2:'))
        self._value2 = QSpinBox()
        self._value2.setRange(1,255)
        self._value2.setValue(255)
        layout.addWidget(self._value2)
        self.setLayout(layout)
    def erParam(self):
        l1 = int(self._value1.value())
        l2 = int(self._value2.value())
        return erCannyP(l1,l2)
class erAdaptiveThresholdWidget(QWidget):
    def __init__(self,parent=None):
        super(erAdaptiveThresholdWidget,self).__init__(parent)
        self._comboType = QComboBox()
        att = AdaptiveThresholdType.names.keys()
        self._comboType.addItems(att)
        self._comboType.setCurrentIndex(att.index('THRESH_BINARY'))
        layout = QHBoxLayout()
        layout.addWidget(QLabel('Adaptive Threshold Type:'))
        layout.addWidget(self._comboType)
        self._comboMethod = QComboBox()
        amt = AdaptiveMethodType.names.keys()
        self._comboMethod.addItems(amt)
        self._comboMethod.setCurrentIndex(amt.index('AM_MEAN'))
        layout.addWidget(QLabel('Adaptive Method Type:'))
        layout.addWidget(self._comboMethod)
        layout.addWidget(QLabel(' Threshold 1:'))
        self._p1 = QSpinBox()
        self._p1.setValue(57)
        layout.addWidget(self._p1)
        layout.addWidget(QLabel(' Neighbour:'))
        self._neigh = QSpinBox()
        self._neigh.setValue(39)
        layout.addWidget(self._neigh)
        layout.addWidget(QLabel(' Threshold 2:'))
        self._p2 = QSpinBox()
        self._p2.setRange(1,255)
        self._p2.setValue(255)
        layout.addWidget(self._p2)
        self.setLayout(layout)
    def erParam(self):
        tipe = AdaptiveThresholdType.names[str(self._comboType.currentText())]
        meth = AdaptiveMethodType.names[str(self._comboMethod.currentText())]
        p1   = int(self._p1.value())
        nei  = int(self._neigh.value())
        p2   = int(self._p2.value())
        return erAdThrP(tipe,meth,p1,nei,p2)

class erAlphaShapeWidget(QWidget):
    def __init__(self,parent=None):
        super(erAlphaShapeWidget,self).__init__(parent)
        layout = QHBoxLayout()
        layout.addWidget(QLabel(' Alpha shape distance :'))
        self._p = QSpinBox()
        self._p.setValue(4)
        layout.addWidget(self._p)
        self.setLayout(layout)
    def erParam(self):
        r = int(self._p.value())
        return erAlphaP(r)
class erTransferParamsWidget(QWidget):
    def __init__(self,parent=None):
        super(erTransferParamsWidget,self).__init__(parent)
        layout=QVBoxLayout()
        self._rec = erRectWidget()
        layout.addWidget(self._rec)
        self._sp1 = erSmootWidget()
        layout.addWidget(self._sp1)
        self._adp = erAdaptiveThresholdWidget()
        layout.addWidget(self._adp)
        self._sp2 = erSmootWidget(default='GAUSSIAN')
        layout.addWidget(self._sp2)
        self._can = erCannyWidget()
        layout.addWidget(self._can)
        self._alp = erAlphaShapeWidget()
        layout.addWidget(self._alp)
        self.setLayout(layout)
    def erParams(self):
        return [self._rec.erParam(),
                self._sp1.erParam(),
                self._adp.erParam(),
                self._sp2.erParam(),
                self._can.erParam(),
                self._alp.erParam()]
    def roi(self):
        return self._rec.erParam()
    def setRoi(self,x,y,w,h):
        self._rec.setRoi(x,y,w,h)
class erTransfertSetter(QMainWindow):
    def __init__(self,parent=None):
        super(erTransfertSetter,self).__init__(parent)
        #-----------------------------------------------------
        #
        #  Variables
        #
        #-----------------------------------------------------
        self._erAnal = erMetalTransfertAnalysis("test","test")
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
        self.setWindowTitle("erTransfer ConSol")
        
        paramToolBar = QToolBar()
        self.addToolBar(Qt.BottomToolBarArea,paramToolBar)
        self._params = erTransferParamsWidget()
        paramToolBar.addWidget(self._params)
        self._roiButton = QPushButton('Define ROI')
        self._applyButton = QPushButton('Apply')
        self.connect(self._applyButton,SIGNAL('clicked()'),self._doIt)
        self.connect(self._roiButton,SIGNAL('clicked()'),self._defineROI)

        paramToolBar.addWidget(self._roiButton)
        paramToolBar.addWidget(self._applyButton)

        self._label=QLabel()
        self.setCentralWidget(self._label)
    def _about(self):
        QMessageBox.about(self,"About erTransfertSetter",
                          """<p> Copyright &copy; LMGC-AS.
                                 All right reserved.
                             <p>This application can be used to analyse experimental test.
                             <p>Version : %s - Date : %s """ % (__version__,__date__))
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
        imsave(FICHIER_IMAGE_TEMP,self._im)
        self._showImage()
    def _loadCine(self):
 
        roi = self._params.roi()
        self._im = self._cin[self._slider.value()][roi.x:roi.x+roi.width,roi.y:roi.y+roi.height]
        imsave(FICHIER_IMAGE_TEMP,self._im) 
        self._im = self._cin[self._slider.value()]
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
        self._erAnal.defineParameters(rect,params[1],params[3],params[4],params[2],params[5])
        self._applyAnalysis()
    def _applyAnalysis(self):
        self._erAnal.doItNumPy(self._im,"cineviewer_ercv_0.bmp")
        output_name=self._erAnal.output_name
        try:
             X=loadtxt(output_name+'_curveCgal_0.txt')

             for xx in X:
                    xX = map(int,xx[::2])
                    yY = map(int,xx[1::2])
                    for ii in range(len(xX)): 
                        x = xX[ii]
                        y = yY[ii]
                        for i in range(3):
                            for j in range(3):
                                self._im[y-i+2,x-j+2]=0
                                
        except IOError:
             print '--Aucun contour detecte....'
        roi = self._params.roi()

        imsave(FICHIER_IMAGE_TEMP,self._im[roi.x:roi.x+roi.width,roi.y:roi.y+roi.height])
        self._showImage()
    def closeEvent(self,event):
        settings = QSettings()
        settings.setValue("Geometry",QVariant(self.saveGeometry()))

def mainErTransferSetter():
       app   = QApplication([])
       app.setOrganizationName("LMGC/UMR5508/UM2")
       app.setOrganizationDomain("http://www.lmgc.univ-montp2.fr")
       app.setApplicationName("erCv ConSol")
       pixmap = QPixmap(":bame.png")
       splash = QSplashScreen(pixmap, Qt.WindowStaysOnTopHint)
       splash.setMask(pixmap.mask()) 
       splash.show()
       splash.showMessage((u'Starting erTransfertSetter...'), Qt.AlignRight | Qt.AlignBottom,Qt.red)
       # make sure Qt really display the splash screen
       app.processEvents()
       frame = erTransfertSetter()
       splash.finish(frame)

       frame.show()

       app.exec_()

if __name__=="__main__":
    mainErTransferSetter()
                    
##@}
