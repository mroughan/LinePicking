function [ names, descriptions, Npar, parameters ] =  LinePickingAllProblems 
% LinePickingAllProblems returns information about the problems. 
%
%     This file was autogenerated by make_gateways.pl v0.01 (Tue Sep  4 2012),
%                                 on Fri  7 Sep 2012 09:53:42 CST
%
%     Copyright 2012 Matthew Roughan <matthew.roughan@adelaide.edu.au>
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
% LinePickingAllProblems returns information about the problems. 
%
%           Example:  [ names, descriptions, Npar, parameters ] =  LinePickingAllProblems 
% 
% INPUTS:       
%
%         
% OUTPUTS:
%    output argument 1 = names, a cell array of problem names 
%    output argument 2 = descriptions, a cell array of brief descriptions of each problem 
%    output argument 3 = Npar, a cell array of the number of parameters for each problem 
%    output argument 4 = parameters, a cell array of arrays of parameters 
%
%
%     
% See Also LinePicking, LinePickingAllProblems, LinePickingCDF, LinePickingCheckParameters, LinePickingMean, LinePickingNameLookup, LinePickingNumberOfProblems, LinePickingPDF, LinePickingPrintAllProblems, LinePickingProblemLookup, LinePickingSimDistances, LinePickingSimPoints, LinePickingSupport, LinePickingVar
%         
%


% Call to the MEX file
[ names, descriptions, Npar, parameters ] =  LinePicking(9);
