# duneproc

David Adams  
March 2022

Package to facilitate the running of DUNE `lar` jobs with `dunesw` (formerly `dunetpc`).

## Installation
To install this package, first install [*dunerun*](https://github.com/dladams/dunerun) specifying the dunesw release.
Here we denote the base installation directory \<install-dir> and assume package-specific installation.
Then set up *dunerun* and the clone and install duneproc as follows:
<pre>
cd &lt;pkgdir>
source &lt;install-dir>/dunerun/setup.sh
git clone https://github.com/dladams/duneproc.git
duneproc/build
</pre>
Here \<pkgdir> is a source installation dir which can be removed after installation and the set up defines the env needed for the build command.

## Set up
To set up to use this package, set up *dunerun* and then use it to start a shell:
<pre>
source &lt;install-dir>/dunerun/setup.sh
dune-run -e dunesw,duneproc shell
duneproc> 
</pre>

## Usage

After set up, use the help command to check for success and see what commans are available:
<pre>
duneproc> duneprocHelp
/home/dladams/proc/install/v09_46_00_00/duneproc/bin/duneprocHelp OPT
  OPT = general for general commands
  OPT = pdsp for protoDUNE commands
  OPT = ib for Iceberg commands
  OPT = ibex fpr Iceberg examples
  OPT = ibex fpr Iceberg examples
</pre>

The command *duneproc* runs a *lar* job with the first argument
specifying the fcl configuration and the second the data to be processed.
For detailed help, use `duneproc -H`. Example:
<pre>
duneproc wfRaw/wfrran500/wftick4000/dpcr\_apa3u/event132560 5777evts132000-133000
</pre>

This package provides many fcl configuration files including the top-level
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
