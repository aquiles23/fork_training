#include <bits/stdc++.h>
using namespace std;
int main(){
    list <int> fifo;
    vector <pair<int,int>> frame_fault;
    int n,pag,quadro,cont = 0,fault = 0;
    bool isfault = true,belady;
    vector <int> pags(n);
    scanf("%d",&n);
    for(int i=0;i<n;i++){
        scanf("%d",&pag);
        pags[i] = pag;
    }
    while(scanf("%d",&quadro) != EOF){
        for(int x : pags){
            cont++;
            if(cont<=quadro)
                fifo.push_back(x);
            else{
                for(int y : fifo){
                    if(y==x){
                        isfault = false;
                        break;
                    }
                }
                if(isfault){
                    fault++;
                    fifo.pop_front();
                    fifo.push_back(x);
                }
            }
        }
        printf("%d %d\n",quadro,fault);
        frame_fault.push_back({quadro,fault});
        quadro = 0;
        fault = 0;
        isfault = true;
        fifo.clear();
    }


    
}