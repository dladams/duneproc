## duneproc tutorial 2: Using the duneproc command.

David Adams   
June 2022

The configuration of a dune event processing (or any larsoft) job is specified in a fcl
file, most commonly a complicated tree of such files nested with include statments
with the top-level file specified on the lar command line.
We often want want to run many similar jobs with small variations to process different
datasets (e.g. runs or files), event selection (e.g. by event ID or trigger)
and different detector regions (e.g. APAs or tick ranges).
In addition there may be different processing options (calibration, mitigation, ...)
and output format preferences (histogram/graph ranges, colors and styles).
It is tedious and error-prone for users to create the top-level fcl files for each job
and difficult to maintain the lower-level fcl files duplicated across jobs.

In addition to providing some standard fcl configurations, this package provides the *duneproc*
script that builds the top-level fcl and processes all files in a provided list of files.
The syntax is:

<pre>
> duneproc FCL DST NPROC NSKIP OPTS
</pre>

* FCL - Slash (/) separated list of fcl names
* DST - Input file list specifier
* NPROC - Maximum number of events to process. Default of 0 means all.
* NSKIP - Number of events to skip. Default of 0 means none.
* OPTS - Other options. See help. Non-integer NPROC or NSKIP are added to OPTS.

The value "." can be used for for NPROC or NSKIP to force use of the default.

The first argument is a sequence of fclnames and the top-level fcl
file includes each of these extended with the fcl extension:
E.g. for FCL = fcl1/fcl2/fcl3:

<pre>
> #include "fcl1.fcl"  
> #include "fcl2.fcl"  
> #include "fcl3.fcl" 
</pre>

In addition, the files extra.fcl, local.fcl and dbg.fcl are also included if
present in the submission directory.
The first is inserted in the second position so it can provide parameters
to the following files.
The other two appear at the end where they can can override earlier definitions.
E.g., if all three were present

<pre>
> #include "fcl1.fcl"  
> #include "extra.fcl"  
> #include "fcl2.fcl"  
> #include "fcl3.fcl"  
> #include "local.fcl"  
> #include "dbg.fcl"
</pre>

If present, the fcl files are taken from the usual fcl search path including
directories from this package, dunetpc and larsoft.
If the file is not on the path, duneproc will construct the fcl if it corresponds
to a known pattern as described in the extended help:

<pre>
> duneproc -H
</pre>

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

<pre>
> cp $DUNEPROC_DIR/doc/mydst.txt ~/data/dune/datasets
</pre>

or create your own file list at that location.

0. Stage the dataset, i.e. make sure copies of of the files reside on disk:
<pre>
> stageDuneDataset mydst
</pre>
This will submit a job to stage the files and return the name of a log file that
you can follow (e.g. tail -f) to monitor progress.
The last time I tried this, it took about 10 minutes and then less than a minute after the
files were staged.

This will create a VOMS proxy if you have not already done so and generate a kerberos
proxy if needed.
In the lattter case, you may be prompted for a password.

#### Getting started

1. To run dataprep (no tools) for the first event (not event number 1) in the dataset:
<pre>
> duneproc run_dataprep mydst 1
</pre>
You will find the name of the run directory (here run_dataprep/mydst_proc000001)
near the end of the output on the screen.
The first argument is the base name of the top-level fcl file (i.e. without the .fcl suffix)
and the second is the name of the dataset.

2. The same using pnfs instead of xrootd to access the input files:
<pre>
> duneproc run_dataprep mydst 1 clean  
> duneproc run_dataprep mydst 1 noxrootd
</pre>
Thie first command removes the old run directory.
The second will fail if /pnfs is not mounted as is the case anywhere but dunegpvm.

3. Dataprep with no tools for event number 1 (not the first in the dataset):
<pre>
> duneproc run_dataprep/event000001 mydst
</pre>
or
<pre>
> duneproc run_dataprep mydst/event000001
</pre>
The results should be the same in either case but the directory naming is different.
We see that a fcl base name (event000001) may be appended with a slash (/) to either the first or
second argument.
In this case it is a special name for which the fcl is automatically generated by duneproc.
To see the long list of such names, use:
<pre>
duneproc -H
</pre>


4. Dataprep with no tools for events 1-5, APA 3 only:
<pre>
> duneproc run_dataprep/dpcr_apa3 mydst/event000001-000006
</pre>
This shows how to select both an APA (more generally a named detector region) and a range of events.
I follow my usual convention of appending all but event selection to the first argument.

