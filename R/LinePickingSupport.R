#' Returns support for pdf for given problem and parameters
#'
#' Given a problem see \link{LinePickingPDF} and parameters gives the range
#' distance t such that the pdf is non-zero
#' @param problem see \code{\link{LinePickingPDF}}
#' @param parameters the parameter necessary to describe 
#' the space given by problem.
#' @return min and max values of support
#' @author Eric Parsonage, Matt Roughan, Jono Tuke
#' @export
#' @useDynLib LinePicking
#' @note August 25 2012
#' @examples
#' LinePickingSupport(problem=0,parameters=10)
LinePickingSupport <- function(problem=0, parameters){
  tmp <- .C("LinePickingSupport",
            t = as.numeric(rep(0,2)),
            problem = as.integer(problem),
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
