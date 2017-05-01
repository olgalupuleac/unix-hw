#include <fstream>
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
        char cmd[1000];
        is.getline(cmd, 1000);
        commands += ((string(cmd)) + "\n");
    }
    while(true){
        system(commands.c_str());
        this_thread::sleep_for(chrono::minutes(freq));
    }
    return 0;
}
