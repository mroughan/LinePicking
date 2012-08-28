function g = LinePicking(entry t, mode, parameters)
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
% LinePicking(entry, ....) is the implementation of a number of functions
%
% INPUTS:
%    entry determines what function to call and hence what parameters are needed      
%         
%
%  TODO pull the values from the switch statement an plug them in here better 
%  
% NOTE it is not intended that most users will call this function diectly
%    there are a number of shim functions that povide a full api to the library
%
% See Also LinePickingPDF, LinePickingCDF, LinePickingMean, LinePickingVar, LinePickingSupport, LinePickingCheckParameters, LinePickingModeLookup, LinePickingPrintAllModes, LinePickingAllmodes