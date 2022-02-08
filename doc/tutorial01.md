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

# Installing this package.

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

## Using the installed packge.

To use the installed package source the installed setup file:
<pre>
source install/duneproc/setup.sh
</pre>
If starting from a fresh shell, first perform the dune setup described above. There is
no need to do the build setup to use an installed package.
This setup will apprpriately modify the executable, library, python and fcl paths.

# Find the files or files of interest, e.g. for a run:
samweb list-files "data_tier raw and DUNE_data.is_fake_data 0 and run_number 5240"
# or events 1000-1999 in that run:
samweb list-files "data_tier raw and DUNE_data.is_fake_data 0 and run_number 5240 and last_event>=1000 and first_event<2000"

# To get the full xrootd path(s) to one of these files:
samweb get-file-access-url np04_raw_run005240_0001_dl1.root --schema=root

# Run dataprep with no tools
mkdir job01
cd job01
lar -c run_dataprep.fcl -n 1 \
    -s root://fndca1.fnal.gov:1094/pnfs/fnal.gov/usr/dune/tape_backed/dunepro/protodune/np04/beam/detector/None/raw/06/68/39/48/np04_raw_run005240_0001_dl1.root
cd ..

# Run DQM (data quality monitoring) with wide display
mkdir job02
cd job02
lar -c dqmw.fcl -n 1 \
    -s root://fndca1.fnal.gov:1094/pnfs/fnal.gov/usr/dune/tape_backed/dunepro/protodune/np04/beam/detector/None/raw/06/68/39/48/np04_raw_run005240_0001_dl1.root
cd ..

# Run dataprep with no tools for APA 7
cd job03
lar -c run_dataprep_apa7.fcl -n 1 \
    -s root://fndca1.fnal.gov:1094/pnfs/fnal.gov/usr/dune/tape_backed/dunepro/protodune-sp/raw/2019/detector/test/None/00/01/00/79/np04_raw_run010079_0001_dl1.root

