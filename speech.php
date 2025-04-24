<?php

const  kCFStringEncodingUTF8 = 0x08000100;

// module built in mac jadi cuma declare header aja
$speech = FFI::load('c/speech.h');

//bikin channerl
$channel = $speech->new("SpeechChannel", false);
$speech->NewSpeechChannel(null, FFI::addr($channel));

//inbloom -neckdeep
$lines = [
    ["line" => "Sometimes at night I let it get to me", "rate" => 100, "pitch" => 130],
    ["line" => "And sometimes I'm sure it gets to all of us", "rate" => 150, "pitch" => 32],
    ["line" => "And last night it had me down and feeling numb", "rate" => 130, "pitch" => 33],
    ["line" => "I can try but sometimes that is not enough", "rate" => 135, "pitch" => 35],

    ["line" => "No sometimes that is not enough", "rate" => 140, "pitch" => 37],
    ["line" => "No sometimes that is not enough", "rate" => 140, "pitch" => 37],

    ["line" => "And stop calling me out we're never going to", "rate" => 150, "pitch" => 100],
    ["line" => "Put the pieces back together", "rate" => 170, "pitch" => 42],
    ["line" => "If you won't let me get better", "rate" => 155, "pitch" => 44],
    ["line" => "And stop digging it up or we're never gonna", "rate" => 150, "pitch" => 41],
    ["line" => "See it all in bloom", "rate" => 50, "pitch" => 40],

    ["line" => "And thinking back upon those days", "rate" => 150, "pitch" => 33],
    ["line" => "Way way back when I was young", "rate" => 150, "pitch" => 33],
    ["line" => "I was such a little shit", "rate" => 150, "pitch" => 35],
    ["line" => "Cos I was always on the run", "rate" => 150, "pitch" => 36],
    ["line" => "Well you know just what they say", "rate" => 150, "pitch" => 34],
    ["line" => "Just like father then like son", "rate" => 150, "pitch" => 34],
    ["line" => "Don't delude me with your sympathy", "rate" => 150, "pitch" => 37],
    ["line" => "Cos I can do this on my own", "rate" => 100, "pitch" => 37],

    ["line" => "And this will be the last time", "rate" => 142, "pitch" => 38],
    ["line" => "That I break down and wanna crawl to bed", "rate" => 145, "pitch" => 40],
    ["line" => "Cos the truth is", "rate" => 80, "pitch" => 37],
    ["line" => "You're the only voice I wanna hear in my head", "rate" => 90, "pitch" => 43],

    ["line" => "And stop calling me out we're never going to", "rate" => 155, "pitch" => 44],
    ["line" => "Put the pieces back together", "rate" => 160, "pitch" => 46],
    ["line" => "If you won't let me get better", "rate" => 160, "pitch" => 46],
    ["line" => "And stop digging it up or we're never gonna", "rate" => 155, "pitch" => 44],
    ["line" => "See it ", "rate" => 110, "pitch" => 42],
    ["line" => "all ", "rate" => 120, "pitch" => 42],
    ["line" => "in bloom", "rate" => 150, "pitch" => 200],


    ["line" => "All in bloom", "rate" => 100, "pitch" => 38],
    ["line" => "All in bloom", "rate" => 100, "pitch" => 37],
];

foreach ($lines as $entry) {
    $string = $speech->CFStringCreateWithCString(null, $entry["line"], kCFStringEncodingUTF8);

    $speech->SetSpeechRate($channel, $entry["rate"] << 16); // Fixed type
    $speech->SetSpeechPitch($channel, $entry["pitch"]);

    $speech->SpeakCFString($channel, $string, null);

    while ($speech->SpeechBusy()) {
        usleep(100_000);
    }

    echo  $entry["line"] . PHP_EOL;
}
