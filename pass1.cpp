#include <iostream>
#include <fstream>
using namespace std;

int main() {
  string opcode, operand, label, code, mnemonics;
  int locCtr, start, lenght;

  ifstream file1("input.txt");
  ifstream file2("optab.txt");

  ofstream file3("symbol.txt");
  ofstream file4("intermediate.txt");

  file1 >> label >> opcode >> operand;
  if (opcode == "START") {
    start = stoi(operand);
    locCtr = start;
    file4 << "\t\t" << label << "\t" << opcode << "\t" << operand << endl;
    file1 >> label >> opcode >> operand;
  } else {
    locCtr = 0;
  }

  while (opcode != "END") {
    file4 << "\t" << locCtr << "\t";

    if (label != "**") {
      file3 << label << "\t" << locCtr << endl;
    }

    file2 >> code >> mnemonics;
    while (code != "END") {
      if (code == opcode) {
        locCtr = locCtr + 3;
        break;
      }
      file2 >> code >> mnemonics;
    }
    if (opcode == "WORD") {
      locCtr = locCtr + 3;
    } else if (opcode == "RESW") {
      locCtr = locCtr + (3 * (stoi(operand)));
    } else if (opcode == "RESB") {
      locCtr = locCtr + (stoi(operand));
    } else if (opcode == "BYTE") {
      ++locCtr;
    }

    file4 << "\t" << label << "\t" << opcode << "\t" << operand << endl;
    file1 >> label >> opcode >> operand;
  }

  file4 << "\t" << locCtr << "\t" << label << "\t" << opcode << "\t" << operand << endl;

  lenght = locCtr - start;
  cout << "Lenght is : " << lenght;
  file1.close();
  file2.close();
  file3.close();
  file4.close();
  return 0;
}
 
