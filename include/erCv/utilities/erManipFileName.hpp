#ifndef _ERCV_MANIP_FILE_NAME_HPP_
#define _ERCV_MANIP_FILE_NAME_HPP_

#include<utility>


std::pair<bool,const char* > get_number_in_file_name(char*);
char* concatenate_file_name(char*,char*,int,char*);



#endif 
