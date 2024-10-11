CC=gcc
CFLAGS=-Wall -Wextra -O2
TARGET=life-expectancy
BUILD_DIR=build
BSD_SOURCE=./life-expectancy.c
BSD_OUTPUT=`pwd`/build/netbsd
FILE_NAME=life-expectancy.c
BSD_PRE_FLAGS=-Os

all: linux windows web netbsd

linux: $(TARGET).c
	$(CC) $(CFLAGS) -o $(BUILD_DIR)/linux/$(TARGET) $(TARGET).c

windows: $(TARGET).c
	i686-w64-mingw32-gcc $(CFLAGS) -o $(BUILD_DIR)/windows/$(TARGET).exe $(TARGET).c

web: $(TARGET).c
	emcc $(TARGET).c -s NO_EXIT_RUNTIME=0 -o $(BUILD_DIR)/web/$(TARGET).html

netbsd:
	cp -v $(BSD_SOURCE) $(BSD_OUTPUT)
	$(CC) $(BSD_PRE_FLAGS) $(BSD_OUTPUT)/$(FILE_NAME) -o $(BSD_OUTPUT)/life-expectancy

clean:
	rm -rf $(BUILD_DIR)
