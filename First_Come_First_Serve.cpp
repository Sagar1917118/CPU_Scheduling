#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
class compare{
    public:
bool operator()(vector<int>&a,vector<int>&b){
    if(a[0]<b[0])
        return true;
    else
        return false;
};
};
int main(){
    int processes;
    cout<<"Enter number of processes\n";
    cin>>processes;
    vector<vector<int>>table;
    for(int i=0;i<processes;i++){
        int at,bt;
        cout<<"Enter arrival and burst time of "<<i+1<<" process\n";
        cin>>at>>bt;
        table.push_back({at,bt});
    }
    sort(table.begin(),table.end());
    int totaltime=table[0][0];
    int averageWaiting=0;
    for(int i=0;i<processes;i++){
        totaltime +=table[i][1];
        if(i>0&&table[i][0]>table[i-1][2])
            totaltime +=table[i][0]-table[i-1][1];
        table[i].push_back(totaltime);
        //pushing turn around  time
        table[i].push_back(table[i][2]-table[i][0]);
        //pushing waitin gtime
        table[i].push_back(table[i][3]-table[i][1]);
        averageWaiting +=table[i][4];

    }
    cout<<"A "<<"B "<<"C "<<"T "<<"W \n";
    for(int i=0;i<processes;i++){
        cout<<table[i][0]<<" "<<table[i][1]<<" "<<table[i][2]<<" "<<table[i][3]<<" "<<table[i][4]<<"\n";
    }
    cout<<"Average waiting time is :"<<(averageWaiting*1.0)/processes<<" s\n";

    return 0;
}