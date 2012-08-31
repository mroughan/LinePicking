%
% Test sums are 1, and scaling with size for each type of distribution, 
%
% Copyright 2012 Matthew Roughan <matthew.roughan@adelaide.edu.au>
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
%
clear;

dt = 0.001;
t = -0.1:dt:10.1;

[g1] = LinePickingPDF(t, 0, 1);
[g5] = LinePickingPDF(t, 0, 5);
sum_square_1 = (sum(g1) -(g1(1)+g1(end))/2 )*dt
sum_square_5 = (sum(g5) -(g5(1)+g5(end))/2 )*dt

[g1] = LinePickingPDF(t, 1, 1);
[g5] = LinePickingPDF(t, 1, 5);
sum_disk_1 = (sum(g1) -(g1(1)+g1(end))/2 )*dt
sum_disk_5 = (sum(g5) -(g5(1)+g5(end))/2 )*dt

[g1] = LinePickingPDF(t, 2, [3,1]);
[g5] = LinePickingPDF(t, 2, [3,5]);
sum__1 = sum(g1*dt)
sum_ball3_1 = (sum(g1) -(g1(1)+g1(end))/2 )*dt
sum_ball3_5 = (sum(g5) -(g5(1)+g5(end))/2 )*dt

[g1] = LinePickingPDF(t, 3, [0.5,1]);
[g5] = LinePickingPDF(t, 3, [2.5,5]);
sum_rect_1 = (sum(g1) -(g1(1)+g1(end))/2 )*dt
sum_rect_5 = (sum(g5) -(g5(1)+g5(end))/2 )*dt

[g1] = LinePickingPDF(t, 4, 1);
[g5] = LinePickingPDF(t, 4, 5);
sum_line_1 = (sum(g1) -(g1(1)+g1(end))/2 )*dt
sum_line_5 = (sum(g5) -(g5(1)+g5(end))/2 )*dt

[g1] = LinePickingPDF(t, 5, 1);
[g5] = LinePickingPDF(t, 5, 5);
sum_cube_1 = (sum(g1) -(g1(1)+g1(end))/2 )*dt
sum_cube_5 = (sum(g5) -(g5(1)+g5(end))/2 )*dt

[g1] = LinePickingPDF(t, 9, [0.5,1]);
[g5] = LinePickingPDF(t, 9, [2.5,5]);
sum_rect_man_1 = (sum(g1) -(g1(1)+g1(end))/2 )*dt
sum_rect_man_5 = (sum(g5) -(g5(1)+g5(end))/2 )*dt

[g1] = LinePickingPDF(t, 10, [0.5,1]);
[g5] = LinePickingPDF(t, 10, [2.5,5]);
sum_rect_max_1 = (sum(g1) -(g1(1)+g1(end))/2 )*dt
sum_rect_max_5 = (sum(g5) -(g5(1)+g5(end))/2 )*dt



% tests of common error conditions
%

