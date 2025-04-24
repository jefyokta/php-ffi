<?php

$ffi = FFI::cdef("
    typedef struct {
    char* task_name;
    int is_done;
} AsyncTask;
    AsyncTask* run_async(const char* name, int delay);
    int task_done(AsyncTask*);
", "./so/async.so");

$start = microtime(true);
echo "PHP: Starting async task...\n";

$sideTask = $ffi->run_async("Ngoding",3);
$mainTask = $ffi->run_async("Scroll Fesnuk",10);


echo " PHP: Waiting while task runs...\n";

while (!$ffi->task_done($mainTask) || !$ffi->task_done($sideTask)) {
    echo "⏳ PHP: Still waiting...\n";
    usleep(500_000); 
}

echo " PHP: Detected task is done took ". (microtime(true) - $start).PHP_EOL;
