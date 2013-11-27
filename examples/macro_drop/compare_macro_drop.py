from pylab import *

im   = imread('imageExemple_1.bmp')
X    = loadtxt('results/macroDrop_mcr_curvCV_1.txt')
Xmod = loadtxt('results/macroDrop_modified_mcr_curvCV_1.txt')
imshow(im,origin='lower')
deb=4;fin=80
debmod=8;finmod=80

plot(X[deb:fin,0],im.shape[0]-X[deb:fin,1],label='base')
plot(Xmod[debmod:finmod,0],im.shape[0]-Xmod[debmod:finmod,1],label='modified')

totpts = 10
a      = polyfit(X[deb:deb+totpts,0],im.shape[0]-X[deb:deb+totpts,1],1)
amod   = polyfit(Xmod[debmod:debmod+totpts,0],im.shape[0]-Xmod[debmod:debmod+totpts,1],1)

plot(Xmod[debmod:debmod+totpts,0],amod[1]+amod[0]*Xmod[debmod:debmod+totpts,0],label='approximation for modified filter')
plot(X[deb:deb+totpts,0],a[1]+a[0]*X[deb:deb+totpts,0],label='approximation for based filter')

print 'Angle in degrees for smooth filter region of 7:',arctan(a[0])*180/pi
print 'Angle in degrees for smooth filter region of 3:',arctan(amod[0])*180/pi

legend()
show()
