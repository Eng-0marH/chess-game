#include "board.h"

void captured(char c[16]){
    for(int i=0;i<16;i++){
        if(c[i]==0) break;
        printf(" %c",c[i]);
    }
}

void Board(char b[8][8]){
    char firstrow[8]={'R','N','B','Q','K','B','N','R'};
    for(int i=0;i<8;i++){
        b[0][i]=firstrow[i];
        b[1][i]='P';
        b[6][i]='p';
        b[7][i]=tolower(firstrow[i]);
    }
    for(int i=2;i<6;i++){
        for(int j=0;j<8;j++){
            b[i][j]=(i+j)%2==0?'-':'.';
        }
    }
}

void showBoard(char b[8][8],char captureW[],char captureB[]){
    printf("\n--------------------\nCaptured White:");
    captured(captureW);
    printf("\n");
    for(int i=0;i<8;i++){
        printf("%d| ",8-i);
        for(int j=0;j<8;j++){
            printf("%c ",b[i][j]);
        }
        printf("|\n");
    }
    printf("   ");
    
    for(int i=0;i<8;i++){
        int k='A';
        k=k+i;
        printf("%c ",k);
    }

    printf("\n");
    printf("Captured Black:");
    captured(captureB);
    printf("\n--------------------");
    printf("\n");
}