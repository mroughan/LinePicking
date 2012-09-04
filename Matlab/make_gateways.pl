#!/usr/bin/perl -w
# make_gateways.pl
#
#     Copyright 2012 Matthew Roughan <matthew.roughan@adelaide.edu.au>
#     This program is free software: you can redistribute it and/or modify
#     it under the terms of the GNU General Public License as published by
#     the Free Software Foundation, either version 3 of the License, or
#     (at your option) any later version.
#
#     This program is distributed in the hope that it will be useful,
#     but WITHOUT ANY WARRANTY; without even the implied warranty of
#     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#     GNU General Public License for more details.
#
#     You should have received a copy of the GNU General Public License
#     along with this program.  If not, see <http://www.gnu.org/licenses/>.
#
#
#
########################################################

use Regexp::Common qw /comment number/;
# http://search.cpan.org/~abigail/Regexp-Common-2011121001/lib/Regexp/Common.pm

$version = "make_gateways.pl v0.01 (Tue Sep  4 2012)";
chomp($today = `date`);
print STDERR "running $version on $today\n";

# get command line options
sub usage {
    "Usage: $0 [--help] [--Debug=i] -f=input_file.c\n";
}

use Getopt::Long;
Getopt::Long::Configure("bundling");
$result = GetOptions('help|h' => \$opt_help,
		     'Debug|D=i' => \$opt_debug,
		     'File|f=s' => \$file,
		     'Template|t=s' => \$template_file,
		     ) || die usage();
$result = 0;

if (defined($opt_help)) {
  die usage();
}

if (defined($opt_debug)) {
  $debug = $opt_debug;
} else {
  $debug = 0;
}

if ($0 =~ /(.*)\/(.*)/) {
  $calling_path = $1;
  $calling_prog = $2;
} else {
  $calling_path = ".";
  $calling_prog = $0;
}

if (!defined($file)) {
  die usage();
}
($base_name = $file) =~ s/\.c//;
$base_name =~ s/.*\///;
print "\$base_name = $base_name\n";

if (!defined($template_file)) {
  $template_file = "${base_name}Template_m";
}
print "\$template_file = $template_file\n";

