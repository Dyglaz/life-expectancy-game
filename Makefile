GCC=gcc
CFLAGS=-Wall -Wextra -O2
TARGET=life-expectancy
BUILD_DIR=build
BSD_SOURCE=./life-expectancy.c
BSD_OUTPUT=`pwd`/build/netbsd
BSD_PRE_FLAGS=-Os

linux:
	@echo "Установка необходимых зависимостей..."
	sudo apt-get update && sudo apt-get install -y build-essential
	@echo "Конец установки необходимых зависимостей..."
	@echo "Компиляция..."
	$(GCC) $(CFLAGS) -o $(BUILD_DIR)/linux/$(TARGET) $(TARGET).c

windows:
	$(GCC) $(TARGET).c -o $(BUILD_DIR)/windows/$(TARGET).exe 

web:
	@echo "Установка необходимых зависимостей..."
	sudo apt-get update
	sudo apt-get install -y git build-essential emscripten nodejs npm
	sudo npm install -g http-server
	@echo "Конец установки необходимых зависимостей..."
	cd .. && git clone https://github.com/emscripten-core/emsdk.git
	cd ../emsdk && ./emsdk install latest && ./emsdk activate latest && . ./emsdk_env.sh
	emcc $(TARGET).c -s NO_EXIT_RUNTIME=0 -o $(BUILD_DIR)/web/$(TARGET).html
	http-server

netbsd:
	@echo "Установка необходимых зависимостей..."
	@pkg_add gcc git
	@echo "Конец установки необходимых зависимостей..."
	$(GCC) $(BSD_PRE_FLAGS) $(BSD_SOURCE) -o $(BSD_OUTPUT)/life-expectancy