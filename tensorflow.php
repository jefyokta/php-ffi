<?php

$tfLib = "/usr/local/lib/libtensorflow.dylib";
$myCHeaderFile = file_get_contents(__DIR__."/c/tensorflow.h");
$ffi = FFI::cdef($myCHeaderFile, $tfLib);

$status = $ffi->TF_NewStatus();
$graph = $ffi->TF_NewGraph();
$sessOpts = $ffi->TF_NewSessionOptions();

$modelDir = __DIR__ . "/logreg_tf_model";

// Buat array pointer const char* dengan 1 elemen
$tagsArray = $ffi->new("const char*[1]");

// Buat string literal 'serve' sebagai C string immutable
// gunakan FFI::new("char[]", false) supaya tidak "owned"
$serveStr = $ffi->new("char[6]", false);
FFI::memcpy($serveStr, "serve\0", 6);

// Cast ke const char* (karena tagsArray butuh const char*)
// lalu assign pointer itu ke tagsArray[0]
$tagsArray[0] = $ffi->cast("const char*", $serveStr);

$session = $ffi->TF_LoadSessionFromSavedModel(
    $sessOpts,
    NULL,
    $modelDir,
    $tagsArray,
    1,
    $graph,
    NULL,
    $status
);

$code = $ffi->TF_GetCode($status);
if ($code != 0) {
    echo "Error loading model: " . $ffi->TF_Message($status) . PHP_EOL;
    exit(1);
}

echo "Model berhasil dimuat!" . PHP_EOL;

// Cleanup
$ffi->TF_CloseSession($session, $status);
$ffi->TF_DeleteSession($session, $status);
$ffi->TF_DeleteSessionOptions($sessOpts);
$ffi->TF_DeleteStatus($status);
$ffi->TF_DeleteGraph($graph);
