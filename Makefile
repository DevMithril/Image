CC= gcc
CFLAGS= -Wall -Wextra -pedantic -std=c99
SOFLAGS= -shared -fpic

LIBSO= libtext.so
SRC_DIR= src/
BUILD_DIR= build/
BIN_DIR= $(BUILD_DIR)bin/
DEP_DIR= $(BUILD_DIR)dep/

SRC= $(wildcard $(SRC_DIR)*.c)
OBJ= $(SRC:$(SRC_DIR)%.c=$(BIN_DIR)%.o)
DEP= $(SRC:$(SRC_DIR)%.c=$(DEP_DIR)%.d)

lib: $(LIBSO)

demo: lib demo/Makefile
	@cd demo/ && make && cd ..

$(LIBSO): $(OBJ)
	$(CC) $(CFLAGS) $(SOFLAGS) -o $@ $^

$(BIN_DIR)%.o: $(SRC_DIR)%.c $(BIN_DIR)
	@$(CC) $(CFLAGS) -o $@ -c $<

$(DEP_DIR)%.d: $(SRC_DIR)%.c $(DEP_DIR)
	@$(CC) -MM -MT $(@:$(DEP_DIR)%.d=$(BIN_DIR)%.o) -MF $@ $<

%/:
	@mkdir -p $@

clean_all: clean
	@rm -f $(LIBSO)

clean:
	@rm -rf $(BUILD_DIR)

-include $(DEP)
