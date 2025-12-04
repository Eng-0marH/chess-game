#include <stdio.h>
#include <ctype.h>
void resetBoard(char b[8][8]){
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
void showBoard(char b[8][8]){
    for(int i=0;i<8;i++){
        printf("%d| ",8-i);
        for(int j=0;j<8;j++){
            printf("%c ",b[i][j]);
        }
        printf("|\n");
    }
    printf("   ");
    for(int i=0;i<8;i++){
        int k='a';
        k=k+i;
        printf("%c ",k);
    }
}
void main(){
    char turn=0;
    char board[8][8];
    Board(board);
  //  while(1){
        char *a=turn==0?"White":"Black";
        printf("%s's Turn\n",a);
        showBoard(board);
        turn=1-turn;
  //  }
}