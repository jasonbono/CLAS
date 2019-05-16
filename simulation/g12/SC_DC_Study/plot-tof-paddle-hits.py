#!/usr/bin/env python

from os import environ
import numpy as np
from matplotlib import pyplot as pl
from subprocess import Popen, PIPE

def get_tof_paddle_hits(filenames):
    ret = {}
    for sec in range(1,7):
        ret[sec] = []
    for filename in filenames:
        proc = Popen('bosdump -M100000 -GSC {0}'.format(filename),
            shell=True, executable='/bin/bash', env=environ,
            stdout=PIPE)
        sec = -1
        for line in proc.stdout.readlines():
            sline = line.split()
            if 'SC' in sline:
                sec = int(sline[3])
            elif 'ID:' in sline:
                ret[sec] += [int(sline[1])]
    return ret

def collate_paddle_occupancy(data):
    '''
    for sec in range(1,7):
        mx = max(data[sec])
        if mx > max_wire:
            max_wire = mx
    '''

    max_paddle = 57
    paddle_occupancy = np.zeros(max_paddle*6)
    paddle_occupancy.shape = (6,max_paddle)
    
    for i in range(6):
        sec = i + 1
        for paddle in data[sec]:
            if paddle > 58:
                paddle = paddle % 256
            paddle_occupancy[i,paddle-1] += 1
        
    return paddle_occupancy

def plot_paddle_occupancy(data):
    fig = pl.figure()
    ax = fig.add_subplot(1,1,1)
    plt = ax.imshow(data,
        extent=(0.5,57.5,0.5,6.5),
        interpolation='nearest',
        origin='lower', aspect='auto')
    ax.set_xlabel('TOF paddle ID')
    ax.set_ylabel('sector')

if __name__ == '__main__':
    from sys import argv
    tof_paddle_hits = get_tof_paddle_hits(argv[1:])
    paddle_occupancy = collate_paddle_occupancy(tof_paddle_hits)
    plot_paddle_occupancy(paddle_occupancy)
    pl.show()


