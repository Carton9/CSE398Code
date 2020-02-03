#!/bin/sh
sshpass -p 'temppwd' scp -o StrictHostKeyChecking=no ./*.cpp debian@192.168.6.2:~ > /dev/null  2>&1
sshpass -p 'temppwd' scp -o StrictHostKeyChecking=no ./*.h debian@192.168.6.2:~ > /dev/null  2>&1
sshpass -p 'temppwd' ssh -o StrictHostKeyChecking=no debian@192.168.6.2 << EndRun
clear
g++ *.cpp -o run
exit
EndRun
exit