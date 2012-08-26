#' Plot the linepicking class to standard output.
#'
#' @param x A \code{linepicking} object.
#' @param dist either "pdf" for pdf or "cdf" for cdf
#' @return NULL. Plots appropriate plot
#' @name plot
#' @aliases plot plot,linepicking-method
#' @docType methods
#' @rdname plot-methods
#' @export
#' @seealso \code{\link{plot}}
#' @examples
#' tmp <- CreateLinePicking(mode=0,para=10)
#' plot(tmp)
#' plot(tmp,dist="cdf")
setMethod("plot", "linepicking", function(x,dist='pdf',...){
  if(dist == 'pdf'){
    plot(x@t,x@pdf,type='l',xlab='t',ylab='f(t)',...)
  } else {
    plot(x@t,x@cdf,type='l',xlab='t',ylab='P(T<=t)',...)
  }
})