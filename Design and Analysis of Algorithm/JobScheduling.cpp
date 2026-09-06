#include <iostream>

using namespace std;

struct Job{
    char id;
    int deadline;
    int profit;
};

int main(){
    int n;

    cout<<"Enter number of jobs: ";
    cin >> n;

    Job jobs[n];

    for(int i=0;i<n;i++){
        cout << "Enter Job ID: ";
        cin >> jobs[i].id;

        cout << "Enter deadline: ";
        cin >> jobs[i].deadline;

        cout << "Enter profit: ";
        cin >> jobs[i].profit;
    }

    //sort by profits
    
    for(int i=0;i<n-1;i++){
        for(int j=0;j<n-i-1;j++){
            if(jobs[j].profit < jobs[j+1].profit){
                Job temp = jobs[j];
                jobs[j] = jobs[j+1];
                jobs[j+1] = temp;
            }
        }
    }

    int maxDeadline = 0;

    for(int i=0;i<n;i++){
        if(jobs[i].deadline > maxDeadline){
            maxDeadline = jobs[i].deadline;
        }
    }

    char slot[maxDeadline + 1];

    for(int i=0; i<= maxDeadline; i++){
        slot[i] = '-';
    }

    int totalProfit = 0;

    for(int i=0; i<n; i++){
        for(int j = jobs[i].deadline; j >= 1; j--){
            if(slot[j] == '-'){
                slot[j] = jobs[i].id;
                totalProfit = totalProfit + jobs[i].profit;
                break;
            }
        }
    }

    cout << "\nScheduled Job Sequence: ";

    for (int i = 1; i <= maxDeadline; i++)
    {
        if (slot[i] != '-')
        {
            cout << slot[i] << " ";
        }
    }

    cout << "\nMaximum Profit: " << totalProfit << endl;

    return 0;
}