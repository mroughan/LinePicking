#' Function to print out information about a given problem
#' 
#' Uses internal function format list to print nice
#' 
#' @param problem see \code{\link{LinePickingPDF}}
#' @param print boolean if TRUE prints out problem nicely
#' @return list of problem info
#' @author Eric Parsonage, Matt Roughan, Jono Tuke
#' @export
#' @useDynLib LinePicking
#' @examples
#' LinePickingProblemLookup(problem=1)
LinePickingProblemLookup <- function(problem=0,print=TRUE){
    tmp <- .Call("rLinePickingAllProblems")
    n <- length(tmp)
    index <- FindProblem(x=tmp,problem=problem)
    if(index==-1) stop()
    x <- tmp[[index]]
    if(print){
      cat("Problem",x$problem,'\n')
      cat("==========\n")
      FormatProblem(x)
    }
    return(x)
}
