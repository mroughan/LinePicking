#' List to data frame
#'
#' Takes a list from LinePickingAllProblems and converts to data frame
#' taking into account the mismatch in number of parameters.
#' Interval function so avoid using.
#'
#' @param x problem list from LinePickingAllProblems c code
#' @param npar Maximum number of parameters that are found in all 
#' problems
#' @return data frame or list
#' @author Eric Parsonage, Matt Roughan, Jono Tuke
ConvertListToDF <- function(x,npar){
  n <- x$npar
  x <- as.data.frame(x)
  if(n < npar){
    full.para <- rep(NA,npar-n)
    x <- data.frame(x,full.para)
  }
  index <- (ncol(x)-npar+1):ncol(x)
  colnames(x)[index] <- paste("P",1:npar,sep='')
  return(x)
}
#' Get max number of parameters
#'
#' Takes a list of all problems in LinePicking and returns
#' the maximum number of parameters.
#' Internal function.
#'
#' @param x list of all problems from LinePickingAllProblems C code
#' @return maximum number of parameters
#' @author Eric Parsonage, Matt Roughan, Jono Tuke
GetMaxNpar <- function(x){
  return(max(sapply(x,function(x) return(x$npar))))
}
#' Function to return data frame or list of information for a given 
#' problem. Problems are integers describing possible geometries 
#' for the line picking problem. 
#' 
#' @param problem see \code{\link{LinePickingPDF}}
#' @param df boolean if TRUE returns a formated data frame
#' if FALSE returns list.
#' @return returns information as either data frame or list
#' @author Eric Parsonage, Matt Roughan, Jono Tuke
#' @export
#' @useDynLib LinePicking
#' @examples
#' LinePickingProblemLookup(problem=1)
LinePickingProblemLookup <- function(problem=1,df=FALSE){
  tmp <- .Call("EricsLinePickingAllProblems")
  n <- length(tmp)
  if (problem <= 0 | problem > n){
    stop(paste("That problem does not exist,", 
         "there are only problems 0 -",n,"\n"))
  }
  x <- tmp[[problem]]
  if(df){
    npar <- GetMaxNpar(tmp)
    x <- ConvertListToDF(x,npar)
  }
  return(x) 
}