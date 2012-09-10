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
  tmp <- .Call("rLinePickingSupport",
                as.integer(problem),
                as.numeric(parameters))
  return(tmp)
}
