# abSynth-FM
FM Synthesizer with step sequencer for Arduboy.

Mr. pcm1723's FM Synthesis engine in [FMMelody](http://www.geocities.jp/pcm1723/html/fmmelody.htm) is used.
# Installation
You need [Arduboy2 Library](https://github.com/MLXXXp/Arduboy2).

# Usage
See this video.

<a href="http://www.youtube.com/watch?feature=player_embedded&v=sLkr5ASdnj8" target="_blank"><img src="http://img.youtube.com/vi/sLkr5ASdnj8/0.jpg" alt="IMAGE ALT TEXT HERE" width="240" height="180" border="10" /></a>

<a href="http://www.youtube.com/watch?feature=player_embedded&v=x0wAuAnk9Uw" target="_blank"><img src="http://img.youtube.com/vi/x0wAuAnk9Uw/0.jpg" alt="IMAGE ALT TEXT HERE" width="240" height="180" border="10" /></a>

#Data format of serial port communication

## Syntax

A series of bytes in hexadecimal digits, separated with delimiters.

Delimiters are newline, return, or space.

All characters from '#' to the end of line are ignored. You can use '#' to include comments in the data.

## Header section

|field           |type      |value  |
|----------------|----------|-------|
|Signature       |uint8_t[4]|abFM   |
|Version         |uint8_t   |1      |
|Num of Sequences|uint8_t   |1 or 16|

## Sequence section

|field           |type      |value  |
|----------------|----------|-------|
|Tempo           |uint8_t   |56..240|
|Transpose       |int8_t    |1-2..+2|
|Flags(reserved) |uint8_t   |128    |
|Synth parameters|uint8_t[5]|0..255 |
|Notes           |int8_t[16]|(below)|

## Note data

|type|value |description                        |
|----|------|-----------------------------------|
|rest|-1    |no sound in the step               |
|tie |-2    |continue previous note in the step |
|note|48..84|48 for C4, 84 for C7               |
