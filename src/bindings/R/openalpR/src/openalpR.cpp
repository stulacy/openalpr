#include <Rcpp.h>
#include <stdlib.h>

#include <alpr.h>

//extern "C" {

//#if defined(WIN32)
//    //  Microsoft
//    #define OPENALPR_EXPORT __declspec(dllexport)
//#else
//    //  do nothing
//    #define OPENALPR_EXPORT
//#endif

using namespace alpr;


// [[Rcpp::export]]
Alpr* initialize(std::string country, std::string configFile, std::string runtimeDir)
{
    //printf("Initialize");

    //std::cout << country << std::endl << configFile << std::endl << runtimeDir << std::endl;
    Alpr* nativeAlpr = new alpr::Alpr(country, configFile, runtimeDir);

    return nativeAlpr;
}




// [[Rcpp::export]]
void dispose(Alpr* nativeAlpr)
{
  delete nativeAlpr;
}


// [[Rcpp::export]]
bool isLoaded(Alpr* nativeAlpr)
{
  //printf("IS LOADED");
  return nativeAlpr->isLoaded();
}

// [[Rcpp::export]]
std::string recognizeFile(Alpr* nativeAlpr, std::string imageFile)
{
  //printf("Recognize file");

  AlprResults results = nativeAlpr->recognize(imageFile);
  std::string json = Alpr::toJson(results);
  return json;
}

// [[Rcpp::export]]
void freeJsonMem(char* ptr)
{
    //printf("freeing address: %p\n", ptr);
    free( ptr );
}


// Detect from raw string/bytes array
// [[Rcpp::export]]
std::string recognizeArray(Alpr* nativeAlpr, unsigned char* buf, int len)
{
  //std::cout << "Using instance: " << nativeAlpr << std::endl;

  std::vector<char> cvec(buf, buf+len);

  AlprResults results = nativeAlpr->recognize(cvec);
  std::string json = Alpr::toJson(results);

  return json;
}

// [[Rcpp::export]]
void setCountry(Alpr* nativeAlpr, std::string country)
{
  nativeAlpr->setCountry(country);
}

// [[Rcpp::export]]
void setPrewarp(Alpr* nativeAlpr, std::string prewarp)
{
  nativeAlpr->setPrewarp(prewarp);
}

// [[Rcpp::export]]
void setDefaultRegion(Alpr* nativeAlpr, std::string default_region)
{
  nativeAlpr->setDefaultRegion(default_region);
}

// [[Rcpp::export]]
void setDetectRegion(Alpr* nativeAlpr, bool detect_region)
{
  nativeAlpr->setDetectRegion(detect_region);
}

// [[Rcpp::export]]
void setTopN(Alpr* nativeAlpr, int top_n)
{
  nativeAlpr->setTopN(top_n);
}

// [[Rcpp::export]]
std::string getVersion(Alpr* nativeAlpr)
{
  std::string version = nativeAlpr->getVersion();
  return version;
}


//}
