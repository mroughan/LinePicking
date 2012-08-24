function g = LinePicking(t, mode, parameters)
%
% Copyright 2012 Matthew Roughan <matthew.roughan@adelaide.edu.au>
% Copyright 2012 Eric Parsonage <eric.parsonagen@adelaide.edu.au>
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
% LinePicking(t, mode, parameters) computes the PDF of the length of a randomly chosen
%     line, within some region chosen by the mode. 
%
% INPUTS:
%    t = vector of points on which to calculate the PDF         
%    mode = region type
%              currently supported: 
%                        0: square, with side length parameters[0]
%                        1: disk, with radius parameters[0]
%                        2: hyper-ball, dimension parameters[0], radius parameters[1]
%                        3: rectangle, side lengths parameters[0], parameters[1]
%                        4: line, length parameters[0]
%                        5: cube, side length parameters[0]
%    parameters = vector of parameters for the region
%         
% OUTPUTS:        
%    g(t) = vector of calculated densities      
%         
%
