#!/bin/sh
#
# Author: U. Egede, Jan 12th 2005
#
# Setup the environment for LHCb users
#
# * March 2014 - stc09
#    --- check for CentOS 5 vs 6 version and use correct cmtconfig
# * December 2014 - stc09
#    --- replace X509 dirs being set explicitly by IC grid setup script
#    --- change MYSITEROOT to point to /cmvfs 

echo =========================================================
echo This is the LHCb setup at Imperial
echo ---------------------------------------------------------
echo Setting up grid for Imperial
. /vols/grid/ui/current.sh

##
# figure out the machine's config -- can remove when CentOS5 is gone
CENTOS_RELEASE=`cat /etc/redhat-release`
CENTOS_VERS=${CENTOS_RELEASE:15:1}
GCC_VERS='gcc46'
if [ $CENTOS_VERS == '7' ]
	then
		GCC_VERS='gcc49'
#		LCG_hostos='x86_64-slc6'
#		export LCG_hostos
fi
export CMTCONFIG=x86_64-slc$CENTOS_VERS-$GCC_VERS-opt
export CMTEXTRATAGS=host-slc$CENTOS_VERS
##

export User_release_area=$HOME/cmtuser
export CMTPATH=$User_release_area

echo Sourcing the cvmfs LHCb login. 
export MYSITEROOT=/cvmfs/lhcb.cern.ch/lib/
. $MYSITEROOT/LbLogin.sh

if [ $CENTOS_VERS == '7' ]
	then
		LCG_hostos='x86_64-slc6'
		export LCG_hostos
fi

GANGA_SITE_CONFIG_AREA=/vols/lhcbdisk05/ganga/config/LHCb
export GANGA_SITE_CONFIG_AREA


PATH=~lhcb/bin:$PATH
export PATH
echo =========================================================
