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
echo "PHP: Starting async task..   .\n";

$sideTask = $ffi->run_async("Ngoding", 5);
$mainTask = $ffi->run_async("Scroll Fesnuk", 10);
// $otherTask = $ffi->run_async("Ngocok", 7);
$otherTask = $ffi->run_async("Makan", 2);
$otherTask1 = $ffi->run_async("Berak", 7);




echo " PHP: Waiting while tasks runs..\n";

while (!$ffi->task_done($mainTask) || !$ffi->task_done($sideTask) || !$ffi->task_done($otherTask)|| !$ffi->task_done($otherTask1)) {
    //dely blocking kasi sikit aja
    usleep(2000);
}

echo "PHP: Detected tasks have done took " . (microtime(true) - $start) . PHP_EOL;
