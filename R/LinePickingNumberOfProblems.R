#' Gets number of problems
#'
#' Problems are integers describing possible geometries for the line picking
#' problem.
#' 
#' @return N: number of problems 
#' @author Eric Parsonage, Matt Roughan, Jono Tuke
#' @export
#' @useDynLib LinePicking
#' @examples
#' LinePickingNumberOfProblems()
LinePickingNumberOfProblems <- function(){
  tmp <- .C("LinePickingNumberOfProblems",
            N = as.integer(0))
  return(tmp$N)
}
