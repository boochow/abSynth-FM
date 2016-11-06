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

Data starts with a header section followd by a series of sequence section.

## Header section

|field           |type      |value  |
|----------------|----------|-------|
|Signature       |uint8_t[4]|'abFM' |
|Version         |uint8_t   |1      |
|Num of Sequences|uint8_t   |1 or 16|

## Sequence section

|field           |type      |value  |
|----------------|----------|-------|
|Tempo           |uint8_t   |56..240|
|Transpose       |int8_t    |-2..+2 |
|Flags(reserved) |uint8_t   |128    |
|Synth parameters|uint8_t[5]|0..255 |
|Notes           |int8_t[16]|(below)|
|End mark        |uint8_t   |128    |

## Note data

|type|value |description                        |
|----|------|-----------------------------------|
|rest|-1    |no sound in the step               |
|tie |-2    |continue previous note in the step |
|note|48..84|48 for C4, 84 for C7               |

## Example

One sequence
```
61 62 46 4D 01 01
3C 00 80 06 02 1B 01 02 3C 3C 43 43 45 45 43 FE 41 41 40 40 3E 3E 3C FE 80
```

16 sequences
```
61 62 46 4D 01 10
#Sequence 1-8
3C 00 80 06 02 1B 01 02 3C 3C 43 43 45 45 43 FE 41 41 40 40 3E 3E 3C FE 80
3C 00 80 05 02 1C 01 02 43 43 41 41 40 40 3E FE 43 43 41 41 40 40 3E FE 80
60 01 80 07 05 26 05 02 40 40 40 FE 40 40 40 FE 40 43 3C 3E 40 FE FF FF 80
60 01 80 07 05 26 05 02 41 41 41 41 41 40 40 40 40 3E 3E 40 3E FF 43 FE 80
60 01 80 07 05 26 05 02 41 41 41 41 41 40 40 40 43 43 41 3E 3C FF FF FF 80
4A FF 80 05 09 20 02 02 41 45 48 4C 41 45 47 4A 40 43 47 4A 40 43 45 48 80
C0 00 80 00 08 22 08 07 43 43 43 43 FF 46 46 46 46 FF 46 46 FF 46 46 46 80
94 00 80 00 08 22 08 07 3C 48 3C 45 3C 41 3C 43 3C 48 3C 4A 3C 47 3C 48 80
#Sequence 9-16
4C 00 80 07 03 20 01 02 34 39 3C 45 3B 3F 43 3F 42 FE 40 FE 3B FE 37 FE 80
7E 00 80 02 0C 00 07 07 3C 48 4B 4A 48 46 44 43 41 3F 3E 3F 3B 3C 3E 37 80
82 FF 80 04 01 10 01 02 3C 3C FF 3C 43 43 FF 43 45 FE 3C 45 41 FE 45 41 80
F0 00 80 04 01 10 01 02 3C 3E 40 42 44 46 48 4A 4C 4A 48 46 44 42 40 3E 80
78 FF 80 04 01 08 03 02 3E 3E 3E 3E 3E 3E 3E 3E 41 41 41 41 3C 3C 3C 40 80
73 FF 80 04 01 08 03 02 3C FE FE 3C FF 37 37 37 3C FE FE 3C FF FF 3C 3F 80
82 FF 80 02 0C 00 07 07 34 FF 45 FF 34 FF 45 34 FF 34 45 FF 34 FF 45 34 80
82 FF 80 02 0C 00 07 07 34 FF 45 FF 34 FF 45 34 FF 34 45 34 45 45 34 44 80
```
