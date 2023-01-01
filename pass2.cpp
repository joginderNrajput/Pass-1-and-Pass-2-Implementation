#include<iostream>
#include<fstream>
using namespace std;

int string_to_int(const std::string& str){
    int result = 0;
    int sign = 1;
    int i = 0;

    if (str[0] == '-'){
        sign = -1;
        i = 1;
    }
    for (; i < str.size(); i++){
        if (!isdigit(str[i])){
            break;
        }
        result = result * 10 + (str[i] - '0');
    }
    return result * sign;
}


int main(){
    string label, opcode, operand, symbol, add;
    string mnemonics[15] = {"LDA", "STA", "LDCH", "STCH"};
    string code[15] = {"33", "44", "53", "57"};

    int st, diff, address, finaddr, prevaddr, j = 0;

    //    ofstream file1("assembly.txt");
    ifstream filep1("symbol.txt");
    ifstream filep2("intermediate.txt");
    ofstream filep3("object.txt");

    filep2 >> label >> opcode >> operand;
    while(opcode != "END"){
        prevaddr = address;
        filep2 >> address >> label >> opcode >> operand;
    }

    finaddr = address;
    filep2.close();

    ifstream filep4("intermediate.txt");
    filep4 >> label >> opcode >> operand;

    if(opcode == "START"){
        filep3 << "H^" << label << "s^" << operand << "s^" << finaddr << endl;
        st = string_to_int(operand);
        diff = finaddr - st;
        filep3 << "T^" << address << "^" << diff;
    }
     cout << "Content of Intermediate file" << endl;
    while(opcode != "END"){
        filep4 >> address >> label >> opcode >> operand;
        cout << label << " " << opcode << " " << operand << endl;

        if((opcode == "BYTE") || (opcode == "WORD")){
            int opNum = string_to_int(operand);
            filep3 << "^" << opNum;
        }else if((opcode == "RESB") || (opcode == "RESW")){
            continue;
        }else{
            while(opcode == mnemonics[j]){
                while(!filep1.eof()){
                    filep1 >> symbol >> add;

                    if(operand == symbol){
                        int opNum = string_to_int(add);
                        filep3 << code[j] << opNum;
                        break;
                    }
                }
                filep1.seekg(0, ios::beg);
                j++;
            }
        }
    }
    filep3 << "\nE^" << st;

    filep1.close();
    filep3.close();
    filep4.close();

    cout << "\n\n\nThe Content of the Object Code file : " << endl << endl;
    ifstream filep5("object.txt");
    string line;
    while(getline(filep5, line)){
        cout << line << endl;
    }
    filep5.close();


    return 0;
}