#' Prints list of all modes
#'
#' Modes are integers describing possible geometries for the line picking
#' problem. This function prints all possible modes.
#' 
#' @return prints out information
#' @author Matt Roughan, Jono Tuke, Eric Parsonage
#' @export
#' @useDynLib LinePicking
#' @note August 25 2012
#' @examples
#' LinePickingAllmodes()
LinePickingAllmodes <- function(){
  .C("LinePickingAllmodes")
  return()
}