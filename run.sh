#!/usr/bin/env bash

if [[ $# -eq 0 ]] ; then
    echo 'Specify directory!'
    exit 0
fi

timestamp() {
   date +%d-%m-%Y_%H-%M-%S
}

destination="${1}"
mkdir $destination

echo "Running..."
echo "Creating dir"
dirname=$(timestamp)

mkdir "${destination}/${dirname}"
mkdir "${destination}/${dirname}/res"

cp bubble_plotter_2d.py "${destination}/${dirname}"
cp bubble_plotter_3d.py "${destination}/${dirname}"

echo "Compiling..."
programname="lbm_$(timestamp).out"
g++ -O3 -o ${programname} main.cpp

echo "Moving to exec folder..."

mv ${programname} "${destination}/${dirname}"
cd ${destination}/${dirname} || { echo "No such dir"; exit 1; }

echo "Executing in background..."
./${programname}

process_id=`/bin/ps -fu $USER| grep ${programname} | grep -v "grep" | awk '{print $2}'`

echo "PID of the process: ${process_id}"
echo "PID of the process: ${process_id}" >> processPID.txt
