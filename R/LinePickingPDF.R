#' Get pdf for distance between two random points
#'
#' Give a shape (square, disk, ...) and 
#' parameters defining the shape, this 
#' function will give a the probability density
#' function for the distances
#' between two Poisson distributed points in the space.
#'
#' @param t vector of points to calculate pdf for. 
#' @param problem \itemize{
#'    \item 0 Square, with side length parameters[0]
#'    \item 1 Disk, with radius parameters[0]
#'    \item 2 Hyper-ball, dimension parameters[0], radius parameters[1]
#'    \item 3 Rectangle, side lengths parameters[0], parameters[1]
#'    \item 4 Line, length parameters[0]
#'    \item 5 Cube, side length parameters[0]
#'    \item 6 Sphere, with radius parameters[0]
#'    \item 7 SphereGeodesic, with radius parameters[0]
#'    \item 8 PrismGeodesic, TBA
#' }
#' @param para the parameter necessary to describe 
#' the space given by problem.
#' @return vector of probability density function values for each
#' element in t.
#' @author Eric Parsonage, Matt Roughan, Jono Tuke
#' @export
#' @useDynLib LinePicking
#' @note August 25 2012
#' @examples
#' t <- seq(0,1,l=1000)
#' y <- LinePickingPDF(t=t,problem=0,para=1)
#' plot(t,y,type='l')
LinePickingPDF <-
function(t,problem=0,para){
  n <- length(t)
  tmp <- .C('LinePickingPDF',
            t = as.double(t),
            pdf = as.double(rep(0,n)),
            n = as.integer(n),
            problem = as.integer(problem),
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
