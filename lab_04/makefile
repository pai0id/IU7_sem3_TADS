# Компилятор
CC := gcc

# Названия папок
INC_DIR := ./inc
SRC_DIR := ./src
OUT_DIR := ./out
# FUNC_DIR := ./func_tests
# UNIT_DIR := ./unit_tests

OBJS := $(OUT_DIR)/arr_stack.o $(OUT_DIR)/list_stack.o $(OUT_DIR)/test_stack.o $(OUT_DIR)/stack_op.o

# UNIT_SRCS := $(UNIT_DIR)/check_alloc.c $(UNIT_DIR)/check_io.c $(UNIT_DIR)/check_op.c 
HEADERS := $(INC_DIR)/arr_stack.h $(INC_DIR)/err.h $(INC_DIR)/list_stack.h $(INC_DIR)/test_stack.h $(INC_DIR)/stack_op.h

# Опции компиляции
CFLAGS := -I$(INC_DIR) -Wall -Wpedantic
# UNIT_LDFLAGS := -lcheck -lm -lpthread -lrt -I$(INC_DIR)

debug : CFLAGS += -g3
debug : app.exe

release : app.exe

app.exe : $(OBJS) $(OUT_DIR)/main.o
	$(CC) $^ -o $@ -lm

# unit_tests.exe : $(OBJS) $(OUT_DIR)/check_main.o $(OUT_DIR)/check_func.o $(UNIT_SRCS)
# 	$(CC) $(OBJS) $(OUT_DIR)/check_main.o $(OUT_DIR)/check_func.o -o $@ -lm $(UNIT_LDFLAGS)

# unit : unit_tests.exe
# 	./$<

# unit_valgrind : unit_tests.exe
# 	valgrind --leak-check=yes -q ./$< 

# func : app.exe
# 	./func_tests/scripts/func_tests.sh

# valgrind : app.exe
# 	./func_tests/scripts/func_tests.sh --valgrind

# debug_gcov : CC += --coverage
# debug_gcov : debug
# 	mv $(wildcard ./*.gcno) $(OUT_DIR) 2> /dev/null || true

# debug_asan : CFLAGS += -fno-omit-frame-pointer
# debug_asan : CC := clang
# debug_asan : CC += -fsanitize=address
# debug_asan : debug

# debug_msan : CFLAGS += -fPIE  -fno-omit-frame-pointer
# debug_msan : CC := clang
# debug_msan : CC += -fsanitize=memory
# debug_msan : debug

# debug_ubsan : CFLAGS += -fno-omit-frame-pointer
# debug_ubsan : CC := clang
# debug_ubsan : CC += -fsanitize=undefined
# debug_ubsan : debug

# all :
# 	./func_tests/scripts/main_test.sh

# $(OUT_DIR)/check_main.o : $(UNIT_DIR)/check_main.c $(HEADERS)
# 	mkdir -p $(OUT_DIR)
# 	$(CC) -o ./$@ $(CFLAGS) -c $<

# $(OUT_DIR)/check_func.o : $(UNIT_DIR)/check_func.c $(HEADERS)
# 	mkdir -p $(OUT_DIR)
# 	$(CC) -o ./$@ $(CFLAGS) -c $<

$(OUT_DIR)/%.o : $(SRC_DIR)/%.c $(HEADERS)
	mkdir -p $(OUT_DIR)
	$(CC) -o ./$@ $(CFLAGS) -c $<

.PHONY : clean debug
clean :
	rm -f -r $(OUT_DIR)
	rm -f ./*.exe ./*tmp*
