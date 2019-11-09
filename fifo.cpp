#include <bits/stdc++.h>
using namespace std;
int main(){
    list <int> fifo;
    vector <pair<int,int>> frame_fault;
    int n,pag,quadro,cont = 0,fault = 0;
    bool isfault = true,belady;
    scanf("%d",&n);
    vector <int> pags(n);
    for(int i=0;i<n;i++){
        scanf("%d",&pag);
        pags[i] = pag;
    }
    while(scanf("%d",&quadro) != EOF){
        for(int x : pags){
            if(!fifo.empty())
                for(int y : fifo){
                    if(y==x){
                        isfault = false;
                        break;
                    }
                }
            if(isfault){
                fault++;
                //printf("page faut em %d\n",x);
                if(cont<quadro){
                    fifo.push_back(x);
                    cont ++;
                }
                else{
                    fifo.pop_front();
                    fifo.push_back(x);
                }
            }
            isfault = true;
        }
        printf("%d %d\n",quadro,fault);
        frame_fault.push_back({quadro,fault});
        quadro = 0;
        fault = 0;
        //isfault = true;
        cont = 0;
        fifo.clear();
    }

    return 0;
    
}

/*
   1 2 3 4 1 2 5 1 2 3 4 5
 0 1 1 1 4 4 4 5 5 5 5 5 5 
 1   2 2 2 1 1 1 1 1 3 3 3
 2     3 3 3 2 2 2 2 2 4 4
         x x x x     x x
*/