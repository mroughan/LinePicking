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
    n <- length(t)
    tmp <- .C('LinePickingCDF',
              t = as.double(t),
              cdf = as.double(rep(0,n)),
              n = as.integer(n),
              problem = as.integer(problem),
              parameters = as.double(parameters),
              Npar = as.integer(length(parameters)),
              results = as.integer(0),
              error_str = as.character(""))
    if(tmp$results != 0 ){
      stop(tmp$error_str)
    } else if (tmp$cdf==-1){
      lower <- LinePickingSupport(problem=problem,
                                parameters=parameters)[1]
      cdf <- integrate(LinePickingPDF,
                       lower=lower,
                       upper=t,
                       problem=problem,
                       parameters=parameters)
      return(cdf$value)
    }
    return(tmp$cdf)    
  }
LinePickingCDF_vector <- Vectorize(LinePickingCDF,vectorize.args="t")