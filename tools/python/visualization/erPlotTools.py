from pylab import *

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

def erTransformSegmentsToClosedList(x):
    
    X=[]
    Y=[]
    try:
        for x1,y1,x2,y2 in x:
            x1inX = x1 in X;y1inY = y1 in Y
            x2inX = x2 in X;y2inY = y2 in Y
            if(x1inX and y1inY and (not (x2inX or y2inY))):
                x1i =X.index(x1);X.insert(x1i+1,x2);Y.insert(x1i+1,y2)
            if(x2inX and y2inY and (not (x1inX or y1inY))):
                x2i =X.index(x2);X.insert(x2i+1,x1);Y.insert(x2i+1,y1)  
            if(not x1inX and not y1inY and not x2inX and not y2inY):
                X.append(x1);X.append(x2);Y.append(y1);Y.append(y2)
            # AFINIR LES TESTS
    except:
        print 'Error : erTransformSegmentsToClosedList() : x ne contient pas des segments'
        sys.exit()
    return array([X,Y],'f')
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
    #print 'name_analysis:'
    #print name_analysis
    #print 'base_image'
    #print base_image
    #print 'typ_curve:'
    #print typ_curve
    #print 'typ_image:'
    #print typ_image
    #print 'format:'
    #print format
    #print 'type:'
    #print type
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
