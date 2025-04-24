<?php

$ffi = FFI::cdef("
    void watch_file(const char* path);
    int file_changed();
    void stop_watching();
", __DIR__ . "/so/filewatcher.so");

$file = __FILE__;


echo "PHP: Monitoring: $file\n";

$ffi->watch_file($file);



while (1) {
    if ($ffi->file_changed()) {
        echo "File $file changed!\n";
    } else {
        echo "nothing...\n";
    }
    usleep(500_000);
}



