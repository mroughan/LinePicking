#' Get the numeric cdf for LinePicking problem
#'
#' Uses numerical integration to give the cdf
#' 
#' @param problem the problem number
#' @param parameters the parameters of the problem of interest
#' @param t value for cdf
#' @return cdf
#' @author Eric Parsonage, Matt Roughan, Jono Tuke
#' @export
#' @note September 14 2012
#' @keywords internal
GetNumCDF <- function(problem,parameters,t){
  support <- LinePickingSupport(problem=problem,parameters=parameters)
  cdf <- t
  for ( i in 1:length(t)){
    cdf[i] <- integrate(LinePickingPDF,lower=support[1],upper=t[i],
                        problem=problem,parameters=parameters)$value
  }
  return(cdf)
}
