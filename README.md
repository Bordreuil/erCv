erCv
====

image treatment in welding.

To be installed, you will need:
  - OpenCv
  - Boost
  - CGAL 

Then you create a directory build, go inside and type cmake .. .
If you want some python bindings, you have to do the commane cmake -DENABLE_PYTHON=1 ..
and then manually add to the PYTHONPATH variable, the path to erCv.py, actually
in build/lib/erCv

Good luck, for any trouble you can contact cyril.bordreuil@univ-montp2.fr
