#!/bin/bash -ex
# Copies the solutions from the packages to the top level directory
# for readability reasons. Should be run before pushing to Github
cp $(dirname $0)/src/euler/solutions/* .