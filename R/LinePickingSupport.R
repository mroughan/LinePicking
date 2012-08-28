#' Returns support for pdf for given mode and parameters
#'
#' Given a mode see \link{LinePickingPDF} and parameters gives the range
#' distance t such that the pdf is non-zero
#' @param mode see \code{\link{LinePickingPDF}}
#' @param parameters the parameter necessary to describe 
#' the space given by mode.
#' @return min and max values of support
#' @author Eric Parsonage, Matt Roughan, Jono Tuke
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
