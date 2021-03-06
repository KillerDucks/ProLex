# Compiler Variables
Compiler = /usr/bin/g++
Flags = -Wall -g -std=c++14 -O0

# Program Variables
ProgName = ProLex

# Lib Directory Variables
# WebXLib := ./src/WebXLib

# Source Directory Variables
Source := ./src
Objects := build/obj
# Build Directory Variables
Build_Debug := ./build/debug
# Program Executable Variables
runProgram := $(Build_Debug)/$(ProgName)

# File Variables
Source_Files :=  $(shell find src/ -type f -name '*.cpp')
Object_Files := $(patsubst $(SRC_DIR)/%.cpp,$(Objects)/%.o,$(Source_Files))

# Debug
# debug: $(Build_Debug)/$(ProgName)

# WebXLib
all: $(Object_Files)
	$(Compiler) $(Flags) -o $(Build_Debug)/$(ProgName) $^ -lstdc++fs



# Make the object files
$(Objects)/WebX_Sockets_Obj.o: $(WebXLib)/Sockets.cpp
	$(Compiler) $(Flags) -c $^ -o $(Objects)/WebX_Sockets_Obj.o

$(Objects)/WebX_Directory_Obj.o: $(WebXLib)/Directory.cpp
	$(Compiler) $(Flags) -c $^ -o $(Objects)/WebX_Directory_Obj.o


clean: 
	@echo "Cleaning Build System..."
	@rm -rf ./build/obj/*
	@rm -rf ./build/debug/*
	@rm -rf ./build/release/*
	@echo "!!! Done Cleaning the Build System !!!"

exec:
	$(runProgram)