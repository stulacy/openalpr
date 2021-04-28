#include <Rcpp.h>
#include <stdlib.h>
#include <alpr.h>

using namespace alpr;

bool initialized = false;
static Alpr* nativeAlpr;

// [[Rcpp::export]]
void initialize_cpp(std::string country, std::string configFile, std::string runtimeDir)
{
    nativeAlpr = new alpr::Alpr(country, configFile, runtimeDir);
    initialized = true;
    return;
}

//' Closes the connection to the ANPR handler.
//'
//' MUST BE RUN AFTER FINISHING NUMBER PLATE RECOGNITION.
//'
//' @return None
//' @export
// [[Rcpp::export]]
void close()
{
  initialized = false;
  delete nativeAlpr;
}

//' Checks whether the number plate recogniser has been successfully loaded.
//'
//' @return A boolean indicating whether ANPR requests can be made or not.
//' @export
// [[Rcpp::export]]
bool is_loaded()
{
  if (!initialized)
    return false;

  return nativeAlpr->isLoaded();
}

// [[Rcpp::export]]
std::string recognize_file_cpp(std::string imageFile)
{
  AlprResults results = nativeAlpr->recognize(imageFile);
  std::string json = Alpr::toJson(results);
  return json;
}

//// Detect from raw string/bytes array
//// [[Rcpp::export]]
//std::string recognizeArray(unsigned char* buf, int len)
//{
//  //std::cout << "Using instance: " << nativeAlpr << std::endl;
//
//  std::vector<char> cvec(buf, buf+len);
//
//  AlprResults results = nativeAlpr->recognize(cvec);
//  std::string json = Alpr::toJson(results);
//
//  return json;
//}

//' Changes the country.
//'
//' @param country 'eu' or 'us'.
//' @return None.
// [[Rcpp::export]]
void set_country(std::string country)
{
  nativeAlpr->setCountry(country);
}

//' Not entirely sure what this does...
//'
//' @param A string representing something...
//' @return None.
// [[Rcpp::export]]
void set_prewarp(std::string prewarp)
{
  nativeAlpr->setPrewarp(prewarp);
}

//' Not entirely sure what this does...
//'
//' @param A string representing something...
//' @return None.
// [[Rcpp::export]]
void set_default_region(std::string default_region)
{
  nativeAlpr->setDefaultRegion(default_region);
}

//' Sets whether the region should be detected automatically or not.
//'
//' I'm unsure if region is the same as country. 
//'
//' @param detect_region Whether to automatically detect the region or not.
//' @return None.
// [[Rcpp::export]]
void setDetectRegion_cpp(bool detect_region)
{
  nativeAlpr->setDetectRegion(detect_region);
}

//' Sets how many candidates to return.
//'
//' @param top_n How many values to return. Default is 10.
//' @return None.
// [[Rcpp::export]]
void set_top_n(int top_n)
{
  nativeAlpr->setTopN(top_n);
}

//' Returns the openalpr library version number.
//'
//' @return The version number as a string
//' @export
// [[Rcpp::export]]
std::string get_version()
{
  std::string version = nativeAlpr->getVersion();
  return version;
}


//}
