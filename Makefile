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
	@echo "The beginning of cloning the repository..."
	cd .. && git clone https://github.com/emscripten-core/emsdk.git
	@echo "End of repository cloning..."
	@echo "Start installing the latest version..."
	cd ../emsdk && ./emsdk install latest && ./emsdk activate latest && . ./emsdk_env.sh
	@echo "End of installation of the latest version..."
	@echo "Compilation..."
	emcc $(TARGET).c -s NO_EXIT_RUNTIME=0 -o $(BUILD_DIR)/web/$(TARGET).html
	@echo "End of compilation..."
	@echo "Starting a local server..."
	http-server
	@echo "Shutting down the local server..."

netbsd:
	# @echo "Installing the necessary dependencies..."
	# @pkg_add gcc git
	# @echo "End of installation of necessary dependencies..."
	@echo "Compilation..."
	$(GCC) $(BSD_PRE_FLAGS) $(BSD_SOURCE) -o $(BSD_OUTPUT)/life-expectancy
	@echo "End of compilation..." 