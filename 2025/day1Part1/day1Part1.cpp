#include <fstream>
#include <iostream>
using namespace std;

class Lock {};

ifstream openFile(string_view ffilename);

void printFileContents(ifstream &ffile);

int main() {
  string filename = "input_example.txt";
  ifstream file = openFile(filename);
  if (file.is_open())
    printFileContents(file);

  return 0;
}

ifstream openFile(string_view ffilename) {
  ifstream rfile(ffilename.data());
  if (!rfile.is_open()) {
    cout << "Failed to open file" << endl;
  }
  return rfile;
}

void printFileContents(ifstream &ffile) {
  string s;
  while (getline(ffile, s)) {
    cout << s << endl;
  }
}
