#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>
using namespace std;
bool compare(vector<int>a,vector<int>b){
    return a[0]<b[0];
}
int main(){
    int processes;
    cin>>processes;
    int burst;
    cin>>burst;
    vector<vector<int>>table(processes);
    for(int i=0;i<processes;i++){
        int at,bt;
        cin>>at>>bt;
        table[i].push_back(at);
        table[i].push_back(bt);
        table[i].push_back(bt);
    }
    sort(table.begin(),table.end(),compare);
    queue<int>q;
    int process=0;
    int aIdx=1;
    int totalTime =table[0][0];
    q.push(0);

    while(process<processes){
        int idx=q.front();
        q.pop();
        if(table[idx][2]>=burst){
            table[idx][2]-=burst;
            totalTime +=burst;
            if(aIdx<processes&&table[aIdx][0]>totalTime){
                int diff=table[aIdx][0]-totalTime;
                totalTime +=diff;
            }
            while(aIdx<processes&&table[aIdx][0]<=totalTime){
                q.push(aIdx);
                aIdx++;
            }
            if(table[idx][2]>0){
                q.push(idx);
            }
            else{
                 table[idx].push_back(totalTime);
                 //turn trun around time
                 table[idx].push_back(table[idx][3]-table[idx][0]);
                 //waiting time
                 table[idx].push_back(table[idx][4]-table[idx][1]);
                 process++;
            }
        }
        else{
            int remTime=table[idx][2];
            table[idx][2] -=remTime;
            totalTime +=remTime;
            process++;
            table[idx].push_back(totalTime);
            //turn trun around time
            table[idx].push_back(table[idx][3]-table[idx][0]);
            //waiting time
            table[idx].push_back(table[idx][4]-table[idx][1]);
            if(aIdx<processes&&table[aIdx][0]>totalTime){
                int diff=table[aIdx][0]-totalTime;
                totalTime +=diff;
            }
            while(aIdx<processes&&table[aIdx][0]<=totalTime){
                q.push(aIdx);
                aIdx++;
            }
        }
    }
    cout<<"AT"<<"  "<<"BT"<<"   "<<"CT"<<"  "<<"TAT"<<"  "<<"WT"<<"\n";
    for(auto i:table){
        for(auto j:i){
            cout<<j<<"  ";
        }
        cout<<"\n";
    }
    return 0;
}