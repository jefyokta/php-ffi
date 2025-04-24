<?php

class FFI
{
    public function run_async(string $name, int $delay): AsyncTask {

        return new AsyncTask;
    }
    public function task_done(AsyncTask $task): int {
        return 1 ?? 0;
    }

    public function watch_file(string $file){}

    function file_changed(){}
    function stop_watching(){}
}



class AsyncTask
{
    /** @var string */
    public string $task_name;

    /** @var int */
    public int $is_done;
}

class AsyncTaskParam {
    
}
