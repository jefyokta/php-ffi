<?php

class FFI
{
    //for async
    public function run_async(string $name, int $delay): AsyncTask
    {

        return new AsyncTask;
    }
    public function task_done(AsyncTask $task): int
    {
        return 1 ?? 0;
    }

    public function capture_image(){}

    //for watch file
    public function watch_file(string $file) {}
    function file_changed() {}
    function stop_watching() {}

    function NewSpeechChannel(VoiceType $voiceType = null, $speechChannel) {}
    function CFStringCreateWithCString($alloc, $cstring, $encoding) {}
    function SpeechBusy(){}
    function SpeakCFString($speechChannel, $string, $opt){}
    function SetSpeechRate(){}
    function SetSpeechPitch(){}
}

class AsyncTask
{
    public string $task_name;

    public int $is_done;
}

class VoiceType {}
