import sys
import os
import re
from pylab import *
def get_bad_images_number(name_anal):
    file=name_anal+'_imagesOUT.txt'
    bad_images_number=[]
    fid=open(file,'r')
    for ligne in fid.readlines():
        if len(ligne) > 1:
            res=re.split("_|\.",ligne)
            bad_images_number.append(res[5])
    return bad_images_number

def get_all_images_number(name_analysis,name_immage):
    all_images_number=[]
    ls=os.listdir('.')
    for f in ls:
        if (f.startswith(name_analysis) and f.endswith(name_image[-3:])):
            res=re.split("_|\.",f)
            all_images_number.append(res[1])
    return all_images_number

def clean_dir(name_analysis):
    ls=os.listdir('.')
    for f in ls:
        if name_analysis in f:
            os.remove(f)
    fid=open(name_analysis+'_imagesOUT.txt','w')
    fid.close()
def get_base_image(name_image):
    return name_image[:-9]



if len(sys.argv) > 1:
    name_analysis = sys.argv[1]
else:
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
    name_params=sys.argv[3]
else:
    name_params = None

command_line='./macro_drop '+name_analysis+' '+name_image
if name_params != None:
    command_line+=' < '+name_params




if name_params != 'visu_alone':
    clean_dir(name_analysis)
    print os.listdir('.')
    os.system(command_line)

bad_images = get_bad_images_number(name_analysis)
all_images = get_all_images_number(name_analysis,name_image)

good_treatment=[elem for elem in all_images if elem not in bad_images]
base_image    = get_base_image(name_image)

last_n=0
for n,good in enumerate(good_treatment):
    fich = name_analysis+'_curve_'+good+'.txt'
    try:
        x=load(fich)
        im=imread(base_image+good+'.bmp')
        figure(n)
        imshow(im,origin='lower')
        hold('on')
        plot(x[:,0],255-x[:,1],linewidth=2)
        axis('equal')
        grid('on')
        last_n=n
    except:
        print 'fichier:',fich

figure(last_n+1)
title('Comparaison de la premiere et l avant derniere ok')

x1=load(name_analysis+'_curve_'+good_treatment[0]+'.txt')
x2=load(name_analysis+'_curve_'+good_treatment[-2]+'.txt')
plot(x1[:,0],255-x1[:,1],'r',x2[:,0],255-x2[:,1],'b',linewidth=2)
legend([good_treatment[0],good_treatment[-2]],loc='upper right')
axis('equal')
grid('on')

show()
