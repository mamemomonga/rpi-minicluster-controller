#!/bin/bash
set -eu
BASEDIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
SERIALPORT=/dev/ttyUSB0

$BASEDIR/pi-reset/pi-reset -a $SERIALPORT
screen $SERIALPORT 115200
$BASEDIR/pi-reset/pi-reset -a $SERIALPORT

