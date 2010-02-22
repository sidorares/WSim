#! /bin/sh

## =============Conf=====================
WSIM=wsim-wsn430
WTRC=wtracer

LOG="--logfile=wsim.log --verbose=2"
TRC="--trace=wsim.trc"
SERIAL="--serial1_io=stdout"
MODE="--mode=time --modearg=30s"
#MODE="--mode=gdb"
UI="--ui"
## ======================================


## =============WSIM=====================
WS1="${WSIM} ${UI} ${MODE} ${SERIAL} ${LOG} ${TRC} ./wsn430-m25p80.elf"
xterm -T wsim-1 -e "${WS1}" &
echo "${WS1}"
## ======================================


## =============Wait=====================
read dummyval
## ======================================


## =============Traces===================
${WTRC} --in=wsim.trc --out=wsim.vcd --format=vcd
## ======================================


## =============End======================
killall -SIGUSR1 ${WSIM}   > /dev/null 2>&1
## ======================================

