# Компилятор
CC := gcc

# Названия папок
INC_DIR := ./inc
SRC_DIR := ./src
OUT_DIR := ./out

OBJS := $(OUT_DIR)/book_arr.o $(OUT_DIR)/book.o $(OUT_DIR)/controls.o $(OUT_DIR)/err.o $(OUT_DIR)/main.o $(OUT_DIR)/UI.o $(OUT_DIR)/research.o

HEADERS := $(INC_DIR)/book_arr.h $(INC_DIR)/book.h $(INC_DIR)/controls.h $(INC_DIR)/err.h $(INC_DIR)/UI.h $(INC_DIR)/research.h


# Опции компиляции
CFLAGS := -I$(INC_DIR) -Wall -Werror -Wpedantic -Wextra -Wfloat-equal -Wfloat-conversion

debug : CFLAGS += -g3
debug : app.exe

release : app.exe

app.exe : $(OBJS) $(OUT_DIR)/main.o
	$(CC) $^ -o $@ -lm -lrt

$(OUT_DIR)/%.o : $(SRC_DIR)/%.c $(inc/arr.h inc/err.h inc/filter.h inc/mysort.h)
	mkdir -p $(OUT_DIR)
	$(CC) -o ./$@ $(CFLAGS) -c $<

.PHONY : clean debug release
clean :
	rm -f -r $(OUT_DIR) .vscode
	rm -f ./*.exe ./*tmp*
