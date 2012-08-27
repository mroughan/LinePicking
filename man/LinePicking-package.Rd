\name{LinePicking-package}
\alias{LinePicking-package}
\alias{LinePicking}
\docType{package}
\title{
Probability density function for distance between points
~~ package title ~~
}
\description{
Given Poisson points in a space, gives
    the probability density function for the distance between these points.
~~ A concise (1-5 lines) description of the package ~~
}
\details{
\tabular{ll}{
Package: \tab LinePicking\cr
Type: \tab Package\cr
Version: \tab 1.0\cr
Date: \tab 2012-08-25\cr
License: \tab GPL 3.0\cr
Collate: \tab 
'LinePickingPDF.R'
'LinePickingModeLookup.R'
'LinePickingAllmodes.R'
'LinePickingCheckParameters.R'
'LinePickingCDF.R'
'LinePickingMean.R'
'LinePickingSupport.R'
'LinePickingVar.R'
'LPclasses.R'
'initialize.R'
'LPaccessors.R'
'LPplot.R'
'LPshow.R'\cr
Built: \tab R 2.15.1; universal-apple-darwin9.8.0; 2012-08-26 23:41:59 UTC; unix\cr
}

Index:
\preformatted{
CalcCDF                 Calculates the cdf for a given distance and
                        'linepicking' object
CalcPDF                 Calculates the pdf for a given distance and
                        'linepicking' object
CreateLinePicking       Creates a linepicking object from mode and
                        parameters
LinePickingAllmodes     Prints list of all modes
LinePickingCDF          Get cdf for distance between two random points
LinePickingCheckParameters
                        Check that a mode and a set of parameters are
                        valid
LinePickingMean         Get expected value for given mode and
                        parameters
LinePickingModeLookup   Gets information for a given mode
LinePickingPDF          Get pdf for distance between two random points
LinePickingSupport      Returns support for pdf for given mode and
                        parameters
LinePickingVar          Get variance for given mode and parameters
linepicking-class       Create a class for LinePicking
para                    Get para for 'linepicking' object
plot                    Plot the linepicking class to standard output.
print                   Print the linepicking class to standard output.
space                   Get mode for 'linepicking' object
stats                   Gets mean and variance for 'linepicking' object
support                 Get support for 'linepicking' object
}
~~ An overview of how to use the package, including the most important functions ~~
}
\author{
Eric Parsonage, Matt Roughan, Jono Tuke

Maintainer: Jono Tuke <simon.tuke@adelaide.edu.au>
~~ The author and/or maintainer of the package ~~
}
\references{
~~ Literature or other references for background information ~~
}
~~ Optionally other standard keywords, one per line, from file KEYWORDS in the R documentation directory ~~
\keyword{ package }
\seealso{
~~ Optional links to other man pages, e.g. ~~
~~ \code{\link[<pkg>:<pkg>-package]{<pkg>}} ~~
}
\examples{
~~ simple examples of the most important functions ~~
}
