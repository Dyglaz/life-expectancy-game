GCC=gcc
CFLAGS=-Wall -Wextra -O2
TARGET=life-expectancy
BUILD_DIR=build
BSD_SOURCE=./life-expectancy.c
BSD_OUTPUT=`pwd`/build/netbsd
BSD_PRE_FLAGS=-Os

linux:
	@echo "Installing the necessary dependencies..."
	sudo apt-get update && sudo apt-get install -y build-essential
	@echo "End of installation of necessary dependencies..."
	@echo "Compilation..."
	$(GCC) $(CFLAGS) -o $(BUILD_DIR)/linux/$(TARGET) $(TARGET).c
	@echo "End of compilation..."

windows:
	@echo "Compilation..."
	$(GCC) $(TARGET).c -o $(BUILD_DIR)/windows/$(TARGET).exe
	@echo "End of compilation..." 

web:
	@echo "Installing the necessary dependencies..."
	sudo apt-get update
	sudo apt-get install -y git build-essential emscripten nodejs npm
	sudo npm install -g http-server
	@echo "End of installation of necessary dependencies..."
	cd .. && git clone https://github.com/emscripten-core/emsdk.git
	cd ../emsdk && ./emsdk install latest && ./emsdk activate latest && . ./emsdk_env.sh
	emcc $(TARGET).c -s NO_EXIT_RUNTIME=0 -o $(BUILD_DIR)/web/$(TARGET).html
	http-server

netbsd:
	# @echo "Installing the necessary dependencies..."
	# @pkg_add gcc git
	# @echo "End of installation of necessary dependencies..."
	@echo "Compilation..."
	$(GCC) $(BSD_PRE_FLAGS) $(BSD_SOURCE) -o $(BSD_OUTPUT)/life-expectancy
	@echo "End of compilation..." 