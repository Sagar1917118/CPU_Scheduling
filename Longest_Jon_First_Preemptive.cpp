#include<iostream>
#include<queue>
#include<vector>
#include<algorithm>
using namespace std;
class compare{
    public:
    bool operator()(pair<pair<int,int>,pair<int,bool>>a,pair<pair<int,int>,pair<int,bool>>b){
        if(b.second.second==true){
            return true;
        }
        else if(b.first.first>a.first.first){
            return true;
        }
        else if(b.first.first==a.first.first){
            if(b.second.first<=a.second.first){
                return true;
            }
            else{
                return false;
            }
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
    for(int i=0;i<processes;i++){
        int at,bt;
        cin>>at>>bt;
        table[i].push_back(at);
        table[i].push_back(bt);
    }
    sort(table.begin(),table.end());
    int aIdx=1;
    int process=0;
    int totalTime=table[0][0];
    priority_queue<pair<pair<int,int>,pair<int,bool>>,vector<pair<pair<int,int>,pair<int,bool>>>,compare>pq;
    pq.push({{table[0][1],table[0][0]},{0,false}});
    while(process<processes){
        if(!pq.empty()){
            pair<pair<int,int>,pair<int,bool>>temp=pq.top();
            pq.pop();
            totalTime +=1;
            while(aIdx<processes&&table[aIdx][0]<=totalTime){
                pq.push({{table[aIdx][1],table[aIdx][0]},{aIdx,false}});
                aIdx++;
            };
            if(temp.first.first-1>0){
                pair<pair<int,int>,pair<int,bool>>temp2=pq.top();
                if(temp2.first.first>temp.first.first-1){
                pq.push({{temp.first.first-1,temp.first.second},{temp.second.first,false}});
                }
                else if(temp2.first.first<=temp.first.first-1){ 
                pq.push({{temp.first.first-1,temp.first.second},{temp.second.first,true}});
                }
            }
            else{
                int idx=temp.second.first;
                table[idx].push_back(totalTime);
                //completion time
                table[idx].push_back(table[idx][2]-table[idx][0]);
                //turn around time
                table[idx].push_back(table[idx][3]-table[idx][1]);
                process++;
            }
        }
        else{
            break;
        }
    }
    cout<<"AT"<<" "<<"BT"<<" "<<"CT"<<" "<<"TAT"<<" "<<"WT"<<"\n";
    for(auto i:table){
        for(auto j:i){
            cout<<j<<"  ";
        }
        cout<<"\n";
    }
    return 0;
}