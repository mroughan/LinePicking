#' Get inverse CDF for LinePicking problems
#' 
#' Takes a point, t, between 0 and 1 and returns point x such that 
#' P(X <= x) = t
#'
#' @param t number between 0 and 1, can also be a vector
#' @param problem see \link{LinePickingCDF}
#' @param parameters values to describe the problem
#' @param trace boolean, if true gives some extra info. Default is false
#' @return points x
#' @author Eric Parsonage, Matt Roughan, Jono Tuke
#' @export
#' @note September 18 2012
#' @examples
#' t <- seq(0,1,by=0.1)
#' LinePickingInverseCDF(t = t, problem = 0,parameters=1)
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
