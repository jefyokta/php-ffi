<?php

$ffi = FFI::cdef("
    typedef struct {
    char* task_name;
    int is_done;
} AsyncTask;
    AsyncTask* run_async(const char* name);
    int task_done(AsyncTask*);
", "./so/libasync.so");

echo "🧠 PHP: Starting async task...\n";
$sideTask = $ffi->run_async("Ngoding");
$mainTask = $ffi->run_async("Scroll Fesnuk");


echo "📍 PHP: Waiting while task runs...\n";

while (!$ffi->task_done($mainTask) || !$ffi->task_done($sideTask)) {
    echo "⏳ PHP: Still waiting...\n";
    usleep(500_000); 
}

echo "✅ PHP: Detected task is done!\n";
