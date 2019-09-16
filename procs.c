#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<string.h>
#include <sys/wait.h>
#include <signal.h>
//#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <stdlib.h>

//usando esta função eu posso compartilhar variaveis entre os processos
void* create_shared_memory(size_t size) {
    int protection = PROT_READ | PROT_WRITE;
    int visibility = MAP_SHARED | MAP_ANONYMOUS;
    return mmap(NULL, size, protection, visibility, -1, 0);
}

int main(int argc, char argv[]){
    int i=0,j=0,*tam,segid;
    char ent[20];
    tam = create_shared_memory(sizeof *tam);
    
    scanf("%s",ent);

    char *minus = create_shared_memory(sizeof ent),
         *maius = create_shared_memory(sizeof ent),
         *conso = create_shared_memory(sizeof ent);

    pid_t fok1,fok2,fok3 = 1;
    fok1 = fork();
    fok2 = fork();
    /* meus processos(ids hipotéticos) tem essa hierarquia a partir deste ponto:
        1001
       /    \
    1002     1003
                \
                1005

    */

    if(fok2 == 0 && fok1 == 0){ // o 1005 pega o tamanho
        *tam = strlen(ent);
    }

    if(fok2 == 0 && fok1 > 0){ // 1002
        for(i=0;i<3;i++){
            
            if(fok3 > 0) // 1002
                
                fok3 = fork();
            if (fok3 == 0){
                switch (i)
                {
                case 0:
                    //aqui removo os char minusculos
                    j = 0;
                    for(i=0;i<strlen(ent);i++){
                        if(ent[i]<=90){
                            maius[j]=ent[i];
                            j++;
                        }
                    }
                    break;
                case 1:
                    //aqui removo os char maiusculos
                    j = 0;
                    for(i=0;i<strlen(ent);i++){
                        if(ent[i]>96){
                            minus[j]=ent[i];
                            j++;
                        }
                    }
                    break;
                case 2:
                    j = 0;
                    for(i=0;i<strlen(ent);i++){
                        if(ent[i]!='a'&&ent[i]!='e'
                        &&ent[i]!='i'&& ent[i]!='o'
                        &&ent[i]!='u'&&ent[i]!='A'
                        &&ent[i]!= 'E'&&ent[i]!='I'
                        &&ent[i]!='O'&&ent[i]!='U'){
                            conso[j]=ent[i];
                            j++;
                        }
                    }
                    break;
                default:
                    printf("isto não pode acontecer\n");
                    break;
                }
            }
        }
    }
    /* meus processos(ids hipotéticos) tem essa hierarquia a partir deste ponto:
        1001
       /    \
    1002     1003
   /  |  \         \
1004 1006 1007      1005

    */

    if(fok2 > 0 && fok1 > 0 && fok3>0){ //  1001
        //faz o 1001 esperar para que não morra antes dos outros.
        sleep(3);
        //wait(NULL);
        printf("tamanho da string %d\n",*tam);
        printf("a string %s sem char maiusculo resulta em: %s\n",ent,minus);
        printf("a string %s sem as vogais resulta em: %s\n",ent,conso);
        printf("a string %s sem char minusculo resulta em: %s\n",ent,maius);
    } 
    //printf("pai %d e filho %d\n",getppid(),getpid());
    return 0;
}