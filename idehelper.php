<?php

class FFI
{
    /**
     * Jalankan fungsi C async (via FFI)
     *
     * @param string $name
     * @param int $delay
     * @return AsyncTask
     */
    public function run_async(string $name, int $delay): AsyncTask {

        return new AsyncTask;
    }

    /**
     * Cek status task async
     *
     * @param AsyncTask $task
     * @return int
     */
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
