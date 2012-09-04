function [ mean ] =  LinePickingMean( problem, parameters ) 
% LinePickingMean returns the mean of the distribution. 
%
%     This file was autogenerated by make_gateways.pl v0.01 (Tue Sep  4 2012),
%                                 on Tue Sep  4 14:48:30 CST 2012
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
% LinePickingMean returns the mean of the distribution. 
%
%           Example:  [ mean ] =  LinePickingMean( problem, parameters ) 
% 
% INPUTS:       
%    input argument 1 = problem, the problem number (See LinePickingPrintAllProblems) 
%    input argument 2 = parameters, the parameters of the problem 
%
%         
% OUTPUTS:
%    output argument 1 = mean, the mean of the distribution. 
%
%
%     
% See Also LinePicking, LinePickingAllProblems, LinePickingCDF, LinePickingCheckParameters, LinePickingMean, LinePickingNumberOfProblems, LinePickingPDF, LinePickingPrintAllProblems, LinePickingProblemLookup, LinePickingSimDistances, LinePickingSimPoints, LinePickingSupport, LinePickingVar
%         
%


% Call to the MEX file
[ mean ] =  LinePicking(2, problem, parameters );
