CPPFLAGS = -std=c++20 -pedantic -Wall -Wextra -Wformat-security -Wduplicated-cond -Wfloat-equal -Wshadow -Wconversion -Wlogical-not-parentheses -Wnull-dereference -Wvla -g3 -O2

all: tri.e

trilib-debug.o: trilib.cpp trilib.h communication.h
	g++ $(CPPFLAGS) -D__NOPASSWORD -D__DEBUG_COMMUNICATION trilib.cpp -c -o trilib-debug.o

trilib-nodebug.o: trilib.cpp trilib.h communication.h
	g++ $(CPPFLAGS) -D__NOPASSWORD trilib.cpp -c -o trilib-nodebug.o

tri.e: tri.cpp trilib-debug.o trilib-nodebug.o
	if [ "$(DEBUG)" = "1" ]; then\
	    g++ $(CPPFLAGS) trilib-debug.o tri.cpp -o tri.e;\
	else\
	    g++ $(CPPFLAGS) trilib-nodebug.o tri.cpp -o tri.e;\
    fi

clean:
	rm -f *.e *.o
