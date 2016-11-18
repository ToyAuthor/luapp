
CC=g++
CFLAGS = -O2 -w -DLUAPP_SCRIPT_PATH='"../../../script/"'
LIBS = -llua

LIB_PATH = -L/usr/lib -L../../build/lib
INC_PATH = -I/usr/include -I../../ -I../../lua

BIN_NAME=../../build/examples/CallFunctionFromLua/CallFunctionFromLua
SOURCE = CallFunctionFromLua.cpp

all:
	@if [ ! -d "../../build/examples/CallFunctionFromLua" ] ; then \
		mkdir ../../build/examples/CallFunctionFromLua; \
	fi

	@echo "Building CallFunctionFromLua bin..."
	@$(CC) $(CFLAGS) $(INC_PATH) $(SOURCE) -o $(BIN_NAME) $(LIB_PATH) $(LIBS)

clean:
	rm -f *.o
	rm -f $(BIN_NAME)
