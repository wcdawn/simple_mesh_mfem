# Makefile

INCLUDE_DIR=../include

CXX = g++

CXXFLAGS = -Wall -Wextra -std=c++23 -pedantic-errors
ifeq ($(METHOD), dbg)
CXXFLAGS += -O0 -g -DDEBUG
else
CXXFLAGS += -O3
endif

SRC = mesh.cpp \
	  calc_mesh.cpp \
	  input_proc.cpp \
	  write_mesh.cpp

HEADERS = $(INCLUDE_DIR)/calc_mesh.hpp \
		  $(INCLUDE_DIR)/geometry.hpp \
		  $(INCLUDE_DIR)/input_proc.hpp \
		  $(INCLUDE_DIR)/write_mesh.hpp

OBJ = $(SRC:.cpp=.o)

EXEC = mesh.x

.SUFFIXES : .cpp .hpp .o

.PHONY : default all clean

default : $(EXEC)

$(EXEC) : $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(EXEC) $(OBJ)

%.o : %.cpp
	$(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) -c $<

format : $(SRC) $(HEADERS)
	clang-format -i --verbose $?

tidy : $(SRC) $(HEADERS)
	clang-tidy --fix $? -- -I$(INCLUDE_DIR)
	$(MAKE) format

clean :
	$(RM) $(OBJ) $(EXEC)

mesh.o       : $(INCLUDE_DIR)/geometry.hpp
calc_mesh.o  : $(INCLUDE_DIR)/geometry.hpp $(INCLUDE_DIR)/calc_mesh.hpp
write_mesh.o : $(INCLUDE_DIR)/geometry.hpp $(INCLUDE_DIR)/write_mesh.hpp
input_proc.o : $(INCLUDE_DIR)/geometry.hpp $(INCLUDE_DIR)/input_proc.hpp
