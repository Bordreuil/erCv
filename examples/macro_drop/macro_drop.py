"""
   Contient un serie de fonction utile pour traiter les
   fichiers issus de ./macro_drop de erCv

   Utilisation normale:
   1, python macro_drop.py nom_analyse image_de_depart 
      On interagit avec le programme d edward
   2, python macro_drop.py nom_analyse image_de_depart params
      Un fichier de parametres (qui fonctionnent) sont passes au programmes
   3, python macro_drop.py nom_analyse image_de_depart visu_alone
      On ne s occupe que de visualiser le resultat

"""
import sys
import os
import re
from pylab import *
def get_bad_images_number(name_anal):
    """
    permet de connaitre les images qui ne sont pas bonnes
    Les images ou le contour n a pas ete detecte se trouve
    dans name_anal+'_imagesOUT.txt'
    """
    file=name_anal+'_imagesOUT.txt'
    bad_images_number=[]
    fid=open(file,'r')
    for ligne in fid.readlines():
        if len(ligne) > 1:
            res=re.split("_|\.",ligne)
            bad_images_number.append(res[5])
    return bad_images_number

def get_all_images_number(name_analysis,name_image):
    """
    vient recuperer les images de l analyse
    """
    all_images_number=[]
    ls=os.listdir('.')
    for f in ls:
        if (f.startswith(name_analysis) and f.endswith(name_image[-3:])):
            res=re.split("_|\.",f)
            all_images_number.append(res[1])
    return all_images_number

def clean_dir(name_analysis):
    """
    permet d enlever tous les fichiers d analyse portant
    deja un nom  d analyse existante.
    Au passage recree le fichier name_analysis+'_imagesOUT.txt'
    """
    ls=os.listdir('.')
    for f in ls:
        if name_analysis in f:
            os.remove(f)
    fid=open(name_analysis+'_imagesOUT.txt','w')
    fid.close()

def get_base_image(name_image):
    """
    permet d acoir le nom sans l extension ni les numero 
    """
    res = re.split("_",name_image)
    base ="_".join(res[:-1])
    base+='_'
    return base
def load_image(image):
    """
    permet de charge une image dont le nom de fichier est image
    On retourne un booleen et un objet image. Le booleen sert
    a savoir sile fichier a ete correctement ouvert
    """
    test=True
    try:
        im=imread(image)
    except:
        print 'Probleme avec le fichier:',image
        im=None
        test=False
    return test,im
def load_curve(curve):
    """
    idem load_image pour une courbe x,y de point dans un fichier curve
    """
    x=[]
    test=True
    try:
        x=loadtxt(curve)   #  Attention possible erreur a changer en loadtxt ou mlab.load
    except:
        print 'Probleme avec le fichier:',curve
        x=[]
        test=False
    return test,x

def load_image_and_curve(name_analysis,base_image,number,format='bmp'):
    """
    permet de charger une image et une courbe a un temps donne
    si l une des deux n a pas ete charge, la premiere sortie sera fausse
    """
    fich = name_analysis+'_curve_'+number+'.txt'
    imag = base_image+number+'.'+format
    loadc,x = load_curve(fich)
    loadi,im = load_image(imag)
    return loadc*loadi,im,x



if __name__=='__main__':            # Ici commence le programme quand on l execute
    if len(sys.argv) > 1:           # sys.argv est une liste qui vient de la ligne de commande
        name_analysis = sys.argv[1] # python macro_drop.py peo ../picture/xxx
    else:                           # sys.argv[0]='macro_drop.py' sys.argv[1]='peo'.....
        print 'Attention: macrop_drop.py doit etre utiliser de la maniere suivante:'
        print '           python macro_drop.py nom_de_l_analyse image initiale (fichier_parametres)'
        sys.exit()

    if len(sys.argv) > 2:
        name_image = sys.argv[2]
    else:
        print 'Attention: macrop_drop.py doit etre utiliser de la maniere suivante:'
        print '           python macro_drop.py nom_de_l_analyse image initiale (fichier_parametres)'
        sys.exit()

    if len(sys.argv) > 3:
        name_params=sys.argv[3]   # ici on vien recuperer le fichier de parametre
    else:
        name_params = None
    # Ici on construit la ligne de commande LINUX ./macro_drop peo ../pictures/xx < params 
    # Si on a besoin de parametre
    command_line='./macro_drop '+name_analysis+' '+name_image

    if name_params != None:
        command_line+=' < '+name_params


    if name_params != 'visu_alone':  # On execute si name_params n est pas en mode 'visu_alone'
        clean_dir(name_analysis)   # avant tout chose on nettoie si on a deja
        #print os.listdir('.')     # donne le meme nom d analyse pour les fichiers de sorties
        os.system(command_line)

    bad_images = get_bad_images_number(name_analysis)             # On recuperes les images qui n ont pas ete traite
    all_images = get_all_images_number(name_analysis,name_image)  # Toutes les images

    # on garde que celles qui ont ete traites correctement
    good_treatment=[elem for elem in all_images if elem not in bad_images] 
    base_image    = get_base_image(name_image)

    last_n=0
    for n,good in enumerate(good_treatment):  
            # On vient charge l image et la courbe correspond a l image traite 'good'
            loaded,im,x = load_image_and_curve(name_analysis,base_image,good)
            # Si on a pu charge la courbe et l image
            if loaded:
                # On cree une nouvelle figure
                figure(n)
                # Ou on vient afficher l image cf doc pylab (tu peux un imread(nom_fichier avant))
                imshow(im,origin='lower')
                # On maintient la figure active
                hold('on')
                # On vient tracer la figure cf doc pylab
                plot(x[:,0],255-x[:,1],color='white',linewidth=2)
                axis('equal')
                grid('on')
                last_n=n
                # ici On vient sauver la figure au format png
                savefig('macrodrop_'+str(n)+'.png')
    # Ici on cree quelques figures annexes pour comparer a des instants particuliers
    # On peut oublier ce qui suit
    #figure(last_n+1)
    #title('Comparaison de la premiere et l avant derniere ok')

    #load1,x1=load_curve(name_analysis+'_curve_'+good_treatment[0]+'.txt')
    #load2,x2=load_curve(name_analysis+'_curve_'+good_treatment[-2]+'.txt')
    #leg=[]
    #if load1:
    #    plot(x1[:,0],255-x1[:,1],'r',linewidth=3)
    #    hold('on')
    #    leg.append(good_treatment[0])
    #if load2:
    #    plot(x2[:,0],255-x2[:,1],'b',linewidth=3)
    #    leg.append(good_treatment[-2])
    #legend(leg,loc='upper right')
    #axis('equal')
    #grid('on')
    
    # IMPORTANT : Pour visualiser les images ne pas oublier la fonction show()
    show()
