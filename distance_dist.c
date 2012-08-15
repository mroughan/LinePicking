/* distance_dist.c	
 *
 * Copyright 2012 Matthew Roughan <matthew.roughan@adelaide.edu.au>
 *     This program is free software: you can redistribute it and/or modify
 *     it under the terms of the GNU General Public License as published by
 *     the Free Software Foundation, either version 3 of the License, or
 *     (at your option) any later version.
 * 
 *     This program is distributed in the hope that it will be useful,
 *     but WITHOUT ANY WARRANTY; without even the implied warranty of
 *     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *     GNU General Public License for more details.
 *
 *     You should have received a copy of the GNU General Public License
 *     along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Compute the distance distribution between two point in a region, 
 * often called the "line picking problem".
 *
 * MEX Call as:   [g] = distance_dist(t, mode, parameters)
 *                   remember: parameter(1) (in matlab) == parameter[0] (in C)
 *
 * C Call as:     result = distance_dist(t, g, N, mode, parameters, Npar);
 *
 * Unix command line call as:  
 *            distance_dist -f input_file -m mode -p parameter0 -P parameter1
 *                   but this isn't finished yet
 *    
 * Various regions are supported:
 *    0: square, with side length parameters[0]
 *    1: disk, with radius parameters[0]
 *    2: hyper-ball, dimension parameters[0], radius parameters[1]
 *    3: rectangle, side lengths parameters[0], parameters[1]
 *    4: line, length parameters[0]
 *    5: cube, side length parameters[0]
 *
 *
 */
#include <math.h>
#include <stdlib.h>
#include <stdint.h> 
#include <string.h>
#include <stdio.h>
#include "distance_dist.h"

#ifdef _MEX
#include "mex.h"
#include "matrix.h"
#endif

 
int distance_dist(double *t, double *g, int N, int mode, double* parameters, int Npar)
/* computer distance density g(t) (at points t) between two points in a region.
 *
 * t = array of points at which to calculate density
 * g = array to store output
 * mode = 
 *    0: square, with side length parameters[0]
 *    1: disk, with radius parameters[0]
 *    2: hyper-ball, dimension parameters[0], radius parameters[1]
 *    3: rectangle, side lengths parameters[0], parameters[1]
 *    4: line, length parameters[0]
 *    5: cube, side length parameters[0]
 * parameters = parameters of the region (see above)
 * Npar = number of parameters
 *  
 */
{
    int i;

    /* calculate the distribution */
    if (mode == 0) /* square, with side length parameters[0] */
    {
	if (Npar < 1) {
	    return(3);
	}
	if (parameters[0] <= 0) {
	    return(2);
	}
	for (i=0; i<N; i++) 
	{
	    g[i] = SquareDistanceDensity(t[i], parameters);
	}
    } else if (mode == 1) /* disk, with radius parameters[0] */
    {
	if (Npar < 1) {
	    return(3);
	}
	if (parameters[0] <= 0) {
	    return(2);
	}
	for (i=0; i<N; i++) 
	{
	    g[i] = DiskDistanceDensity(t[i], parameters);
	}
    } else if (mode == 2) /* hyper-ball, with dimension parameters[0], and radius parameters[1] */
    {
	if (Npar < 2) {
	    return(3);
	}
	if (parameters[0] < 1) {
	    return(2);
	}
	if (parameters[1] <= 0) {  
	    return(2);
	}
	for (i=0; i<N; i++) 
	{
	    g[i] = HyperballDistanceDensity(t[i], parameters);
	}
    } else if (mode == 3) /* rectangle, side lengths parameters[0], parameters[1] */
    {
	if (Npar < 2) {
	    return(3);
	}
	if (parameters[0] <= 0 || parameters[1] <= 0) {
	    return(2);
	}
	for (i=0; i<N; i++) 
	{
	    g[i] = RectangleDistanceDensity(t[i], parameters);
	}
    } else if (mode == 4) /* line, length parameters[0] */
    {
	if (Npar < 1) {
	    return(3);
	}
	if (parameters[0] <= 0) {
	    return(2);
	}
	for (i=0; i<N; i++) 
	{
	    g[i] = LineDistanceDensity(t[i], parameters);
	}
    } else if (mode == 5) /* cube, side length parameters[0] */
    {
	if (Npar < 1) {
	    return(3);
	}
	if (parameters[0] <= 0) {
	    return(2);
	}
	for (i=0; i<N; i++) 
	{
	    g[i] = CubeDistanceDensity(t[i], parameters);
	}
    } else {
	return(1); /* first type of error */
    }
    return(0); /* correctly executed */
}


