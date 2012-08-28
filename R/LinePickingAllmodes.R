# internal function to get number of non-empty entries
GetLength <- function(x){
  i <- min(which(x==""))
  return(i)
}
#' Gets list of all modes
#'
#' Modes are integers describing possible geometries for the line picking
#' problem. This function prints all possible modes.
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
#' LinePickingAllModes()
LinePickingAllModes <- function(){
  tmp <- .C("LinePickingAllModes",
            names = as.character(rep("",100)),
            description = as.character(rep("",100)))
  n <- GetLength(tmp$names) - 1
  tmp$names <- tmp$names[1:n]
  tmp$description <- tmp$description[1:n]
  return(tmp)
}