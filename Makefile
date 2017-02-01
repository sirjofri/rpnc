rpnc: mycalc.h mycalc.cpp rpnc.cpp cview.cpp cview.h
	@echo "Compiling linux version ..."
	g++ -std=c++11 -o rpnc mycalc.cpp cview.cpp rpnc.cpp -lxcb -g
	@echo "Man:"
	@echo "./rpnc            starts rpnc with a gui"
	@echo "./rpnc anything   starts rpnc without a gui"
	@echo " "

.PHONY: all
all: rpnc rpnc.exe

.PHONY: both
both: rpnc rpnc.exe

.PHONY: win
win: rpnc.exe

.PHONY: windows
windows: rpnc.exe

.PHONY: win32
win32: rpnc.exe

.PHONY: linux
linux: rpnc

.PHONY: unix
unix: rpnc

rpnc.exe: mycalc.h mycalc.cpp rpnc.cpp
	@echo "Compiling windows version ..."
	i686-w64-mingw32-g++ -static-libgcc -static-libstdc++ mycalc.cpp rpnc.cpp -o rpnc.exe -std=c++11
	@echo " "
