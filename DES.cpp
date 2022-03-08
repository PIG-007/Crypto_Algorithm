#include <iostream>
#include<fstream>
#include<string>
#include<windows.h>
#include <sstream>

using namespace std;

int shiftBox[16] = {1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1};

int PC_1Box[56] =
        {57, 49, 41, 33, 25, 17, 9, 1, 58, 50, 42, 34, 26, 18,
         10, 2, 59, 51, 43, 35, 27, 19, 11, 3, 60, 52, 44, 36,
         63, 55, 47, 39, 31, 23, 15, 7, 62, 54, 46, 38, 30, 22,
         14, 6, 61, 53, 45, 37, 29, 21, 13, 5, 28, 20, 12, 4};
int PC_2Box[48] = {14, 17, 11, 24, 1, 5, 3, 28, 15, 6, 21, 10, 23, 19, 12, 4, 26, 8, 16, 7, 27, 20, 13, 2, 41,
                   52, 31, 37, 47, 55, 30, 40, 51, 45, 33, 48, 44, 49, 39, 56, 34, 53, 46, 42, 50, 36, 29, 32};

int IT[64] =
        {58, 50, 42, 34, 26, 18, 10, 2, 60, 52, 44, 36, 28, 20, 12, 4,
         62, 54, 46, 38, 30, 22, 14, 6, 64, 56, 48, 40, 32, 24, 16, 8,
         57, 49, 41, 33, 25, 17, 9, 1, 59, 51, 43, 35, 27, 19, 11, 3,
         61, 53, 45, 37, 29, 21, 13, 5, 63, 55, 47, 39, 31, 23, 15, 7};

int EBOX[48] =
        {32, 1, 2, 3, 4, 5, 4, 5, 6, 7, 8, 9,
         8, 9, 10, 11, 12, 13, 12, 13, 14, 15, 16, 17,
         16, 17, 18, 19, 20, 21, 20, 21, 22, 23, 24, 25,
         24, 25, 26, 27, 28, 29, 28, 29, 30, 31, 32, 1};

int SBOX[8][4][16] =
        {                     //8 S boxes
                // S1
                14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7,
                0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8,
                4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0,
                15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13,
                //S2
                15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10,
                3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5,
                0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15,
                13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9,
                //S3
                10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8,
                13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1,
                13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7,
                1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12,
                //S4
                7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15,
                13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9,
                10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4,
                3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14,
                //S5
                2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9,
                14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6,
                4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14,
                11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3,
                //S6
                12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11,
                10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8,
                9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6,
                4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13,
                //S7
                4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1,
                13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6,
                1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2,
                6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12,
                //S8
                13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7,
                1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2,
                7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8,
                2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11
        };


int PBOX[32] =
        {                                             //  P box
                16, 7, 20, 21, 29, 12, 28, 17, 1, 15, 23, 26, 5, 18, 31, 10,
                2, 8, 24, 14, 32, 27, 3, 9, 19, 13, 30, 6, 22, 11, 4, 25};


int FP[64] =
        {                                    //Inverse IP permutation matrix
                40, 8, 48, 16, 56, 24, 64, 32, 39, 7, 47, 15, 55, 23, 63, 31,
                38, 6, 46, 14, 54, 22, 62, 30, 37, 5, 45, 13, 53, 21, 61, 29,
                36, 4, 44, 12, 52, 20, 60, 28, 35, 3, 43, 11, 51, 19, 59, 27,
                34, 2, 42, 10, 50, 18, 58, 26, 33, 1, 41, 9, 49, 17, 57, 25};

string s2b(string block) {
    //get binary block of tmp
    char *ptr = new char[9];
    strcpy(ptr, block.c_str());

    for (int i = block.length(); i < 8; i++) {
        ptr[i] = '\x00';
    }


    char tmp[8][8];
    for (int i = 0; i < 8; ++ptr) {
        int j = 0;
        for (int pos = 7; pos >= 0; --pos) {
            (*ptr & 1 << pos) ? tmp[i][j] = '1' : tmp[i][j] = '0';
            j++;
        }
        i++;
    }

    //get binary block
    string binary_unit;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            binary_unit += tmp[i][j];
        }
    }

    //before return
    ptr = NULL;
    return binary_unit;

}

