#' Check that a problem and a set of parameters are valid
#'
#' Problems are integers describing possible 
#' geometries for the line picking problem. 
#' This function takes a problem and a parameter 
#' vector and checks if valid
#' 
#' @param problem see \code{\link{LinePickingPDF}}
#' @param parameters numeric vector of parameter describing problem
#' @return exit code \itemize{
#' \item 0: parameters are valid
#' \item 1: unsupported problem
#' \item 2: parameters out of range.
#' \item 3: not enough parameters were entered.
#' \item 4: other error.
#' }
#' @author Eric Parsonage, Matt Roughan, Jono Tuke
#' @export
#' @useDynLib LinePicking
#' @note August 25 2012
#' @examples
#' LinePickingCheckParameters(problem=0, parameters=c(10))
#' LinePickingCheckParameters(problem=99,parameters=c(10))
#' LinePickingCheckParameters(problem=0, parameters=c(1,2))
#' LinePickingCheckParameters(problem=3, parameters=c(1))
LinePickingCheckParameters <- function(problem=0,parameters){
  tmp <- .Call("rLinePickingCheckParameters",
            as.integer(problem),
            as.double(parameters))
  return(tmp)
}
