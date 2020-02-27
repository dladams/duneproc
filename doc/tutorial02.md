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

If present, the fcl files are taken from the usual fcl search path including
directories from this package, dunetpc and larsoft.
If the file is not on the path, duneproc will construct the fcl if it corresponds
to a known pattern as described in the extended help:

> duneproc -H

Assumptions about the presence and naming of modules and tools are made in the construction
of these fcl files and there may be no or disastrous effect if these assumptions are violated.
A fcl dump file run.fcldump is created in the run directory to check the fcl is valid and
allow the user to chech the final configuration.

The input file list infiles.txt is created from the second argument DST.
If the file file $HOME/data/dune/datasets/DST.txt exists, it is copied.
If not, the pattern DST = RRRevtsEE1-EE2 is used to search in the run slices directory  
  $HOME/data/dune/np04/run_slices/files  
If DST does not match that pattern (contain "evts"),
there are som more complicated options that are likely to be removed.
