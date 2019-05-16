#!/usr/bin/env python
from subprocess import Popen, PIPE



 

#	proc = Popen(ls bosdumpSC.txt)
call(["ls", "bosdumpSC.txt"])
#	sec = -1
#	for line in proc.stdout.readlines():
#     	sline = line.split()
#      	if 'SC' in sline:
#        	sec = int(sline[3])
#        elif 'ID:' in sline:
#        	ret[sec] += [int(sline[1])]
#    return ret
