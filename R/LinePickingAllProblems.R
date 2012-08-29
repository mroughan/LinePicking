#' Gets list of all problems
#'
#' Problems are integers describing possible geometries for the line picking
#' problem. This function prints all possible problems.
#' 
#' @param short_tab boolean is false gives description as well.
#' @return Data frame with 
#' \itemize{
#' \item problems: problem number see \code{\line{LinePickingPDF}}
#' \item names: list of the problem names
#' \item description: brief description of each space
#' }
#' @author Eric Parsonage, Matt Roughan, Jono Tuke
#' @export
#' @useDynLib LinePicking
#' @note August 25 2012
#' @examples
#' LinePickingAllProblems()
LinePickingAllProblems <- function(short_tab=TRUE){
  N <- LinePickingNumberOfProblems()
  tmp <- .C("LinePickingAllProblems",
            names = as.character(rep("",N)),
            description = as.character(rep("",N)))
  tmp <- data.frame(problem=0:(N-1),names=tmp$names,description=tmp$description)
  if(short_tab){
    tmp <- tmp[,1:2]
  }
  return(tmp)
}
