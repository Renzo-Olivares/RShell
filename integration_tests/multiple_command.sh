#!/bin/sh

echo a ; echo b
echoa; echo b

echo a;echo b;
echo a && echo b
echo a || echo b
git status || echo a
echo A#&&echo B
echo a || exit
ls -a && echo "hey" && mkdir test1 && echo goodbye
cd test1 ;  mkdir test2
ls -a || echo a && echo b  

