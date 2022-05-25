# Staging and cloning event data

David Adams   
May 2022  
  
Prototype-specific packages such as [vdcoldbox](https://github.com/dladams/vdcoldbox/)
provide information on how to identify event data files of interest,
e.g. for a particular run or time period
and those results are expressed in terms of *datasets* which are list of logical file names.
The convention in this package ([duneproc](https://github.com/dladams/duneproc)) is to
search the directory tree $HOME/data/dune/datasets for a file named \<dsname>.txt that
holds the list of file names for dataset \<dsname>.

A dataset name is used to specify the input event data files for a job created with *duneproc* command.
With or without *duneproc*, the logical file names have to be converted to physical file names
for processing and the physical files may need to be staged and/or copied.
Here we dsicuss those procedures and some of the scripts the *duneproc* package provides
to facilitate them.

## Authentication

Access to DUNE event data and its metatdata typically require the user obtain a kerberos-based VOMS proxy.
The commands to run run are *kinit* followed by voms-proxy-init.
This package provides a script *getGridProxy* that
runs the former if needed and the latter in any case.
For example, I see:
<pre>
duneproc> getGridProxy 
Fetching kerberos ticket
Password for dladams@FNAL.GOV: 
Checking if /tmp/x509up_u6585 can be reused ... no
Authorizing ...... authorized
Fetching certificate ..... fetched
Storing certificate in /tmp/x509up_u6585
Your certificate is valid until: Wed Jun  1 14:18:03 2022
Your identity: /DC=org/DC=cilogon/C=US/O=Fermi National Accelerator Laboratory/OU=People/CN=David Adams/CN=UID:dladams
Contacting  voms2.fnal.gov:15042 [/DC=org/DC=incommon/C=US/ST=Illinois/O=Fermi Research Alliance/OU=Fermilab/CN=voms2.fnal.gov] "dune" Done
Creating proxy ......................................................................................... Done
</pre>

The [*dunerun*]() package provides the command *dunerun-check-proxy* which checks if proxy with sufficient time remains
and (redundantly) obtains the proxy and kerberos certificates only if needed. After the above, I see:
<pre>
duneproc> dunerun-check-proxy
subject   : /DC=org/DC=cilogon/C=US/O=Fermi National Accelerator Laboratory/OU=People/CN=David Adams/CN=UID:dladams/CN=2834622243
issuer    : /DC=org/DC=cilogon/C=US/O=Fermi National Accelerator Laboratory/OU=People/CN=David Adams/CN=UID:dladams
identity  : /DC=org/DC=cilogon/C=US/O=Fermi National Accelerator Laboratory/OU=People/CN=David Adams/CN=UID:dladams
type      : RFC compliant proxy
strength  : 2048 bits
path      : /tmp/x509up_u6585
timeleft  : 11:54:40
</pre>

Either command can be used to obtain the proxy.
The commands voms-proxy-destroy and kdestroy can be used to respectively reomve the VOMS proxy and kerberos certificates.

## Defining datasets

There are detector-specific commands *xxxfindFilesXXX* (*xxx* is a detector label) that list files
that meet user-supplied criteria.
Typically providing a final argument '-' ensures this list is saved according to the *duneproc* convention.
For example, here is the help for vertical-drift, bottom coldbox data:
<pre>
duneproc> vdbcbFindFiles -h
Usage: /home/dladams/proc/install/v09_52_00d00/duneproc/bin/vdbcbFindFiles RUNPAT DIR
  RUNPAT is run number or RUN_FFFF where FFFF is the file index.
  DIR is the directory to write the file list.
  If DIR="-", /home/dladams/data/dune/datasets/vdcb is used.
</pre>

To provide concrete example, we look for files from run 11990 in the vertical-drift bottom coldbox 
data from 2021. To list the files:
<pre>
duneproc> vdbcbFindFiles 11990
np02_bde_coldbox_run011990_0000_20211104T091015.hdf5
duneproc>
</pre>
We see there is one file and it is in hdf5 format. This is the format used for this run and anticipated for future runs.
Earlier data is likely to be in artdaq root format.

To create a dataset definition:
<pre>
duneproc> vdbcbFindFiles 11990 -
np02_bde_coldbox_run011990_0000_20211104T091015.hdf5
Dataset written to /home/dladams/data/dune/datasets/vdcb/vdcb011990.txt
</pre>
We see the file containing the file list is in the expected directory tree and the dataset name is "vdcb011990".

If we try to create it agin, the old definition is retained:
<pre>
duneproc> vdbcbFindFiles 11990 -
Output file already exists: /home/dladams/data/dune/datasets/vdcb/vdcb011990.txt
duneproc> 
</pre>

Use the command *duneprocHelp* to discover files for other detectors (pdsp, iceberg, ...).

## Getting physical file names

Commands are provided to convert a logical file name into a physical name.
E.g. for the above logical name, we find:
<pre>
duneproc> findFileXroot np02_bde_coldbox_run011990_0000_20211104T091015.hdf5
xroot://fndca1.fnal.gov:1094/pnfs/fnal.gov/usr/dune/tape_backed/dunepro/vd-coldbox-bottom/raw/2021/detector/test/None/00/01/19/90/np02_bde_coldbox_run011990_0000_20211104T091015.hdf5
duneproc>
duneproc> findFilePnfs np02_bde_coldbox_run011990_0000_20211104T091015.hdf5
/pnfs/dune/tape_backed/dunepro/vd-coldbox-bottom/raw/2021/detector/test/None/00/01/19/90/np02_bde_coldbox_run011990_0000_20211104T091015.hdf5
duneproc>
duneproc> findFileCache np02_bde_coldbox_run011990_0000_20211104T091015.hdf5
duneproc>
</pre>
At present, the first two assume and do not check if the file is actually present in FNAL dcache.
They also do not look for replicas in any other repositories such as CERN EOS.
And they do not check if is is staged, i.e. a replica is currently accessible on disk.
If there =is demand, such features could be added.

The last commnd checks the user's local cache (see "Caching files" below), here reporting that the file
wa not found there.

## Staging files

A user processing files from FNAL dcache may experience delays of severla minutes up to hours or longer
to open each file that is not already staged.
FNAL is one importatnt repository of physical file replicas but does not guarantee that files will
always be immediately available on disk



## Copying and Streaming data



## Caching files



