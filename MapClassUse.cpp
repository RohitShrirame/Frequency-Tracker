#include<iostream>
#include<vector>
#include<string>
#include"MapClass_1.h"
using namespace std;
void takeinput(myMap<int> &mpp){
    string s;
    cout<<"Enter a paragraph or a sentence"<<endl;
    cout<<"Note : press Enter only after the complete input is typed/pasted"<<endl;
    getline(cin,s);
    string tmp ="";
    for(int i=0; i<s.size(); i++){
        if( s[i] == ' ' || s[i] == '.' || s[i]== ','){
            int v = mpp.getValue(tmp);
            v++;
            mpp.insert(tmp,v);
            tmp = "";
        }
        else{
            tmp += s[i];
        }
    }
}
void initialise(){
    cout<<endl;
    cout<<" Choose the operation you want to perform "<<endl;
    cout<<endl;
    cout<<"1 : Check the Number of words present in our paragraph/sentence "<<endl;
    cout<<"2 : Check if a particular word is present in our paragraph or not"<<endl;
    cout<<"3 : Check the frequency of particular word "<<endl;
    cout<<"0 : To exit"<<endl;
}
void check(myMap<int> &mpp){
    cout<<"Enter a Word (Entered Word is case sensitive ) "<<endl;
    string tmp;
    cin>>tmp;
    if( mpp.Search(tmp) )
        cout<<endl<<"The word "<<tmp<<" is present in our paragraph/sentence "<<endl;
    else
        cout<<endl<<"The word "<<tmp<<" is not present in our paragraph/sentence"<<endl;
}
void freq(myMap<int> &mpp){
    cout<<"Enter a Word (Entered Word is case sensitive )"<<endl;
    string tmp;
    cin>>tmp;
    cout<<endl<<"The frequency of word "<<tmp<<" is "<<mpp.getValue(tmp)<<endl;
}
void start(myMap<int> &mpp){
    int flag = 1;
    while( flag ){

        initialise();
        int t; cin>>t;
        switch(t)
        {
            case 0:
                flag = 0;
                break;
            case 1:
                cout<<endl<<"Total Words Present are "<<mpp.getSize()<<endl;
                break;

            case 2: check(mpp);
                break;

            case 3: freq(mpp);
                break;
        }
    }
}
int main()
{
    myMap<int> mpp;

    takeinput(mpp);
    
    start(mpp);

    return 0;
}
