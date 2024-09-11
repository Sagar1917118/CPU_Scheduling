#include<iostream>
#include<vector>
#include<unordered_map>
#include<queue>
#include<algorithm>
using namespace std;
class compare{
    public:
    bool operator()(pair<pair<int,int>,pair<int,int>>a,pair<pair<int,int>,pair<int,int>>b){
        //incomming priority is greater than presetn element priority
        if(b.first.first<a.first.first)
            return true;
        //priority is same process with less arrival time wil be encountered
        else if(b.first.first==a.first.first){
            return b.first.second<=a.first.second;
        }
        else{
            return false;
        }
    }
};

int main(){
    int processes;
    cin>>processes;
    vector<vector<int>>table(processes);
    //{burst time,{priority,{arrival time}}}
    priority_queue<pair<pair<int,int>,pair<int,int>>,vector<pair<pair<int,int>,pair<int,int>>>,compare>pq;
    for(int i=0;i<processes;i++){
        int at,priority,bt;
        cin>>at>>priority>>bt;
        table[i].push_back(at);
        table[i].push_back(priority);
        table[i].push_back(bt);
    }
    sort(table.begin(),table.end());
    int totalTime=table[0][0];
    int process=0;
    // priority arrival index burst
    pq.push({{table[0][1],table[0][0]},{0,table[0][2]}});
    int aIdx=1;
    while(process<processes){
        if(!pq.empty()){
            pair<pair<int,int>,pair<int,int>>temp=pq.top();
            pq.pop();
            int remBurstTime=temp.second.second;
            int idx=temp.second.first;
            totalTime +=remBurstTime;
            //include  incomming process upto total time
            while(aIdx<processes&&table[aIdx][0]<=totalTime){
                pq.push({{table[aIdx][1],table[aIdx][0]},{aIdx,table[aIdx][2]}});
                aIdx++;
            }
            //pushing completion time
            table[idx].push_back(totalTime);
            //pushing turn around time
            table[idx].push_back(table[idx][3]-table[idx][0]);
            //pushing waiting time
            table[idx].push_back(table[idx][4]-table[idx][2]);
            process++;

        }  
        else if(aIdx<processes){
            //handel burst  time
            int diff=table[aIdx][0]-totalTime;
            totalTime +=diff;
            pq.push({{table[aIdx][1],table[aIdx][0]},{aIdx,table[aIdx][2]}});
            aIdx++;
        }
    }
    cout<<"AT"<<" "<<"PR"<<" "<<"BT"<<" "<<"CT"<<" "<<"TAT"<<" "<<"WT"<<"\n";
    for(auto i:table){
        for(auto j:i){
            cout<<j<<"  ";
        }
        cout<<"\n";
    }
    return 0;
}