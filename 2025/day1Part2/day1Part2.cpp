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
  }
  void rotateLeft(int count) {
    // hit zero count may be artificially inflated for 1, so pre-adjusting 
    if (dial == 0 && count > 0 && count < 100) {
      cout << "pre-adjusting " << count << endl;
      hitZeroCount--;
    }
    dial -= count;
    keepWithin99();
    checkIfZeroHit();
  }

  void rotateRight(int count) {
    dial += count;
    keepWithin99();
    checkIfZeroHit();
  }

  void checkIfZeroHit() {
    if (dial == 0)
      incrementHitZeroCount();
    cout << dial << endl;
  }

  void keepWithin99() {
    while(dial > 99) {
      dial -= 100;
      if (dial != 0) incrementHitZeroCount();
    }
    while(dial < 0) {
      dial += 100;
      if (dial != 0)
        incrementHitZeroCount();
    }
  }

  void incrementHitZeroCount() {
    hitZeroCount++;
    cout << "+";
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

// 6380 too high
// 5834 too low
// 6273 too high
// 5941 incorrect