#' Returns support for pdf for given mode and parameters
#'
#' Given a mode see \link{LinePickingPDF} and parameters gives the range
#' distance t such that the pdf is non-zero
#' @param mode \itemize{
#'    \item 0 square, with side length parameters[0]
#'    \item 1 disk, with radius parameters[0]
#'    \item 2 hyper-ball, dimension parameters[0], radius parameters[1]
#'    \item 3 rectangle, side lengths parameters[0], parameters[1]
#'    \item 4 line, length parameters[0]
#'    \item 5 cube, side length parameters[0]
#'    \item 6 sphere, with radius parameters[0]
#'    \item 7 sphere geodesic, with radius parameters[0]
#'    \item 8 prism geodesic, with length parameters[0], and perimeter parameters[1]
#' }
#' @param para the parameter necessary to describe 
#' the space given by mode.
#' @return min and max values of support
#' @author Matt Roughan, Jono Tuke, Eric Parsonage
#' @export
#' @useDynLib LinePicking
#' @note August 25 2012
#' @examples
#' LinePickingSupport(mode=0,parameters=10)
LinePickingSupport <- function(mode=0, parameters){
  tmp <- .C("LinePickingSupport",
            t = as.numeric(rep(0,2)),
            mode = as.integer(mode),
            parameters = as.numeric(parameters),
            Npar = as.integer(length(parameters)),
            results = as.integer(99),
            error_str = as.character(""))
  if(tmp$results != 0 ){
    stop(tmp$error_str)
  } else {
    return(tmp$t)
  }
}
