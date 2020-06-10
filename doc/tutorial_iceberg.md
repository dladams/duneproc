## duneproc tutorial for Iceberg

David Adams   
April 2020

As of April 2020, duneproc provides additional help for Iceberg,
a LAr TPC prototype constructed and run at FNAL.
First build and set up [this package](../README.md).

Configuration files specific to Iceberg may be found in
[Fcl/Iceberg](../Fcl/Iceberg).
These may be used with the duneproc command, used directly
on a lar command line (if they are top-level fcl),
or included in other fcl files.

Duneproc makes use of a
catalog of datasets in the user&apos;s dataset directory
$HOME/data/dune/datasets.
The command ibFindFiles can be used to find the raw data files for
any Iceberg run and optionally populate this database.
The command findFilePnfs and findFileXroot can be used to find
the full pnfs or xrootd path to any file.

### Commands

The command ibFindFiles can be used to find the raw data files for a given run.
In run 3, the runs were only 10 min long and so there is one file per run. For
example,
<pre>
> ibFindFiles 4481 -
</pre>
lists the file for run 4481 and (thanks to the second argument) puts
a copy of that list in iceberg004481.txt in the default dataset directory
$HOME/data/dune/datasets/iceberg/.

Datasets with multiple runs can be defined with ibGroupRuns, e.g.
<pre>
> ibGroupRuns 4809 4823 -
</pre>
with the file list ibgroup004809-004823 written again to the default dataset
directory.

### Configuration files

The following top-level fcl files are provided:

#### run_dataprep_iceberg.fcl
Runs dataprep with no tools. Useful to check and stage files. For example:
<pre>
duneproc run_dataprep_iceberg iceberg4481/event000010
</pre>
should creaate the DQM1 plots for event 10 in run 4481.
Note that a grid certificate is required to acess the data file.
To circumvent this, use pnfs access by adding the noxrootd flag:
<pre>
duneproc run_dataprep_iceberg iceberg4481/event000010 noxrootd
</pre>

#### run_iceberg_dqm1.fcl
Run dunetpc DQM to separately view pedestal-subtracted raw data for each event.
The produced plots include
* Channel-tick displays for each view (collection, induction u and v)
* A series of metric vs. channel plots including pedestal, pedestal rms and noise,
and various tail meaures.

#### run_iceberg_rawchtz.fcl
Creates a channel vs. tick plot for the pedestal-subtracted raw data in
the collection planes for each event.

#### run_iceberg_rawchtall.fcl
Creates a channel vs. tick plot for the pedestal-subtracted raw data
for all channels in each event.

#### ibWfRaw.fcl
Creates a 1000-tick raw waveform plots. Eight channels are shown on each plot.
E.g. to plot all channels in one event for a plane:
<pre>
duneproc ibWfRaw/dpcr_apau iceberg005044/event000001
</pre>

#### ibWfMit.fcl
Creates a 1000-tick mitigated waveform plots. Eight channels are shown on each plot.

#### ibWfRawDist.fcl
Creates histograms of ADC code multiplicity for each channel.
