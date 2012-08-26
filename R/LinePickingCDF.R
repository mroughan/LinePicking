#' Get cdf for distance between two random points
#'
#' Give a shape (square, disk, ...) and 
#' parameters defining the shape, this 
#' function will give a the probability density
#' function for the distances
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
#'    \item 6 sphere, with radius parameters[0]
#'    \item 7 sphere geodesic, with radius parameters[0]
#'    \item 8 prism geodesic, with length parameters[0], and perimeter parameters[1]
#' }
#' @param para the parameter necessary to describe 
#' the space given by mode.
#' @return vector of probability density function values for each
#' element in t.
#' @author Matt Roughan, Jono Tuke, Eric Parsonage
#' @export
#' @useDynLib LinePicking
#' @note August 25 2012
#' @examples
#' t <- seq(0,1,l=1000)
#' y <- LinePickingCDF(t=t,mode=0,para=1)
#' plot(t,y,type='l')
LinePickingCDF <-
function(t,mode=0,para){
  n <- length(t)
  tmp <- .C('LinePickingCDF',
            t = as.double(t),
            pdf = as.double(rep(0,n)),
            n = as.integer(n),
            mode = as.integer(mode),
            para = as.double(para),
            Npar = as.integer(length(para)),
            results = as.integer(0),
            error_str = as.character(""))
  if(tmp$results != 0 ){
    stop(tmp$error_str)
  } else {
    return(tmp$pdf)    
  }
}
