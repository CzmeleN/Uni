#!/bin/sh
mkdir cb
cd cb

mkdir proj1
cd proj1
mkdir bin
touch bin/plik1
touch del.cbp

cd ..
mkdir proj2
touch proj2/not_del

mkdir test
cd test
mkdir dir
touch test.txt
truncate -s 20M big_file
