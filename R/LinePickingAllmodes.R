#' Prints list of all modes
#'
#' Modes are integers describing possible geometries for the line picking
#' problem. This function prints all possible modes.
#' 
#' @return prints out information
#' @author Eric Parsonage, Matt Roughan, Jono Tuke
#' @export
#' @useDynLib LinePicking
#' @note August 25 2012
#' @examples
#' LinePickingAllModes()
LinePickingAllModes <- function(){
  .C("LinePickingAllModes")
  return()
}
