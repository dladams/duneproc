# duneproc

David Adams  
January 2020

Package to facilitate the running of `lar` jobs with `dunetpc`.

The command `processData` runs a `lar` job with the first argument
specifying the fcl configuration and the second the data to be processed.
For detailed help, use `processData -H`.

Fcl configuration files are also provided. The top-level `run_dataprep.fcl`
runs the event and trigger filters and dataprep configured to read
detector data by APA. Alone, it does not run any tools but these may be added
in the usual fashion, e.g. by adding  
`services.RawDigitPrepService.AdcChannelToolNames: @local::protodune_dataprep_tools_calib_noiserem`  
to `local.fcl` in the job submission directory.
