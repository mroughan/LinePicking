#' Print the linepicking class to standard output.
#'
#' @param object A \code{linepicking} object.
#'
#' @return NULL. Prints to standard out.
#'
#' @name print
#' @aliases print print,linepicking-method
#' @docType methods
#' @rdname print-methods
#' @export
#' @author Eric Parsonage, Matt Roughan, Jono Tuke
#' @examples
#' tmp <- CreateLinePicking(mode=0,para=10)
#' tmp
setMethod("show", "linepicking", function(object){
  cat("A LinePicking object with\n")
  cat("Mode:",space(object),"\n")
  LinePickingAllmodes()
  cat("Parameters:", para(object),"\n")
  cat("Support: ", support(object)[1],"-",
      support(object)[2],"\n",sep='')
  cat("Statistics:\n")
  print(stats(object))
})