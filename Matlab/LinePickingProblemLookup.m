function [ name, description, Npar, parameters ] =  LinePickingProblemLookup( problem ) 
% LinePickingProblemLookup checks if a particular problem exists, and returns information about it.
%
%     This file was autogenerated by make_gateways.pl v0.01 (Tue Sep  4 2012),
%                                 on Thu  6 Sep 2012 23:21:32 CST
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
% LinePickingProblemLookup checks if a particular problem exists, and returns information about it.
%
%           Example:  [ name, description, Npar, parameters ] =  LinePickingProblemLookup( problem ) 
% 
% INPUTS:       
%    input argument 1 = problem, the problem number (See LinePickingPrintAllProblems) 
%
%         
% OUTPUTS:
%    output argument 1 = name, the name of the problem 
%    output argument 2 = description, a brief description of the problem 
%    output argument 3 = Npar, the number of parameters the problem has 
%    output argument 4 = parameters, the parameters 
%
%
%     
% See Also LinePicking, LinePickingAllProblems, LinePickingCDF, LinePickingCheckParameters, LinePickingMean, LinePickingNameLookup, LinePickingNumberOfProblems, LinePickingPDF, LinePickingPrintAllProblems, LinePickingProblemLookup, LinePickingSimDistances, LinePickingSimPoints, LinePickingSupport, LinePickingVar
%         
%


% Call to the MEX file
[ name, description, Npar, parameters ] =  LinePicking(5, problem );
