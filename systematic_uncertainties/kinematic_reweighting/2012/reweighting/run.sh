
cd bin

#reweigh 100 bins or if 2D 15 times 15 bins p and pt
#plot 50 bins

#./main  #run 1d kinre
#./main2D #run 2d kin rew
./plot  #1d kin rewe
./plot2D #plot 2d for jpsik
./plot2D_new #plot 2d for jpsik but applied to true p and pt
./plot2DSig #plot 2d for sig with jpsik weigths
./plot2DSig_new #plot 2d for sig with jpsik weigths to true p and pt

cd ../

source movetopublic.sh
