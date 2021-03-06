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

#include <erCv/erCvAnalysis.hpp>
#include <erCv/erCvFilters.hpp>
#include <erCv/erCvSegmentation.hpp>
#include <erCv/utilities/erPredicates.hpp>
#include <erCv/erCvExtract.hpp>
#include <erCv/erCvToCgal.hpp>


/********************************************************************

                      ER_MACRODROP_ANALYSIS

*********************************************************************/

erMacroDropAnalysis::erMacroDropAnalysis() { };

erMacroDropAnalysis::erMacroDropAnalysis( std::string name, std::string infofile):
  erAnalysis( name, infofile), rectOI( ), cerc_to_start( ), param_smooth1( ), param_smooth2( ),
  param_canny( ), param_adaptive_threshold( ), param_equalizer_histogram( )
{ };




void erMacroDropAnalysis::defineParameters( CvRect rect, erCerc cerc, erSmootP smooth1, erSmootP smooth2, erCannyP cann, erAdThrP adthr, erEqualP equal)
{
  rectOI                   = rect;
  cerc_to_start            = cerc;
  param_smooth1            = smooth1;
  param_smooth2            = smooth2;
  param_canny              = cann;
  param_adaptive_threshold = adthr;
  param_equalizer_histogram = equal;
};

bool erMacroDropAnalysis::doIt(std::string fich)
{      bool loaded;
       char* file_name         = const_cast<char*>(fich.c_str());
       setCurrentFileName(file_name);
       erImage ea;
       boost::tie( ea, loaded) = erLoadImage( file_name);
       if( !loaded) return false;
       doItImage(ea);
};
bool erMacroDropAnalysis::doItImage(erImage& ea)
{      
       erImage  eb, ec, ed; 
       std::list<CvPoint> cvPts;
       output_name = (dir_analysis+"/"+name+"_mcr");
       char* nom               = const_cast<char*>(output_name.c_str());

       std::cout << std::endl;
       eb = erConvertToBlackAndWhite( &ea);        
       ec = erDef_ROI( &eb, &rectOI); 
       //erShowImage("essai",&eb);
       erCvEqualizeHist( &ec, &param_equalizer_histogram);
       erCvSmooth( &ec, &param_smooth1);
       erCvAdaptiveThreshold( &ec, &param_adaptive_threshold);
       erCvSmooth( &ec, &param_smooth2);
       erCvCanny( &ec, &param_canny);
       erSaveImage( &ec, currentFileName(), nom);
       IsEqualTo is_equal_255( 255); 
       erExtractCvPoints( cvPts, &ec, is_equal_255, rectOI);
       erExtractCurveMacroDrop( cvPts, &ec, rectOI, &cerc_to_start,currentFileName());
       erPrintCvPoint( cvPts,currentFileName(), nom); 
       
       return true;
};

