#' Create a class for LinePicking
#' 
#' Easy way to play with linepicking. Define and space and this object
#' has most of the features of the space
#'
#' @exportClass linepicking
#' @name linepicking-class
#' @rdname linepicking-class
#' @author Eric Parsonage, Matt Roughan, Jono Tuke
#' @section Slots: \itemize{
#'    \item Problems: type of space
#'    \item parameters: parameters to define space
#'    \item support: range of values pdf if non-zero
#'    \item t: points in support for pdf and cdf
#'    \item pdf: probability density function for values t
#'    \item cdf: cumulative density function for values t
#'    \item mean: expected value of pdf
#'    \item var: variance of pdf
#' }
#' @return an object of class \code{linepicking}
#' @examples
#' getSlots("linepicking")
#
setClass("linepicking",
         representation=representation(problem="numeric", 
                                       parameters="numeric",
                                       support="numeric",
                                       t="numeric",
                                       pdf="numeric",
                                       cdf="numeric",
                                       mean="numeric",
                                       var="numeric")
)