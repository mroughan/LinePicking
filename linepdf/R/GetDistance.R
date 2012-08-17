#' Get pdf for distance between two random points
#'
#' to do
#' sum of them
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
#' @return data
#' @author Matt Roughan, Jono Tuke
#' @export
#' @note August 17 2012
#' @examples
#' GetDistance(t=1:100,mode=0,para=50)
GetDistance <-
function(t,mode=0,para){
  n <- length(t)
  tmp <- .C('distance_dist',
            t = as.double(t),
            tab = as.double(rep(0,n)),
            n = as.integer(n),
            mode = as.integer(mode),
            para = as.double(para),
            Npar = as.integer(length(para)))
  return(tmp)
}
