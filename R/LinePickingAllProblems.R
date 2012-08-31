#' Gets list of all problems
#'
#' Problems are integers describing possible geometries for the line picking
#' problem. This function prints all possible problems.
#' 
#' @param short_tab boolean is false gives description as well.
#' @return Data frame with information on each problem
#' @author Eric Parsonage, Matt Roughan, Jono Tuke
#' @export
#' @useDynLib LinePicking
#' @note August 25 2012
#' @examples
#' LinePickingAllProblems()
LinePickingAllProblems <- function(short_tab=TRUE){
  N <- LinePickingNumberOfProblems()
  tab <- NULL
  for(i in 0:(N-1)){
    tab <- rbind(tab,LinePickingProblemLookup(problem=i))
  }
  tab <- data.frame(tmp)
  if(short_tab){
    tab <- tab[,1:2]
  }
  return(tab)
}
