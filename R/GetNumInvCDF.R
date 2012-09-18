#' Gets numerical inverse CDF
#' 
#' For the cases where c code does not return an inverse CDF. This
#' uses uniroot to find an approximation.
#'
#' @param problem see \link{LinePickingCDF}
#' @param parameters 
#' @param t probabilities
#' @return points x such that P(X <= x)=t
#' @author Eric Parsonage, Matt Roughan, Jono Tuke
#' @export
#' @note September 18 2012
#' @keywords internal
GetNumInvCDF <- function(problem,parameters,t){ 
  f <- function(x,problem,parameters,t){
    return(LinePickingCDF(t=x,problem=problem,parameters=parameters)-t)
  }
  invCDF <- t
  for(i in 1:length(t)){
    if( t[i] < 0 | t[i] > 1){
      stop("t must be between 0 and 1")
    }
    invCDF[i] <- uniroot(f,
                         interval=LinePickingSupport(problem=problem,
                                                     parameters=parameters),
                         problem=problem,parameters=parameters,t=t[i])$root
  }
  return(invCDF)
}
