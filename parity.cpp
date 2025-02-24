// Online C++ compiler to run C++ program online
#include <iostream>
using namespace std;
int main() {
    int sender[9]={1,0,0,1,0,1,1,0};
    string parity;
    cout<<"Enter parity"<<endl;
    cin>>parity;
    int count=0;
    for(int i=0;i<8;i++){
        if(sender[i]==1){
            count++;
        }
    }
    if((parity=="even") && (count%2!=0)){
        sender[8]=1;
        count++;
    }else if((parity=="odd") && (count%2==0)){
        sender[8]=1;
        count++;
    }

    int receiver[9]={1,0,0,1,0,1,1,0};
    string recparity;
    cout<<"Enter parity"<<endl;
    cin>>recparity;
    int reccount=0;
    for(int i=0;i<8;i++){
        if(receiver[i]==1){
            reccount++;
        }
    }
    if((recparity=="even") && (reccount%2!=0)){
        receiver[8]=1;
        reccount++;
    }else if((recparity=="odd") && (reccount%2==0)){
        receiver[8]=1;
        reccount++;
    }
    if(count==reccount){
        cout<<"No error";
    }else{
        cout<<"Error";
    }
    return 0;
}
