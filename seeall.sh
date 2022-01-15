#!/bin/bash

for file in `ls gameLog*`; do

  echo `tail -10 $file`

  echo
  echo
  echo

done
