

ERR_PATH=/vols/lhcb/ss4314/error_library/lib
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$ERR_PATH

make clean

make


cd bin


./mainCompareAll


for i in *tex;
do pdflatex $i;
done


mkdir /home/hep/ss4314/public_html/getsyst/
mkdir /home/hep/ss4314/public_html/getsyst/
mkdir /home/hep/ss4314/public_html/getsyst/DataMCReweighting
mkdir /home/hep/ss4314/public_html/getsyst/DataMCReweighting/Run1


cp bin/*.pdf /home/hep/ss4314/public_html/getsyst/DataMCReweighting/Run1/


