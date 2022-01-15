#!/bin/bash

for file in `ls gameLog*`; do

  lastline=`tail -1 $file`

  echo $lastline,

  if [ "$lastline" == 'A8 A8' ]; then
    echo removed
    rm "$file"
  fi
done
