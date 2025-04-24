#!/bin/bash
gcc -shared -fPIC c/async.c -o so/async.so -lpthread
echo "async.so created!"
echo ""
