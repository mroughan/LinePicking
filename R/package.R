#'  Numerical code for geometric probability problems, 
#'  in particular PDFs, CDFs, means and variances for the "line picking" problem.
#'  
#'  The problem is a standard problem in stochastic
#'  geometry, where we pick lines at random from some region. The typical
#'  questions one asks are: what will the mean line length be? What will
#'  the Probability Density Function (PDF) be? This software implements the 
#'  current list of known PDFs, CDFs, means and variances for such problems.
#'  It also provides solutions to some previously unsolved problems. 
#' 
#'  The library has been designed to provide a small set of entry points  
#'  which are callable from R, Matlab and other C programs. Documentation
#'  for the R and Matlab bindings to this libary have been provided 
#'  in the a format suitable for each of their help systems.
#' 
#'  Much of this manual is dedicated to documenting functions specific 
#'  to a particular problem but users of the library generally only need to 
#'  understand the entry points documented in the api.
#'  
#' @name LinePicking
#' @references see \url{http://doi.acm.org/10.1145/131766.131776}
#' @references see \url{http://www.boost.org/doc/libs/1_38_0/libs/math/doc/sf_and_dist/html/math_toolkit/special/sf_beta/ibeta_function.html}
#' @references see \url{http://dlmf.nist.gov/8.17}
#' @author Eric Parsonage, Matt Roughan, Jono Tuke
#' @useDynLib LinePicking
#' @docType package
NULL
