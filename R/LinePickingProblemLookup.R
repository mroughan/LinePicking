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
    if (problem < 0 | problem >= n){
        stop(paste("That problem does not exist,", 
        "there are only problems 0 -",n - 1,"\n"))
    }
    problem <- problem + 1; 
    x <- tmp[[problem]]
    if(print){
      cat("Problem",problem-1,'\n')
      cat("==========\n")
      FormatProblem(x)
    }
    return(x)
}
