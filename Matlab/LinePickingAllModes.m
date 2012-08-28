function [names descriptions] =  LinePickingAllModes(mode) 
%
%     Copyright 2012 Eric Parsonage <eric.parsonage@adelaide.edu.au>
%     This program is free software: you can redistribute it and/or modify
%     it under the terms of the GNU General Public License as published by
%     the Free Software Foundation, either version 3 of the License, or
%     (at your option) any later version.
%   
%     This program is distributed in the hope that it will be useful,
%     but WITHOUT ANY WARRANTY; without even the implied warranty of
%     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
%     GNU General Public License for more details.
%
%     You should have received a copy of the GNU General Public License
%     along with this program.  If not, see <http://www.gnu.org/licenses/>.
% 
% LinePickingModeLookup(mode) gets information for a given mode
%
% INPUTS:       
%    mode = region type to get information about
%         
% OUTPUTS:
%    [name description] arrays of strings with name and description of each mode
%
%     
% See Also LinePickingPDF, LinePickingCDF, LinePickingMean, LinePickingVar, LinePickingSupport, LinePickingCheckParameters, LinePickingPrintAllModes, LinePickingAllModes 
%         
%

[names descriptions] = LinePicking(8);
