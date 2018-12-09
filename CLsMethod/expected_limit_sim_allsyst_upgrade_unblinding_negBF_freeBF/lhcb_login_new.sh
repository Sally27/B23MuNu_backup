#!/bin/sh
#
# Author: U. Egede, Jan 12th 2005
#
# Setup the environment for LHCb users
#
# * June 2018 - palvare1
#    --- Updated the way of getting CENTOS_VERS after new naming convention  
# * June 2016 - palvare1
#    --- Let LbLogin decide on the correct cmtconfig
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
# CENTOS_RELEASE=`cat /etc/redhat-release`
# CENTOS_VERS=${CENTOS_RELEASE:15:1}
CENTOS_VERS=`cat /etc/redhat-release | sed 's/[^0-9]*\([0-9]*\).*/\1/'`
# GCC_VERS='gcc46'
# if [ $CENTOS_VERS == '6' ]
# 	then
# 		GCC_VERS='gcc48'
# #		LCG_hostos='x86_64-slc6'
# #		export LCG_hostos
# fi
# export CMTCONFIG=x86_64-slc$CENTOS_VERS-$GCC_VERS-opt

if [ $CENTOS_VERS == '5' ]
	then
		GCC_VERS='gcc46'
		export CMTCONFIG=x86_64-slc$CENTOS_VERS-$GCC_VERS-opt
#		LCG_hostos='x86_64-slc6'
#		export LCG_hostos
fi

export CMTEXTRATAGS=host-slc$CENTOS_VERS
##

export User_release_area=$HOME/cmtuser
export CMTPATH=$User_release_area

echo Sourcing the cvmfs LHCb login. 
export MYSITEROOT=/cvmfs/lhcb.cern.ch/lib/
. $MYSITEROOT/LbLogin.sh

if [ $CENTOS_VERS == '6' ]
	then
		LCG_hostos='x86_64-slc6'
		export LCG_hostos
fi

if [ $CENTOS_VERS == '7' ]
then
    LCG_hostos='x86_64-centos7'
    export LCG_hostos
    export CMTEXTRATAGS='host-centos7'
fi

GANGA_SITE_CONFIG_AREA=/home/hep/lhcb/ganga/config/LHCb
export GANGA_SITE_CONFIG_AREA


PATH=~lhcb/bin:$PATH
export PATH
echo =========================================================
