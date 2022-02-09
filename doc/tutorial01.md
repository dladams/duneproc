# duneproc tutorial01

David Adams   
February 2022  
  
This is a tutuorial on using my analysis packages.  
For more information on getting started with DUNE computing, see
https://wiki.dunescience.org/wiki/DUNE_Computing/Getting_Started_Tutorial

## Setting up

Log in and create a new directory.
<pre>
ssh -Y -K dunegpvm05.fnal.gov
mkdir /dune/data/users/$USER/proc/tutorial
cd /dune/data/users/$USER/proc/tutorial
</pre>
The directories shown here are the ones I use on dunegpvm. Choose any location you wish.

Set up a release of dunesw, e.g. if cvmfs is available:
<pre>
source /cvmfs/dune.opensciencegrid.org/products/dune/setup_dune.sh
setup dunesw v09_42_00_02 -q e20:prof
</pre>
Replace the version and options with current ones. To list all:
<pre>
ups list -aK+ dunesw
</pre>
If using a local build, additionally set up that build area, e.g.
<pre>
source /home/dladams/proc/build/dev01/workdir/localProducts_dunesw_v09_42_00_02_e20_prof/setup
mrbslp
</pre>
If the local build has been done with [dune-dev](https://github.com/dladams/dune-dev),
the the above two blocks can be replaced with the dune shell command. E.g. to use my
standard private (and perhaps newer and better) dunetpc build on dunegpvm:
<pre>
source ~dladams/proc/build/dev01/dunesetup.sh 
dune shell
</pre>

Get kerberos and grid certificates.  
The latter is needed for xrootd file access.
<pre>
kinit    # Not needed if you already have a kerberos ticket
kx509 --minhours 12
voms-proxy-init -noregen -rfc -voms dune:/dune/Role=Analysis
</pre>

To check you have set up a release and see some of the available commands:
<pre>
duneHelp
</pre>

## Installing this package.

To install this package, choose and create a package directory and
clone in that area:
<pre>
mkdir pkgs
cd pkgs
git clone https://github.com/dladams/duneproc
cd ..
</pre>
Or, if you have already done this and want to update:
<pre>
cd pkgs/duneproc
git pull
cd ../..
</pre>

This and most of my other analysis packages contain a script build that
builds and installs the package, i.e. complies and copies files to a
user-specified installation directory.
To use this script, the directories for building and installation must
be specified and some build tools set up. For example (after setting up a dunesw release or build):
<pre>
export DUNE_BUILD_DIR=$HOME/tmp/build
export DUNE_INSTALL_DIR=$HOME/proc/install
setup cmake v3_22_0
setup studio
</pre>
Note this environment is only required for building and installation
and not for using the installalled software.

After this, execute the build script in the package, e.g.
<pre>
./pkgs/duneproc/duneproc/build
</pre>
and the package will be installed at $DUNE_INSTALL_DIR/duneproc including
a bash setup file setup.sh.

Other of my analysis packages (dunenoise, dunececalib, ...) may be installed
in the same way by replacing dunebuild with that package name in the above.

## Using the installed package.

To use the installed package source the installed setup file:
<pre>
source install/duneproc/setup.sh
</pre>
If starting from a fresh shell, first perform the dune setup described above. There is
no need to do the build setup to use an installed package.
This setup will apprpriately modify the executable, library, python and fcl paths.

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

To see something more intersting, run DQM (data quality monitoring) with wide display
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
or if you are running from a jupyter notebook (or local interactive python), view with
<pre>
from IPython.display import Image
dir = '/home/dladams/proc/run01/tutorial/job02/'
display(Image(filename=dir + 'adcraw_tpp3z_run005240_evt000007.png'))
</pre>
Connect to https://analytics-hub.fnal.gov and follow the above setup, installation and running instructions in a terminal to prepare plots to view in this manner.
