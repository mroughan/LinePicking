#!/usr/bin/perl -w
# make_gateways.pl
#   This creates the Matlab .m gateway functions to a set of MEX entry points
#   created by make_mex.pl.
#
#   In reads
#        - the same definitions file as make_mex.pl
#        - a template file for the .m file (by default named "${base_name}Template_h")
#        - a license file (if needed) to include in the template
#
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

$version = "make_gateways.pl v0.02 (Sep 11 2012)";
chomp($today = `date`);
print STDERR "running $version on $today\n";

# get command line options
sub usage {
    "Usage: $0 [--help] [--Debug=i] [-t=template_file] -f=input_file.c -b=base_name -l=license_file\n";
}

use Getopt::Long;
Getopt::Long::Configure("bundling");
$result = GetOptions('help|h' => \$opt_help,
		     'Debug|D=i' => \$opt_debug,
		     'File|f=s' => \$definitions_file,
		     'basename|b=s' => \$base_name,
		     'license|l=s' => \$license_file,
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

if (!defined($definitions_file)) {
  die usage();
}
if (!defined($base_name)) {
  die usage();
}


if (!defined($template_file)) {
  $template_file = "${base_name}Template_m";
}
print "\$template_file = $template_file\n";

# read in the C functions definition file
$case_i = -1;
open(FILE, "< $definitions_file") or die "Error:could not open $definitions_file: $!\n";
while (<FILE>) {
  # find gateway commands
  if (/ExpandForMatlab\((\w+)[,\s]+(\d+)[,\s]+(\d+)\)/) {
    $inp = $2;
    $out = $3;
    if ($1 =~ m/($base_name[^*\s]*)\s*([^*]*)/) {
      $case_i++;
      $gateway = $1;
      $gateways{$case_i} = $gateway;
      $inp_args{$gateway} = $inp - 1; # -1, because the first argument is the case number
      $out_args{$gateway} = $out;
      print "\n gateway[$case_i]=$gateway\n";
    }
  }

  if ($case_i >= 0) {
    # C comments (on a single line) provide more information
    if (/$RE{comment}{C}{-keep}/) {
      # description of the function (must not include a *)
      if ($1 =~ /$gateway\s+([^*]*)/) {
	$descriptions{$gateway} = $1;
	print "     description: $descriptions{$gateway}\n";
	print "     input args:  $inp_args{$gateway}\n";
	print "     output args: $out_args{$gateway}\n";
      }
      # information about input and output arguments (must not include a *)
      if ($1 =~ /(input|output) argument (\d+):\s*(\w+),\s*([^*]*)/) {
	$inp_out = $1;
	$number = $2;
	$name = $3;
	$description = $4;
	print "         $inp_out, \$number=$number, \$name=$name, \$description=$description\n";
	$argument_number{$gateway}{$inp_out}{$name} = $number;
	$argument_name{$gateway}{$inp_out}{$number} = $name;
	$argument_desc{$gateway}{$inp_out}{$number} = $description;
      }
    }
  }
}
close(FILE) or die "Error: could not close $definitions_file: $!\n";

# read in the license file
if (defined($license_file)) {
  open(FILE, "< $license_file") or die "Error:could not open $license_file: $!\n";
  {
    local $/; # use this to read entire file into one scalar
    $license = <FILE>;
  }
  close(FILE) or die "Error: could not close $license_file: $!\n";
} else {
  $license = "%";
}

# for each gateway function, read in the template and create a gateway Matlab function
$name_list = "LinePicking, " . join(', ', (sort {$a cmp $b} (values %gateways)));
foreach $case_i (sort {$a <=> $b} (keys %gateways)) {
  $gateway = $gateways{$case_i};
  $matlab_file = "$gateway.m";
  if (!defined($descriptions{$gateways{$case_i}})) {
    $descriptions{$gateways{$case_i}} = "(no description available, please fill in comments in MatlabDefinitions.def).";
  }


  $out_arg_details = "";
  $out_arg_details = "";
  for ($i=1;$i<=$out_args{$gateway};$i++) {
    if (!defined($argument_name{$gateway}{output}{$i})) {
      $argument_name{$gateway}{output}{$i} = "output$i";
      $argument_desc{$gateway}{output}{$i} = "";
      $argument_number{$gateway}{output}{"output$i"} = $i;
    }
    $out_arg_details .= "%    output argument $i = $argument_name{$gateway}{output}{$i}, $argument_desc{$gateway}{output}{$i}\n";
  }
  $out_arg_details  .= "%";
  $inp_arg_details = "";
  for ($i=1;$i<=$inp_args{$gateway};$i++) {
    if (!defined($argument_name{$gateway}{input}{$i})) {
      $argument_name{$gateway}{input}{$i} = "input$i";
      $argument_desc{$gateway}{input}{$i} = "";
      $argument_number{$gateway}{input}{"input$i"} = $i;
    }
    $inp_arg_details .= "%    input argument $i = $argument_name{$gateway}{input}{$i}, $argument_desc{$gateway}{input}{$i}\n";
  }
  $inp_arg_details  .= "%";


  $input_arg_list = join(', ', (sort {$argument_number{$gateway}{input}{$a} <=> 
				       $argument_number{$gateway}{input}{$b}}
			 (values %{$argument_name{$gateway}{input}})));
  $output_arg_list = join(', ', (sort {$argument_number{$gateway}{output}{$a} <=> 
				       $argument_number{$gateway}{output}{$b}}
			 (values %{$argument_name{$gateway}{output}})));

  open(MATLAB_FILE, "> $matlab_file") or die "Error:could not open $matlab_file: $!\n";
  open(TEMP_FILE, "< $template_file") or die "Error:could not open $template_file: $!\n";
  while (<TEMP_FILE>) {
    s/_BASE_/$base_name/;
    s/_VERSION_/$version/;
    s/_DATE_/$today/;
    s/_NAME_/$gateways{$case_i}/;
    s/_LICENSE_/$license/;
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

# $name_list = join("\n%          ", (sort {$a cmp $b} (values %gateways)));
$name_list = "";
foreach $case_i (sort {$a <=> $b} (keys %gateways)) {
  $name_list .= "%          $gateways{$case_i} = $descriptions{$gateways{$case_i}}\n";
}
$name_list .= "%";
print_matlab_index("$base_name.m", $name_list);
print_matlab_index("Contents.m", $name_list);


# create a central Matlab file, with just the help information as a reference point
sub print_matlab_index {
  my ($filename, $name_list) = @_;
  open(FILE, "> $filename") or die "Error:could not open $filename: $!\n";
print FILE <<END_TEXT;
% Toolbox $base_name Solves problems related to choosing lines at random form some region.
% Version 1.0 11-Sep-2012
%
%     This file was autogenerated by $version,
%                                 on $today
%
$license
%
%     Routines included here are:
$name_list
%
END_TEXT
close(FILE) or die "Error: could not close $filename: $!\n";

}

