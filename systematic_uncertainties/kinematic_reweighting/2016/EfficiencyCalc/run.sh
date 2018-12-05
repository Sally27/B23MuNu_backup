
ERR_PATH=/vols/lhcb/ss4314/error_library/lib
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$ERR_PATH


make clean

make

cd bin

#./mainCompare
./mainCompareAll


for i in *tex;
do pdflatex $i;
done

cd ../


mkdir /home/hep/ss4314/public_html/getsyst/
mkdir /home/hep/ss4314/public_html/getsyst/
mkdir /home/hep/ss4314/public_html/getsyst/DataMCReweighting
mkdir /home/hep/ss4314/public_html/getsyst/DataMCReweighting/2016


cp bin/*.pdf /home/hep/ss4314/public_html/getsyst/DataMCReweighting/2016
