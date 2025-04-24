<?php
if (PHP_OS === 'Linux') {
    //please built the so file first
    $ffi = FFI::cdef("
        void watch_file(const char* path);
        int file_changed();
        void stop_watching();
    ", __DIR__ . "/so/filewatcher_inotify.so");
} elseif (PHP_OS === 'Darwin') {
    $ffi = FFI::cdef("
            void watch_file(const char* path);
            int file_changed();
            void stop_watching();
        ", __DIR__ . "/so/filewatcher.so");
}
else{
    throw new Error("yntkts");
}

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
