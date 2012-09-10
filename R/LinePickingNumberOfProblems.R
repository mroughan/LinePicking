#' Gets number of problems
#'
#' Problems are integers describing possible geometries for the line picking
#' problem.
#' 
#' @return number of problems 
#' @author Eric Parsonage, Matt Roughan, Jono Tuke
#' @export
#' @useDynLib LinePicking
#' @examples
#' LinePickingNumberOfProblems()
LinePickingNumberOfProblems <- function(){
  tmp <- .Call("rLinePickingAllProblems")
  return(length(tmp))
}