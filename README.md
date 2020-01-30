# duneproc

David Adams  
January 2020

Package to facilitate the running of `lar` jobs with `dunetpc`.

The command `processData` runs a `lar` job with the first argument
specifying the fcl configuration and the second the data to be processed.
For detailed help, use `processData -H`. Example:
  processData wfRaw/wfrran500/wftick4000/dpcr\_apa3u/event132560 5777evts132000-133000

To gain access to this command, first set up a recent version of dunetpc or protoduneana e.g.
following the instructions on the [DUNE LAr SW page](https://wiki.dunescience.org/wiki/DUNE_LAr_Software_Releases#Using_DUNE_releases).
The clone this package and source setup.sh in the top-level directory.

Fcl configuration files are also provided. The top-level `run_dataprep.fcl`
runs the event and trigger filters and dataprep configured to read
detector data by APA. Alone, it does not run any tools but these may be added
in the usual fashion, e.g. by adding  
`services.RawDigitPrepService.AdcChannelToolNames: @local::protodune_dataprep_tools_calib_noiserem`  
to `local.fcl` in the job submission directory.
This runs the standard processing up to the point where the ROIs and energy calibration
are dropped in preparation for wirecell processing.
