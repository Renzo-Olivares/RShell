#!/bin/sh

echo "Testing commented commands"

echo "echo '#'"
../rshell < "commenta.txt"
echo

echo "echo A#"
../rshell < "commentb.txt"
echo

echo "Comment test complete"

