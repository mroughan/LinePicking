\name{LinePickingVar}
\alias{LinePickingVar}
\title{Get variance for given mode and parameters}
\usage{
  LinePickingVar(mode = 0, para)
}
\arguments{
  \item{mode}{\itemize{ \item 0 square, with side length
  parameters[0] \item 1 disk, with radius parameters[0]
  \item 2 hyper-ball, dimension parameters[0], radius
  parameters[1] \item 3 rectangle, side lengths
  parameters[0], parameters[1] \item 4 line, length
  parameters[0] \item 5 cube, side length parameters[0] }}

  \item{para}{the parameter necessary to describe the space
  given by mode.}
}
\value{
  variance
}
\description{
  For a given mode and parameters gives the variance
}
\note{
  August 25 2012
}
\examples{
LinePickingVar(mode=0,para=10)
}
\author{
  Matt Roughan, Jono Tuke, Eric Parsonage
}

