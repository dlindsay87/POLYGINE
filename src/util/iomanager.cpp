#include "iomanager.h"

namespace UTIL
{

char *fileReader(const char *filePath, bool verbose)
{
	if (verbose)
		cout << "Reading file " << filePath << "...\n";
	std::ifstream file(filePath, ios::in | ios::binary | ios::ate);
	if (!file.is_open()) {
		std::cerr << "Failed to open file " << filePath << endl;
		exit(1);
	}

	int size = file.tellg();
	char *content = new char[size + 1];
	file.seekg(0, ios::beg);
	file.read(content, size);
	content[size] = '\0';
	file.close();

	if (verbose)
		cout << "File read.\n";
	return content;
}

void fileSaver(const char *filePath, char *content, bool verbose)
{
	if (verbose)
		std::cout << "Writing file " << filePath << "...\n";

	std::ofstream file(filePath, ios::out | ios::binary);
	if (!file.is_open()) {
		std::cerr << "Failed to open file " << filePath << endl;
		exit(1);
	}

	file.write(content, std::strlen(content));
	file.close();

	if (verbose)
		std::cout << "File written.\n";
}

} // namespace UTIL
