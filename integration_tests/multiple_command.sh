#!/bin/sh

echo a ; echo b
echoa; echo b

echo a;echo b;
echo a && echo b
echo a || echo b
git status || echo a
echo A#&&echo B
echo a || exit

echo a && echo b  

