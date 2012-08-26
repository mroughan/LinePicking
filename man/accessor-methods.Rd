\docType{methods}
\name{mode}
\alias{accessor,linepicking-method}
\alias{mode}
\alias{para}
\alias{support}
\title{Accessor function for linepicking x}
\arguments{
  \item{x}{A \code{linepicking} x}
}
\value{
  value from slot
}
\description{
  Gets to the slots with out using @
}
\examples{
tmp <- CreateLinePicking(mode=0,para=10)
mode(tmp)
stats(tmp)
}

