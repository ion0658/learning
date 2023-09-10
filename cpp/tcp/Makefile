# プログラム名とオブジェクトファイル名
PROGRAM = main
CC			= gcc
CXX			= g++
CFLAGS		= -g -Wall
CXXFLAGS	= -g -Wall -std=c++17
INCLUDE		= -I./include
LDFLAGS		= 
LIB_DIR		=
LIBRARIES 	= 
BIN_DIR		= ./bin
TARGET		= $(BIN_DIR)/$(PROGRAM)
INCLUDE_DIR	= ./include
SRC_DIR		= ./src
OBJ_DIR		= ./obj
HEADERS		= $(wildcard $(INCLUDE_DIR)/*.h)
C_SOURCES	= $(wildcard $(SRC_DIR)/*.c)
C_OBJECTS	= $(subst $(SRC_DIR),$(OBJ_DIR),$(C_SOURCES:.c=.o))
CXX_SOURCES	= $(wildcard $(SRC_DIR)/*.cpp)
CXX_OBJECTS	= $(subst $(SRC_DIR),$(OBJ_DIR),$(CXX_SOURCES:.cpp=.o))

.PHONY: clean all
all: clean $(TARGET)

$(TARGET): $(C_OBJECTS) $(CXX_OBJECTS)
	@[ -d $(BIN_DIR) ] || mkdir -p $(BIN_DIR)
	$(CXX) -o $@ $^ $(LDFLAGS)


$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS)
	@[ -d $(OBJ_DIR) ] || mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDE) -o $@ -c $<

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp $(HEADERS)
	@[ -d $(OBJ_DIR) ] || mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -o $@ -c $<

clean:
	@[ -d $(OBJ_DIR) ] & rm -rf $(OBJ_DIR)
	@[ -d $(BIN_DIR) ] & rm -rf $(BIN_DIR)

run: $(TARGET)
	$(TARGET)