#' Gets list of all problems
#'
#' Problems are integers describing possible geometries for the line picking
#' problem. This function prints all possible problems.
#' 
#' @param df boolean if TRUE then data frame else a list
#' @return Data frame or list with information on each problem
#' @author Eric Parsonage, Matt Roughan, Jono Tuke
#' @export
#' @useDynLib LinePicking
#' @examples
#' LinePickingAllProblems()
LinePickingAllProblems <- function(df=TRUE){
  tmp <- .Call("EricsLinePickingAllProblems")
  if(df){
    npar <- GetMaxNpar(tmp)
    tab <- NULL
    for(i in 1:length(tmp)){
      x <- ConvertListToDF(tmp[[i]],npar)
      tab <- rbind(tab,x)
    }
    return(tab)
  } else {
    return(tmp)
  }
}
