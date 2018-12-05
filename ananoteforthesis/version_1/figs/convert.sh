#/usr/bin/bash
for file in *.eps
do
  echo "Converting $file"
  epstopdf $file
done

