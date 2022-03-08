#include <iostream>
#include<fstream>
#include<string>
#include<windows.h>
#include <sstream>

using namespace std;

char *result;

//ReRepetition the key.
string ReRepetition(string key)
{
    char *temp1 = new char[key.length()+1];
    char *temp2 = new char[key.length()+1];

    for(int i = 0;i <= key.length();i++ )
    {
        strcpy(temp1,key.c_str());
        strcpy(temp2,key.c_str());

        int flag = 0;
        for(int j = 0;j <= key.length(); j++ )
        {

            if (temp1[i] == temp2[j])
                flag++;
            if(flag==2)
            {
                int pos = key.find(temp1[i]);
                key.erase(pos,1);
                flag --;
            }

        }
    }
    //before return
    delete[] temp1;
    temp1 = nullptr;
    delete[] temp2;
    temp2 = nullptr;
    return key;

}

void Encode(string plaintext, string key)
{
    result=new char[plaintext.length() + 1];

    int j = 0;
    int k = 0;
    int key_len = key.length();
    int plaintext_len = plaintext.length();

    //For lowcase or capital
    for(int i = 0; i < plaintext_len; i++)
    {
        if (plaintext[i] >= 'A' && plaintext[i] <= 'Z')
        {
            if(j == key_len)
            {
                j=0;
                result[k]= (plaintext[i] - 'A' + key[j] - 'A') % 26 + 'A';
            }
            else
            {
                result[k]= (plaintext[i] - 'A' + key[j] - 'A') % 26 + 'A';
            }
            j++;
        }
        else if (plaintext[i] >= 'a' && plaintext[i] <= 'z')
        {
            if(j == key_len)
            {
                j=0;
                result[k]= (plaintext[i] - 'a' + key[j] - 'a') % 26 + 'a';
            } else
            {
                result[k]= (plaintext[i] - 'a' + key[j] - 'a') % 26 + 'a';
            }
            j++;
        }
        k++;
    }
}

void Decode(string ciphertext, string key)
{
    result=new char[ciphertext.length() + 1];

    int j = 0;
    int k = 0;
    int key_len = key.length();
    int ciphertext_len = ciphertext.length();

    //For lowcase or capital
    for(int i = 0; i < ciphertext_len; i++)
    {

        if (ciphertext[i] >= 'A' && ciphertext[i] <= 'Z')
        {
            if(j == key_len)
            {
                j=0;
                result[k]= (ciphertext[i] - key[j] + 26 ) % 26 + 'A' ;
            }
            else
            {
                result[k]= (ciphertext[i] - key[j] + 26 ) % 26 + 'A' ;
            }
            j++;
        }
        else if (ciphertext[i] >= 'a' && ciphertext[i] <= 'z')
        {
            if(j == key_len)
            {
                j=0;
                result[k]= (ciphertext[i] - key[j] + 26) % 26 + 'a';
            }
            else
            {
                result[k]= (ciphertext[i] - key[j] + 26) % 26 + 'a';
            }
            j++;
        }
        k++;
    }

}


////preparing before begining
bool prepare()
{
    string text;
    string key;
    string temp;

    cout<<"========================================================="<<endl;
    cout<<"                  "<<"Vigenere Cipher"<<endl;
    cout<<"                   "<<"Author:PIG-007"<<endl;
    cout<<"========================================================="<<endl;
    cout<<"1.Encode a string."<<endl;
    cout<<"2.Decode a string."<<endl;
    cout<<"3.Encode a plaintext.txt."<<endl;
    cout<<"4.Decode a ciphertext.txt."<<endl;
    cout<<"Please select one option:";
    char option;
    cin>>option;

    if (option == '1')
    {
        cout<<"Please input your plaintext which must all be lowcase alphabet or all capital alphabet:";
        cin>>text;
        cout<<"Please input your key which must all be lowcase alphabet or all capital alphabet:";
        cin>>key;
        key = ReRepetition(key);
        cout<<"The key after ReRepetition is "<<key<<endl;

        Encode(text,key);
        cout<<"The ciphertext is ";
        for(int i = 0 ; i < text.length() ; i ++ )
        {
            cout<<result[i];
        }
        cout<<endl;

        return true;
    }

    else if (option == '2')
    {
        cout<<"Please input your ciphertext which must all be lowcase alphabet or all capital alphabet:";
        cin>>text;
        cout<<"Please input your key which must all be lowcase alphabet or all capital alphabet:";
        cin>>key;
        key = ReRepetition(key);
        cout<<"The key after ReRepetition is "<<key<<endl;

        Decode(text,key);
        cout<<"The plaintext is ";
        for(int i = 0 ; i < text.length() ; i ++ )
        {
            cout<<result[i];
        }
        cout<<endl;

        return true;
    }

    else if (option == '3')
    {
        cout<<"Please input the path of your file:";
        cin >> temp;
        char *path = new char[temp.length() + 1];
        strcpy(path, temp.c_str());

        ifstream myfile(path);
        myfile >> text;

        cout<<"The plaintext in your file is "<<text<<"."<<endl;
        cout<<"Please input your key:";
        cin>>key;
        key = ReRepetition(key);
        cout<<"The key after ReRepetition is "<<key<<endl;


        Encode(text,key);
        cout<<"The ciphertext is ";
        for(int i = 0 ; i < text.length() ; i ++ )
        {
            cout<<result[i];
        }
        cout<<endl;


        //before return
        delete[] path;
        path = nullptr;
        myfile.close();
        return true;
    }

    else if (option == '4')
    {
        cout<<"Please input the path of your file:";
        cin >> temp;

        char *path = new char[temp.length() + 1];
        strcpy(path, temp.c_str());

        ifstream myfile(path);
        myfile >> text;

        cout<<"The ciphertext in your file is "<<text<<"."<<endl;
        cout<<"Please input your key:";
        cin>>key;
        key = ReRepetition(key);
        cout<<"The key after ReRepetition is "<<key<<endl;


        Decode(text,key);
        cout<<"The plaintext is ";
        for(int i = 0 ; i < text.length() ; i ++ )
        {
            cout<<result[i];
        }
        cout<<endl;


        //before return
        delete[] path;
        path = nullptr;
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
