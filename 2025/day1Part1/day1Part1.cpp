#include <cassert>
#include <fstream>
#include <iostream>
using namespace std;

class Lock {
  int dial;
  int hitZeroCount = 0;

public:
  Lock() { dial = 50; }

public:
  int getHitZeroCount() { return hitZeroCount; }

  void turnDial(string rotation) {
    // make number out of rotation[1...end]
    int count = stoi(rotation.substr(1));
    if (rotation[0] == 'L')
      rotateLeft(count);
    else
      rotateRight(count);
  }
  void rotateLeft(int count) {
    dial -= count;
    if (dial < 0)
      dial += 100;
    checkIfZeroHit();
  }

  void rotateRight(int count) {
    dial += count;
    if (dial > 99)
      dial -= 100;
    checkIfZeroHit();
  }

  void checkIfZeroHit() {
    if (dial == 0)
      hitZeroCount++;
    cout << dial << endl;
  }
};

ifstream openFile(string_view ffilename);

void printFileContents(ifstream &ffile);

int main() {
  string filename = "input_example.txt";
  ifstream file = openFile(filename);
  assert(file.is_open());
  // North Pole base lock
  Lock npbLock;
  string line;
  while (getline(file, line)) {
    npbLock.turnDial(line);
  }
  int result = npbLock.getHitZeroCount();
  cout << "Final result: " << result << endl;

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
