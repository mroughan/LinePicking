#' Check that a mode and a set of parameters are valid
#'
#' Modes are integers describing possible geometries for the line picking
#' problem. This function takes a mode and a parameter vector and checks if 
#' valid
#' 
#' @param mode see \code{\link{LinePickingPDF}}
#' @param parameters numeric vector of parameter describing mode
#' @return exit code \itemize{
#' \item 0: parameters are valid
#' \item 1: unsupported mode
#' \item 2: parameters out of range.
#' \item 3: not enough parameters were entered.
#' \item 4: other error.
#' }
#' @author Eric Parsonage, Matt Roughan, Jono Tuke
#' @export
#' @useDynLib LinePicking
#' @note August 25 2012
#' @examples
#' LinePickingCheckParameters(mode=0, parameters=c(10))
#' LinePickingCheckParameters(mode=99,parameters=c(10))
#' LinePickingCheckParameters(mode=0, parameters=c(1,2))
#' LinePickingCheckParameters(mode=3, parameters=c(1))
LinePickingCheckParameters <- function(mode=0,parameters){
  Npar <- length(parameters)
  tmp <- .C("LinePickingCheckParameters",
            mode = as.integer(mode),
            parameters = as.numeric(parameters),
            Npar = as.integer(Npar),
            results = as.integer(0),
            error_str = as.character(""))
  if(tmp$results > 0){
    cat(tmp$error_str,"\n")
  }
  return(tmp$results)
}
