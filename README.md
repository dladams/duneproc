# duneproc

David Adams  
March 2022

Package to facilitate the running of DUNE `lar` jobs with `dunesw` (formerly `dunetpc`).

The command *duneproc* runs a *lar* job with the first argument
specifying the fcl configuration and the second the data to be processed.
For detailed help, use `duneproc -H`. Example:
<pre>
duneproc wfRaw/wfrran500/wftick4000/dpcr\_apa3u/event132560 5777evts132000-133000
</pre>

To gain access to this command, install [dunerun](https://github.com/dladams/dunerun)
specifying a DUNE release version, and the use it to set up the DUNE SW and to
buid and set up this package.

This package provides many fcl configuration files including the he top-level
*run_dataprep.fcl* which runs the event and trigger filters and dataprep configured
to read protoDUNE (I) data by APA.
Alone, it does not run any tools but these may be added in the usual fashion, e.g. by adding
<pre>
services.RawDigitPrepService.AdcChannelToolNames: @local::protodune_dataprep_tools_calib_noiserem
</pre>
to `local.fcl` in the job submission directory.
This runs the standard processing up to the point where the ROIs and energy calibration
are dropped in preparation for wirecell processing.

A tutorial to get started is available [doc/tutorial01.md](doc/tutorial01.md)
and a tutorial on the duneproc command is at [doc/tutorial02.md](doc/tutorial02.md).
The latter has some useful protoDUNE examples.

There is also a [tutorial for Iceberg](doc/tutorial_iceberg.md).
