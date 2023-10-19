.PHONY: build

build:
	rm -rf build
	mkdir build

	cmake -S . -B build -GXcode \
		-DCMAKE_BUILD_TYPE=Debug \
		-DCMAKE_TOOLCHAIN_FILE=../ios.toolchain.cmake \
		-DPLATFORM=OS64 \
		-DIPHONEOS_DEPLOYMENT_TARGET=14.0

	cmake --build build --config Debug
