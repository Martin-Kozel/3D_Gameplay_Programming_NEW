CXX := gcc
BUILD_DIR := ./bin
SRC_DIR := ./src
MSG_START := "Build Started"
MSG_END := "Build Complete"
MSG_CLEAN := "Cleaning up"

# Windows-specific settings
ifeq ($(OS),Windows_NT)
    os := Windows
    # Use MSYS2 path for dependencies
    SDK := ${MSYS2}
    SDK_PATH := $(subst \,/,$(subst C:\,/c/,$(SDK)))
    
    # Include paths for headers
    INCLUDES := -I${SDK_PATH}/include -I. -I./include
    
    # Library paths
    LIBS := -L${SDK_PATH}/lib
    
    # Compiler flags
    CXXFLAGS := -std=c99 -Wall -Wextra -g ${INCLUDES}
    
    # Required libraries for OpenGL/GLFW on Windows
    LIBRARIES := -lglfw3 -lopengl32 -lglu32 -lgdi32 -luser32 -lkernel32
    
    TARGET := ${BUILD_DIR}/sampleapp.exe
else
    # Unix-like systems (Linux, macOS)
    os := $(shell uname -s)
    
    # Include paths
    INCLUDES := -I. -I./include
    
    # Library paths - add common installation directories
    LIBS := -L. -L/usr/lib -L/usr/local/lib
    
    # Compiler flags
    CXXFLAGS := -std=c99 -Wall -Wextra -g ${INCLUDES}
    
    # Required libraries for OpenGL/GLFW on Unix
    LIBRARIES := -lglfw -lGL -lGLU -lm
    
    TARGET := ${BUILD_DIR}/sampleapp.bin
endif

# Source files
SRC := $(wildcard ${SRC_DIR}/*.c)

# Default target
all: build

# Build target
build:
	@echo ${MSG_START} ${os}
	@echo "*** C++ Compiler ***"
	@echo ${CXX}
	@echo "*** C++ Flags ***"
	@echo ${CXXFLAGS}
	@echo "*** LIBRARIES ***"
	@echo ${LIBRARIES}
	@echo "*** SRC ***"
	@echo ${SRC}
	@echo "*** TARGET ***"
	@echo ${TARGET}
	
	# Create build directory
	@rm -rf ${BUILD_DIR} || true
	@mkdir -p ${BUILD_DIR}
	
	# Compile and link
	${CXX} ${CXXFLAGS} -o ${TARGET} ${SRC} ${LIBS} ${LIBRARIES}
	@echo ${MSG_END}
	
	# Run the program
	./${TARGET}

# Clean target
.PHONY: clean
clean:
	@echo ${MSG_CLEAN}
	rm -rf ${BUILD_DIR} || true