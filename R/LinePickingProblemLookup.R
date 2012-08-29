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
#' LinePickingProblemsLookup(problem=0)
LinePickingProblemsLookup <- function(problem=0){
  tmp <- .C("LinePickingProblemsLookup",
            problem = as.integer(problem),
            name = as.character(""),
            description = as.character(""))
  print(tmp)
}
