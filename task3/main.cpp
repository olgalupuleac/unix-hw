#include <fstream>
#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>
#include <chrono>
#include <thread>

using namespace std;

int main(){
    fstream is("/etc/mycron.cfg");
    int freq;
    is >> freq;
    string commands;
    while(! is.eof()){
	    char c = is.get();
        if(! is.eof())
            commands += c;
    }
    cout << commands << endl;
    while(true){
        system(commands.c_str());
        this_thread::sleep_for(chrono::minutes(freq));
    }
    return 0;
}
