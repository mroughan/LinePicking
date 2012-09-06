function [ result, error_str ] =  LinePickingCheckParameters( problem, parameters ) 
% LinePickingCheckParameters checks if the supplied parameters are correct
%
%     This file was autogenerated by make_gateways.pl v0.01 (Tue Sep  4 2012),
%                                 on Thu Sep  6 11:47:33 CST 2012
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
% LinePickingCheckParameters checks if the supplied parameters are correct
%
%           Example:  [ result, error_str ] =  LinePickingCheckParameters( problem, parameters ) 
% 
% INPUTS:       
%    input argument 1 = problem, the problem number (See LinePickingPrintAllProblems) 
%    input argument 2 = parameters, the parameters of the problem 
%
%         
% OUTPUTS:
%    output argument 1 = result, an integer error code 
%    output argument 2 = error_str, gives a message explaining the error 
%
%
%     
% See Also LinePicking, LinePickingAllProblems, LinePickingCDF, LinePickingCheckParameters, LinePickingMean, LinePickingNameLookup, LinePickingNumberOfProblems, LinePickingPDF, LinePickingPrintAllProblems, LinePickingProblemLookup, LinePickingSimDistances, LinePickingSimPoints, LinePickingSupport, LinePickingVar
%         
%


% Call to the MEX file
[ result, error_str ] =  LinePicking(8, problem, parameters );
