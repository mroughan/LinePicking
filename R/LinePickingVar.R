#' Get variance for given problem and parameters
#'
#' For a given problem and parameters gives the variance
#'
#' @param problem see \code{\link{LinePickingPDF}}
#' @param parameters the parameter necessary to describe 
#' the space given by problem.
#' @return variance
#' @author Eric Parsonage, Matt Roughan, Jono Tuke
#' @export
#' @useDynLib LinePicking
#' @note August 25 2012
#' @examples
#' LinePickingVar(problem=0,parameters=10)
LinePickingVar <-
function(problem=0,parameters){
  tmp <- .Call('rLinePickingVar',
                as.integer(problem),
                as.double(parameters))
  if(tmp == -1){
    EX <- GetNumMoment(problem=problem,parameters=parameters,k=1)
    EX2 <- GetNumMoment(problem=problem,parameters=parameters,k=2)
    tmp <- EX2 - EX^2
  }
  return(tmp)    
}
