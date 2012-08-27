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
