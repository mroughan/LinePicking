#' Get pdf for distance between two random points
#'
#' Give a shape (square, disk, ...) and parameters defining the shape, this 
#' function will give a the probability density function for the distances
#' between two Poisson distributed points in the space.
#'
#' @param t vector of points to calculate pdf for. 
#' @param mode \itemize{
#'    \item 0 square, with side length parameters[0]
#'    \item 1 disk, with radius parameters[0]
#'    \item 2 hyper-ball, dimension parameters[0], radius parameters[1]
#'    \item 3 rectangle, side lengths parameters[0], parameters[1]
#'    \item 4 line, length parameters[0]
#'    \item 5 cube, side length parameters[0]
#' }
#' @param para the parameter necessary to describe the space given by mode.
#' @return vector of probability density function values for each
#' element in t.
#' @author Matt Roughan, Jono Tuke
#' @export
#' @useDynLib linepdf
#' @note August 17 2012
#' @examples
#' t <- seq(0,1,l=1000)
#' y <- LinePickingPDF(t=t,mode=0,para=1)
#' plot(t,y,type='l')
LinePickingPDF <-
function(t,mode=0,para,results,error_str){
  n <- length(t)
  tmp <- .C('LinePickingPDF',
            t = as.double(t),
            pdf = as.double(rep(0,n)),
            n = as.integer(n),
            mode = as.integer(mode),
            para = as.double(para),
            Npar = as.integer(length(para)),
	    results = as.integer(results),
	    error_str = as.string(error_str))
  return(tmp$pdf)
}
