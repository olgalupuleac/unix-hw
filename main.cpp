#include <iostream>
#include <fstream>
#include <unordered_map>

using namespace std;

int main() {
	ifstream ifs("MBR");
	char partition[16];
	ifs.seekg(446);
	int cnt = 0;
	for (int i = 0; i < 4; i++) {
		ifs.read(partition, sizeof partition);
		for(j = 0; j < 16; j++)
			if (partition[j] != 0) {
				cnt++;
				break;
			}
	}
	cout << cnt << endl;
	return 0;
}