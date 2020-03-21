# directSetup.sh
#
# David Adams
# January 2020

ERRMSG='***********************************************
This is the direct packages setup.
It is preferable to build with ./build and then
run setup from the installation directory.
***********************************************'

echo "$ERRMSG"

if [ -n "$DUNEPROC_DIR" ]; then
  echo It appears duneproc is already set up:
  echo DUNEPROC_DIR = $DUNEPROC_DIR

elif [ -z "$DUNETPC_VERSION" ]; then
  echo "Please set up dunetpc."

else

  echo Setting up duneproc
  DUNEPROC_DIR=$(dirname $(readlink -f $BASH_SOURCE))
  PATH=$DUNEPROC_DIR/bin:$PATH
  TMPPATH=.:./job:
  if [ ${FHICL_FILE_PATH:0:8} = $TMPPATH ]; then FHICL_FILE_PATH=${FHICL_FILE_PATH:8}; fi
  FHICL_FILE_PATH=${TMPPATH}$DUNEPROC_DIR/fcl:$FHICL_FILE_PATH
  unset TMPPATH

fi

echo "$ERRMSG"
