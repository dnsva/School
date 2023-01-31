#include <iostream>

using namespace std;

int questions = 0;

void get_range(){
    int first, last = -1;
    char check_if_range;
    cin>>first;
    check_if_range = cin.peek();
    if(check_if_range == '-'){
        cin>>check_if_range;
        cin>>last;
    }
    if(last == -1){
        //if there is no range of questions 
        ++questions; //only one
    }else{
        //there is a range of questions
        questions += last-first+1;
    }
}

int main(){
    get_range(); //get the first instruction
    while(true){
        char peeking = cin.peek();
        char garbage;
        if(peeking == ';'){
            //cout<<"found a semicolon\n";
            cin>>garbage;
            get_range();
        }else{
            break;
        }
    }
    cout<<questions<<"\n";
    return 0;
}