# read in the C code
$mex = 0;
$k = 0;
$case_i = -1;
open(FILE, "< $file") or die "Error:could not open $file: $!\n";
while (<FILE>) {
  if ($mex > 0) {
    # print "\$mex=$mex, $_";
    if (m"#ifdef" || m"#ifndef") {
      $mex++;
    }
    if (m"#endif") {
      $mex--;
    }

    # find case statements corresponding to the gateway commands
    if (/case\s+(\d+):\s+($RE{comment}{C})/) {
      $case_i = $1;
      if ($2 =~ m/($base_name[^*\s]*)\s*([^*]*)/) {
	$gateway = $1;
	$gateways{$case_i} = $gateway;
	$descriptions{$gateway} = $2;
      }
      print "\n case=$case_i, \t gateway=$gateway, \t description=$descriptions{$gateway}\n";
    } elsif (/default:/) {
      $case_i = -1;
    }

    if ($case_i >= 0) {
      # look for checks of numbers of input and output arguments
      if (/CheckNumberInputArg\(nrhs,\s*(\d+)/) {
	$inp_args{$gateway} = $1 - 1; # -1, because the first argument is the case number
	print "       input args $inp_args{$gateway}\n";
      } elsif (/CheckNumberOutputArg\(nlhs,\s*(\d+)/) {
	$out_args{$gateway} = $1;
	print "       output args $out_args{$gateway}\n";
      }

    }

    # find single line comments for more informations
    if (/$RE{comment}{C}{-keep}/) {
      if ($1 =~ /(input|output) argument (\d+):\s*(\w+),\s*([^*]*)/) {
	$inp_out = $1;
	$number = $2;
	$name = $3;
	$description = $4;
	print "               $inp_out, \$number=$number, \$name=$name, \$description=$description\n";
	$argument_number{$gateway}{$inp_out}{$name} = $number;
	$argument_name{$gateway}{$inp_out}{$number} = $name;
	$argument_desc{$gateway}{$inp_out}{$number} = $description;
      }
    }
  }

  # only bother reading the bits between the MEX defines
  if (m"#ifdef _MEX") {
    $mex = 1;
  }
}
close(FILE) or die "Error: could not close $file: $!\n";

# for each gateway function, read in the template and create a gateway Matlab function
$name_list = "LinePicking, " . join(', ', (sort {$a cmp $b} (values %gateways)));
foreach $case_i (sort {$a <=> $b} (keys %gateways)) {
  $gateway = $gateways{$case_i};
  $matlab_file = "$gateway.m";
  $input_arg_list = join(', ', (sort {$argument_number{$gateway}{input}{$a} <=> 
				       $argument_number{$gateway}{input}{$b}}
			 (values %{$argument_name{$gateway}{input}})));
  $output_arg_list = join(', ', (sort {$argument_number{$gateway}{output}{$a} <=> 
				       $argument_number{$gateway}{output}{$b}}
			 (values %{$argument_name{$gateway}{output}})));
  $out_arg_details = "";
  $out_arg_details = "";
  for ($i=1;$i<=$out_args{$gateway};$i++) {
    $out_arg_details .= "%    output argument $i = $argument_name{$gateway}{output}{$i}, $argument_desc{$gateway}{output}{$i}\n";
  }
  $out_arg_details  .= "%";
  $inp_arg_details = "";
  for ($i=1;$i<=$inp_args{$gateway};$i++) {
    $inp_arg_details .= "%    input argument $i = $argument_name{$gateway}{input}{$i}, $argument_desc{$gateway}{input}{$i}\n";
  }
  $inp_arg_details  .= "%";

  open(MATLAB_FILE, "> $matlab_file") or die "Error:could not open $matlab_file: $!\n";
  open(TEMP_FILE, "< $template_file") or die "Error:could not open $template_file: $!\n";
  while (<TEMP_FILE>) {
    s/_VERSION_/$version/;
    s/_DATE_/$today/;
    s/_NAME_/$gateways{$case_i}/;
    s/_I_/$case_i/;
    s/_DESCRIPTION_/$descriptions{$gateways{$case_i}}/;
    s/_NAMELIST_/$name_list/;
    s/_INPUT_LIST_/$input_arg_list/;
    s/_OUTPUT_LIST_/$output_arg_list/;
    s/%\s+_INP_ARG_DETAILS_/$inp_arg_details/;
    s/%\s+_OUT_ARG_DETAILS_/$out_arg_details/;
    s/,\s+\)/\)/; # remove dangling commas
    s/\[\s+\]\s+=//; # remove empty output arguments
    s/\(\s+\)//; # remove empty input arguments
    print MATLAB_FILE $_;
  }
  close(TEMP_FILE) or die "Error: could not close $template_file: $!\n";
  close(MATLAB_FILE) or die "Error: could not close $matlab_file: $!\n";
}

# create a central Matlab file, with just the help information as a reference point
$matlab_file = "$base_name.m";
$name_list = join("\n%          ", (sort {$a cmp $b} (values %gateways)));
open(MATLAB_FILE, "> $matlab_file") or die "Error:could not open $matlab_file: $!\n";
print MATLAB_FILE <<END_TEXT;
%
%     This file was autogenerated by $version,
%                                 on $today
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
%     Routines included here are:
%          $name_list
%
END_TEXT
close(MATLAB_FILE) or die "Error: could not close $matlab_file: $!\n";

# create a contents Matlab file, with just the help information as a reference point
$matlab_file = "Contents.m";
$name_list = join("\n%          ", (sort {$a cmp $b} (values %gateways)));
open(MATLAB_FILE, "> $matlab_file") or die "Error:could not open $matlab_file: $!\n";
print MATLAB_FILE <<END_TEXT;
% Toolbox LinePicking Solves problems related to choosing lines at random form some region.
% Version 1.0 09-Sep-2012
%
%     This file was autogenerated by $version,
%                                 on $today
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
%     Routines included here are:
%          $name_list
%
END_TEXT
close(MATLAB_FILE) or die "Error: could not close $matlab_file: $!\n";



