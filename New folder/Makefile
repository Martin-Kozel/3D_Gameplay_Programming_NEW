CXX				:= g++

BUILD_DIR		:= ./bin
SRC_DIR			:= ./src

MSG_START		:= "Build Started"
MSG_END			:= "Build Complete"
MSG_CLEAN		:= "Cleaning up"


ifeq ($(OS),Windows_NT)
    os  := Windows
	# Make sure your Env Variable is set to SFML
	# Tested with SFML 2.5.1 GCC 7.3.0 MinGW (SEH) - 64-bit
	# Convert Windows directory path to UNIX Path
	SDK			:=${MYSYS2}
	SDK_PATH	:=$(subst \,/,$(subst C:\,/c/,$(SDK)))
	INCLUDES	:= -I${SDK_PATH}/include -I.
	LIBS		:= -L${SDK_PATH}/lib
	CXXFLAGS 	:= -std=c++11 -Wall -Wextra -g ${INCLUDES}
	LIBRARIES	:= -l libsfml-graphics -l libsfml-window -l libsfml-system -l libglew32 -l opengl32 
	TARGET		:= ${BUILD_DIR}/sampleapp.exe
else
    os := $(shell uname -s)
	INCLUDES	:= -I.
	LIBS		:= -L.
	CXXFLAGS 	:= -std=c++11 -Wall -Wextra -g ${INCLUDES}
	LIBRARIES	:= -l sfml-graphics -l sfml-window -l sfml-system -l GL -l GLEW
	TARGET		:= ${BUILD_DIR}/sampleapp.bin
endif

SRC				:=	$(wildcard ${SRC_DIR}/*.c ${SRC_DIR}/*.cpp) # List the CPP src files

all				:= build

build:
	@echo 	${MSG_START} ${os}

	@echo 		"***	C++ Compiler	***"
	@echo 		${CXX}
	@echo 		"*** C++ Flags		***"
	@echo 		${CXXFLAGS}
	@echo 		"*** LIBRARIES		***"
	@echo 		${LIBRARIES}
	@echo 		"*** SRC		***"
	@echo 		${SRC}
	@echo 		"*** TARGET		***"
	@echo 		${TARGET}

	@#remove directory if it exits and then create directory
	@rm -rf 		${BUILD_DIR} 	|| 	true

	@#create bin directory
	@mkdir 		${BUILD_DIR}

	${CXX} ${CXXFLAGS} -o ${TARGET} ${SRC} ${LIBS} ${LIBRARIES}
	
	@echo ${MSG_END}
	
	@# Run TARGET
	./${TARGET}

.PHONY: clean

clean:
	@echo 		${MSG_CLEAN}
	rm -rf 		${BUILD_DIR} || true