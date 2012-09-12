#!/usr/bin/perl -w
# make_mex.pl
#   This creates the Matlab MEX entry points a a set of C functions.
#   It reads a definitions file, and a set of "codelets", and uses these to 
#   construct a C-file with MEX entry points, suitable for integration with
#   make_gateways.m
#
#   In reads
#        - the same definitions file as make_gateways.pl
#        - template files for the .c and .h output (by default named "Template_mex_c" and "Template_mex_h")
#        - a codelets file, containing brief bits of code used for different arguments
#        - the src C file
#        - a license file (if needed) to include in output
#
#
#   Assumptions:
#        R assumptions
#                all variables are passed by reference
#                functions all return void
#                ???
#        there are only a fixed number of types of arguments supported
#             integer
#             double
#             char
#        all arrays from or two Matlab call function are double
#        we deal with arrays of at most 2 dimensions
#        a 1D array X passed to or from a C function, will also have a parameter called
#                   X_length which contains the size of the array
#        a 2D array X passed to or from a C function, will also have 2 parameters called
#                   X_I and X_J, which give the size of the array
#           NB: the sense of the array is changed between Matlab and C
#        NB: array indices in Matlab run from 1..N, and in C from 0..N-1
#
#        functions will be defined in the form "void BASENAMEXXX( arglist )"
#           where BASENAME is the name of the main gateway to MEX in the C code
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

$version = "make_mex.pl v0.02 (Sep 11 2012)";
chomp($today = `date`);
print STDERR "running $version on $today\n";

# get command line options
sub usage {
    "Usage: $0 [--help] [--Debug=i] [-c=codelets_file] [-l=license_file] -f=input_file.def -s=source_file\n";
}

use Getopt::Long;
Getopt::Long::Configure("bundling");
$result = GetOptions('help|h' => \$opt_help,
		     'Debug|D=i' => \$opt_debug,
		     'File|f=s' => \$definitions_file,
		     'source|s=s' => \$source_file,
		     'license|l=s' => \$license_file,
		     'Template|t=s' => \$template_name,
		     'codelets|c=s' => \$codelets_file,
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
if (!defined($source_file)) {
  die usage();
}
($base_name = $source_file) =~ s|.*\/||;
$base_name =~ s/\.[ch]//;
print "\$base_name = $base_name\n";

if (!defined($template_name)) {
  $template_name = "Template_mex";
}
print "\$template_name = $template_name\n";

if (!defined($codelets_file)) {
  $codelets_file = "Codelets_mex";
}
print "\$codelets_file = $codelets_file\n";

#
# read in the codelets
#
print "-----reading codelets--------------------------------\n\n";
open(FILE, "< $codelets_file") or die "Error:could not open $codelets_file: $!\n";
$codelet_block = 0;
$variable_block = 0;
$match_block = 0;
$i=1;
while (<FILE>) {
  s/#.*//;
  if (/^\s*CODELET\s+([^(\n\s]*)/) {
    # print " codelet=$1 /-/ $_";
    $match_block = 0;
    $variable_block = 0;
    $codelet_block = $i++;
    $codelet = $1;
    $codelets{$codelet} = $codelet_block;
    $codelet_text{$codelet} = "";
    $codelet_var{$codelet} = "";
  } elsif (/ENDBLOCK/) {
    $match_block = 0;
    $codelet_block = 0;
    $variable_block = 0;
  } elsif (/VARIABLES/) {
    $match_block = 0;
    $codelet_block  = 0;
    $variable_block = 1;
  } elsif (/MATCH/) {
    $match_block = 1;
    $codelet_block  = 0;
    $variable_block = 0;
  } elsif ($codelet_block > 0) {
    $codelet_text{$codelet} .= $_;
  } elsif ($variable_block > 0) {
    $codelet_var{$codelet} .= $_;
  } elsif ($match_block > 0) {
    $match_text .= $_;
  }
}

close(FILE) or die "Error: could not close $file: $!\n";

# have a look at the codelet blocks
print "  1-------------------------------------\n\n";
$match_text =~ s/\\/\\\\/g; # have to replace escape '\' by '\\'
print "$match_text";
print "  2-------------------------------------\n\n";
eval $match_text;
print "\n";
print "\$st = $st\n";
print "\@codelet_name(" . scalar @codelet_name .") = @codelet_name\n";
print "\@codelet_regexp(" .  scalar @codelet_regexp .") = @codelet_regexp\n";
print "  3-------------------------------------\n\n";
$match_text =~ s/"/\\"/g;
$match_text =~ s|\$|\\\$|g;
$match_text =~ s|\@|\\\@|g;
print eval('"' . $match_text . '"');
print "  4-------------------------------------\n\n";
$function = "_FUNCTION_";
$fn_desc{$function} = "_FN_DESC_";
$var_list{$function} = "_VARIABLES_";
$arg_n = "_I_";
$arg = "_ARG_";
$type = "_TYPE_";
$desc{$function}{$arg_n} = "_VAR_DESC_";
$input_arguments{$function} = $indent . "_INP_";
$output_arguments{$function} = $indent . "_OUT_";
foreach $codelet (keys %codelets) {
  print "CODELET $codelet = \n";
  $codelet_text{$codelet} =~ s/"/\\"/g;
  print eval('"' . $codelet_text{$codelet} . '"');
  print "\n\n";
}


print "-----reading C source--------------------------------\n\n";
#
# read in the C src file, looking for function definitions
#   -- we are only interested in those that return void
open(FILE, "< $source_file") or die "Error:could not open $source_file: $!\n";
$start_func = 0; # use for multiline function definitions
while (<FILE>) {
  if (m"\S" && !m"mex"i) {
    if ($start_func ==0 && /^\s*void\s+(\w+)\(([^)]*)\)/) {
      $start_func = 2;
      $function = $1;
      $c_functions{$function} = 1;
      $argstring = $2;
    } elsif ($start_func ==0 && /^\s*void\s+(\w+)\(([^)]*)/) {
      $start_func = 1;
      $function = $1;
      $c_functions{$function} = 1;
      $argstring = $2;
    } elsif ($start_func == 1 && !m"\)") {
      $argstring .= $_;
    } elsif ($start_func == 1 && /(.*)\)/) {
      $argstring .= $1;
      $start_func = 2;
    }

    # now process it all
    if ($start_func == 2) {
      $argstring =~ s/\n//;
      @arglist = split(',', $argstring);
      $c_function_args{$function} = scalar @arglist;
      for ($i=0;$i<@arglist;$i++) {
	$arglist[$i]  =~ s/^\s+//;  # remove leading spaces
	$arglist[$i]  =~ s/\s+$//;  # remove trailing spaces
	$c_function_arglist{$function}[$i] = $arglist[$i];
	# all vars of interest are by reference, so we can get the name this way
	($c_function_arglist_name{$function}[$i] = $arglist[$i]) =~ s/.*[*\s]\s*//;
	for ($k=0;$k<@codelet_regexp;$k++) {
	  if ($arglist[$i] =~ /$codelet_regexp[$k]/) {
	    $c_function_arglist_codelet{$function}[$i] = $codelet_name[$k];
	  }
	}
	for ($k=0;$k<@supported_types;$k++) {
	  if ($arglist[$i] =~ /$supported_types[$k]/) {
	    $c_function_arglist_type{$function}[$i] = $supported_types[$k];
	  }
	}
      }

      $start_func = 0;
    }
  }
}
close(FILE) or die "Error: could not close $source_file: $!\n";

