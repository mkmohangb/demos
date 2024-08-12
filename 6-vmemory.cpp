#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <thread>

using namespace std;

int main() {

    int size = 16 * 1024 * 1024;
    unsigned char *array = new unsigned char[size];
    cout << "address of main is " << main << endl;
    cout << "address of array is " << (int *)array << endl;
    cout << "address on stack holding array pointer is " << (int *)&array << endl;

    for (int i = 0; i < size; i++) {
        array[i] = (unsigned char)i;
    }

    cout << "main thread id is " << this_thread::get_id()<<", "<<::getpid() << endl;

    cout<<"press enter"<<endl;
    cin.ignore();

    delete array;

    ifstream input_stream("1-race.c");
    vector<string> text;
    string line;
    while (getline(input_stream, line)) {
        text.push_back(line);
    }

    cout<<"first line is "<<text.front() << endl;
    cout<<"second line is "<<text[1] << endl;

    cout<<"press enter"<<endl;
    cin.ignore();
}
