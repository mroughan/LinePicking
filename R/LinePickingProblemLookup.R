#' Gets information for a given problem
#'
#' Problemss are integers describing possible geometries for the line picking
#' problem. This function gives you the information for a given problem.
#' 
#' @param problem see \code{\link{LinePickingPDF}}
#' @return prints out information
#' @author Eric Parsonage, Matt Roughan, Jono Tuke
#' @export
#' @useDynLib LinePicking
#' @note August 25 2012
#' @examples
#' LinePickingProblemLookup(problem=0)
LinePickingProblemLookup <- function(problem=0){
  N <- LinePickingNparLookup(problem=problem)
  if(N == -1){
    stop("That problem is giving problems with number of parameters")
  }
  tmp <- .C("LinePickingProblemLookup",
            problem = as.integer(problem),
            name = as.character(""),
            description = as.character(""),
            Npar = as.integer(0),
            parameters = as.numeric(rep(0,N)))
  return(tmp)
}
