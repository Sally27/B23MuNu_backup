

cd bin 

./mainRun1
./mainRun1LowFCME
./mainRun1HighFCME

for i in *tex;
do pdflatex $i;
done

cd ../

mkdir /home/hep/ss4314/public_html/getsyst/
mkdir /home/hep/ss4314/public_html/getsyst/SignalModel
mkdir /home/hep/ss4314/public_html/getsyst/SignalModel/PHSP


cp bin/*.pdf /home/hep/ss4314/public_html/getsyst/SignalModel/PHSP
