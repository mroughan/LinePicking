#' Get simulated distances between two random points
#'
#' Give the number of distances required
#'
#' and the shape (square, disk, ...) and 
#' parameters defining the shape, 
#' and a seed for the random number generator this 
#' function will return a list of distances.
#'
#' @inheritParams LinePickingPDF
#' @return vector of probability density function values for each
#' element in t.
#' @author Eric Parsonage
#' @export
#' @useDynLib LinePicking
#' @note September 9 2012
#' @examples
#' t <- seq(0,1,l=1000)
#' y <- LinePickingCDF(t=t,problem=0,para=1)
#' plot(t,y,type='l')
LinePickingSimPoints <-
  function(NPoints, problem, parameters, seed)
  {
    tmp <- .Call('rLinePickingSimPoints',
              as.integer(NPoints),
              as.integer(problem),
              parameters,
              as.integer(seed))
      
  }
