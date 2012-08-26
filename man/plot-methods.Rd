\docType{methods}
\name{plot}
\alias{plot}
\alias{plot,linepicking-method}
\title{Plot the linepicking class to standard output.}
\arguments{
  \item{x}{A \code{linepicking} object.}

  \item{dist}{either "pdf" for pdf or "cdf" for cdf}
}
\value{
  NULL. Plots appropriate plot
}
\description{
  Plot the linepicking class to standard output.
}
\examples{
tmp <- CreateLinePicking(mode=0,para=10)
plot(tmp)
plot(tmp,dist="cdf")
}
\seealso{
  \code{\link{plot}}
}

