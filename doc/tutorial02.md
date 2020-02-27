## duneproc turorial 2: Using the duneproc command.

David Adams   
February 2020

The configuration of a dune event processing (or any larsoft) job is specified in a fcl
file, most commonly a complicated tree of such files nested with include statments
with the top-level file specified on the lar command line.
We often want want to run many similar jobs with small variations to process different
datasets (e.g. runs or files), event selection (e.g. by event ID or trigger)
and different detector regions (e.g. APAs or tick ranges).
In addition there may be different processing options (calibration, metigation, ...)
and output format preferences (histogram/graph ranges, colors and styles).
It is tedious and error-prone for users to create the top-level fcl files for each job
and difficult to maintain the lower-level fcl files duplicated across jobs.

In addition to providing some standard fcl configurations, this package provides the *duneproc*
script that builds the top-level fcl and processes all files in a provided list of files.
The syntax is:

> duneproc FCL DST NPROC NSKIP OPT

* FCL - Slash (/) separated list of fcl names
* DST - Input file list specifier
* NPROC - Maximum number of events to process. Default of 0 means all.
* NSKIP - Number of events to skip. Default of 0 means none.
* OPT - Other options. See help. Typically this can be omitted.

The first argument is a sequence of fclnames and the top-level fcl
file includes each of these extended with the fcl extension:
E.g. for FCL = fcl1/fcl2/fcl3:

> #include "fcl1.fcl"  
> #include "fcl2.fcl"  
> #include "fcl3.fcl"  

In addition, the files extra.fcl, local.fcl and dbg.fcl are also included if
present in the submission directory.
The first is inserted in the second position so it can provide parameters
to the following files.
The other two appear at the end where they can can override earlier definitions.
E.g., if all three were present

> #include "fcl1.fcl"  
> #include "extra.fcl"  
> #include "fcl2.fcl"  
> #include "fcl3.fcl"  
> #include "local.fcl"  
> #include "dbg.fcl"

