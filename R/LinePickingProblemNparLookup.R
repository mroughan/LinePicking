#' Gets number of problems
#'
#' Problems are integers describing possible geometries for the line picking
#' problem.
#' @param problem number of problem of interest
#' @return N number of parameters for this problem
#' @author Eric Parsonage, Matt Roughan, Jono Tuke
#' @export
#' @useDynLib LinePicking
#' @examples
#' LinePickingProblemNparLookup(problem=1)
LinePickingNparLookup <- function(problem=1){
  tmp <- .C("LinePickingProblemNparLookup",
            problem = as.integer(problem),
            Npar = as.integer(0))
  return(tmp$Npar)
}
