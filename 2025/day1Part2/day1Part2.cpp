// just redesign the entire thing: 
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
    cout << rotation << " ";
    if (rotation[0] == 'L')
      rotateLeft(count);
    else
      rotateRight(count);
    cout << dial << endl;
  }
  void rotateLeft(int count) {
    countZeroHitsLeft(count);
    dial -= count;
    keepWithin99();
  }

  void rotateRight(int count) {
    countZeroHitsRight(count);
    dial += count;
    keepWithin99();
  }

  void countZeroHitsLeft(int fcount) {
    for (int i = 0; i < fcount / 100; i++) {
      incrementHitZeroCount('h');
    }
    if (dial != 0 && dial <= fcount % 100)
      incrementHitZeroCount();
  }

  void countZeroHitsRight(int fcount) {
    for (int i = 0; i < fcount / 100; i++) {
      incrementHitZeroCount('h');
    }
    if (100 <= dial + (fcount % 100))
      incrementHitZeroCount();
  }



  void keepWithin99() {
    while(dial > 99) {
      dial -= 100;
    }
    while(dial < 0) {
      dial += 100;
    }
  }

  void incrementHitZeroCount(char fsign = '+')
  {
    hitZeroCount++;
    cout << fsign;
  }
};

ifstream openFile(string_view ffilename);

void printFileContents(ifstream &ffile);

int main() {
  string filename = "input.txt";
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

// 5923
