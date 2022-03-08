#include <iostream>
#include<fstream>
#include<string>
#include<windows.h>
#include <sstream>

using namespace std;


int* sort(string key)
{

    char alphabet[27] = "abcdefghijklmnopqrstuvwxyz";
    int *que_array = new int[key.length()+1];

    //make specification for key
    for(int i = 0 ; i < key.length() ; i ++)
    {
        if(key[i] < 'a' || key[i] > 'z')
        {
            que_array[0] = -1;
            return que_array;
        }
    }

    //sort the key
    int que_idx = 1;
    for(int i =0;i <= 25;i++ )
    {
        for(int j = 0 ; j <= key.length() ; j++)
        {
            if(alphabet[i] == key[j])
            {
                que_array[j] = que_idx;
                que_idx = que_idx + 1;
            }
        }
    }
    return que_array;
}

string Encode(string p, int* key, int key_len)
{
    string tmp;

    char *plaintext =new char[p.length()+1];
    strcpy(plaintext,p.c_str());

    int row = int(p.length()/key_len)+1;

    for (int i = 0 ; i < key_len ; i ++)
    {
        for(int j = 0 ; j < row ; j ++)
        {
            int idx = key[i]+key_len*j-1;
            if(idx >= p.length()) break;
            else
            {
                tmp = tmp + plaintext[idx];
            }

        }
    }

    delete plaintext;
    plaintext = NULL;

    return tmp;

}

string Decode(string c, int* key, int key_len)
{

    string tmp;

    char *ciphertext = new char[c.length() + 1];
    strcpy(ciphertext, c.c_str());

    int column = int(c.length() / key_len) + 1;
    char table[key_len][column];
    int out = c.length() - (column - 1) * key_len;

    //init table
    for (int i = 0; i < key_len; i++)
    {
        for (int j = 0; j < column; j++)
        {
            table[i][j] = '0';
        }
    }

    //occupy
    for (int i = out + 1; i <= key_len; i++)
    {
        for (int j = 0; j < key_len; j++)
        {
            if (i == key[j])
            {
                table[j][column - 1] = '~';
            }
        }
    }

    //make table
    int k = 0;
    for (int i = 0; i < key_len; i++)
    {
        for (int j = 0; j < column; j++)
        {
            if (table[i][j] == '0')
            {
                table[i][j] = ciphertext[k];
                k++;
            }
        }
    }


    //decode
    for (int i = 0; i < column; i++)
    {
        for (int j = 1; j <= key_len; j++)
        {
            for (int k = 0; k < key_len; k++)
            {
                if (key[k] == j)
                {
                    if (table[k][i] == '~') break;
                    else
                    {
                        tmp = tmp + table[k][i];
                    }

                }
            }
        }
    }

    delete ciphertext;
    ciphertext = NULL;

    return tmp;

}


