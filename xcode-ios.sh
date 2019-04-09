cmake -E make_directory "build-ios" && cmake -E chdir "build-ios" cmake -G "Xcode" ../ -DCMAKE_TOOLCHAIN_FILE=../cmake/toolchain/ios.toolchain.cmake -DPLATFORM=OS64COMBINED
