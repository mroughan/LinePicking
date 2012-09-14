#' Get the numeric kth moment for LinePicking problem
#'
#' Uses numerical integration to give the kth moment
#' 
#' @param problem the problem number
#' @param parameters the parameters of the problem of interest
#' @param k which moment
#' @return expected value
#' @author Eric Parsonage, Matt Roughan, Jono Tuke
#' @export
#' @note September 14 2012
#' @keywords internal
GetNumMoment <- function(problem,parameters,k=1){
  f <- function(x,problem,parameters,k){
    return( (x^k) * LinePickingPDF(x,problem=problem,parameters=parameters))
  }
  support <- LinePickingSupport(problem=problem,parameters=parameters)
  tmp <- integrate(f,lower=support[1],upper=support[2],problem=problem,parameters=parameters,k=k)
  return(tmp$value)
}