
mkdir /home/hep/ss4314/public_html/getsyst/
mkdir /home/hep/ss4314/public_html/getsyst/total_systematics_summary


cp bin/*.pdf /home/hep/ss4314/public_html/getsyst/total_systematics_summary

cp bin/*.tex /home/hep/ss4314/public_html/getsyst/total_systematics_summary
echo $PWD >> pathtocode.txt

cp pathtocode.txt /home/hep/ss4314/public_html/getsyst/total_systematics_summary/

varprepath=getsyst/total_systematics_summary

mkdir /home/hep/ss4314/public_html/$varprepath/code_calculation

cp -r include /home/hep/ss4314/public_html/$varprepath/code_calculation/
cp -r src /home/hep/ss4314/public_html/$varprepath/code_calculation/

cp Makefile /home/hep/ss4314/public_html/$varprepath/code_calculation/
cp *sh /home/hep/ss4314/public_html/$varprepath/code_calculation/