#### Data quality plots

5. DQM with wide display for event 1. This includes a channel-tick
display for each plane and many metric vs. channel plots:
<pre>
> duneproc dqmw mydst/event000001  
> display dqmw/mydst/event000001/adcraw_tpp0v_run008564_evt000001.png
</pre>
The latter command works on dunegpvm. On a Jupyter servers, use the file browser to select
and display that or any of the image files.

6. DQM3 for events 1-5. These produces metric vs. channel plots averages
over the events.
<pre>
> duneproc dqm3 mydst/event000001-000005  
> display dqm3/mydst/event000001-000005/chmet_pednoise_tps0_run008564.png
</pre>

#### Waveforms

7. Raw waveforms for ticks 3000-4000 in event 1 for the v-wires in FEMB 302.
<pre>
> duneproc wfRaw/event000001/dpcr_femb302v/wftick3000 mydst  
> display wfRaw/event000001/dpcr_femb302v/wftick3000/runmydst/wfraw_run008564_evt000001_chan01536.png
</pre>

8. Mitigated waveforms for the same.
<pre>
> duneproc wfMit/event000001/dpcr_femb302v/wftick3000 mydst  
> display wfMit/event000001/dpcr_femb302v/wftick3000/runmydst/wfprep_run008564_evt000001_chan01536.png
</pre>

8. Same with expanded ADC scale so we can see the full signal.
<pre>
> duneproc wfMit/event000001/dpcr_femb302v/wftick3000/wfpran150 mydst  
> display wfMit/event000001/dpcr_femb302v/wftick3000/wfpran150/runmydst/wfprep_run008564_evt000001_chan01536.png
</pre>

#### Reco

9. ***NOT WORKING June 2022*** Run standard PDSP data reco, stop after dataprep, and create channel-tick displays.
<pre>
> duneproc reco_dataprep mydst 1  
> display reco_dataprep/mydst_proc000001/adcprp_tpp0z_run008564_evt000008.png
</pre>
Note the output here is that expected for wirecell processing: scaled to be in approximate
ADC counts (instead of ke) and bad channels zeroed.

10. ***NOT WORKING June 2022*** Run standard PDSP simulation reco, stop after dataprep, and create channel-tick displays.
<pre>
> duneproc reco_dataprep_sim mysimdst 1  
> display reco_dataprep_sim/mysimdst_proc000001/adcprp_tpp0z_run22603710_evt001271.png
</pre>
Before running this, create dataset [mysimdst](mysimdst.txt) as was done above for mydst.

#### Dataprep

11. ***NOT WORKING June 2022*** Run PDSP (protoDUNE single phase) dataprep through tail removal for event 1 plane 3z and create wide channel-tick displays
using the high level-job configuration is specified in this package in [run_dataprep.fcl](../fcl/run_dataprep.fcl).
<pre>
> duneproc run_dataprep/event000001/dptools_calib_tail/dpcr_apa3z/addChannelTickPrep mydst  
> display run_dataprep/event000001/dptools_calib_tail/dpcr_apa3z/addChannelTickPrep/mydst/adcprp_tpp0z_run008564_evt000001.png
</pre>

Note that "calib_tail" in the FCL field can be swapped out for different stages in stages in reco including
* calib_only - Calibration but no mitigation, tail removal or noise removal.
* calib_mit - Calibration and mitigation but no tail removal or noise removal.
* calib_tail - Calibration, mitigation and tail removal but no noise removal.
* calib_noiserem - Calibration, mitigation, tail removal and noise removal.
* wirecell - Above plus switch back to approximate ADC scale and zeroing of bad channels.
Add pdchtzmax50 or pdchtamax50 to put the plots on ADC scale.  

The results with the wirecell option should be the same as for reco above.

12. ***NOT WORKING June 2022*** Produce ROI plots for the same dataprep for FEMB 302u using an ROI finder with threshold 0.5 ke.
<pre>
> duneproc run_dataprep/dptools_calib_tail/dpcr_femb302u/roithresh0.5/addRoiViewer mydst 5
> display run_dataprep/dptools_calib_tail/dpcr_femb302u/roithresh0.5/addRoiViewer/mydst_proc000005/roi_chan000459_000.png
</pre>



