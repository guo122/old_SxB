cmake -E make_directory "build" && cmake -E chdir "build" cmake -G "Xcode" ../ -DCMAKE_TOOLCHAIN_FILE=../cmake/toolchain/iOS.toolchain.cmake -DIOS_PLATFORM=SIMULATOR
