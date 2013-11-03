#! /bin/sh

files=`ldd $1 | awk '{print $3}' | grep '/'`

for file in $files
do
  echo $file
  cp $file $2
done