string k2b(string key) {
    //get binary key of tmp
    char *ptr = new char[9];
    strcpy(ptr, key.c_str());

    char tmp[8][8];
    int i = 0;
    for (; *ptr != 0; ++ptr) {
        int j = 0;
        for (int pos = 7; pos >= 0; --pos) {
            (*ptr & 1 << pos) ? tmp[i][j] = '1' : tmp[i][j] = '0';
            j++;
        }
        i++;
    }

    //print Parity check bits
    string parity_bit;
    for (int i = 0; i < 8; i++) {
        parity_bit += tmp[i][7];
    }
    cout << "The Parity check bits is " << parity_bit << endl;


    //get binary key
    string binary_key;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            binary_key += tmp[i][j];
        }
    }

    //before return
    ptr = NULL;
    return binary_key;

}

void loop_move_left(char *p, int i) {
    char *temp = new char[29];
    strcpy(temp, p);
    for (int j = 0; j < 28 - i; j++) {
        *(p + j) = temp[i + j];
    }
    for (int k = 28 - i; k < 28; k++) {
        *(p + k) = temp[k + i - 28];
    }

    //before return
    delete[] temp;
    temp = NULL;

}

void generate_Key(string key, char **ptr_key) {
    string binary_key = k2b(key);

    //Through PC_1
    char PC_1K[56];
    for (int j = 1; j <= 64; j++) {
        for (int k = 0; k < 56; k++) {
            if (PC_1Box[k] == j) {
                PC_1K[k] = binary_key[j - 1];
            }
        }
    }

    //get KL KR
    string KL;
    string KR;
    for (int i = 0; i < 28; i++) {
        KL += PC_1K[i];
        KR += PC_1K[i + 28];
    }


    //loop 16
    char *pKL = new char[KL.length() + 1];
    strcpy(pKL, KL.c_str());

    char *pKR = new char[KR.length() + 1];
    strcpy(pKR, KR.c_str());

    char merge[56];
    for (int i = 0; i < 16; i++) {

        loop_move_left(pKL, shiftBox[i]);
        loop_move_left(pKR, shiftBox[i]);

        for (int j = 0; j < 28; j++) {
            merge[j] = pKL[j];
            merge[j + 28] = pKR[j];
        }


        for (int j = 1; j <= 56; j++) {
            for (int k = 0; k < 48; k++) {
                if (PC_2Box[k] == j) {
                    ptr_key[i][k] = merge[j - 1];
                }

            }
        }
    }
//    for(int i = 0 ; i < 16 ; i ++)
//    {
//        for (int j = 0 ; j < 48 ; j++)
//        {
//            cout<<temp[i][j];
//        }
//        cout<<endl;
//    }

    //before return
    delete[] pKL;
    delete[] pKR;
    pKL = NULL;
    pKR = NULL;
}

