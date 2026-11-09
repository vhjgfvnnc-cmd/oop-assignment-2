#include "VoleMachine.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>  
using namespace std;
 


namespace vole {

VoleMachine::VoleMachine() : cpu(&memory, &registers) {
}

void VoleMachine::setMemory(int address, int value) {
    memory.write(address , value );
}

void VoleMachine::setRegister(int registersnum, int value) {
    registers.set(registersnum , value );
}

void VoleMachine::step() {
    cpu.step();
}

bool VoleMachine::loadProgram(const string& filename, int startAddress) {
    if (startAddress % 2 != 0) return false;      

    ifstream file(filename);
    if (!file.is_open()) return false;

    vector<unsigned char> bytes;
    string line;

    while (getline(file, line)) {
        if (line.empty()) continue;      
        if (line[0]==';') continue;
        if (line.size() < 4) return false ;
        for (int i = 0; i < 4; i++) {
    char c = line[i];
    bool isHex = (c >= '0' && c <= '9') || (c >= 'A' && c <= 'F') || (c >= 'a' && c <= 'f');
    if (!isHex) return false;
}

        int first  = stoi(line.substr(0, 2), nullptr, 16);   
        int second = stoi(line.substr(2, 2), nullptr, 16);   
        bytes.push_back(first);
        bytes.push_back(second);
    }

    if (!memory.loadBytes(startAddress, bytes)) return false;

    cpu.setPC(startAddress);
    return true;
}


void VoleMachine::run() {
    while (!cpu.isHalted()) {
        step();
    }
    display();
}

void VoleMachine::display() {
    cout << "PC: " << cpu.getPC() << endl;      
    cout << "IR: " << cpu.getIR() << endl;       

        cout << "Registers:" << endl;
         for (int i = 0; i < 16; i++) {
        cout << "R" << hex << uppercase << i << ": "
 << setw(2) << setfill('0') << (int)registers.get(i) << endl;
    }
    

        cout << "Memory:" << endl;
    for (int r = 0; r < 16; r++) {
        for (int c = 0; c < 16; c++) {
            cout << setw(2) << setfill('0') << (int)memory.read(r * 16 + c) << " ";
        }
        cout << endl;
    }
    cout << dec;
}

bool VoleMachine::isHalted() {
    return cpu.isHalted() ; 
}



}