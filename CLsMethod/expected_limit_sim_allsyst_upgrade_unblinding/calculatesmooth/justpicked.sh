
#hadd -f plotExclusionLimit/info_new.root toy_1000_*/info_new.root 
#hadd -f plotExclusionLimit/bin/info_new.root toy_1000_*/info_new.root #toy_1000_4_0*/info_new.root


#path1="toy_1000_minus_2_5e_8sig"
#path2="toy_1000_minus_2_25e_8"
#path3="toy_1000_minus_2_0e_8sig"
#path4="toy_1000_minus_1_75e_8sig"
#path5="toy_1000_minus_1_5e_8sig"
#path6="toy_1000_minus_1_25e_8sig"
#path7="toy_1000_minus_1_0e_8"
#path8="toy_1000_minus_0_75e_8sig"
#path9="toy_1000_minus_0_5e_8sig"
#pathp1="toy_1000_minus_0_0e_8sig"
#pathp2="toy_1000_0_5e_8sig"
#pathp3="toy_1000_0_75e_8sig"
#pathp4="toy_1000_1_0e_8"
#pathp5="toy_1000_1_05e_8"
#pathp6="toy_1000_1_10e_8"
#pathp7="toy_1000_1_15e_8"
#pathp8="toy_1000_1_20e_8"
#pathp9="toy_1000_1_25e_8sig"
#pathp10="toy_1000_1_5e_8sig"
#pathp11="toy_1000_1_75e_8sig"
#pathp12="toy_1000_2_0e_8sig"
#pathp13="toy_1000_2_25e_8"
#
#
#for a in $path1,-2.5e-8 $path2,-2.25e-8 $path3,-2.0e-8 $path4,-1.75e-8 $path5,-1.5e-8 $path6,-1.25e-8 $path7,-1.0e-8 $path8,-0.75e-8 $path9,-0.5e-8 $pathp1,0.0 $pathp2,0.5e-8 $pathp3,0.75e-8 $pathp4,1.0e-8 $pathp5,1.05e-8 $pathp6,1.10e-8 $pathp7,1.15e-8 $pathp8,1.20e-8 $pathp9,1.25e-8 $pathp10,1.5e-8 $pathp11,1.75e-8 $pathp12,2.0e-8 $pathp13,,2.25e-8
#do 
#
#    i=`echo "$a" | cut -d',' -f1`
#    j=`echo "$a" | cut -d',' -f2`
#     echo $i
#     echo $j
#
#    mkdir $i
#    cp bin/main $i/
#    cp $i/info_new.root $i/
#    cp $i/roofitresult.root $i/
#    cp $i/fitresults_forCLs.root $i/
#    cd $i
#    ./main 1000 $j
#    cd  
#
#
#
#done
#
#i=0

#for b in -2.5e-8 -2.25e-8 -2.0e-8 -2.75e-8 -1.5e-8 -1.25e-8 -1.0e-8 -0.75e-8 -0.5e-8 0.0 0.5e-8 0.75e-8 1.0e-8 1.05e-8 1.10e-8 1.15e-8 1.20e-8 1.25e-8 1.5e-8 1.75e-8 2.0e-8 2.25e-8

#i=0
#int i 
#do
#    i=0

#IFS=" "
#for ch in $ch1; do
#    echo ${b:$i:1} ${a:$i:1}
#    (( i+=1 ))
# echo b
# echo $b
# cd $path1

#done



#pathp9=toy_1000_2_0e_8sig

hadd -f plotExclusionLimit/bin/info_new_picked.root  toy_1000_*/info_new.root 

#toy_1000_minus_2_25e_8/info_new.root toy_1000_minus_2_0e_8sig/info_new.root toy_1000_minus_1_75e_8sig/info_new.root toy_1000_minus_1_5e_8sig/info_new.root toy_1000_minus_1_25e_8sig/info_new.root toy_1000_minus_1_0e_8/info_new.root toy_1000_minus_0_75e_8sig/info_new.root toy_1000_minus_0_5e_8sig/info_new.root toy_1000_minus_0_0e_8sig/info_new.root toy_1000_0_5e_8sig/info_new.root toy_1000_0_75e_8sig/info_new.root toy_1000_1_0e_8/info_new.root toy_1000_1_25e_8sig/info_new.root toy_1000_1_5e_8sig/info_new.root toy_1000_1_75e_8sig/info_new.root toy_1000_2_0e_8sig/info_new.root toy_1000_2_25e_8/info_new.root toy_1000_2_5e_8sig/info_new.root

#hadd Source file 33: toy_1000_minus_2_75e_8/info_new.root

