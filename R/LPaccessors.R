#' Get mode for \code{linepicking} object
#'
#' Returns the mode for \code{linepicking} object rather than using @@
#'
#' @param x A \code{linepicking} object
#' @return value from slot
#' @export
#' @author Eric Parsonage, Matt Roughan, Jono Tuke
#' @examples
#' tmp <- CreateLinePicking(mode=0,para=10)
#' space(tmp)
setGeneric("space",function(x) {
  standardGeneric("space")
})
setMethod("space", "linepicking", function(x){
  slot(x,"mode")
})
#' Get para for \code{linepicking} object
#'
#' Returns the para for \code{linepicking} object rather than using @@
#'
#' @param x A \code{linepicking} object
#' @return value from slot
#' @export
#' @author Eric Parsonage, Matt Roughan, Jono Tuke
#' @examples
#' tmp <- CreateLinePicking(mode=0,para=10)
#' para(tmp)
#'
setGeneric("para", function(x) {
  standardGeneric("para")
})
setMethod("para", "linepicking", function(x){
  slot(x,"parameters")
})
#' Get support for \code{linepicking} object
#'
#' Returns the support for \code{linepicking} object rather than using @@
#'
#' @param x A \code{linepicking} object
#' @return value from slot
#' @export
#' @author Eric Parsonage, Matt Roughan, Jono Tuke
#' @examples
#' tmp <- CreateLinePicking(mode=0,para=10)
#' support(tmp)
#' para(tmp)
setGeneric("support",function(x) {
  standardGeneric("support")
})
setMethod("support", "linepicking", function(x){
  slot(x,"support")
})
#' Gets mean and variance for \code{linepicking} object
#'
#' Returns the mean and variance for \code{linepicking} object rather than using @@
#'
#' @param x A \code{linepicking} object
#' @return value from slot
#' @export
#' @author Eric Parsonage, Matt Roughan, Jono Tuke
#' @examples
#' tmp <- CreateLinePicking(mode=0,para=10)
#' stats(tmp)
setGeneric("stats",function(x) {
  standardGeneric("stats")
})
setMethod("stats", "linepicking", function(x){
  tmp <- c(mean=slot(x,"mean"),
           var=slot(x,"var"))
  return(tmp)
})
#' Calculates the pdf for a given distance and \code{linepicking} object
#'
#' Given a \code{linepicking} object and a distance t returns the probability density function 
#' 
#' @param x A \code{linepicking} object
#' @param t a distance
#' @return probability density function 
#' @export
#' @author Eric Parsonage, Matt Roughan, Jono Tuke
#' @examples
#' tmp <- CreateLinePicking(mode=0,para=10)
#' CalcPDF(tmp,t=5)
#'
setGeneric("CalcPDF",function(x,t) {
  standardGeneric("CalcPDF")
})
setMethod("CalcPDF", "linepicking", function(x,t){
  tmp <- LinePickingPDF(t,space(x),para(x))
  return(tmp)
})
#' Calculates the cdf for a given distance and \code{linepicking} object
#'
#' Given a \code{linepicking} object and a distance t returns the cumulative density function 
#' 
#' @param x A \code{linepicking} object
#' @param t a distance
#' @return cumulative density function
#' @export
#' @author Eric Parsonage, Matt Roughan, Jono Tuke
#' @examples
#' tmp <- CreateLinePicking(mode=0,para=10)
#' CalcCDF(tmp,t=5)
#'
setGeneric("CalcCDF",function(x,t) {
  standardGeneric("CalcCDF")
})
setMethod("CalcCDF", "linepicking", function(x,t){
  tmp <- LinePickingCDF(t,space(x),para(x))
  return(tmp)
})
