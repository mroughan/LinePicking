# internal function to get number of non-empty entries
GetLength <- function(x){
  i <- min(which(x==""))
  return(i)
}
#' Gets list of all problems
#'
#' Problemss are integers describing possible geometries for the line picking
#' problem. This function prints all possible problems.
#' 
#' @return List with 
#' \itemize{
#' \item names: list of the spaces names
#' \item description: brief description of each space
#' }
#' @author Eric Parsonage, Matt Roughan, Jono Tuke
#' @export
#' @useDynLib LinePicking
#' @note August 25 2012
#' @examples
#' LinePickingAllProblems()
LinePickingAllProblems <- function(){
  tmp <- .C("LinePickingAllProblems",
            names = as.character(rep("",100)),
            description = as.character(rep("",100)))
  n <- GetLength(tmp$names) - 1
  tmp$names <- tmp$names[1:n]
  tmp$description <- tmp$description[1:n]
  return(tmp)
}