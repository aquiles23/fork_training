#include <bits/stdc++.h>
using namespace std;
int main(){
    //freopen("input.txt","r",stdin);
    list <int> fifo;
    vector <pair<int,int>> frame_fault;
    int n,pag,quadro,cont = 0,fault = 0;
    bool isfault = true,belady = false;
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
    sort(frame_fault.begin(),frame_fault.end());
    for(int i = 1;i<frame_fault.size();i++){
        if(frame_fault[i].second > frame_fault[i - 1].second){
            belady =  true;
        }
    }
    if(belady){
        printf("Belady detectado\n");
    }
    else{
        printf("Sem anomalia\n");
    }
    //fclose(stdin);
    return 0;
    
}