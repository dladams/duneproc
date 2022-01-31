# duneproc tutorial01

David Adams   
January 2022  
  
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

Set up a release of dunetpc.  
See https://wiki.dunescience.org/wiki/DUNE_LAr_Software_Releases.
<pre>
source /cvmfs/dune.opensciencegrid.org/products/dune/setup_dune.sh
setup dunesw v09_42_00_01 -q e20:prof
</pre>
Replace the version and options with current ones. If using a local build, additionally 
set up that build area, e.g.
<pre>
source /home/dladams/proc/build/dev01/workdir/localProducts_dunesw_v09_42_00_01_e20_prof/setup
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

# Installin this package package.
To install this package, choose and create and installation directory and
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

# Fetch, build and set up this package following the 
[myproj instructions](https://github.com/dladams/myproj/blob/master/README.md) 
replacing myproj with duneproc.

# If using any other anaylsis package (dunenoise, dunececalib, ...),
# fetch, build and check it out and set up in the same way

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

