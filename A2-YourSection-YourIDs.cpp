#include <iostream>
#include <string>
#include "VoleMachine.h"
using namespace std;
using namespace vole;

int main() {
    VoleMachine machine;
    int choice;

    do {
        cout << "\n1. Load program\n";
        cout << "2. Run (all at once)\n";
        cout << "3. Step by step\n";
        cout << "4. Set register\n";
        cout << "5. Set memory\n";
        cout << "6. Display\n";
        cout << "0. Exit\n";
        cout << "Choice: ";
        cin >> dec >> choice;

        if (choice == 1) {
            string filename;
            int address;
            cout << "File name: ";
            cin >> filename;
            cout << "Start address (decimal, even): ";
            cin >> address;
            if (machine.loadProgram(filename, address) == true) cout << "Loaded.\n";        
            else cout << "Failed to load.\n";
        }
        else if (choice == 2) {
            machine.run();                              
        }

        else if (choice == 3) {
            cin.ignore();                      
            while (!machine.isHalted()) {
            machine.step();
            machine.display();
            cin.get();                     
          }
        }

        else if (choice == 4) {
            int R , valueR;
            cout << "Register number (hex): ";
            cin >> hex >> R;
            cout << "Value (hex): ";
            cin >> hex >> valueR;
            machine.setRegister(R, valueR);
            cout << dec;
        }
        else if (choice == 5) {
            int M, valueM;
            cout << "Memory (hex): ";
            cin >> hex >> M;
            cout << "Value (hex): ";
            cin >> hex >> valueM;
            machine.setMemory(M, valueM);
            cout << dec;                           
        }

        else if (choice == 6) {
           machine.display();                 
        }
        
    } while (choice != 0);

    return 0;
}