#!/bin/bash

git add -A
git rm --cached Server/moc*.cpp
git rm --cached Server/*.o
git rm --cached Server/.qmake.stash
git commit -a -m "`date`"

git push origin master

