#include <iostream>
#include <string>
using namespace std;

int array[9] = {0,2,4,6,8,10,14,16,18};

int& f(int n){
  return array[n];
}

int main(int argc, char *argv[]){
  f(9) = 100;

  for(int i = 0 ; i < 10 ; i++){
    cout << array[i] << ' ';
  }

  return 0;
}



/*
int main(int argc, char *argv[]){
  string s("I Love");
  string a;
  a = s;
  a.append(" C++");

  cout << a << endl;

  a.erase(6,10);
  a.append(" You");

  cout << a << endl;

  int len = a.length();

  for(int i = 0 ; i < 3 ;  i++){
    string first = a.substr(0,1);
    string sub = a.substr(1, len - 1);
    a = sub + " " + first;
    cout << a << endl;
  }

  return 0;
}
*/
