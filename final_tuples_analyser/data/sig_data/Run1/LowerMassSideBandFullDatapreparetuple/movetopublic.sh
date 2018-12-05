

here=/vols/lhcb/ss4314/$PWD
path=$(dirname $here)
file=$(basename $here)

path2=$(basename $(dirname $here))
path3=$(basename $(dirname $(dirname $here)))
path4=$(basename $(dirname $(dirname $(dirname $here))))
#file2=$(basename $here)
echo $path
echo $file
echo $path2
echo $path3
echo $path4

mkdir ~/public_html/final_tuples_analyser/$path4
mkdir ~/public_html/final_tuples_analyser/$path4/$path3
mkdir ~/public_html/final_tuples_analyser/$path4/$path3/$path2
mkdir ~/public_html/final_tuples_analyser/$path4/$path3/$path2/$file
cp bin/*pdf ~/public_html/final_tuples_analyser/$path4/$path3/$path2/$file/



