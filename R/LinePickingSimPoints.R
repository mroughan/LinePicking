#' Get simulated points on region  
#'
#' Give the number of points required
#' and the shape (square, disk, ...) and 
#' parameters defining the shape, 
#' and a seed for the random number generator this 
#' function will return a list of points.
#'
#' @param Npoints the number of points to generate.
#' @param problem see \code{\link{LinePickingPDF}}.
#' @param parameters numeric vector of parameters describing problem.
#' @param seed a seed for the random number generator
#' @return vector of N points. 
#' @author Eric Parsonage
#' @export
#' @useDynLib LinePicking
#' @note September 9 2012
#' @examples
#' t <- LinePickingSimDistances(10, 0 , list(1), 67)
LinePickingSimPoints <-function(NPoints, problem, parameters, seed){
  tmp <- .Call('rLinePickingSimPoints',
               as.integer(NPoints),
               as.integer(problem),
               as.double(parameters),
               as.integer(seed))
  return(t(tmp))
}
