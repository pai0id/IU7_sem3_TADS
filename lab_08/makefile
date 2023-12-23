# Компилятор
CC := gcc

# Названия папок
INC_DIR := ./inc
SRC_DIR := ./src
OUT_DIR := ./out

OBJS := $(OUT_DIR)/UI.o $(OUT_DIR)/graph_list.o $(OUT_DIR)/graph_mtr.o $(OUT_DIR)/research.o

HEADERS := $(INC_DIR)/UI.h $(INC_DIR)/graph_list.h $(INC_DIR)/graph_mtr.h $(INC_DIR)/research.h

CFLAGS := -g -I$(INC_DIR) -Wall -Wpedantic

debug : CFLAGS += -g3
debug : app.exe

release : app.exe

app.exe : $(OBJS) $(OUT_DIR)/main.o
	$(CC) $(CFLAGS) $^ -o $@ -lm

$(OUT_DIR)/%.o : $(SRC_DIR)/%.c $(HEADERS)
	mkdir -p $(OUT_DIR)
	$(CC) -o ./$@ $(CFLAGS) -c $<

.PHONY : clean debug
clean :
	rm -f -r $(OUT_DIR)
	rm -f ./*.exe ./*tmp* ./*.gv ./*.png
