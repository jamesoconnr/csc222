#include <ncurses.h>
#include <menu.h>
#include <stdlib.h>
#include <iostream>
#include <cstdio>
#include <memory>
#include <stdexcept>
#include <string>
#include <array>
#include <vector>
using namespace std;


struct File{
	string name;

	File(string n);
};
struct Directory{
	vector<File> files;

	Directory(vector<string> ls);
	void to_string();
};

File::File(string n){
	name = n;
}
Directory::Directory(vector<string> ls){
	for (int i = 0; i < ls.size(); i++){
		files.push_back(File(ls[i]));
	}
}
void Directory::to_string(){
	for (int i = 0; i < files.size(); i++){
		cout << files[i] << endl;
	}
}

vector<string> lsdir() {
	char cmd[] = "ls -a1";
    array<char, 128> buffer;
    string result;
	vector<string> output;
    unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        output.push_back(buffer.data());
    }
	return output;
}
int main(){
	Directory currentDir(lsdir());
	//initscr();
	//for (int i = 0; i < lsout.size(); i++){
	//	addstr(lsout[i].c_str());
	//}
	//refresh();
	//getch();
	//endwin();
	return 0;
}
