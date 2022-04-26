# duneproc tutorial01: Running DQM for one event

David Adams   
April 2022  
  
This is a tutuorial on using *duneproc* and other analysis packages from David Adams.  
For more information on getting started with DUNE computing, see
https://wiki.dunescience.org/wiki/DUNE_Computing/Getting_Started_Tutorial.

This document assumes use of [*dunerun*](https://github.com/dladams/dunerun).
To work without *dunerun* (not recommended), see the [old version](tutorial01-old.md)
of this tutorial. *Dunerun* facilitates using an environment that includes DUNE
software release along with additional ups and dunerun-compliant packages such
*duneproc*.

## Computing environment

The DUNE software is on cvmfs and can be run on any SL7 machine (or SL7 virtual environment) where the DUNE cvmfs directories are mounted or the
software has been otherwise installed.
Users with DUNE FNAL accounts can use the dunegpvm machines, e.g.
<pre>
ssh -Y -K dunegpvm05.fnal.gov
</pre>
where 05 can be replaced with any of {01, 02, ..., 15}.

An alternative to dunegpvm is to connect to a Jupyter service at FNAL (<https://analytics-hub.fnal.gov>) or elsewhere and open a terminal session.
The [dqm](https://github.com/dladams/duneproc/blob/master/ipynb/dqm.ipynb) and
[dqmw](https://github.com/dladams/duneproc/blob/master/ipynb/dqmw.ipynb) notebooks provide python equivalents to this tutorial.

First install [*dunerun*](https://github.com/dladams/dunerun) specifying the dunesw release.
Here we denote the base installation directory \<install-dir> and assume package-specific installation.
Set up *dunerun* and the clone and install duneproc as follows:
<pre>
cd &lt;pkgdir>
source &lt;install-dir>/dunerun/setup.sh
git clone https://github.com/dladams/duneproc.git
duneproc/build
</pre>
Here \<pkgdir> is a source installation dir which can be removed after installation and the set up defines the env needed for the build command.

An alternative on dunegpvm is to use my installation area `/home/dladams/proc/install/dev01` but then you are stuck with whatever DUNE version and
local modifications I am using that day.
The FNAL Jupyter service does not provide access to this filesystem or those of any other users and you will have to install *dunerun* and *duneproc*
as discussed above.
The DUNE software is av available on cvmfs.

## Setting up

To set up to use *duneproc* in a subsequent session, repeat the *dunerun* set up and then use the *dune-run* command to open a shell in that environment:
<pre>
mkdir &lt;workdir>
cd &lt;workdir>
source &lt;install-dir>/dunerun/setup.sh
dune-run -e dunesw,duneproc shell
...
</pre>
It is also to run a command without opening the shell by replacing *shell* with that command. And it is possible to run a command or open the shell
from the python command line withthe class *dunerun.DuneRun*.
See the [*dunerun*](https://github.com/dladams/dunerun) documentation for details on those options.

## Grid certificate

A grid ceritificate (and authorization) is required to access the DUNE data files and explore their metadata with sam.
One option (the only available at present?) it to obtain a kerberos-based VOMS proxy as follows:
<pre>
kinit    # Not needed if you already have a kerberos ticket
kx509 --minhours 12
voms-proxy-init -noregen -rfc -voms dune:/dune/Role=Analysis
</pre>

The command `voms-proxy-info` can be used to check the proxy exists and is not expired (timeleft > 0).

There is helper class to obtain the proxy in python.
For information about that and examples showing how to find and access data files, see the
[dunedata notebook](https://github.com/dladams/dunerun/blob/master/ipynb/dunedata.ipynb).

## Finding files

To list raw datat files from protoDUNE run 5240:
<pre>
samweb list-files "data_tier raw and DUNE_data.is_fake_data 0 and run_number 5240"
</pre>

or the files containing events 1000-1999 from that run:
<pre>
samweb list-files "data_tier raw and DUNE_data.is_fake_data 0 and run_number 5240 and last_event>=1000 and first_event<2000"
</pre>

To get the full xrootd path(s) to one of these files:
<pre>
MYFILE=$(samweb get-file-access-url np04_raw_run005240_0001_dl1.root --schema=root | grep fnal)
echo $MYFILE
</pre>
There is grep for fnal to avoid the file replica at CERN. Change that or select a file by hand
if you prefer to use the CERN replica.
  
## Running dataprep
  
Now we run some dataprep jobs using the above file. First with no tools:
<pre>
mkdir job01
cd job01
lar -c run_dataprep.fcl -n 1 -s $MYFILE
cd ..
</pre>
The job may hang for a while at "... Initiating request to open input file..." if the file has to be staged in from tape. Have a coffe, come back tomorrow
or try a different file if it takes to long. The command limit processing one event and so you should see the first event, number 7, is processed.
Messages from the dataprep module are prefixed with "DataPrepByApaModule::" and you will see it is configured here to process each APA independently and
to be noisy and report the number of digits (channel waveforms), clocks and status flags for each APA. The first two should be 2560 and the last one.
The report for APA3 is a little different because one FEMB runs on an internal clock and has a slightly different number of time samples.

To see something more interesting, run DQM (data quality monitoring) with wide display
<pre>
mkdir job02
cd job02
lar -c dqmw.fcl -n 1 -s $MYFILE
cd ..
</pre>
Many image files will be produced. On dunegpvm, they can be viewd with
<pre>
display adcraw_tpp3z_run005240_evt000007.png
</pre>
or, if you are running from a Jupyter notebook, view with
<pre>
from IPython.display import Image
dir = '/home/dladams/proc/run01/tutorial/job02/'
display(Image(filename=dir + 'adcraw_tpp3z_run005240_evt000007.png'))
</pre>
or use the file browser (left pane) to locate and open the file.
