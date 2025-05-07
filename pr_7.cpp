#include <iostream>
using namespace std;
int main() {
int ip, row, col, n, mincost;
cout<<"Enter the number of vertices: "; cin>>n;
int visited[n], cost[n][n];
string name[n];
string city;
for(int i=0; i<n; i++) {
cout<<"\nEnter name of cities: "; cin>>city;
name[i]= city;
visited[i]=0; //initialize cost to -1
for(int j=0; j<n; j++) {
cost[i][j]=-1; //initialize cost to -1
}
}
for(int i=0; i<n; i++) {

for(int j=i+1; j<n; j++) {
char c;
cout<<"\nEnter 'y' if edge is present between "<< name[i]<<" & "<<name[j]<<": ";
cin>>c;
if(c=='y') {
cout<<"\nEnter the cost: "; cin>>ip;
cost[i][j]=cost[j][i]= ip;
}
}
}
cout<<"\nAdjacency Representation: \n      ";
for(int i=0; i<n; i++) {
cout<<name[i]<<"        ";
}
for(int i=0; i<n; i++) {
cout<<endl<<name[i]<<"      ";
visited[i]=0;
for(int j=0; j<n; j++) {
cout<<cost[i][j]<<"    ";
}
}
mincost=0;
visited[0]=1;
for(int k=0; k<n-1; k++) {
int min=999999999;
for(int i=0; i<n; i++) {
for(int j=0; j<n; j++) {
if(visited[i]==1 && visited[j]!=1) {
if(cost[i][j] != -1 && min> cost[i][j]) {
min=cost[i][j];
row=i;
col=j;
}
}
}
}

visited[col]=1;
mincost += min;
cout<<"\n "<<name[row]<<"-->"<<name[col];
cost[row][col]= cost[col][row]=-1;
}
cout<<"\nThe min cost: "<<mincost<<" Rupees";
}

