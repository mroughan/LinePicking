#' Create a class for LinePicking
#' 
#' Numerous slots. 
#'
#' @name linepicking-class
#' @rdname linepicking-class
#' @exportClass linepicking
#'
#' @examples
#' getSlots("linepicking")
#
setClass("linepicking",
         representation=representation(mode="numeric", 
                                       parameters="numeric",
                                       support="numeric",
                                       t="numeric",
                                       pdf="numeric",
                                       cdf="numeric",
                                       mean="numeric",
                                       var="numeric")
)