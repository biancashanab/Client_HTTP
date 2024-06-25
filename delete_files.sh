#!/bin/bash

CACHE_DIR="Cache"

while true
do
    find &> /dev/null "$CACHE_DIR" -type f -exec sh -c 'echo "" &> /dev/null > {}' \; 
    sleep 3600
done