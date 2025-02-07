CFLAGS = -Wall -Wextra -Werror
CPPFLAGS = -MMD -Iinclude
INC_DIR = include
LIB_NAME = geometry
APP_NAME = app
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

APP_SRC = $(SRC_DIR)/app/main.c
APP_OBJ = $(patsubst $(SRC_DIR)/app/%.c,$(OBJ_DIR)/src/app/%.o, $(APP_SRC))

LIB_SRC = $(wildcard $(SRC_DIR)/geometry/*.c)
LIB_OBJ = $(patsubst $(SRC_DIR)/geometry/%.c,$(OBJ_DIR)/src/geometry/%.o, $(LIB_SRC))

WKT_PARSER_SRC = $(SRC_DIR)/wkt_parser.c
WKT_PARSER_OBJ = $(OBJ_DIR)/wkt_parser.o

TEST_SRC = test.c
TEST_OBJ = $(OBJ_DIR)/test.o
TEST_EXEC = test

DEP_FILES = $(LIB_OBJ:.o=.d) $(APP_OBJ:.o=.d) $(WKT_PARSER_OBJ:.o=.d)

# Создание необходимых каталогов
$(OBJ_DIR)/src/app:
	@mkdir -p $@

$(OBJ_DIR)/src/geometry:
	@mkdir -p $@

$(OBJ_DIR):
	@mkdir -p $@

$(BIN_DIR):
	@mkdir -p $@

all: $(BIN_DIR)/$(APP_NAME)

$(BIN_DIR)/$(APP_NAME): $(APP_OBJ) $(WKT_PARSER_OBJ) $(LIB_NAME).a
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $(APP_OBJ) $(WKT_PARSER_OBJ) $(LIB_NAME).a -lm

$(OBJ_DIR)/src/app/%.o: $(SRC_DIR)/app/%.c
	@mkdir -p $(@D)
	$(CC) -c $(CFLAGS) $(CPPFLAGS) -o $@ $<

$(OBJ_DIR)/src/geometry/%.o: $(SRC_DIR)/geometry/%.c
	@mkdir -p $(@D)
	$(CC) -c $(CFLAGS) $(CPPFLAGS) -o $@ $<

$(OBJ_DIR)/wkt_parser.o: $(SRC_DIR)/wkt_parser.c
	@mkdir -p $(@D)
	$(CC) -c $(CFLAGS) $(CPPFLAGS) -o $@ $<

$(TEST_OBJ): $(TEST_SRC)
	$(CC) -c $(CFLAGS) $(CPPFLAGS) -I$(INC_DIR) -o $@ $<

$(LIB_NAME).a: $(LIB_OBJ)
	ar rcs $@ $^

test: $(TEST_OBJ) $(LIB_NAME).a
	$(CC) $(CFLAGS) -o $(TEST_EXEC) $(TEST_OBJ) $(LIB_NAME).a -lm

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR) $(LIB_NAME).a *.d

run: $(BIN_DIR)/$(APP_NAME)
	$(BIN_DIR)/$(APP_NAME)

-include $(DEP_FILES)