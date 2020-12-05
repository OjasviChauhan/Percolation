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
            n = N*N;        // Total Cells
            this->N = N;    // Number of rows and columns


            // this array will store whether any cell is open or close
            open = new bool[n+2];     
            for(int i=0;i<n+2;i++){
                // initially all cells are closed
                open[i]=false;        
            }

            // but source and sink will remain open
            open[0] = true;
            open[n+1] = true;

            // initialization for union & find 
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

            // for(int i=0;i<n+2;i++){
            //     cout<<parent[i]<<" ";
            // }
            // cout<<endl;
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
            
            //cout<<"Index ID: "<<index<<endl;

            if(open[index]) 
                return;
            open[index] = true;
            openCount++;

            // for(int i=0;i<n+2;i++){
            //     cout<<open[i]<<" ";
            // }
            // cout<<endl;


            // connect to top component
            if (row > 1 && open[index - N]){
                //cout<<1<<endl; 
                connect(index, index - N);
            }
            // connect to bottom component
            if (row < N && open[index + N]){
                //cout<<2<<endl; 
                connect(index, index + N);
            }
            // connect to left component
            if (col > 1 && open[index - 1]){
                //cout<<3<<endl; 
                connect(index, index - 1);
            }
            // connect to right component
            if (col < N && open[index + 1]){
                //cout<<4<<endl; 
                connect(index, index + 1);
            }
        }
        
        // check the connection
        bool percolates(int source,int sink){
            if(findSet(source,parent) == findSet(sink,parent)){
                return true;
            }
            else return false;
        }
};

int main(){

    int N;               // size of matrix and how many edges or connected sites.
    cout<<"Enter the size of matrix: ";
    cin>>N;
    
    int source = 0;
    int sink = N*N+1;
    
    Percolation p(N);
    
    for(int i=1;i<=N;i++){      //connecting upper cells to source
        p.connect(source,i);
    }
    
    for(int i=(sink-N);i<sink;i++){   // connecting lower cells to sink
        p.connect(sink,i);
    }
    
    cout<<"Start Opening Sites\n";
    
    int count=0;
    while(true){       // opening sites in between
        
        if(count > N*N) break;  // Checking overflow condition for while loop
        
        int u,v;    // here u and v are row and columns
        cin>>u>>v;
        p.openSite(u,v);
        
        if(p.percolates(source,sink)){
            cout<<"\nSystem will start Percolating now"<<endl;
            cout<<"Total Open Sites: "<<p.openCount<<endl;
            cout<<"Probability Threshold: "<<(double)p.openCount/(N*N)<<endl;
            cout<<endl;
            break;
        }
        else{
            cout<<"Not Percolates yet\n";
        }
        count++;
    }
    
return 0;
}

// total time complexity O(row*col)