# write out a list of functions
foreach $function (sort (keys %c_functions)) {
  print "function: $function(), " . join('|', @{$c_function_arglist{$function}}) . "\n";
  for ($i=0;$i<@{$c_function_arglist{$function}};$i++) {
    if (!defined($c_function_arglist_codelet{$function}[$i])) {
      $c_function_arglist_codelet{$function}[$i] = "undef";
    }
    if (!defined($c_function_arglist_type{$function}[$i])) {
      $c_function_arglist_type{$function}[$i] = "undef";
    }
    print "     arg[$i]=$c_function_arglist_name{$function}[$i], $c_function_arglist{$function}[$i], $c_function_arglist_codelet{$function}[$i], $c_function_arglist_type{$function}[$i]\n";
  }
}
print "--------reading C definitions-----------------------------\n\n";

#
# read in the C functions definition file
#
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
      $function = $gateway;
      print "\n gateway[$case_i]=$gateway\n";
      if (defined($c_functions{$function})) {
	for ($i=0;$i<@{$c_function_arglist{$function}};$i++) {
	  print "        arg[$i]=$c_function_arglist_name{$function}[$i], $c_function_arglist_codelet{$function}[$i], $c_function_arglist_type{$function}[$i]\n";
	}
      } else {
	die "        no c function $function\n";
      }
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

	# map this argument to one of the C arguments
	for ($i=0;$i<@{$c_function_arglist{$gateway}};$i++) {
	  if ( ($name cmp $c_function_arglist_name{$gateway}[$i]) == 0) {
	    $arg_map{$gateway}[$i] = $number;
	    $arg_direction{$gateway}[$i] = $inp_out;
	    $arg_comment{$gateway}[$i] = "";
	    print "            mapping Carg[$i] to Marg[$inp_out][$arg_map{$gateway}[$i]] \n";
	  } elsif ( ($name cmp "N$c_function_arglist_name{$gateway}[$i]") == 0) {
	    # a C argument that is a size of a vector or array
	  } elsif ( ($name cmp "M$c_function_arglist_name{$gateway}[$i]") == 0) {
	    # a C argument for size of 2D array
	  }
	}

      }
    }
  }
}
close(FILE) or die "Error: could not close $definitions_file: $!\n";


