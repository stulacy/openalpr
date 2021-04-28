#' @useDynLib openalpR
#' @importFrom Rcpp sourceCpp
#' @importFrom Rcpp evalCpp
NULL

#' Instantiates a number plate recognizer.
#'
#' @param country Either 'eu' or 'us'
#' @param configFile File path to config file
#' @param runtimeDir File path to runtime dir
#' @return None
#' @export
initialize <- function(country="eu",
                       configFile="/etc/openalpr/openalpr.conf",
                       runtimeDir="/usr/share/openalpr/runtime_data") {
    # Here can assign defaults depending on OS. Easier to do in R than C++
    initialize_cpp(country, configFile, runtimeDir)
}

#' Detects number plates in an image file
#'
#' @param filepath The location on disk of the image file
#' @return A JSON containing candidate number plates
#' @export
detect <- function(filepath) {
    res <- recognize_file_cpp(filepath)
    res_json <- jsonlite::fromJSON(res)
    res_json$results$candidates
}