//flag_code==1,Encode;     //flag_code == 0,Decode
string block_code(char **key_16, string block_origintext, int flag_code) {
    string block_binary = "1110101010101000101001001001110001000110100000000110111111110101";
    //string block_binary = s2b(block_origintext);

    //init permutation
    char init_P[64];
    for (int j = 1; j <= 64; j++) {
        for (int k = 0; k < 64; k++) {
            if (IT[k] == j) {
                init_P[k] = block_binary[j - 1];
            }
        }
    }

    //get IL IR
    string IL;
    string IR;
    for (int i = 0; i < 32; i++) {
        IL += init_P[i];
        IR += init_P[i + 32];
    }


    string IR_base = IR;
    for (int m = 0; m < 16; m++) {

        if (m > 0) {
            IL = IR_base;
            IR_base = IR;
        }

        //Through EBOX
        char ER[48];
        for (int j = 1; j <= 32; j++) {
            for (int k = 0; k < 48; k++) {
                if (EBOX[k] == j) {
                    ER[k] = IR[j - 1];
                }
            }
        }
//===================
        //xor Key
        char K_X_ER[48];
        for (int j = 0; j < 48; j++) {
            int k_i;
            int p_i = (int) ER[j] - 48;
            if (flag_code == 1)//encode
            {
                k_i = (int) key_16[m][j] - 48;
            }
            if (flag_code == 0)//Decode
            {
                k_i = (int) key_16[15 - m][j] - 48;
            }
            K_X_ER[j] = char((p_i xor k_i) + 48);
        }
//        cout << endl;
//        for (int i = 0; i < 48; ++i) {
//            cout << ER[i];
//        }
//        cout << endl;
//===================

        //Through SBOX
        string row_s;
        string column_s;
        string SR;
        int row_i;
        int column_i;
        int S_tmp;
        for (int i = 0; i < 8; i++) {
            row_s.clear();
            column_s.clear();
            row_s += K_X_ER[i * 6];
            row_s += K_X_ER[i * 6 + 5];
            column_s += K_X_ER[i * 6 + 1];
            column_s += K_X_ER[i * 6 + 2];
            column_s += K_X_ER[i * 6 + 3];
            column_s += K_X_ER[i * 6 + 4];
            row_i = stoi(row_s, 0, 2);
            column_i = stoi(column_s, 0, 2);
            S_tmp = SBOX[i][row_i][column_i];
            for(int i = 3 ; i >= 0; i --)
            {
                SR += char((S_tmp>>i & 1)+48);
            }
//            for (int i = 3; i >= 0; i--) {
//                if (S_tmp & (1 << i))
//                    bin[2 - i] = 1;
//                else
//                    bin[2 - i] = 0;
//                SR += char(bin[2 - i] + 48);
//            }
        }


        //Through PBOX
        char PR[32];
        for (int j = 1; j <= 32; j++) {
            for (int k = 0; k < 32; k++) {
                if (PBOX[k] == j) {
                    PR[k] = SR[j - 1];
                }
            }
        }


        //R xor L
        IR.clear();
        for (int i = 0; i < 32; i++) {
            IR += char((((int) IL[i] - 48) xor ((int) PR[i] - 48)) + 48);
        }

    }

    //reverse L and R
    string L_X_R = IR + IR_base;


    //Through FP
    char final[64];
    for (int j = 1; j <= 64; j++) {
        for (int k = 0; k < 64; k++) {
            if (FP[k] == j) {
                final[k] = L_X_R[j - 1];
            }
        }
    }

    //generate block_changetext
    string block_changetext;
    for (int i = 0; i < 64; i++) {
        block_changetext += final[i];
    }
    return block_changetext;
}

string Encode(string key, string plaintext) {
    string block_plaintext;
    string ciphertext;

    //generate key_16
    char **key_16 = new char *[16];
    for (int i = 0; i < 16; i++) {
        key_16[i] = new char[48];
    }
    generate_Key(key, key_16);

    int out = plaintext.length() - (plaintext.length() / 8) * 8;

    for (int i = 0; i < (plaintext.length() / 8); i++) {
        block_plaintext.clear();
        for (int j = 0; j < 8; j++) {
            block_plaintext.push_back(plaintext[j + i * 8]);
        }
        ciphertext += block_code(key_16, block_plaintext, 1);
    }

    if (out != 0) {
        block_plaintext.clear();
        for (int i = 0; i < out; i++) {
            block_plaintext.push_back(plaintext[(plaintext.length() / 8) * 8 + i]);
        }
        ciphertext += block_code(key_16, block_plaintext, 1);
    }


    //before return
    for (int i = 0; i < 16; i++) {
        delete[] key_16[i];
    }
    delete[] key_16;
    key_16 = NULL;

    return ciphertext;
}

string Decode(string key, string ciphertext) {
    string block_ciphertext;
    string plaintext;

    //generate key_16
    char **key_16 = new char *[16];
    for (int i = 0; i < 16; i++) {
        key_16[i] = new char[48];
    }
    generate_Key(key, key_16);

    for (int i = 0; i < (ciphertext.length() / 8); i++) {
        block_ciphertext.clear();
        for (int j = 0; j < 8; j++) {
            block_ciphertext.push_back(ciphertext[j + i * 8]);
        }
        plaintext += block_code(key_16, block_ciphertext, 0);
    }

    //before return
    for (int i = 0; i < 16; i++) {
        delete[] key_16[i];
    }
    delete[] key_16;
    key_16 = NULL;
    return plaintext;
}


