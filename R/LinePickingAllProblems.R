#' Gets list of all problems
#'
#' Problems are integers describing possible geometries
#' for the line picking problem. This function prints 
#' all possible problems.
#' 
#' @param print boolean if TRUE then prints out all the info
#' @return list with information on each problem
#' @author Eric Parsonage, Matt Roughan, Jono Tuke
#' @export
#' @useDynLib LinePicking
#' @examples
#' LinePickingAllProblems()
LinePickingAllProblems <- function(print=TRUE){
  tmp <- .Call("rLinePickingAllProblems")
  if(print){
    for(i in 1:length(tmp)){
      problem <- i - 1  
      cat("Problem",problem,'\n')
      cat("==========\n")
      FormatProblem(tmp[[i]])
    }
  }
  return(tmp)
}
