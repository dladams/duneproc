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
a copy of that list at data/dune/datasets/iceberg/iceberg004481.txt.

### Configuration files

The following top-level fcl files are provided:

#### run_dataprep_iceberg.fcl
Runs dataprep with no tools. Useful to check and stage files.

#### run_iceberg_dqm1.fcl
Run dunetpc DQM to separately view pedestal-subtracted raw data for each event.
The produced plots include
* Channel-tick displays for each view (collection, induction u and v)
* A series of metric vs. channel plots including pedestal, pedestal rms and noise,
and various tail meaures.

#### run_iceberg_rawchtz.fcl
Creates a channel vs. tick plot for the pedestal-subtracted raw data in
the collection planes for each event.

#### run_iceberg_rawchtallz.fcl
Creates a channel vs. tick plot for the pedestal-subtracted raw data
for all channels in each event.

#### ibWfRaw.fcl
Creates a 1000-tick raw waveform plots. Eight channels are shown on each plot.
