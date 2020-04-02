## duneproc tutorial for Iceberg

David Adams   
April 2020

As of April 2020, duneproc provides additional help for Iceberg,
a LAr TPC prototype constructed and run at FNAL.
First build and set up [this package](../README.md).

Ignore the following

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

> duneproc FCL DST NPROC NSKIP OPTS

* FCL - Slash (/) separated list of fcl names
* DST - Input file list specifier
* NPROC - Maximum number of events to process. Default of 0 means all.
* NSKIP - Number of events to skip. Default of 0 means none.
* OPTS - Other options. See help. Non-integer NPROC or NSKIP are added to OPTS.

The value "." can be used for for NPROC or NSKIP to force use of the default.

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
If the file DST.txt is found in $HOME/data/dune/datasets or any of its
subdirectories, it is copied.
If not, the pattern DST = RRRevtsEE1-EE2 is used to search in the run slices directory
$HOME/data/dune/np04/run_slices/files.
If DST does not match that pattern (contain "evts"),
there are some more complicated options that are likely to be removed.

The file lists are expected to be one file name per line and the name may be
just the base name (LFN) or may include a full pnfs path or xrootd URL.
In the latter cases, a call to samweb may be avoided at job startup.

The job directory is constructed from the first two options: ./FCL/DST with
additional subdirectories if NPROC or NSKIP are set.

### Examples

Some examples demonstrating use of duneproc fcl files and patterns follow.
Either copy the example [here](mydst.txt):

> cp $DUNEPROC_DIR/doc/mydst.txt ~/data/dune/datasets

or create your own file list at that location.

#### Getting started

1. To run dataprep (no tools) for the first event in the dataset:
> duneproc run_dataprep mydst 1

2. The same using pnfs instead of xrootd to access the input files.
First remove the run directory from the previous job:
> duneproc run_dataprep/event000001 mydst . . clean  
> duneproc run_dataprep/event000001 mydst . . noxrootd

3. Dataprep with no tools for event 1:
> duneproc run_dataprep/event000001 mydst
or
> duneproc run_dataprep mydst/event000001

4. Dataprep with no tools for events 1-5, APA 3 only:
> duneproc run_dataprep/dpcr_apa3 mydst/event000001-000006

#### Data quality plots

5. DQM with wide display for event 1. This includes a channel-tick
display for each plane and many metric vs. channel plots:
> duneproc dqmw mydst/event000001
> display dqmw/mydst/event000001/adcraw_tpp0v_run008564_evt000001.png 

6. DQM3 for events 1-5. These produces metric vs. channel plots averages
over the events.
> duneproc dqm3 mydst/event000001-000005
> display dqm3/mydst/event000001-000005/chmet_pednoise_tps0_run008564.png

#### Waveforms

7. Raw waveforms for ticks 3000-4000 in event 1 for the v-wires in FEMB 302.
> duneproc wfRaw/event000001/dpcr_femb302v/wftick3000 mydst  
> display wfRaw/event000001/dpcr_femb302v/wftick3000/runmydst/wfraw_run008564_evt000001_chan01536.png

8. Mitigated waveforms for the same.
> duneproc wfMit/event000001/dpcr_femb302v/wftick3000 mydst  
> display wfMit/event000001/dpcr_femb302v/wftick3000/runmydst/wfprep_run008564_evt000001_chan01536.png

8. Same with expanded ADC scale so we can see the full signal.
> duneproc wfMit/event000001/dpcr_femb302v/wftick3000/wfpran150 mydst  
> display wfMit/event000001/dpcr_femb302v/wftick3000/wfpran150/runmydst/wfprep_run008564_evt000001_chan01536.png 

#### Reco

9. Run standard PDSP data reco, stop after dataprep, and create channel-tick displays.
> duneproc reco_dataprep mydst 1  
> display reco_dataprep/mydst_proc000001/adcprp_tpp0z_run008564_evt000008.png 
Note the output here is that expected for wirecell processing: scaled to be in approximate
ADC counts (nstead of ke) and bad channels zeroed.

10. Run standard PDSP simulation reco, stop after dataprep, and create channel-tick displays.
> duneproc reco_dataprep_sim mysimdst 1  
> display reco_dataprep_sim/mysimdst_proc000001/adcprp_tpp0z_run22603710_evt001271.png

#### Dataprep

11. Run PDSP (protoDUNE single phase) dataprep through tail removal for event 1 plane 3z and create wide channel-tick displays
using the high level-job configuration is specified in this package in [run_dataprep.fcl](../fcl/run_dataprep.fcl).
> duneproc run_dataprep/event000001/dptools_calib_tail/dpcr_apa3z/addChannelTickPrep mydst  
> display run_dataprep/event000001/dptools_calib_tail/dpcr_apa3z/addChannelTickPrep/mydst/adcprp_tpp0z_run008564_evt000001.png

Note that "calib_tail" in the FCL field can be swapped out for different stages in stages in reco including
* calib_only - Calibration but no mitigation, tail removal or noise removal.
* calib_mit - Calibration and mitigation but no tail removal or noise removal.
* calib_tail - Calibration, mitigation and tail removal but no noise removal.
* calib_noiserem - Calibration, mitigation, tail removal and noise removal.
* wirecell - Above plus switch back to approximate ADC scale and zeroing of bad channels.
Add pdchtzmax50 or pdchtamax50 to put the plots on ADC scale.  

The results with the wirecell option should be the same as for reco above.

12. Produce ROI plots for the same dataprep for FEMB 302u using an ROI finder with threshold 0.5 ke.
> duneproc run_dataprep/dptools_calib_tail/dpcr_femb302u/roithresh0.5/addRoiViewer mydst 5
> display run_dataprep/dptools_calib_tail/dpcr_femb302u/roithresh0.5/addRoiViewer/mydst_proc000005/roi_chan000459_000.png




