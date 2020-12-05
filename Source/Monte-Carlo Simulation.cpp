#include <bits/stdc++.h>
using namespace std;

class Percolation{
    int n;
    bool *open;
    int *parent;
    int *rank;
    int N;

    public:
        int openCount;

        Percolation(int N){
            if(N<=0){
                cout<<"Grid size should be 1 or more";
                exit(1);
            }
            n = N*N;        
            this->N = N;    
            open = new bool[n+2];     
            for(int i=0;i<n+2;i++){
                open[i]=false;        
            }
            open[0] = true;
            open[n+1] = true;
            parent = new int[n+2];
            rank = new int[n+2];
            for(int i=0;i<n+2;i++){
                parent[i] = -1;
                rank[i] = 1;
            }
            openCount=0;
        }
            
        int findSet(int i,int parent[]){
            if(parent[i]==-1){
                return i;
            }  
            return parent[i] = findSet(parent[i],parent);
        }
    
        void unionSet(int x,int y,int parent[],int rank[]){
            int s1 = findSet(x,parent);
            int s2 = findSet(y,parent);
            
            if(s1!=s2){
                if(rank[s1]<rank[s2]){
                    parent[s1] = s2;
                    rank[s2] += rank[s1];
                }
                else{
                    parent[s2] = s1;
                    rank[s1] += rank[s2];
                }
            }
        }

        void connect(int a,int b){
            int s1 = findSet(a,parent);         //O(1)
            int s2 = findSet(b,parent);         //O(1)
                
            if(s1 != s2){
                unionSet(s1,s2,parent,rank);    //O(1)
            }
        }

        bool validate(int m) {
            if (m < 0 || m > n){
                cout<< "Incorrect location supplied!\nPlease Re-enter the cell\n";
                return false;
            }
            return true;
        }

        int getIndex(int i,int j){
            return (i-1)*N + j;
        }

        void openSite(int row,int col){
            int index = getIndex(row,col);
            if(!validate(index))
                return;
            if(open[index]) 
                return;
            open[index] = true;
            openCount++;

            // connect to top component
            if (row > 1 && open[index - N]){
                connect(index, index - N);
            }
            // connect to bottom component
            if (row < N && open[index + N]){
                connect(index, index + N);
            }
            // connect to left component
            if (col > 1 && open[index - 1]){
                connect(index, index - 1);
            }
            // connect to right component
            if (col < N && open[index + 1]){
                connect(index, index + 1);
            }
        }

        bool percolates(int source,int sink){
            if(findSet(source,parent) == findSet(sink,parent)){
                return true;
            }
            else return false;
        }
};

int main(){
    int times;
    cout<<"Enter number of times: ";
    cin>>times;
    int limit;
    cout<<"Enter the limit of Matrix size: ";
    cin>>limit;

    double sum=0,sum2=0;
    double mean;
    double deviation;
    vector<double> Xi; 

    srand((unsigned) time(0));

    for(int i=0;i<times;i++){
        int N = 10 + (rand() % limit);     
        int source = 0;
        int sink = N*N+1;       
        Percolation p(N);       
        for(int i=1;i<=N;i++){    
            p.connect(source,i);
        }       
        for(int i=(sink-N);i<sink;i++){   
            p.connect(sink,i);
        }        
        int count=0;
        while(true){       
            if(count > N*N) break;  
            int u = 1 + (rand() % N);
            int v = 1 + (rand() % N);          
            p.openSite(u,v);           
            if(p.percolates(source,sink)){
                double x = (double)p.openCount/(N*N);
                //cout<<x<<" ";
                Xi.push_back(x);
                sum += x;
                break;
            }
            count++;
        }
    }

    mean = sum/times;
    cout<<"Sample Mean: ";
    cout<<mean<<endl;
    //cout<<Xi.size()<<endl;
    for(auto ele: Xi){
    	sum2 += (ele-mean)*(ele-mean);
    }
    deviation = sum2/(times-1);
  	
  	cout.precision(6);
  	cout<<std::fixed;
  	cout<<"Variance: "<<deviation<<endl;

return 0;
}



// total time complexity O(row*col)
