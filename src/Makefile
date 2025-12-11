# 使用 SDK 里的 ARM 交叉编译器
CC := /home/leon/Desktop/t113-linux/brandy/brandy-2.0/tools/toolchain/gcc-linaro-7.2.1-2017.11-x86_64_arm-linux-gnueabi/bin/arm-linux-gnueabi-gcc

# CFLAGS 加入 SDK 提供的架构选项（适用于 ARMv7-A）
CFLAGS := -Wall -I. -I./lvgl -I./lvgl/src -I./lv_drivers -I./generated -I./custom -march=armv7-a

# LVGL 核心模块
LVGL_CORE   := $(wildcard ./lvgl/src/core/*.c)
LVGL_DRAW   := $(wildcard ./lvgl/src/draw/*.c) \
               $(wildcard ./lvgl/src/draw/*/*.c)
LVGL_FONT   := $(wildcard ./lvgl/src/font/*.c)
LVGL_MISC   := $(wildcard ./lvgl/src/misc/*.c)
LVGL_HAL    := $(wildcard ./lvgl/src/hal/*.c)
LVGL_WIDGET := $(wildcard ./lvgl/src/widgets/*.c)

LVGL_EXTRA  := $(filter-out ./lvgl/src/extra/layouts/*/*.c, \
                $(wildcard ./lvgl/src/extra/*/*.c)) \
               $(wildcard ./lvgl/src/extra/*/*/*.c) \
               ./lvgl/src/extra/lv_extra.c

LVGL_THEME  := $(wildcard ./lvgl/src/themes/*/*.c)

LVGL_FONTS := $(wildcard ./generated/guider_fonts/*.c) \
              $(wildcard ./generated/guider_fonts/*/*.c)

LVGL_SRC := $(LVGL_CORE) $(LVGL_DRAW) $(LVGL_FONT) $(LVGL_MISC) \
            $(LVGL_HAL) $(LVGL_WIDGET) $(LVGL_EXTRA) $(LVGL_THEME) $(LVGL_FONTS)

# lv_drivers
DRIVER_SRC := $(wildcard ./lv_drivers/*.c) \
              $(wildcard ./lv_drivers/*/*.c)

# GUI Guider 和 custom 源文件
GUI_SRC := $(wildcard ./generated/*.c)
CUSTOM_SRC := $(wildcard ./custom/*.c)
IMG_SRC := $(wildcard ./generated/images/*.c)

# 所有源文件
SRC := main.c $(LVGL_SRC) $(DRIVER_SRC) $(GUI_SRC) $(CUSTOM_SRC) $(IMG_SRC)

OBJ := $(SRC:.c=.o)

TARGET := ../bin/lv_ui

all: prepare $(TARGET)

prepare:
	@mkdir -p ../bin

# 链接生成可执行文件
$(TARGET): $(OBJ)
	@echo "Using cross compiler: $(CC)"
	$(CC) $(OBJ) -o $@ $(LDFLAGS)

# 编译每个 .c 文件为 .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)

.PHONY: all clean prepare
