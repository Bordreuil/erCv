from pylab import *
import glob
print 'Ce Fichier doit etre executer dans le repertoire de resultat '
print ' de l analyse que vous desirez visualiser'

files = glob.glob('*.txt')
colors=['red','black','blue','green']*2
for i,file in enumerate(files):
    X=loadtxt(file)
    if 'poly' not in file:
        pass
        #for x in X:
        #    plot(x[::2],x[1::2],colors[i])
        #    hold('on')
    else:
        plot(X[:,0],X[:,1],colors[i],linewidth=2)
        hold('on')
axis('equal')
show()
