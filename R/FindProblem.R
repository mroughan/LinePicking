#' Gets problem from list of problems
#'
#'
#' Takes either a problem number of name and finds it in the list of all problems
#'
#' @param x list of all problems
#' @param problem problem number or name
#' @return index or -1 if error
#' @author Eric Parsonage, Matt Roughan, Jono Tuke
#' @export
#' @note September 14 2012
#' @keywords internal
FindProblem <- function(x,problem=0){
  warn <- "No problem of that number or name"
  if(is.numeric(problem)){
    index <- which(sapply(x,function(x)x$problem)==problem)
    if(length(index)==0){
      cat(warn)
      return(-1)
    }
    return(index)
  } else if(is.character(problem)) {
    names <- sapply(x,function(x)x$name)
    index <- grep(problem,names)
    if(length(index)==0){
      cat(warn)
      return(-1)
    } else if(length(index) > 1){
      cat("There is more than one problem for that name\nThey are\n\n")
      for ( i in index){
        print(x[[i]])
      }
      return(-1)
    } else {
      return(index)
    }
  }
}
