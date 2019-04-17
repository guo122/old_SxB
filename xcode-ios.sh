
cmakeImpl() {
	cmake -E make_directory "build-ios" && cmake -E chdir "build-ios" cmake -G "Xcode" ../ -DCMAKE_TOOLCHAIN_FILE=../cmake/toolchain/ios.toolchain.cmake -DPLATFORM=OS64COMBINED $1
}

if [ "$1" == "test" ] ; then
	cmakeImpl -DSXB_TEST=true
else
	cmakeImpl -DSXB_TEST=false
fi

if [ -d build-ios/SxB.xcodeproj ] ; then
	open build-ios/SxB.xcodeproj
fi
