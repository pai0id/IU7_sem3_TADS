# Компилятор
CC := gcc

# Названия папок
INC_DIR := ./inc
SRC_DIR := ./src
OUT_DIR := ./out

OBJS := $(OUT_DIR)/list_queue.o $(OUT_DIR)/arr_queue.o $(OUT_DIR)/arr_stat_queue.o $(OUT_DIR)/simulation.o $(OUT_DIR)/research.o

HEADERS := $(INC_DIR)/list_queue.h $(INC_DIR)/arr_queue.h $(INC_DIR)/arr_stat_queue.h $(INC_DIR)/simulation.h $(INC_DIR)/err.h $(INC_DIR)/research.h

CFLAGS := -I$(INC_DIR) -Wall -Wpedantic

debug : CFLAGS += -g3
debug : app.exe

release : app.exe

app.exe : $(OBJS) $(OUT_DIR)/main.o
	$(CC) $^ -o $@ -lm

$(OUT_DIR)/%.o : $(SRC_DIR)/%.c $(HEADERS)
	mkdir -p $(OUT_DIR)
	$(CC) -o ./$@ $(CFLAGS) -c $<

clean :
	rm -f -r $(OUT_DIR)
	rm -f ./*.exe ./*tmp*

.PHONY : clean debug release
