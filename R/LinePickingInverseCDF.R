#' Get inverse cdf for distance between two random points
#' @author Eric Parsonage
#' @export
#' @useDynLib LinePicking
#' @note September 17 2012
#' @examples
#' t <- seq(0,1,l=1000)
#' y <- InverseLinePickingCDF(t=t,problem=0,para=1)
#' plot(t,y,type='l')
LinePickingInverseCDF <-
function(t,problem=0,parameters,trace=FALSE){
    tmp <- .Call('rLinePickingInverseCDF',
    as.double(t),
    as.integer(problem),
    as.double(parameters))
    if(-1%in%tmp){
      if(trace){
      cat("No inverse cdf so calculating using GetNumInvCDF\n")
      }
      tmp <- GetNumInvCDF(problem=problem,parameters=parameters,t=t)
    }
    return(tmp)
}
