#' Gets information for a given mode
#'
#' Modes are integers describing possible geometries for the line picking
#' problem. This function gives you the information for a given mode.
#' 
#' @param mode see \code{\link{LinePickingPDF}}
#' @return prints out information
#' @author Eric Parsonage, Matt Roughan, Jono Tuke
#' @export
#' @useDynLib LinePicking
#' @note August 25 2012
#' @examples
#' LinePickingModeLookup(mode=0)
LinePickingModeLookup <- function(mode=0){
  tmp <- .C("LinePickingModeLookup",
            mode = as.integer(mode),
            name = as.character(""),
            description = as.character(""))
  print(tmp)
}