#
# for each C gateway function, use CODELETs for each of its arguments to construct
#    blocks of code to put into its function definition
#
foreach $case_i (sort {$a <=> $b} (keys %gateways)) {
  $function = $gateways{$case_i};
  $fn_desc{$function} = $descriptions{$function};
  $arg_list{$function} = join(', ', @{$c_function_arglist_name{$function}});
  $var_list{$function} = "";
  $input_arguments{$function} = "";
  $output_arguments{$function} = "";

  # construct each of the others by building up over the list of arguments
  # in the order that they appear in the C function
  for ($i=0;$i<@{$c_function_arglist{$function}};$i++) {
    if (defined($arg_map{$function}[$i])) {
      # for Matlab in and out variables create a codeblock
      $arg_n = $arg_map{$function}[$i]; # map the order of paramters in C to Matlab
      $arg = $c_function_arglist_name{$function}[$i];
      $type = $c_function_arglist_type{$function}[$i];
      $inp_out = $arg_direction{$gateway}[$i];
      $desc{$function}{$arg_n} = $argument_desc{$gateway}{$inp_out}{$arg_n};
      if ($inp_out eq 'input') {
	$codelet = "INPUT_$c_function_arglist_codelet{$function}[$i]"; # first find the correct codelet
 	$input_arguments{$function} .= eval('"' . $codelet_text{$codelet} . '"');
      } elsif ($inp_out eq 'output') {
	$codelet = "OUTPUT_$c_function_arglist_codelet{$function}[$i]"; # first find the correct codelet
	$output_arguments{$function} .= eval('"' . $codelet_text{$codelet} . '"');
      }
      $var_list{$function} .= eval('"' . $codelet_var{$codelet} . '"');
   } else {
      # for variables that are just used for C,
      #    e.g., sizes of arrays
      #    e.g., error codes, or error strings passed back from functions

      # or variables that are just for Matlab, such as a seed passed to C, but not the C function

    }
  }

}


#
# read in the license file, if provided
#
if (defined($license_file) && -e $license_file) {
  open(FILE, "< $license_file") or die "Error:could not open $license_file: $!\n";
  {
    local $/; # use this to read entire file into one scalar
    $license = <FILE>;
  }
  close(FILE) or die "Error: could not close $license_file: $!\n";
} else {
  $license = "% license goes here";
}
$license =~ s/%/ */g;

#
# create the MEX .c file, based on a template
#
$c_file = "${base_name}MEX.c";
open(C_FILE, "> $c_file") or die "Error:could not open $c_file: $!\n";
$template_file = "${template_name}_c";
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
  print C_FILE $_;
}
close(TEMP_FILE) or die "Error: could not close $template_file: $!\n";

# now add in the CODELETS for each function
foreach $case_i (sort {$a <=> $b} (keys %gateways)) {
  $function = $gateways{$case_i};
  print C_FILE "\n";
  print C_FILE eval('"' . $codelet_text{"FUNCTION"} . '"');
  print C_FILE "\n";
}
close(C_FILE) or die "Error: could not close $c_file: $!\n";





#
# create the MEX .h file, based on a template
#
$h_file = "${base_name}MEX.h";
$template_file = "${template_name}_h";
$macro = uc("_${base_name}_H");

# create a function prototype for each function
foreach $case_i (sort {$a <=> $b} (keys %gateways)) {
  $function = $gateways{$case_i};
  $function_prototypes .= eval('"' . $codelet_text{"FUNCTION_H"}. '"');
}

# write out the file
open(H_FILE, "> $h_file") or die "Error:could not open $h_file: $!\n";
open(TEMP_FILE, "< $template_file") or die "Error:could not open $template_file: $!\n";
while (<TEMP_FILE>) {
  # don't tell it to include itself
  s/_VERSION_/$version/;
  s/_DATE_/$today/;
  s/_NAME_/$gateways{$case_i}/;
  s/_MACRO_/$macro/;
  s/_LICENSE_/$license/;
  s/_I_/$case_i/;
  s/_DESCRIPTION_/$descriptions{$gateways{$case_i}}/;
  s/_PROTOTYPES_/$function_prototypes/;
  s/_NAMELIST_/$name_list/;
  s/_INPUT_LIST_/$input_arg_list/;
  s/_OUTPUT_LIST_/$output_arg_list/;
  s/%\s+_INP_ARG_DETAILS_/$inp_arg_details/;
  s/%\s+_OUT_ARG_DETAILS_/$out_arg_details/;
  s/,\s+\)/\)/; # remove dangling commas
  s/\[\s+\]\s+=//; # remove empty output arguments
  s/\(\s+\)//; # remove empty input arguments
  print H_FILE $_;
}
close(TEMP_FILE) or die "Error: could not close $template_file: $!\n";
close(H_FILE) or die "Error: could not close $h_file: $!\n";

