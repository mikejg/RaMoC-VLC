#!/bin/bash

IFS=$'\n' read -d '' -r -a lines < /var/www/html/nas-settings

ping -c1 -w1 -q ${lines[0]} > /dev/null
if [ $? -ne 0 ]
then
  logger "WAKEUP: Send wake on lan"
  wakeonlan ${lines[1]}
fi
