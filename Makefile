CC = gcc
CFLAGS = -Wall $(addprefix -I,$(INCLUDE_DIR))
LDFLAGS = $(addprefix -L,$(LIB_DIR)) -Wl,-rpath,$(LIB_DIR) \
		  -lcsfml-graphics -lcsfml-window -lcsfml-system \
		  -lsfml-graphics -lsfml-window -lsfml-system -lGLEW

# DIRECTORIES ARE HERE
SOURCE_DIR = src
OBJECT_DIR = obj
BIN_DIR = bin
INCLUDE_DIR = include 
LIB_DIR = lib

# FILE DEPENDENCIES
SOURCES = $(wildcard $(SOURCE_DIR)/*.c)
DEPS = $(wildcard $(INCLUDE_DIR)/*.h)
LIBS = $(wildcard $(LIB_DIR)/*.a)
OBJECTS = $(SOURCES:$(SOURCE_DIR)/%.c=$(OBJECT_DIR)/%.o)
TARGET= ./game

.PHONY: all
all: $(TARGET) run

.PHONY: build
build: $(TARGET)
	@echo Building.....

$(TARGET): $(OBJECTS)
	$(CC) $^ -o $@ $(LDFLAGS)  

$(OBJECT_DIR)/%.o: $(SOURCE_DIR)/%.c $(DEPS)
	$(CC) -c $< -o $@ $(CFLAGS) 

.PHONY: run
run: 
	@echo Running....
	@$(TARGET)

.PHONY: clean
clean: 
	@echo Cleaning.....
	@rm -f $(OBJECT_DIR)/*.o $(TARGET)
