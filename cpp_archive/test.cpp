#include <iostream>
#include <string>

using namespace std;

int main(int argc, const char *argv[])
{
	cout << "aa" << endl;
	
	char address[100];
	cin.getline(address, 100, '\n');

	cout << "주소는 " << address << " 입니다";


	return 0;
}
