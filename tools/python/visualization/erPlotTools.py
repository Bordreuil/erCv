from pylab import *
try:
    from SoGranu.geometry.PySoGranuContour import *
except ImportError:
    print 'erTransformSegments needs SoGranu!!'
TOLER =0.5
class erPoint:
    def __init__(self,x,y):
        self._x = x
        self._y = y
    def x(self):
        return self._x
    def y(self):
        return self._y 
    def __eq__(self,pt):
        return abs(self.x()-pt.x()) < TOLER and abs(self.y()-pt.y()) < TOLER
    def __str__(self):
        return str(self.x())+' '+str(self.y())
class erSegment:
    def __init__(self,source,target):
        self._source = source
        self._target = target
    def source(self):
        return self._source
    def target(self):
        return self._target
    def __str__(self):
             return '['+str(self.source())+','+str(self.target())+']'     


def erLoadImage(image):
    """
    permet de charger une image 
    retourne une paire:
    - booleen pour savoir si ca ete charge
    - une image
    """
    test = True
    try:
        im=imread(image)
    except:
        print 'Probleme avec le fichier:',image
        im   = None
        test = False
    return test,im

def erTransformPoints(x):
    """
    Pour faire un polygone a partir d une liste de points
    TO TEST
    """
    taille   = x.shape
    X        = zeros((taille[0]+1,taille[1]),'f')
    X[:-1,:] = x
    X[-1,:]  = x[0,:]
    return X

def erTransformSegmentsToPointsList(x):
    
    pts   = []
    edges=[]
    for x1,y1,x2,y2 in x:
           pt1    = erPoint(x1,y1)
           pt2    = erPoint(x2,y2)
           edges.append(erSegment(pt1,pt2))
           if pt1 not in pts:
               pts.append(pt1)
           if pt2 not in pts:
               pts.append(pt2)
    #ed  = edges.pop(0)
    #pts.append(ed.target())
    #inc = 0 
    #while(len(edges) != 0 and inc < 250):
    #    inc+=1
    #    topop=[]
    #    for i,edge in enumerate(edges):
    #          if edge.source() == pts[-1]:
    #               pts.append(edge.target())
    #               topop.append(i)
    #               break
    #          if edge.source() in pts:
    #              topop.append(i)
    #    for to in topop:
    #        edges.pop(to)
              #if edge.target() == pts[-1]:
              #     pts.append(edge.source())
              #     edges.pop(i)
              #     break
    #       pt1in  = pt1 in pts
    #       pt2in  = pt2 in pts
    
    #       if (not pt1in) and (not pt2in):
    #           pts.append(pt1);pts.append(pt2)
    #       if (not pt1in) and pt2in:
    #           ind  = pts.index(pt2)
    #           pts.insert(ind,pt1)
    #       if pt1in and (not pt2in):
    #           ind  = pts.index(pt1)
    #           pts.insert(ind+1,pt2)
    #     edges.append([[x1,y1],[x2,y2]])
    #polygone = zeros((1000,2),'f') 
    #npol     = soGranuConnectedSegments(edges,polygone)
    Pts      = zeros((len(pts),2),'f')
    for i,pt in enumerate(pts):
        Pts[i,:] = [pt.x(),pt.y()]
    return Pts
    return polygon[npol,:]
def erLoadCurve(curve,type='asItIs'):
    """
    permet de charger une courbe 
    Doit pouvoir afficher des points mais aussi
    transformer une fichier de segments en points ordonnes
    Si type = 'pointsToClose' on suppose que l on veut fermer la liste de points
    Si type = 'segmentsToList' on suppose le contour forme de segments
    TOTEST
    """
    x=[]
    test=True
    try:
        x=loadtxt(curve)
    except:
        print 'Probleme avec le fichier:',curve
        x=[]
        test=False
    if type=='asItIs':
        pass
    elif type=='pointsToClose':
        x=erTransformPoints(x)
    elif type=='segmentsToList':
        x=erTransformSegmentsToClosedList(x)
    else:
        print "erLoadCurve : prevue uniquement pour type ='pointsToClose' ou 'segmentsToList' ou 'asItIs'"
    return test,x

def erLoadImageAndCurve( name_analysis, base_image, number, typ_curve = '_curve_', typ_image = '', format='bmp', type='asItIs'):
    """
    permet de charger une image et une courbe a un temps donne
    si l une des deux n a pas ete charge, la premiere sortie sera fausse
    """
 
    fich     = name_analysis + typ_curve + number + '.txt'
    imag     = base_image + typ_image + number + '.' + format
    loadc,x  = erLoadCurve(fich,type)
    loadi,im = erLoadImage(imag)
    return loadc*loadi,im,x

def erPlotImageAndCurve(x,im,figure_number=1):
    """
    permet de tracer une courbe et une image sur le meme graphe
    """
    figure(figure_number)
    imshow(im,origin='lower')
    hold('on')
    plot(x[:,0],255-x[:,1],linewidth=2,color='white')

def erPlotSegments(fichier,figure_number=1):
    """
    permet de charge un fichier de segments
    et le trace sur la figure 'figure_number'
    """
    x=loadtxt(fichier)
    if x.shape[1] != 4:
        print('erPlotSegments : Attention le fichier %s n est pas un fichier de segments' % fichier)
        return
    figure(figure_number)
    for i in range(x.shape[0]):
        plot([x[i,0],x[i,2]],[255-x[i,1],255-x[i,3]],color='black',linewidth=2)
        hold('on')
    grid('on')
