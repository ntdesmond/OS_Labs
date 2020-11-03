#!/bin/bash
# print bytes from /dev/random, discarding everything except printable chars, limit to the first 20.
# tested with /dev/urandom only
cat /dev/random | tr -dc [:print:] | head -c20 > ex1.txt

