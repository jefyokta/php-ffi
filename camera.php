<?php
//accessing macos camera with php
$ffi = FFI::cdef("
    void capture_image(const char *output_path);
", "./so/libcamera.dylib");

$ffi->capture_image("./photo.jpg");
