from analysis.analysis        import *
from GUI.imagesAndCurveViewer import *

ms=bameTests(['MCR_19042010_4','MCR_02042010_9','MCR_31052010_4'])
bameConfigureExtraction(ms, config=({'name':'intensity','type':'intensity','file':'current.dat','K':-63,'inc':1},
                                    {'name':'tension','type':'tension','file':'arcvoltage.dat','K':11.,'inc':2},
                                        {'type':'cameras'}))
#bamePlotValues(ms,'intensity',offset=False)
#bamePlotValues(ms,'tension',offset=False,figure_number=2)
#pylab.show()
app   = QApplication([])
frame = FrameForImageAndCurve(manip=ms[2],valeur='intensity')
frame.show()
app.exec_()