//preparing
bool prepare() {
    string text;
    string key;
    string temp;
    string result;

    cout << "=========================================================" << endl;
    cout << "               " << "DES Cipher" << endl;
    cout << "                                     " << "Author:PIG-007" << endl;
    cout << "=========================================================" << endl;
    cout << "1.Encode a string." << endl;
    cout << "2.Decode a string." << endl;
    cout << "3.Encode a plaintext.txt." << endl;
    cout << "4.Decode a ciphertext.txt." << endl;
    cout << "Please select one option:";
    char option;
    cin >> option;

    //Encode a string
    if (option == '1') {
        //output hint
        cout << "Please input your plaintext:";
        cin >> text;

        //format key
        while (1) {
            cout << "Please input your key,the length has to be equal to 8:";
            cin >> key;
            if (key.length() == 8) {
                break;
            }
            cout << "The length of the key is illegal!Agagin!" << endl;
        }


        //output result
        result = Encode(key, text);
        cout << "The ciphertext is " << result << endl;



        return true;
    }


        //Decode a string
    else if (option == '2') {
        //output hint
        cout << "Please input your ciphertext:";
        cin >> text;

        //format key
        while (1) {
            cout << "Please input your key,the length has to be equal to 8:";
            cin >> key;
            if (key.length() == 8) {
                break;
            }
            cout << "The length of the key is illegal!Agagin!" << endl;
        }


        //output result
        result = Decode(key, text);
        cout << "The plaintext is " << result << endl;
        return true;
    }


        //Encode a plaintext.txt
    else if (option == '3') {
        //output hint
        cout << "Please input the path of your file:";
        cin >> temp;
        char *path = new char[temp.length() + 1];
        strcpy(path, temp.c_str());

        ifstream myfile(path);
        if (!myfile) {
            cout << "fail to open the file" << endl;
            cout << "Restart!" << endl;
            return true;//或者抛出异常。
        } else {
            cout << "Open the file successfully!" << endl;
        }

        myfile >> text;
        while (1) {
            if (text.length() - (text.length()/8)*8 == 0 ) {
                break;
            }
            cout << "The length of the file is illegal!Agagin!" << endl;
            return true;
        }
        cout << "The plaintext in your file is " << text << "." << endl;

        //format key
        while (1) {
            cout << "Please input your key,the length has to be equal to 8:";
            cin >> key;
            if (key.length() == 8) {
                break;
            }
            cout << "The length of the key is illegal!Agagin!" << endl;
        }

        //output result
        result = Encode(key, text);
        cout << "The ciphertext is " << result << endl;


        //before return
        delete[] path;
        path = NULL;

        myfile.close();
        return true;
    }


        //Decode a ciphertext.txt
    else if (option == '4') {
        //output hint
        cout << "Please input the path of your file:";
        cin >> temp;
        char *path = new char[temp.length() + 1];
        strcpy(path, temp.c_str());
        ifstream myfile(path);
        if (!myfile) {
            cout << "fail to open the file" << endl;
            cout << "Restart!" << endl;
            return true;//或者抛出异常。
        } else {
            cout << "open the file successfully" << endl;
        }
        myfile >> text;
        cout << "The ciphertext in your file is " << text << "." << endl;

        //format key
        while (1) {
            cout << "Please input your key,the length has to be equal to 8:";
            cin >> key;
            if (key.length() == 8) {
                break;
            }
            cout << "The length of the key is illegal!Agagin!" << endl;
        }

        //output result
        result = Decode(key, text);
        cout << "The plaintext is " << result << endl;

        //before return
        delete[] path;
        path = NULL;

        myfile.close();
        return true;
    } else {
        return false;
    }


}

int main() {
    while (1) {
        bool flag = prepare();
        if (!flag) {
            cout << "Thanks for using.Quit....." << endl;
            break;
        }
    }
//    string key = "abcdefgh";
//    string p = "abcdefgh";
//    string c = Decode(key,p);
//    cout<<c;

    return 0;
}
