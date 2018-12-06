#!/bin/bash
set -eu
BASEDIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
SERIALPORT=/dev/ttyUSB0
BOOTWAIT=360
cd $BASEDIR

function log {
	echo '['$(date +"%Y/%m/%d %H:%M:%S")'] '$1
}

while true; do
	if [ "$(curl -s -m 5 http://pi1:4000 >/dev/null; echo $?)" != "0" ]; then
		log "RESET PI1"
		./pi-reset/pi-reset -1 $SERIALPORT
		sleep $BOOTWAIT
		log "CONTINUE CHECKING"
	fi
	if [ "$(curl -s -m 5 http://pi2:3000 >/dev/null; echo $?)" != "0" ]; then
		log "RESET PI2"
		./pi-reset/pi-reset -2 $SERIALPORT
		sleep $BOOTWAIT
		log "CONTINUE CHECKING"
	fi
	if [ "$(curl -s -m 5 http://pi3:3000 >/dev/null; echo $?)" != "0" ]; then
		log "RESET PI3"
		./pi-reset/pi-reset -3 $SERIALPORT
		sleep $BOOTWAIT
		log "CONTINUE CHECKING"
	fi
	sleep 1
done
