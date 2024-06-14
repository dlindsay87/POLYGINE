#include "iomanager.h"

namespace POLYGINE {
	
	char* fileReader(cc* filePath) {
		cout << "Reading file " << filePath << "... ";
		std::ifstream file (filePath, ios::in|ios::binary|ios::ate);
		if (!file.is_open()) {
			std::cerr << "Failed to open file.\n";
			exit(1);
		}

		int size = file.tellg();
		char* content = new char[size + 1];
	    file.seekg(0, ios::beg);
	    file.read(content, size);
		content[size] = '\0';
	    file.close();
		
		cout << "File read.\n";
		return content;
		
	}
	
}

