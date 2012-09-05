function [ distances ] =  LinePickingSimDistances( N, problem, parameters, seed ) 
% LinePickingSimDistances simulates a set of distances for a problem. 
%
%     This file was autogenerated by make_gateways.pl v0.01 (Tue Sep  4 2012),
%                                 on Wed  5 Sep 2012 20:40:20 CST
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
% LinePickingSimDistances simulates a set of distances for a problem. 
%
%           Example:  [ distances ] =  LinePickingSimDistances( N, problem, parameters, seed ) 
% 
% INPUTS:       
%    input argument 1 = N, the number of distances to simulate 
%    input argument 2 = problem, the problem number (See LinePickingPrintAllProblems) 
%    input argument 3 = parameters, the parameters of the problem 
%    input argument 4 = seed, the seed to the random number generator 
%
%         
% OUTPUTS:
%    output argument 1 = distances, returns a vector of the simulated distances 
%
%
%     
% See Also LinePicking, LinePickingAllProblems, LinePickingCDF, LinePickingCheckParameters, LinePickingMean, LinePickingNameLookup, LinePickingNumberOfProblems, LinePickingPDF, LinePickingPrintAllProblems, LinePickingProblemLookup, LinePickingSimDistances, LinePickingSimPoints, LinePickingSupport, LinePickingVar
%         
%


% Call to the MEX file
[ distances ] =  LinePicking(12, N, problem, parameters, seed );
