#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>
using namespace std;
class compare{
    public:
    bool operator()(vector<int>a,vector<int>b){
        if(b[0]<a[0])
            return true;
        if(b[0]==a[0]&&b[1]<a[1])
            return true;
        else 
            return false;
    }
};
int main(){
    int processes;
    cin>>processes;
    //AT BT PT
    vector<vector<int>>table;
    for(int i=0;i<processes;i++){
        int at,bt;
        cin>>at>>bt;
        table.push_back({at,bt});
    }
    sort(table.begin(),table.end());
    int totalTime=table[0][0];
    int process=0;
    int pIdx=1;
    //Burst_Time Priority Arrival_time Index
    priority_queue<vector<int>,vector<vector<int>>,compare>pq;
    pq.push({table[0][1],table[0][0],0});
    while(process<processes){
        // cout<<"1"<<" ";
        if(!pq.empty()){
            // cout<<"2"<<" ";
            vector<int>temp=pq.top();
            for(auto i:temp)
                cout<<i<<" ";
            cout<<"\n";
            pq.pop();
            int bTime=temp[0],aTime=temp[1],index=temp[2];
            totalTime +=bTime;
            //insert the arrived process
            while(pIdx<processes&&table[pIdx][0]<=totalTime){
                pq.push({table[pIdx][1],table[pIdx][0],pIdx});
                pIdx++;
            }
                //process accomplished
                table[index].push_back(totalTime);
                //turn around time
                table[index].push_back(table[index][2]-table[index][0]);
                // //waiting time
                table[index].push_back(table[index][3]-table[index][1]);
                process++;
        }
        //cpu will remain idle
        else{
            // cout<<"3"<<" ";
            if(pIdx<processes){
                totalTime +=(table[pIdx][0]-totalTime);
                pq.push({table[pIdx][1],table[pIdx][0],pIdx});
                pIdx++;
            }
        }
    }
    cout<<"\n";
    for(auto i:table){
        for(auto j:i)
            cout<<j<<" ";
        cout<<"\n";
    }

    return 0;
}