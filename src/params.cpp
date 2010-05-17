#include<erCv/erCvFilters.hpp>
#include<erCv/erCvSegmentation.hpp>

const int nbSmoothType = 5;
char* smoothtype [nbSmoothType]= {"Blur no scale","Blur","Gaussian","Median","Bilateral"};


const int nbFindContoursMode = 4;
char*  findcontoursmode[nbFindContoursMode]= {"Retr external","Retr list","Retr ccom","Retr tree"};

const int nbFindContoursMeth = 4;
char*  findcontoursmeth[nbFindContoursMeth]= {"Chain code","Chain approx none","Chain approx simple","Chain approx tc89 l1"};