#ifdef _MEX
/* function to integrate this with Matlab */
void mexFunction(
        int nlhs,       mxArray *plhs[],
        int nrhs, const mxArray *prhs[]
        )
{
  
  double *t; /* points at which to calculate the distribution */
  double *g; /* value of the distribution at the points t */
  uint32_t N, M;    /* number of points */
  uint32_t Npar, Mpar;    /* number of parmeters */
  int i;					
  int mode;    /* the type of region on which to calculate the distribution */
  double *parameters; /*  input parameter vector  
			       note that meaning of parameters depends on the mode */
  int result;

  /* Check for proper number of input and output arguments. */    
  if (nrhs < 1)
       mexErrMsgTxt("distance_dist: Not enough input arguments: [g] = distance_dist(t, mode, parameters).");
  if (nlhs > 1) 
       mexErrMsgTxt("distance_dist: Too many output arguments: [g] = distance_dist(t, mode, parameters).");
  
  /* Get the input arguments */
  t = mxGetPr(prhs[0]);       /*  */
  N = (uint32_t) mxGetN(prhs[0]); /*  */
  M = (uint32_t) mxGetM(prhs[0]); /*  */
  if (N<1 || M>1) 
       mexErrMsgTxt("distance_dist: t should be an Nx1 matrix.");

  if (nrhs < 2) 
  {
      mode = 1; /* default mode is a square */
  } else {
      mode = (int) mxGetScalar(prhs[1]);
  }

  Npar = (uint32_t) mxGetN(prhs[2]);
  Mpar = (uint32_t) mxGetM(prhs[2]);
  if (nrhs < 3 || Npar*Mpar<1)
  {
      parameters = (double *) malloc((size_t) sizeof(double)*3);
	  /* allocate three, even though at the moment we only need 2 */
      parameters[0] = 1;
      parameters[1] = 1;
      parameters[2] = 1;
  } else {
      parameters = mxGetPr(prhs[2]); 
  }
  
  /* create output matrices */
  plhs[0] = mxCreateDoubleMatrix(1, N, mxREAL);
  g = mxGetPr(plhs[0]);

  result = distance_dist(t, g, N, mode, parameters, Mpar*Npar);
  if (result == 0) {
      /* this means it returned correctly */
  } else if (result == 1) {
      mexErrMsgTxt("distance_dist: unsupported mode.");
  } else if (result == 2) {
      mexErrMsgTxt("distance_dist: parameters out of range.");
  } else if (result == 3) {
      mexErrMsgTxt("distance_dist: not enough parameters were entered.");
  }

}
#endif


/* bits needed to run this as a stand alone command-line function */
static void 
usage_distance_dist()
{
  fprintf(stderr, "Usage: distance_dist -f input_file -m mode -p parameter0 -P parameter1 \n");
  fprintf(stderr, "           input_file contains a list of points t.\n");
  exit(1);
}

static void 
set_pars_distance_dist(int argc, char *argv[], char **file, int *mode, double *parameters)
{
  char c;
  extern char    *optarg;
  extern int      optind;
  int F;

  /* defaults */
  *mode = 0;
  *file = (char *) malloc((size_t) sizeof(char)*256); /* longest file name is 256 characters */
  /* *parameters = (double *) malloc((size_t) sizeof(double)*3); */
  /* (*parameters)[0] = 1.1; */
  /* (*parameters)[1] = 1.2; */
  /* (*parameters)[2] = 1.3; */
  parameters[0] = 1.0; 
  parameters[1] = 1.0;
  parameters[2] = 1.0; 
  
  while ((c=getopt(argc,argv,"f:m:p:q:s:z")) != EOF)
      switch ((char)c) { 
      case 'f': 
	  if (sscanf(optarg,"%s",*file) != 1) usage_distance_dist(); 
	  break; 
      case 'm':  
	  if (sscanf(optarg,"%d",mode) != 1) usage_distance_dist(); 
	  break; 
      case 'p': 
	  if (sscanf(optarg,"%lf",&(parameters[0])) != 1) usage_distance_dist(); 
	  break; 
      case 'q': 
	  if (sscanf(optarg,"%lf",&(parameters[1])) != 1) usage_distance_dist(); 
	  break;  
      case 's': 
	  if (sscanf(optarg,"%lf",&(parameters[2])) != 1) usage_distance_dist(); 
	  break;  
      case 'h':;
      default: 
	  usage_distance_dist(); 
      }
}
 
int main(int argc, char *argv[])
{
  int i=0;
  char *readbuf;
  double epsilon;
  int mode;
  double parameters[3];
  char *version = "version 1.0";
  char *file;

  /*print out program name and version*/
  fprintf(stderr,"%% %s: %s \n", *argv, version);

  /* read in programs options  */
  set_pars_distance_dist(argc, argv, 
			 &file, &mode, parameters);
  fprintf(stderr,"%%   file=%s, mode=%d, ", file, mode);
  for (i=0;i<3;i++) {
      fprintf(stderr, " p[%d]=%.3f", i, parameters[i]);
  }
  fprintf(stderr, "\n");

  return(0);
}


