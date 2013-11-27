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
sys.path.append('../../tools/python')
from erCv import *
from pylab import *




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
        erCleanDir(name_analysis)   # avant tout chose on nettoie si on a deja
        #print os.listdir('.')     # donne le meme nom d analyse pour les fichiers de sorties
        os.system(command_line)

    bad_images = erGetBadImagesNumber(name_analysis)             # On recuperes les images qui n ont pas ete traite
    all_images = erGetAllImagesNumber(name_analysis,name_image)  # Toutes les images

    # on garde que celles qui ont ete traites correctement
    good_treatment=[elem for elem in all_images if elem not in bad_images] 
    base_image    = erGetBaseImage(name_image)

    last_n=0
    #x=[,117,119]
    #y=[,100,96]
    posy=[114,112,110,108,107,105,102,100,97,95,93]
    for n,good in enumerate(good_treatment):  
            # On vient charge l image et la courbe correspond a l image traite 'good'
            loaded,im,x = erLoadImageAndCurve(name_analysis,base_image,good)
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
                #axis('equal')
                grid('on')
                last_n=n
                text(125,50,'Macro goutte',color='white')
                text(130,150,'Fil d apport',color='white',rotation=90)
                text(40,20,'Materiau de base',color='white')
                text(50,100,'Goutte',color='white')
                text(20,200,'LMGC/UM2/UM5508',color='white')
                text(20,190,'ANR TEMMSA',color='white')
                plot([80,120],[100,posy[n]],color='white',linewidth=2)

                # ici On vient sauver la figure au format png
                num="000"+str(n)
                axis([0,255,0,255])
                savefig('macrodrop_'+num[-2:]+'.png')

    
    # IMPORTANT : Pour visualiser les images ne pas oublier la fonction show()
    show()
