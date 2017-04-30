#include <iostream>
#include <stdlib.h>
#include <cassert>
#include <sstream>
#include <string>
#include <fstream>
#include <unordered_map>

using namespace std;

int main() {
	ifstream ifs("MBR", ifstream::binary);
        ifstream is("partition_types.txt");
        unordered_map<char, string> partition_types;
        while(! is.eof()){
            string code;
            is >> code;
            char description[500];
            is.ignore(2);
            is.getline(description, 500);
            char* pEnd;
            auto i = strtol(code.substr(0, 2).c_str(), &pEnd, 16);
            partition_types[i] = string(description);
        }
	char partition[16];
	ifs.seekg(446);
	int cnt = 0;
	for (int i = 0; i < 4; i++) {
		ifs.read(partition, sizeof partition);
		for(int j = 0; j < 16; j++)
			if (partition[j] != 0) {
                                cout << partition_types[partition[4]] << endl;
				cnt++;
				break;
			}
	}
	cout << cnt << endl;
	return 0;
}
