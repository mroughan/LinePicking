#' Accessor functions for linepicking object
#'
#' Gets to the slots with out using @@
#'
#' @param x A \code{linepicking} object
#' @return value from slot
#' @export
#' @docType methods
#' @rdname accessor-methods
#' @examples
#' tmp <- CreateLinePicking(mode=0,para=10)
#' mode(tmp)
#' stats(tmp)
#' 
setGeneric("mode",function(x) {
  standardGeneric("mode")
})
#' @rdname accessor-methods
#' @aliases accessor,linepicking-method
setMethod("mode", "linepicking", function(x){
  slot(x,"mode")
})
#' @rdname accessor-methods
#' @aliases accessor,linepicking-method
setGeneric("para", function(x) {
  standardGeneric("para")
})
#' @rdname accessor-methods
#' @aliases accessor,linepicking-method
setMethod("para", "linepicking", function(x){
  slot(x,"parameters")
})
#' @rdname accessor-methods
#' @aliases support
#' @export
setGeneric("support",function(x) {
  standardGeneric("support")
})
#' @rdname accessor-methods
#' @aliases support
#' @export
setMethod("support", "linepicking", function(x){
  slot(x,"support")
})
setGeneric("stats",function(x) {
  standardGeneric("stats")
})
setMethod("stats", "linepicking", function(x){
  tmp <- c(mean=slot(x,"mean"),
           var=slot(x,"var"))
  return(tmp)
})
setGeneric("pdf",function(x,t) {
  standardGeneric("pdf")
})
setMethod("pdf", "linepicking", function(x,t){
  tmp <- LinePickingPDF(t,mode(x),para(x))
  return(tmp)
})
