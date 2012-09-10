#' Get simulated distances between two random points 
#'
#' Give the number of distances required
#'
#' and the shape (square, disk, ...) and 
#' parameters defining the shape, 
#' and a seed for the random number generator this 
#' function will return a list of distances.
#'
#' @param N the number of distances to generate.
#' @param problem see \code{\link{LinePickingPDF}}.
#' @param parameters numeric vector of parameter describing problem.
#' @param seed a seed for the random number generator
#' @return vector of N distances. 
#' @author Eric Parsonage
#' @export
#' @useDynLib LinePicking
#' @note September 9 2012
#' @examples
#' t <- LinePickingSimDistances(10, 0 , list(1), 67)
LinePickingSimDistances <-
  function(N, problem, parameters, seed)
  {
    tmp <- .Call('rLinePickingSimDistances',
              as.integer(N),
              as.integer(problem),
              parameters,
              as.integer(seed))
      
  }
