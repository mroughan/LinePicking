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
  tmp <- .C('LinePickingMean',
            mean = as.double(0),
            problem = as.integer(problem),
            parameters = as.double(parameters),
            Npar = as.integer(length(parameters)),
            results = as.integer(99),
            error_str = as.character(""))
  if(tmp$results != 0 ){
    stop(tmp$error_str)
  } else {
    return(tmp$mean)    
  }
}
