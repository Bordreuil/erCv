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
from PyQt4.QtCore  import *
from PyQt4.QtGui   import *
from erCv          import * 
from erRectWidget  import *

class erTemplateWidget(QWidget):
    def __init__(self,parent=None,default='SQDIFF_NORMED'):
        super(erTemplateWidget,self).__init__(parent)
        self._comboType = QComboBox()
        smt=MatchTemplateType.names.keys()
        self._comboType.addItems(smt)
        self._comboType.setCurrentIndex(smt.index(default))
        layout = QHBoxLayout()
        layout.addWidget(QLabel('Template Type:'))
        layout.addWidget(self._comboType)
        layout.addWidget(QLabel('Rect template :'))
        self._rect = erRectWidget()
        layout.addWidget(self._rect)
        self.setLayout(layout)
    def setErParam(self,temp):
        self._comboType.setCurrentIndex(temp.type)
        self._rect.setRoi(temp.rectan.x,temp.rectan.y,temp.rectan.width,temp.rectan.height)
    def erParam(self):
        rect = self._rect.erParam()
        return erTemplP(MatchTemplateType.names[str(self._comboType.currentText())],
                       rect,
                       True)

