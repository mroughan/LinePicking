#' Creates a linepicking object from mode and parameters
#'
#' Modes are integers describing possible geometries for the line picking
#' problem. Each has appropraite parameters
#' 
#' @param mode see \code{\link{LinePickingPDF}}
#' @param para parameters for mode.
#' @param n number of points for plots.
#' @return an instance of \code{linepicking} class
#' @author Matt Roughan, Jono Tuke, Eric Parsonage
#' @export
#' @useDynLib LinePicking
#' @note August 25 2012
#' @examples
#' tmp <- CreateLinePicking(mode=0,para=10)
#' print(tmp)
CreateLinePicking <- function(mode, para, n=1000){
  # Check possible space
  exit <- LinePickingCheckParameters(mode=mode, parameters=para)
  if(exit == 1){
    cat("Possible modes are :\n")
    LinePickingAllModes()
    return(NULL)
  }
  if(exit > 1) return(NULL)
  support <- LinePickingSupport(mode=mode,parameters=para)
  t <- seq(support[1],support[2],length=n)
  new("linepicking", 
      mode = mode, 
      parameters = para,
      support = LinePickingSupport(mode=mode,parameters=para), 
      t = t,
      pdf = LinePickingPDF(t=t,mode=mode,para=para),
      cdf = LinePickingCDF(t=t,mode=mode,para=para),
      mean = LinePickingMean(mode=mode,para=para),
      var = LinePickingVar(mode=mode,para=para))
}
