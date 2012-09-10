#' Get cdf for distance between two random points
#'
#' Give a shape (square, disk, ...) and 
#' parameters defining the shape, this 
#' function will give  the probability density
#' function for the distances
#' between two Poisson distributed points in the space.
#'
#' @inheritParams LinePickingPDF
#' @return vector of probability density function values for each
#' element in t.
#' @author Eric Parsonage, Matt Roughan, Jono Tuke
#' @export
#' @useDynLib LinePicking
#' @note August 25 2012
#' @examples
#' t <- seq(0,1,l=1000)
#' y <- LinePickingCDF(t=t,problem=0,para=1)
#' plot(t,y,type='l')
LinePickingCDF <-
function(t,problem=0,parameters){
    tmp <- .Call('rLinePickingCDF',
    as.double(t),
    as.integer(problem),
    as.double(parameters))
    return(tmp)
}