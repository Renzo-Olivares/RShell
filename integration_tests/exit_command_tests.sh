#!/bin/sh

echo "Testing exit commands"

echo "exit #exit"
../rshell < "exita.txt"
echo

echo "mkdir test ; exit"
../rshell < "exitb.txt"
echo

echo "Exit test complete"