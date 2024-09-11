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
        else if(b[0]>a[0])
            return false;
        if(b[1]>a[1])
            return true;
        if(b[1]==a[1]&&b[2]<a[2])
            return true;
        return false;
    }
};
int main(){
    int processes;
    cin>>processes;
    //AT BT PT
    vector<vector<int>>table;
    for(int i=0;i<processes;i++){
        int at,bt,pr;
        cin>>at>>bt>>pr;
        table.push_back({at,bt,pr});
    }
    sort(table.begin(),table.end());
    int totalTime=table[0][0];
    int process=0;
    int pIdx=1;
    //Burst_Time Priority Arrival_time Index
    priority_queue<vector<int>,vector<vector<int>>,compare>pq;
    pq.push({table[0][1],table[0][2],table[0][0],0});
    while(process<processes){
        // cout<<"1"<<" ";
        if(!pq.empty()){
            // cout<<"2"<<" ";
            vector<int>temp=pq.top();
            pq.pop();
            totalTime +=1;
            //insert the arrived process
            while(pIdx<processes&&table[pIdx][0]<=totalTime){
                pq.push({table[pIdx][1],table[pIdx][2],table[pIdx][0],pIdx});
                pIdx++;
            }
            int bTime=temp[0]-1,p=temp[1],aTime=temp[2],index=temp[3];
            cout<<"P"<<index+1<<" ";
            if(bTime>0){
                pq.push({bTime,p,aTime,index});
            }
            else{
                //process accomplished
                table[index].push_back(totalTime);
                //turn around time
                table[index].push_back(table[index][3]-table[index][0]);
                // //waiting time
                table[index].push_back(table[index][4]-table[index][1]);
                process++;
            }
        }
        //cpu will remain idle
        else{
            // cout<<"3"<<" ";
            if(pIdx<processes){
                totalTime +=(table[pIdx][0]-totalTime);
                pq.push({table[pIdx][1],table[pIdx][2],table[pIdx][0],pIdx});
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