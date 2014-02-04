#! /bin/sh

#sudo ../../bin/NidaqReader.bin 0 1 0 &
#sudo taskset 0x00000001 ../../bin/NidaqReader.bin 0 1 0 &
sudo taskset 0x00000001 /home/jb/Desktop/Work/rexeno/trunk/prototypes/Launcher/launcher.bin 0 1 0 &
sleep 1
#sudo taskset 0x00000002 ../../bin/NidaqSaver/NidaqSaver.bin &
sudo ../../bin/NidaqSaver/NidaqSaver.bin &
sudo taskset 0x00000002 ./display 0 1 0
#sudo ./display 0 1 0
pkill -9 NidaqSaver.bin
pkill -9 NidaqReader.bin

# Creation d'un fichier qui indique au nidaqreader qu'il faut s'arreter !
touch ../../bin/test.txt
sleep 4
rm ../../bin/test.txt

sleep 3

#sudo /home/bin/matlab -nodesktop -nosplash -nojvm -r "dummy" > toto.txt
sleep 2
sudo chmod 777 a_b.txt
tail -n 5 toto.txt > a_b.txt
rm toto.txt
#a = `head -n 1 a_b.txt`
#b = `tail -n 1 a_b.txt | head -n 1`

# Copie les constantes de calibrations dans le fichier principal !
cp a_b.txt ..
