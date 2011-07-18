// Copyright Universite Montpellier 2/CNRS 
// Contributor(s) : 
//         Edward Romero 
//         Cyril Bordreuil
// Contact: cyril.bordreuil@univ-montp2.fr
// 
// This software is a computer program whose purpose is to [describe
//  functionalities and technical features of your software].
//
// This software is governed by the CeCILL license under French law and
// abiding by the rules of distribution of free software.  You can  use, 
// modify and/ or redistribute the software under the terms of the CeCILL
// license as circulated by CEA, CNRS and INRIA at the following URL
// "http://www.cecill.info". 
//
// As a counterpart to the access to the source code and  rights to copy,
// modify and redistribute granted by the license, users are provided only
// with a limited warranty  and the software's author,  the holder of the
// economic rights,  and the successive licensors  have only  limited
// liability. 
//
// In this respect, the user's attention is drawn to the risks associated
// with loading,  using,  modifying and/or developing or reproducing the
// software by the user in light of its specific status of free software,
// that may mean  that it is complicated to manipulate,  and  that  also
// therefore means  that it is reserved for developers  and  experienced
// professionals having in-depth computer knowledge. Users are therefore
// encouraged to load and test the software's suitability as regards their
// requirements in conditions enabling the security of their systems and/or 
// data to be ensured and,  more generally, to use and operate it in the 
// same conditions as regards security. 
// 
// The fact that you are presently reading this means that you have had
// knowledge of the CeCILL license and that you accept its terms.
/** \mainpage
    Le projet erCv est un module developpe au cours du projet ANR Jeunes Chercheurs
    TEMMSA 2007 effectue au sein du Laboratoire de Mecanique et Genie Civil/UMR5508 de 
    l' Universite de Montpellier 2. Le module developpe par Edward Romero (Le physicien fou)
    edward.romero@lmgc.univ-montp2.fr (a l'epoque)
    est essentiellement un couplage entre plusieurs bibliotheques OpenSource

    \image html physicien_fou.png Edward Romero en forme apres une sceance de c++


    - OpenCv   : permet de realiser le traitement d image (segmentation, seuillage, calibration,..)
    - Boost    : boost::graph est utiliser pour detecter les contours les plus grands,... 
    - CGAL 3.8 : permet de quantifier tous les aspects geometriques, et tous les aspects de voisinages.
    
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

    \section refernce References
    Des articles sur la mise en oeuvre des articles est en cours.
 */
