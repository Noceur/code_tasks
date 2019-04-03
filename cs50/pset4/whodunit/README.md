# Questions

## What's `stdint.h`?
* It's a header file which defines ints of certain sizes, for example in some systems a int might not be the size that you are used to so being able to specify a int of x amount of bytes becomes useful, fixed-width integer.

## What's the point of using `uint8_t`, `uint32_t`, `int32_t`, and `uint16_t` in a program?
* To better indicate what the use of the variable is or in systems where you want to be specific with the ints size. uint8_t is a int 8 bits big. Also saves memory because it's small which might be useful where memory is limited (embedded perhaps?)

## How many bytes is a `BYTE`, a `DWORD`, a `LONG`, and a `WORD`, respectively?
* BYTE = 1 byte
* WORD = 2 bytes
* DWORD = 4 bytes
* LONG = 4 bytes

## What (in ASCII, decimal, or hexadecimal) must the first two bytes of any BMP file be? Leading bytes used to identify file formats (with high probability) are generally called "magic numbers."
*  0x42 0x4D

## What's the difference between `bfSize` and `biSize`?
* bfSize is the size of the whole bitmap, biSize is the size of the BITMAPINFOHEADER (40 bytes) which contains information regarding dimensions and color format of a device-indepedent bitmap (DIB).

## What does it mean if `biHeight` is negative?
* It means that the DIB is top-down and origin is at the upper left corner.

## What field in `BITMAPINFOHEADER` specifies the BMP's color depth (i.e., bits per pixel)?
* biBitCount

## Why might `fopen` return `NULL` in lines 24 and 32 of `copy.c`?
* Because a file could not be opened, if the pointer is NULL.

## Why is the third argument to `fread` always `1` in our code?
* Because we are reading in a single block the size of BITMAPFILEHEADER.

## What value does line 65 of `copy.c` assign to `padding` if `bi.biWidth` is `3`?
* 3 because 3pixels*3bytes=9, to be possible to divide by 12 it needs another 3 byte.

## What does `fseek` do?
* Moves the file pointer using an offset, it can move it to the start of the file, from where it currently is or from the end of the file.

## What is `SEEK_CUR`?
* SEEK_CUR is where the file pointer currently is.

## Whodunit?
* Professor plum with a candlestick in the library.