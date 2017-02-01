# rpnc

This is a very simple rpn calculator (integers only).
It is compilable for windows and linux.
Did I mention that it is simple?

## Requirements

- gcc (`g++` with `-lxcb`)
- mingw (`i686-w64-mingw32-g++` with `-static-libgcc` and `-static-libstdc++`)

I compiled that all on a linux box (ubuntu) with the `-std=c++11` statement.

## Compiling

A Makefile is shipped:

	# linux version only (one of them)
	make
	make linux
	make unix
	make rpnc
	
	# windows version only (one of them)
	make win
	make win32
	make windows
	make rpnc.exe
	
	#both versions (one of them)
	make all
	make both

## Usage

_Use the numpad!_
_Use integers only!_

The three registers are x, y and z (in that order). Use this calculator as you would use any rpn calculator. To exit press the `q` button (in gui mode the `ESC` button will work, too).

## License

As this is just for me to learn xcb and c++ use this repository what you want. Copy, paste, change the code. But don't run to me if your computer crashes or a big cow stands in front of your house.
