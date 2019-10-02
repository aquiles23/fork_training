#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <sys/stat.h>
#include<stdlib.h>

int A[2000][2000],B[2000][2000],C[2000][2000];
int filho11 = 0,filho22 = 0,pai = 0,n;
void product(int size_l, int size_m, int size_n,int ini){
    int k,j,i;
    /*
        Description:   - Matrix multiplication AB by outer products
        Runtime:       - O(l*m*n)
        Input:         - (float **A)   Reference on input matrix A
                    - (float **B)   Refrence on input matrix B
                    - (float **C)   Reference on output matrix C
                    - (int size_l)  row length of A
                    - (int size_m)  row and col length of A and B
                    - (int size_n)  col length of B
        Output:        - void
        */ 
    
    for(k = 0; k < size_m; k++){
        for(i=ini; i < size_l; i++){
            for(j = 0; j < size_n; j++){
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}


void sigfi2(int sig){
    int i,j;
    for(i=n - n/2;i<n;i++){
        for(j = 0;j<n;j++){
            printf("%d ",C[i][j]);
            //fflush(stdout);
        }
        printf("\n");
    }
    exit(0);
}


int main(){
    int i,j,k,sig,status;
    scanf("%d",&n);
    for(i=0;i<n;i++){
        for(j = 0;j<n;j++){
            scanf("%d",&A[i][j]);
        }
    }
    for(i=0;i<n;i++){
        for(j = 0;j<n;j++){
            scanf("%d",&B[i][j]);
        }
    }
    //signal(SIGUSR1,sigfi1);
    signal(SIGUSR2,sigfi2);
    pid_t filho1 = fork(),filho2;
    if(filho1>0) filho2 = fork();
    else if(filho1 == 0){
        product(n/2,n,n,0);
        //signal(SIGUSR1,sigmaster);
        //kill(getppid(),SIGUSR1);
        //sigwait(&usr1,&sig);
        //pause();
        //printf("filho depois do usr1\n");
        //while(pai != SIGUSR1 );

        for(i=0;i<n/2;i++){
            for(j = 0;j<n;j++){
                printf("%d ",C[i][j]);
                //fflush(stdout);
            }
            printf("\n");
        }
        exit(0);
    }
    if(filho2 == 0){
        product(n,n,n,n - n/2);
        //signal(SIGUSR1,cont);
        //kill(getppid(),SIGUSR2);
        //sigwait(&usr2,&sig);
        //printf("filho depois do usr2\n");
        pause();
        //while(pai != SIGUSR2);
        
        
        exit(0);
    }
    if (filho1>0)
    {
        
        //while(filho11 !=1 );
        //pause();
        //sigwait(&usr1,&sig);
        //printf("pai depois do usr1\n");
        //kill(filho1,SIGUSR1);
        //while(filho22 !=1 );
        //pause();
        waitpid(filho1,0,0);
        //printf("pai depois do usr2\n");
        kill(filho2,SIGUSR2);
        
        wait(0);

    }
    
    return 0;
}
