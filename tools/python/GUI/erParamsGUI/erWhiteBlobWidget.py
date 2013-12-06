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


#from mplwidget     import *
from PyQt4.QtCore  import *
from PyQt4.QtGui   import *
from erCv          import * 


class erWhiteBlobWidget(QWidget):
    def __init__(self,parent=None):
        super(erWhiteBlobWidget,self).__init__(parent)
        
        layout = QHBoxLayout()
        
        layout.addWidget(QLabel('White Threshold:'))
        self._p1 = QSpinBox()
        self._p1.setValue(50)
        layout.addWidget(self._p1)
        layout.addWidget(QLabel(' Black Threshold:'))
        self._p2 = QSpinBox()
        self._p2.setRange(1,255)
        self._p2.setValue(5.)
        layout.addWidget(self._p2)
        layout.addWidget(QLabel(' Distance for border:'))
        self._p3 = QSpinBox()
        self._p3.setValue(50)
        layout.addWidget(self._p3)
        layout.addWidget(QLabel(' Size of Blob:'))
        self._p4 = QSpinBox()
        self._p4.setValue(50)
        layout.addWidget(self._p4)
        self.setLayout(layout)

    def erParam(self):
        
        p1   = int(self._p1.value())
        p2   = int(self._p2.value())
        p3   = int(self._p3.value())
        p4   = int(self._p4.value())
        return erWhitBP(p1,p2,p3,p4)
