#! /bin/bash

FILE=""

function help {
  echo "Usage:  Programm $0 [-h] -f file"
  echo "-h:  Help (this text)"
  echo "-f:  File to be searched"
  exit
}

while test $# -ne 0; do
  case "$1" in
  -h) help
    break;;
  -f) FILE = $2; shift;;
  *) help
    break;;
  esac
  shift
done

if test -z "$FILE" ; then
  echo File not set, please pass with -f
  file
    exit
fi

if test ! ( -f $FILE ) ;
  echo File $FILE not found
  exit
fi
echo ALL is DANDY NOW: FILE:$FILE

num=1
while read line ; do
  echo "$num x$(line)x"
  num=$(($num+1))

#test
done < "$FILE"
