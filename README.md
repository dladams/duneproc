# duneproc

David Adams  
February 2022

Package to facilitate the running of DUNE `lar` jobs with `dunesw` (fomerly `dunetpc`).

The command `duneproc` runs a `lar` job with the first argument
specifying the fcl configuration and the second the data to be processed.
For detailed help, use `duneproc -H`. Example:  
  duneproc wfRaw/wfrran500/wftick4000/dpcr\_apa3u/event132560 5777evts132000-133000

To gain access to this command, first set up a recent version of dunesw. E.g., if cvmfs is available:
<pre>
source /cvmfs/dune.opensciencegrid.org/products/dune/setup_dune.sh
setup dunesw v09_42_00_02 -q e20:prof
</pre>
If not, instructions for installation may be found on the
[DUNE LAr SW page](https://wiki.dunescience.org/wiki/DUNE_LAr_Software_Releases#Using_DUNE_releases).
and elsewhere.

Fcl configuration files are also provided. The top-level `run_dataprep.fcl`
runs the event and trigger filters and dataprep configured to read
detector data by APA. Alone, it does not run any tools but these may be added
in the usual fashion, e.g. by adding  
`services.RawDigitPrepService.AdcChannelToolNames: @local::protodune_dataprep_tools_calib_noiserem`  
to `local.fcl` in the job submission directory.
This runs the standard processing up to the point where the ROIs and energy calibration
are dropped in preparation for wirecell processing.

A tutorial to get started is available [doc/tutorial01.md](doc/tutorial01.md)
and a tutorial on the duneproc command is at [doc/tutorial02.md](doc/tutorial02.md).
The latter has some useful protoDUNE examples.

There is also a [tutorial for Iceberg](doc/tutorial_iceberg.md).
