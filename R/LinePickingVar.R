#' Get variance for given mode and parameters
#'
#' For a given mode and parameters gives the variance
#'
#' @param mode

#' @param para the parameter necessary to describe 
#' the space given by mode.
#' @return variance
#' @author Eric Parsonage, Matt Roughan, Jono Tuke
#' @export
#' @useDynLib LinePicking
#' @note August 25 2012
#' @examples
#' LinePickingVar(mode=0,para=10)
LinePickingVar <-
function(mode=0,para){
  tmp <- .C('LinePickingVar',
            mean = as.double(0),
            mode = as.integer(mode),
            para = as.double(para),
            Npar = as.integer(length(para)),
            results = as.integer(99),
            error_str = as.character(""))
  if(tmp$results != 0 ){
    stop(tmp$error_str)
  } else {
    return(tmp$mean)    
  }
}
