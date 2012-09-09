#' Clean printing of problem
#' 
#' Nice printing of problem list
#'
#' @param x problem list
#' @return prints out information nice-like
#' @author Eric Parsonage, Matt Roughan, Jono Tuke
FormatProblem <- function(x){
  cat('The problem name is',x$name,'\n\n') 
  cat("Its description is:\n",x$description,'\n\n')
  if (x$npar == 1){
    cat("It is defined by one parameter",
        "whose default value is",as.numeric(x$parameters),'\n\n')
  } else {
    cat("It is defined by",x$npar,"parameters",
        "whose default values are",as.numeric(x$parameters),'\n\n')
  }
}
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
LinePickingProblemLookup <- function(problem=1,print=TRUE){
  tmp <- .Call("rLinePickingAllProblems")
  n <- length(tmp)
  if (problem <= 0 | problem > n){
    stop(paste("That problem does not exist,", 
         "there are only problems 0 -",n,"\n"))
  }
  x <- tmp[[problem]]
  if(print){
    FormatProblem(x)
  }
  return(x)
}
