#include <stdio.h>
#include <dlfcn.h>
#include <fstream>
#include <string>

int call_library(std::string & path_to_lib)
{
	void *handle  = NULL;
	handle = dlopen(path_to_lib.c_str(), RTLD_NOW | RTLD_GLOBAL);
	if (handle == NULL)
	{
		fprintf(stderr, "Unable to open lib: %s\n", dlerror());
		return -1;
	}

	int (*func)() = NULL;
	func = (int (*)()) dlsym(handle, "f");

	if (func == NULL) {
		fprintf(stderr, "Unable to get symbol\n");
		return -1;
	}

	func();
	return 0;
}

int main(int argc, const char *argv[])
{
	std::ifstream in;
	in.open("config.txt");
	std::string path_to_lib;
	std::getline(in, path_to_lib);
	in.close();
		call_library(path_to_lib);
		return 0;
}