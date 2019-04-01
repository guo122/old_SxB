
#include <iostream>

int main(int argc, char *argv[])
 {
	FILE *file = fopen("../../../bgfx/examples/runtime/shaders/dx11/vs_cubes.bin", "rb");
	char * mesg = strerror(errno);
	fseek(file, 0, SEEK_END);
	long fileSize = ftell(file);
	fseek(file, 0, SEEK_SET);
	std::cout << "asdf";
	return 0;
 }