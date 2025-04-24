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
