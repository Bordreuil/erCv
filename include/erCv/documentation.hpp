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
    erCv's project is a library developped during ANR Project
    TEMMSA 2007 at  Laboratoire de Mecanique et Genie Civil/UMR5508 of
    Montpellier 2 University. The library was implemented by  Edward Romero (mad scientist)
    based on high efficient open source libraries.

    \image html physicien_fou.png Edward Romero after c++ implementation time.

    The open source libraries used are:
    - <a href="http://opencv.willowgarage.com/wiki/"> OpenCv</a>   : for basic image treatment  (segmentation, threashold, calibration,..)
    -  <a href="http://www.boost.org">Boost   </a> : boost::graph is used for detecting cycle,... and Boost.Python if you want python bindings
    -  <a href="http://www.cgal.org">CGAL 3.8 </a>: perform all geometrical operations (delaunay,....)
    
    It is mainly implemented in C++ but some bindings exist in Python.
    To install erCv, you will need  <a href="http://www.cmake.org">CMake</a> 
   

    \section Install Installation
    Install the libraries in the following order : Opencv, Boost, CGAL. If troubles go to install pages of this libraries.
    Then, you can install erCv in two ways the first is with cmake, the other is with cmake-gui (you see environment variable for real).

    \subsection source Source
    First, create a directory with build-name_of_the_compiler, go inside this directory,
    then type : cmake -DCMAKE_CXX_COMPILER=compiler ..

    \subsection Python Python
    To install python, you have to install python and boost.python and to add to cmake commande line cmake -DENABLE_PYTHON=1 ..

    \subsection binaire Packages
    Some packages can be made on different platforms ask if you got trouble with installation.


    For any trouble with install, contact cyril.bordreuil@univ-montp2.fr

    \section test Tests
    Some tests are coming the version in order to see if all compile fine.
    Go to 'tests' directory then type 'ctest -I' 

    \section project Using erCv in other project
    In the CMAKE_BINARY_DIR (build directory), you will find a lib/erCv directory where there is a ercv-config.cmake file with
    all the variable needed by erCv.
    Then in an other CMakeLists.txt you add FIND_PACKAGE(erCv) and then you have erCv_INCLUDE_DIRS and erCv_LIBRARY variable available for

    \section reference References
    
 */
