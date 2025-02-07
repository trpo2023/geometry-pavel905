CFLAGS = -Wall -Wextra -Werror
CPPFLAGS = -MMD
INC_DIR = include
LIB_NAME = geometry
APP_NAME = app
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin
LIB_SRC = $(wildcard $(SRC_DIR)/geometry/*.c)
LIB_OBJ = $(patsubst $(SRC_DIR)/geometry/%.c,$(OBJ_DIR)/src/geometry/%.o, $(LIB_SRC))
APP_SRC = $(SRC_DIR)/app/main.c
APP_OBJ = $(patsubst $(SRC_DIR)/app/%.c,$(OBJ_DIR)/src/app/%.o, $(APP_SRC))
DEP_FILES = $(LIB_OBJ:.o=.d) $(APP_OBJ:.o=.d)

all: $(BIN_DIR)/$(APP_NAME)

$(BIN_DIR)/$(APP_NAME): $(APP_OBJ) lib$(LIB_NAME).a
    @mkdir -p $(BIN_DIR)
    $(CC) $(CFLAGS) -o $@ $^ -L. -l$(LIB_NAME)

$(OBJ_DIR)/src/app/%.o: $(SRC_DIR)/app/%.c
    @mkdir -p $(@D)
    $(CC) -c $(CFLAGS) $(CPPFLAGS) -I$(INC_DIR) -o $@ $<

$(OBJ_DIR)/src/geometry/%.o: $(SRC_DIR)/geometry/%.c
    @mkdir -p $(@D)
    $(CC) -c $(CFLAGS) $(CPPFLAGS) -I$(INC_DIR) -o $@ $<

lib$(LIB_NAME).a: $(LIB_OBJ)
    ar rcs $@ $^

clean:
    rm -rf $(OBJ_DIR) $(BIN_DIR) *.a *.d

-include $(DEP_FILES)