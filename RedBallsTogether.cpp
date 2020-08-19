/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <iostream>
#include <climits>
//https://leetcode.com/discuss/interview-question/414660/
//https://leetcode.com/discuss/interview-question/125154/
using namespace std;

int minSwapsForRedBalls(const string& places) {
  int k = 0, j = places.size() - 1;
  int nBallsLeft = 1, nBallsRight = 1;
  int total = 0;
  
  while (places[k] != 'R') {
    k++;
  }
  while (places[j] != 'R') {
    j--;
  }
  int nextK=k+1, nextJ=j-1, diffK, diffJ, valueRight, valueLeft;
  bool addRightAtLast = false, addLeftAtLast = false;
  while (nextK < nextJ) {
    addRightAtLast = false, addLeftAtLast = false;
    while (places[nextK] != 'R') {
      nextK++;
    }
    while (places[nextJ] != 'R') {
      nextJ--;
    }
    diffK = nextK - k;
    diffJ = j - nextJ;
    valueLeft = nBallsLeft*(diffK-1);
    valueRight =  nBallsRight*(diffJ-1);
    if (valueRight < valueLeft) {
      total = total + nBallsRight*(diffJ-1);
      j = nextJ;
      nextJ = j - 1;
      nBallsRight++;
      addLeftAtLast = true;
    } else {
      total = total + nBallsLeft*(diffK-1);
      k = nextK;
      nextK = k + 1;
      nBallsLeft++;
      addRightAtLast = true;
    }
  }
  if (addRightAtLast) {
    total += valueRight;
  } else if(addLeftAtLast) {
    total += valueLeft;
  }
  return total;
}

int minSwapsForKBalls(const string& places, int k) {
  int counter = 0;
  int rCount = 0, start = 0, end = 0;
  while (counter < places.size()) {
    if (places[counter] == 'R') {
      if (rCount == 0) {
        start = counter;
      } else if (rCount == k-1) {
        end = counter;
        break;
      }
      rCount++;
    }
    counter++;
  }
  
  int minCount = INT_MAX;
  while (end < places.size()) {
    int val = minSwapsForRedBalls(places.substr(start, end - start + 1));
    if (minCount > val) {
      minCount = val;
    }
    int c = start+1;
    while(c < places.size() && places[c] != 'R') {
      c++;
    }
    start = c;
    c = end+1;
    while(c < places.size() && places[c] != 'R') {
      c++;
    }
    end = c;
  }
  return minCount;
}

int main()
{
    //cout << minSwapsForRedBalls("BBRBBRBRBBBRBR") << endl;
    //cout << minSwapsForRedBalls("WWRWWWRWR") << endl;
    //cout << minSwapsForRedBalls("WRRWWR") << endl;
    cout << minSwapsForKBalls("BRRBRBRBBRRR", 4) << endl;
    cout << minSwapsForKBalls("BRRBBR", 3) << endl;
    return 0;
}
