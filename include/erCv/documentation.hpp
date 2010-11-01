/** \mainpage
    Le projet erCv est un module developpe au cours du projet ANR Jeunes Chercheurs
    TEMMSA 2007 effectue au sein du Laboratoire de Mecanique et Genie Civil/UMR5508 de 
    l' Universite de Montpellier 2. Le module developpe par Edward Romero (Le physicien fou)
    edward.romero@lmgc.univ-montp2.fr (a l'epoque)
    est essentiellement un couplage entre plusieurs bibliotheques OpenSource

    \image html physicien_fou.png Edward Romero en forme apres une sceance de c++


    - OpenCv   : permet de realiser le traitement d image (segmentation, seuillage, calibration,..)
    - Boost    : boost::graph est utiliser pour detecter les contours les plus grands,... 
    - CGAL 3.4 : permet de quantifier tous les aspects geometriques, et tous les aspects de voisinages.
    
    L'installation necessite un compilateur C++.
    L'installation d erCv necessite le logiciel OpenSource CMake http://www.cmake.org
    Une extension du module est prevu en python et necessite la bibliotheque Boost.python.
    Pour  la  compilation pour ces modules, il faut passer la commande -DBUILD_PYTHON_MODULE=1 a cmake
   

    Les fichiers interfaces (.hpp) sont accessibles dans un programme en specifiant le repertoire include ou include/erCv suivant l utilisation qu'on veut en faire.

    \section Install Installation
    
    \subsection source Source
    Pour utiliser les sources, il conveint d'installer les librairies dans l'ordre de 
    la presentation (OpenCv, Boost, CGAL). 

    Il est conseiller de creer un repertoire build-nom_du_compilo, puis de se placer dans ce repertoire,
    ensuite on tape la ligne de commande : cmake -DCMAKE_CXX_COMPILER=nom_compilo ..

    Cela permet d avoir une installation propre et un acces simple au source sans rien surcharge
    dans les repertoire des sources.
    \subsection binaire Paquets
    Des paquets sont disponibles pour :

    - Mac Os x: Leopard/Tiger 
    - Ubuntu  : YaKa demander
    - Opensuse: Yaka demander
    - Windows : On work

    Pour tout probleme avec l'installation, vous pouvez contacter cyril.bordreuil@univ-montp2.fr

    \section test Tests
    Une serie de tests est en developpement par Edward pour voir si tout tourne correctement apres
    l installation.
    Dans le repertoire ou vous l'avez installer, rentrer dans le repertoire tests et taper
    la ligne de commande ctest -I 

    
 */
