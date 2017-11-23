#!/bin/bash

rm -f png/AlgoPNG* 
BinaryBuilder png/ ./ AlgoPNG
mv AlgoPNG* png/

