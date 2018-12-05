
mkdir /vols/lhcb/ss4314/fitsignal_before_misidbdt

folder_old=estimateformisidbdt_newTCK_2016
folder_new=estimateformisidbdt_finalPID_2016

cd /vols/lhcb/ss4314/fitsignal_before_misidbdt/

mkdir /vols/lhcb/ss4314/fitsignal_before_misidbdt/$folder_new

cp -r /vols/lhcb/ss4314/fitsignal_before_misidbdt/$folder_old/* /vols/lhcb/ss4314/fitsignal_before_misidbdt/$folder_new/

cd $folder_new 

#need to change all of these to fit
