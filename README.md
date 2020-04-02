# duneproc

David Adams  
March 2020

Package to facilitate the running of DUNE `lar` jobs with `dunetpc`.

The command `duneproc` runs a `lar` job with the first argument
specifying the fcl configuration and the second the data to be processed.
For detailed help, use `duneproc -H`. Example:  
  duneproc wfRaw/wfrran500/wftick4000/dpcr\_apa3u/event132560 5777evts132000-133000

To gain access to this command, first set up a recent version of dunetpc or
protoduneana e.g. by following the instructions on the
[DUNE LAr SW page](https://wiki.dunescience.org/wiki/DUNE_LAr_Software_Releases#Using_DUNE_releases).
Then fetch, build and set up this package following the
[myproj instructions](https://github.com/dladams/myproj/blob/master/README.md)
replacing myproj with duneproc.

Fcl configuration files are also provided. The top-level `run_dataprep.fcl`
runs the event and trigger filters and dataprep configured to read
detector data by APA. Alone, it does not run any tools but these may be added
in the usual fashion, e.g. by adding  
`services.RawDigitPrepService.AdcChannelToolNames: @local::protodune_dataprep_tools_calib_noiserem`  
to `local.fcl` in the job submission directory.
This runs the standard processing up to the point where the ROIs and energy calibration
are dropped in preparation for wirecell processing.

A tutorial to get started is available [doc/tutorial01.txt](doc/tutorial01.txt)
and a tutorial on the duneproc command is at [doc/tutorial02.md](doc/tutorial02.md).

There is also a [tutorial for Iceberg](doc/tutorial_iceberg.md).
