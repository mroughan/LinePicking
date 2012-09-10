#' Clean printing of problem
#' 
#' Nice printing of problem list
#'
#' @param x problem list
#' @return prints out information nice-like
#' @author Eric Parsonage, Matt Roughan, Jono Tuke
#' @export
#' @keywords internal
FormatProblem <- function(x){
  cat('The problem name is',x$name,'\n\n') 
  cat('Its number is:',x$problem,'\n\n')  
  cat("Its description is:\n",x$description,'\n\n')
  if (x$npar == 1){
    cat("It is defined by one parameter",
        "whose default value is",as.numeric(x$parameters),'\n\n')
  } else {
    cat("It is defined by",x$npar,"parameters",
        "whose default values are",as.numeric(x$parameters),'\n\n')
  }
}