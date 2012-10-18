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
#
import sys, os, random
from PyQt4 import *
from PyQt4.QtGui import *
import matplotlib
matplotlib.use('Qt4Agg')

import pylab

from pylab  import arange, sin, pi

from matplotlib.backends.backend_qt4agg import FigureCanvasQTAgg as FigureCanvas
from matplotlib.figure import Figure


class MatplotlibWidget(FigureCanvas):
    """Ultimately, this is a QWidget (as well as a FigureCanvasAgg, etc.)."""
    def __init__(self, parent=None, name=None, width=10, height=4, dpi=100, bgcolor=None):
        fig = Figure(figsize=(width, height), dpi=dpi)
        self.figure=fig

        self.axes1 = fig.add_subplot(111)
        # We want the axes cleared every time plot() is called
        self.axes1.hold(False)

        self.compute_figure()

        FigureCanvas.__init__(self, fig)

        self.setParent(parent)

        FigureCanvas.setSizePolicy(self,
                                   QSizePolicy.Expanding,
                                   QSizePolicy.Expanding)
        FigureCanvas.updateGeometry(self)
        self._lineDefined = False

    def compute_figure(self):
        pass

   
class MatplotlibImageWidget(MatplotlibWidget):
 
    def setImage(self,name):
        if '_imfig' in self.__dict__.keys():
            self.axes1.cla()
        self._im = pylab.imread(name)
        self._imfig=self.axes1.imshow(self._im,origin='lower')
    
    def update_figure(self):
        self.draw()
          
    def compute_figure(self):
        self._im=pylab.imread('test.bmp')
        self.update_figure()

class MatplotlibPlotWidget(MatplotlibWidget):
   
    def setValues(self,times,values):
        self._times= times
        self._values = values
        self.axes1.plot(self._times,self._values,'b')
        self.axes1.hold(True)
    def setValue(self,time,value):
        if self._lineDefined:
            self.axes1.lines.remove(self._line)
        self._time=[time]
        self._value=[value]
        self._line,=self.axes1.plot(self._time,self._value,'ro',markersize=8)
        self.axes1.hold(True)
        self._lineDefined=True
    def compute_figure(self):
        t=arange(0.,100.,0.1)
        self.axes1.plot(t,t**2)
    def set_xlim(self,interval):
        self.axes1.set_xlim(interval)
    def update_figure(self):
        
        self.draw()