//preparing
bool prepare()
{
    string text;
    string key;
    string temp;
    string result;
    int* key_sort;

    cout<<"========================================================="<<endl;
    cout<<"               "<<"Column_Permutation Cipher"<<endl;
    cout<<"                                       "<<"Author:PIG-007"<<endl;
    cout<<"========================================================="<<endl;
    cout<<"1.Encode a string."<<endl;
    cout<<"2.Decode a string."<<endl;
    cout<<"3.Encode a plaintext.txt."<<endl;
    cout<<"4.Decode a ciphertext.txt."<<endl;
    cout<<"Please select one option:";
    char option;
    cin>>option;

    //Encode a string
    if (option == '1')
    {
        //output hint
        cout<<"Please input your plaintext:";
        cin>>text;

        //format key
        while(1)
        {
            cout<<"Please input your key:";
            cin>>key;

            if(text.length()<key.length())
            {
                for (int i = text.length(); i < key.length(); i ++)
                {
                    key.erase(i);
                }
            }



            //output key information
            key_sort = sort(key);
            if(key_sort[0] == -1)
            {
                cout<<"The format of key is wrong."<<endl;
                cout<<"Please input again,make sure for that the key is lowercase"<<endl;
            }
            else break;
        }
        cout<<"The key after sort is ";
        for (int i = 0 ; i < key.length() ; i++ )
        {
            cout<<key_sort[i]<<",";
        }
        cout<<endl;


        //output result
        result = Encode(text,key_sort,key.length());
        cout<<"The ciphertext is "<<result<<endl;

        delete[] key_sort;
        key_sort = NULL;
        return true;
    }

    //Decode a string
    else if (option == '2')
    {
        //output hint
        cout<<"Please input your ciphertext:";
        cin>>text;


        //format key
        while(1)
        {
            if(text.length()<key.length())
            {
                for (int i = text.length(); i < key.length(); i ++)
                {
                    key.erase(i);
                }
            }

            cout<<"Please input your key:";
            cin>>key;


            //output key information
            key_sort = sort(key);
            if(key_sort[0] == -1)
            {
                cout<<"The format of key is wrong."<<endl;
                cout<<"Please input again,make sure for that the key is lowercase"<<endl;
            }
            else break;
        }
        cout<<"The key after sort is ";
        for (int i = 0 ; i < key.length() ; i++ )
        {
            cout<<key_sort[i]<<",";
        }
        cout<<endl;

        //output result
        result = Decode(text,key_sort,key.length());
        cout<<"The plaintext is "<<result<<endl;


        //before return
        delete[] key_sort;
        key_sort = NULL;
        return true;
    }

    //Encode a plaintext.txt
    else if (option == '3')
    {
        //output hint
        cout<<"Please input the path of your file:";
        cin >> temp;
        char *path = new char[temp.length() + 1];
        strcpy(path, temp.c_str());
        ifstream myfile(path);
        myfile >> text;
        cout<<"The plaintext in your file is "<<text<<"."<<endl;

        //format key
        while(1)
        {
            cout<<"Please input your key:";
            cin>>key;

            if(text.length()<key.length())
            {
                for (int i = text.length(); i < key.length(); i ++)
                {
                    key.erase(i);
                }
            }


            //output key information
            key_sort = sort(key);
            if(key_sort[0] == -1)
            {
                cout<<"The format of key is wrong."<<endl;
                cout<<"Please input again,make sure for that the key is lowercase"<<endl;
            }
            else break;
        }
        cout<<"The key after sort is ";
        for (int i = 0 ; i < key.length() ; i++ )
        {
            cout<<key_sort[i]<<",";
        }
        cout<<endl;

        //output result
        result = Encode(text,key_sort,key.length());
        cout<<"The ciphertext is "<<result<<endl;


        //before return
        delete[] path;
        path = NULL;

        delete[] key_sort;
        key_sort = NULL;

        myfile.close();
        return true;
    }


    //Decode a ciphertext.txt
    else if (option == '4')
    {
        //output hint
        cout<<"Please input the path of your file:";
        cin >> temp;
        char *path = new char[temp.length() + 1];
        strcpy(path, temp.c_str());
        ifstream myfile(path);
        myfile >> text;
        cout<<"The ciphertext in your file is "<<text<<"."<<endl;

        //format key
        while(1)
        {
            cout<<"Please input your key:";
            cin>>key;

            if(text.length()<key.length())
            {
                for (int i = text.length(); i < key.length(); i ++)
                {
                    key.erase(i);
                }
            }


            //output key information
            key_sort = sort(key);
            if(key_sort[0] == -1)
            {
                cout<<"The format of key is wrong."<<endl;
                cout<<"Please input again,make sure for that the key is lowercase"<<endl;
            }
            else break;
        }
        cout<<"The key after sort is ";
        for (int i = 0 ; i < key.length() ; i++ )
        {
            cout<<key_sort[i]<<",";
        }
        cout<<endl;


        //output result
        result = Decode(text,key_sort,key.length());
        cout<<"The plaintext is "<<result<<endl;

        //before return
        delete[] path;
        path = NULL;

        delete[] key_sort;
        key_sort = NULL;

        myfile.close();
        return true;
    }

    else
    {
        return false;
    }


}


int main()
{

    while(1)
    {
        bool flag = prepare();
        if (!flag)
        {
            cout<<"Thanks for using.Quit....."<<endl;
            break;
        }
    }

    return 0;


}
