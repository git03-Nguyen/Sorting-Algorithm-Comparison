/*
	@file Main.cpp
*/

#include"Header.h"

// Main function
int main(int argc, char* argv[]) {
	srand((int)time(NULL));
	try {
		menuTest();
	}
	catch (const exception& e) {
		cout << "Error: " << e.what() << endl;
	}
	catch (const char* msg) {
		cout << "Error: " << msg << endl;
	}
	system("PAUSE");
	return 0;
}

// --------------------------------------------
// End of @file Main.cpp

