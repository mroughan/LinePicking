function g =  LinePickingPDF(t, problem, parameters) 
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
% LinePickingPDF(t, problem, parameters) computes the PDF of the length of a 
%     randomly chosen line, within some region chosen by the problem. 
%
% INPUTS:
%    t = vector of points on which to calculate the PDF         
%    problem = region type
%              currently supported: 
%                        0: square, with side length parameters[0]
%                        1: disk, with radius parameters[0]
%                        2: hyper-ball, dimension parameters[0], radius parameters[1]
%                        3: rectangle, side lengths parameters[0], parameters[1]
%                        4: line, length parameters[0]
%                        5: cube, side length parameters[0]
%                        6: sphere, with radius parameters[0]
%                        7: sphere geodesic, with radius parameters[0]
%                        8: prism geodesic, with length parameters[0], and perimeter parameters[1]
%
%
%    parameters = vector of parameters for the region
%         
% OUTPUTS:        
%   g(t) = vector of calculated densities      
%         
%
% See Also LinePickingCDF, LinePickingMean, LinePickingVar, LinePickingSupport, LinePickingCheckParameters, LinePickingProblemLookup, LinePickingAllProblems 
g = LinePicking(0, t, problem, parameters);