#include<string>
#include<erCv/erCvBase.hpp>
std::string INFOFILE="log.log";
const char * nameInfoFile(std::string nameInfo)
{
  nameInfo+='.txt';
  return nameInfo.c_str();
};
