#!/bin/bash

can() {
  ./cancl &
  ./cansv
}

vcan() {
  vcan_if_default="vcan0"
  read -p "Name for vcan if (default $vcan_if_default): " vcan_if
  vcan_if="${vcan_if:-$vcan_if_default}"
  modprobe vcan
  ip link add dev $vcan_if type vcan
  ip link set up $vcan_if
}
