#! /bin/sh
rm -f *.log
nohup ./service -p 9987 > service.log 2>&1 &
