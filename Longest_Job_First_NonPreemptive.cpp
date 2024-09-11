#include<iostream>
#include<vector>
#include<algorithm>
#include<limits.h>
#include<queue>
using namespace std;
class compare{
    public:
    bool operator()(pair<int,int>&a,pair<int,int>&b){
        return a.first>=b.second;
    }
};
int main(){
    int processes;
    // cout<<"Enter number of processes\n";
    cin>>processes;
    vector<vector<int>>table;
    vector<int>flag(processes,0);
    priority_queue<pair<int,int>,vector<pair<int,int>>>pq;
    for(int i=0;i<processes;i++){
        int at,bt;
        cin>>at>>bt;
        table.push_back({at,bt});
    }
    sort(table.begin(),table.end());
    int p=0;
    int m=0;
    int totalTime=table[0][0];
    pq.push({table[0][1],0});
    flag[0]=1;
    while(p<processes){
         if(!pq.empty()){
            pair<int,int>temp=pq.top();
            pq.pop();
            int idx=temp.second;
            int burst=temp.first;
            totalTime +=burst;
            table[idx].push_back(totalTime);
            //pushing tat ime
            table[idx].push_back(table[idx][2]-table[idx][0]);
            //pushing waiting time
             table[idx].push_back(table[idx][3]-table[idx][1]);
            p++;
            m=p;
            while(m<processes&&table[m][0]<=totalTime){
                if(flag[m]==0){
                pq.push({table[m][1],m});
                flag[m]=1;
                }
                m++;
            }
         }
         else{
            int t=(table[p][0]-totalTime);
            totalTime +=t;
            pq.push({table[p][1],p});
            flag[p]=1;
         }
    }
    cout<<"AT"<<"   "<<"BT"<<"   "<<"CT"<<"   "<<"TAT"<<"   "<<"WT"<<"\n";
    for(auto i:table){
        for(auto j:i){
            cout<<j<<"    ";
        }
        cout<<"\n";
    }
    return 0;
}