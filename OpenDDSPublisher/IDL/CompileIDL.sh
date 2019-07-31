#!/bin/sh

export DANCE_ROOT=unused
export DYLD_LIBRARY_PATH=${DYLD_LIBRARY_PATH}:/Users/nikhil.bagul/OpenDDS/OpenDDS-3.13.2/ACE_wrappers/lib:/Users/nikhil.bagul/OpenDDS/OpenDDS-3.13.2/lib
export CIAO_ROOT=unused
export TAO_ROOT=/Users/nikhil.bagul/OpenDDS/OpenDDS-3.13.2/ACE_wrappers/TAO
export DDS_ROOT=/Users/nikhil.bagul/OpenDDS/OpenDDS-3.13.2
export PATH=${PATH}:/Users/nikhil.bagul/OpenDDS/OpenDDS-3.13.2/ACE_wrappers/bin:/Users/nikhil.bagul/OpenDDS/OpenDDS-3.13.2/bin
export MPC_ROOT=/Users/nikhil.bagul/OpenDDS/OpenDDS-3.13.2/ACE_wrappers/MPC
export ACE_ROOT=/Users/nikhil.bagul/OpenDDS/OpenDDS-3.13.2/ACE_wrappers

$ACE_ROOT/bin/mwc.pl -static -type gnuace MessengerMinimal.mwc

make
