# Makefile
# mcalx
#  12 / 07 / 2017
#  --------------
#
CFLAGS=-O$(O) -I/usr/include/freetype2 -mtune=generic -O2 -Wall -pipe --param=ssp-buffer-size=4 -fvisibility-inlines-hidden -D_LARGEFILE_SOURCE -D_LARGEFILE64_SOURCE -D_THREAD_SAFE -D_REENTRANT -std=c++11
O=2
LFLAGS=-Wl,-rpath,/usr/lib -Wl,-O1,--sort-common,--as-needed,-z,relro -lfltk -lXcursor -lXfixes -lXext -lXft -lfontconfig -lXinerama -lpthread -ldl -lm -lX11

GCC_VERSION=$(shell g++ -dumpversion | awk '{print $$1<4.9?"0":"1"}')
ifeq ($(GCC_VERSION), 1)
	CFLAGS+=-fstack-protector-strong
else
	CFLAGS+=-fstack-protector
endif

OBJS=objs/Fl_Scientific_Button.o objs/transpose.o objs/operations.o objs/logdisplay.o objs/matrix.o objs/sheet.o objs/squarematrix.o objs/upper_lower.o objs/mcalx.o objs/copy.o objs/calc.o objs/config.o



# compile all
.PHONY: a all
a: all
all: mcalx
mcalx: objs $(OBJS)
	@ echo "    LINK bin/mcalx"
	@ $(CXX) $(OBJS) -o "bin/mcalx" $(LFLAGS)

objs:
	@ mkdir "objs"

objs/config.o: src/config.cpp src/config.h
	@ echo "    CXX  src/config.cpp"
	@ $(CXX) $(CFLAGS) -c "src/config.cpp" -o $@

objs/Fl_Scientific_Button.o: src/Fl_Scientific_Button.cpp src/Fl_Scientific_Button.h
	@ echo "    CXX  src/Fl_Scientific_Button.cpp"
	@ $(CXX) $(CFLAGS) -c "src/Fl_Scientific_Button.cpp" -o $@
objs/transpose.o: src/transpose.cpp src/matrix.h
	@ echo "    CXX  src/transpose.cpp"
	@ $(CXX) $(CFLAGS) -c "src/transpose.cpp" -o $@
objs/operations.o: src/operations.cpp src/matrix.h src/operations.h \
 src/sheet.h src/logdisplay.h src/squarematrix.h src/upper_lower.h \
 src/transpose.h
	@ echo "    CXX  src/operations.cpp"
	@ $(CXX) $(CFLAGS) -c "src/operations.cpp" -o $@
objs/logdisplay.o: src/logdisplay.cpp src/logdisplay.h
	@ echo "    CXX  src/logdisplay.cpp"
	@ $(CXX) $(CFLAGS) -c "src/logdisplay.cpp" -o $@
objs/matrix.o: src/matrix.cpp src/matrix.h
	@ echo "    CXX  src/matrix.cpp"
	@ $(CXX) $(CFLAGS) -c "src/matrix.cpp" -o $@
objs/sheet.o: src/sheet.cpp src/sheet.h
	@ echo "    CXX  src/sheet.cpp"
	@ $(CXX) $(CFLAGS) -c "src/sheet.cpp" -o $@
objs/squarematrix.o: src/squarematrix.cpp src/squarematrix.h src/upper_lower.h \
 src/matrix.h
	@ echo "    CXX  src/squarematrix.cpp"
	@ $(CXX) $(CFLAGS) -c "src/squarematrix.cpp" -o $@
objs/upper_lower.o: src/upper_lower.cpp src/matrix.h
	@ echo "    CXX  src/upper_lower.cpp"
	@ $(CXX) $(CFLAGS) -c "src/upper_lower.cpp" -o $@
objs/mcalx.o: src/mcalx.cpp src/mcalx.h src/logdisplay.h src/sheet.h \
 src/copy.h src/matrix.h src/operations.h src/calcu/small.h
	@ echo "    CXX  src/mcalx.cpp"
	@ $(CXX) $(CFLAGS) -c "src/mcalx.cpp" -o $@
objs/copy.o: src/copy.cpp src/matrix.h src/copy.h src/sheet.h src/logdisplay.h
	@ echo "    CXX  src/copy.cpp"
	@ $(CXX) $(CFLAGS) -c "src/copy.cpp" -o $@
objs/calc.o: src/calcu/small.c
	@ echo "    CXX  src/calcu/small.c"
	@ $(CXX) $(CFLAGS) -c "src/calcu/small.c" -o $@


# clean all
.PHONY: c clean
c: clean
clean:
	@ if [ -d "objs" ]; then rm -rf "objs" ; fi
	@ rm -f "bin/mcalx"
	@ echo "    CLEAN"

# clean and compile
.PHONY: f fresh
f: fresh
fresh: clean
	@ make all --no-print-directory

# compile and run
.PHONY: r run
r: run
run: all
	@ ./bin/mcalx

# compile with debugging
.PHONY: d debug
d: debug
debug: CFLAGS += -DDEBUG -g3 -Wall -Wextra
debug: O=0
debug: all

# check syntax
.PHONY: s check-syntax
s: check-syntax
check-syntax:
	$(CXX) $(CFLAGS) -fsyntax-only -Wall -o /dev/null -S $(CHK_SOURCES)
