#' Get slot values for \code{linepicking} object
#'
#' Returns the slot value for \code{linepicking} object rather than using @@
#'
#' @param x A \code{linepicking} object
#' @return value from slot
#' @name accessors
#' @export
#' @docType methods
#' @rdname accessor-methods
#' @author Eric Parsonage, Matt Roughan, Jono Tuke
#' @examples
#' tmp <- CreateLinePicking(problem=0,para=10)
#' problem(tmp)
setGeneric("problem",function(x) {
  standardGeneric("problem")
})
#' @rdname accessor-methods
#' @aliases problem,linepicking-method
setMethod("problem", "linepicking", function(x){
  slot(x,"problem")
})
#' @rdname accessor-methods
#' @aliases para
setGeneric("para", function(x) {
  standardGeneric("para")
})
#' @rdname accessor-methods
#' @aliases para,linepicking-method
setMethod("para", "linepicking", function(x){
  slot(x,"parameters")
})
#' @rdname accessor-methods
setGeneric("support",function(x) {
  standardGeneric("support")
})
#' @rdname accessor-methods
#' @aliases support,linepicking-method
setMethod("support", "linepicking", function(x){
  slot(x,"support")
})
#' @rdname accessor-methods
setGeneric("stats",function(x) {
  standardGeneric("stats")
})
#' @rdname accessor-methods
#' @aliases stats,linepicking-method
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
#' @rdname pdf-method
#' @author Eric Parsonage, Matt Roughan, Jono Tuke
#' @examples
#' tmp <- CreateLinePicking(problem=0,para=10)
#' CalcPDF(tmp,t=5)
#'
setGeneric("CalcPDF",function(x,t) {
  standardGeneric("CalcPDF")
})
#' @rdname pdf-method
#' @aliases CalcPDF,linepicking-method
setMethod("CalcPDF", "linepicking", function(x,t){
  tmp <- LinePickingPDF(t,problem(x),para(x))
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
#' @docType methods
#' @rdname cdf-method
#' @author Eric Parsonage, Matt Roughan, Jono Tuke
#' @examples
#' tmp <- CreateLinePicking(problem=0,para=10)
#' CalcCDF(tmp,t=5)
#'
setGeneric("CalcCDF",function(x,t) {
  standardGeneric("CalcCDF")
})
#' @aliases CalcCDF CalcCDF,linepicking-method
#' @rdname cdf-method
setMethod("CalcCDF", "linepicking", function(x,t){
  tmp <- LinePickingCDF(t,problem(x),para(x))
  return(tmp)
})
