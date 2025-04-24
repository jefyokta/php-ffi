#!/bin/bash
gcc -shared -fPIC c/async.c -o so/async.so -lpthread
echo "async.so created!"
gcc -shared -fPIC -pthread -o so/filewatcher.so c/filewatcher.c
echo "filewatcher.so"
