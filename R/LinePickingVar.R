#' Get variance for given mode and parameters
#'
#' For a given mode and parameters gives the variance
#'
#' @param mode \itemize{
#'    \item 0 square, with side length parameters[0]
#'    \item 1 disk, with radius parameters[0]
#'    \item 2 hyper-ball, dimension parameters[0], radius parameters[1]
#'    \item 3 rectangle, side lengths parameters[0], parameters[1]
#'    \item 4 line, length parameters[0]
#'    \item 5 cube, side length parameters[0]
#' }
#' @param para the parameter necessary to describe 
#' the space given by mode.
#' @return variance
#' @author Matt Roughan, Jono Tuke, Eric Parsonage
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
