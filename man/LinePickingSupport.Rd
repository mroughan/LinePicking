\name{LinePickingSupport}
\alias{LinePickingSupport}
\title{Returns support for pdf for given mode and parameters}
\usage{
  LinePickingSupport(mode = 0, parameters)
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
  min and max values of support
}
\description{
  Given a mode see \link{LinePickingPDF} and parameters
  gives the range distance t such that the pdf is non-zero
}
\note{
  August 25 2012
}
\examples{
LinePickingSupport(mode=0,parameters=10)
}
\author{
  Matt Roughan, Jono Tuke, Eric Parsonage
}

