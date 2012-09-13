#' Get expected value for given problem and parameters
#'
#' For a given problem and parameters gives the expected value
#'
#' @param problem see \code{\link{LinePickingPDF}}
#' @param parameters the parameter necessary to describe 
#' the space given by problem.
#' @return expected value
#' @author Eric Parsonage, Matt Roughan, Jono Tuke
#' @export
#' @useDynLib LinePicking
#' @note August 25 2012
#' @examples
#' LinePickingMean(problem=0,parameters=10)
LinePickingMean <-
function(problem=0,parameters){
  tmp <- .Call('rLinePickingMean',
               as.integer(problem),
               parameters = as.double(parameters))
  return(tmp)
}

# TODO add numerical for mean -1
