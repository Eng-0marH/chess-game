#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
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
int Bishop(char B[8][8], int row1, int column1, int row2, int column2)
{
    if (abs(row2 - row1) != abs(column2 - column1))
        return 0;

    int row_direction = (row2 > row1) ? 1 : -1;
    int column_direction = (column2 > column1) ? 1 : -1;

    int r = row1 + row_direction;
    int c = column1 + column_direction;

    
    while (r != row2 && c != column2)
    {
        if (B[r][c] != '-' && B[r][c] != '.')
            return 0;   
        r += row_direction;
        c += column_direction;
    }

    char start = B[row1][column1];
    char end   = B[row2][column2];


    if (isupper(start) && isupper(end)) return 0;
    if (islower(start) && islower(end)) return 0;

    return 1;  
}
int Pawn(char B[8][8], int row1, int column1, int row2, int column2){
    if(islower(B[row1][column1])){
        if(row1==6){
            if(column1==column2 && row2==row1-2 &&
            (B[row2][column2]=='.' || B[row2][column2]=='-')&&
            (B[row2+1][column2]=='.' || B[row2+1][column2]=='-')) return 1;
            if(column1==column2 && row2==row1-1 &&
            (B[row2][column2]=='.' || B[row2][column2]=='-')) return 1;
        }
        else{
            if(column1==column2 && row2==row1-1 &&
            (B[row2][column2]=='.' || B[row2][column2]=='-')) return 1;
        }
        if(abs(column1-column2)==1){
            if(row2==row1-1 && isupper(B[row2][column2])) return 1;
        }
    }
    else{
        if(row1==1){
            if(column1==column2 && row2==row1+2 &&
            (B[row2][column2]=='.' || B[row2][column2]=='-')&&
            (B[row2-1][column2]=='.' || B[row2-1][column2]=='-')) return 1;
            if(column1==column2 && row2==row1+1 &&
            (B[row2][column2]=='.' || B[row2][column2]=='-')) return 1;
        }
        else{
            if(column1==column2 && row2==row1+1 &&
            (B[row2][column2]=='.' || B[row2][column2]=='-')) return 1;
        }
        if(abs(column1-column2)==1){
            if(row2==row1+1 && islower(B[row2][column2])) return 1;
        }
    }
    return 0;
}
int Promotion(char b[8][8],int r1,int c1,int r2,int c2,char turn){
    if(toupper(b[r1][c1])!='P') return 0;
    if(turn==0){
        if (r1==1 && r2==0)
        return Pawn(b,r1,c1,r2,c2);
    }
    else{
        if (r1==6 && r2==7)
        return Pawn(b,r1,c1,r2,c2);
    }
    return 0;
}
void move(char B[8][8], int row1, int column1, int row2, int column2,char w[16], char b[16],
    int *cW,int *cB,char prom,char turn,int validprom)
{
    if(B[row2][column2]!='.' && B[row2][column2]!='-'){
        if(islower(B[row2][column2])){
            w[*cW]=B[row2][column2];
            (*cW)++;
        }
        else{
            b[*cB]=B[row2][column2];
            (*cB)++;
        }
    }
    if(validprom && toupper(B[row1][column1])=='P'){
        B[row2][column2] = turn==0?tolower(prom):prom;
        B[row1][column1] = (row1 + column1) % 2 == 0 ? '-' : '.';
    }
    else{
        B[row2][column2] = B[row1][column1];
        B[row1][column1] = (row1 + column1) % 2 == 0 ? '-' : '.'; 
    }
}
int Rook(char B[8][8], int row1, int column1, int row2, int column2){
    if (row1 != row2 && column1!=column2)
        return 0;
        int rdi,cdi;
    if(row1==row2){
        rdi = 0;
        cdi = (column2 > column1) ? 1 : -1;
    }
    else{
        cdi=0;
        rdi= (row2 > row1) ? 1 : -1;
    }
    int r = row1 + rdi;
    int c = column1 + cdi;

    while ((r != row2  && rdi!=0) || (c != column2 && cdi!= 0))
    {
        if (B[r][c] != '-' && B[r][c] != '.')
            return 0;   
        r += rdi;
        c += cdi;
    }
    char start = B[row1][column1];
    char end   = B[row2][column2];


    if (isupper(start) && isupper(end)) return 0;
    if (islower(start) && islower(end)) return 0;

    return 1;  
    
}
int Queen(char B[8][8], int row1, int column1, int row2, int column2)  // Rook and Bishop move are available 
{
    if (Rook(B, row1, column1, row2, column2)) 
        return 1;

    if (Bishop(B, row1, column1, row2, column2)) 
        return 1;

    return 0;
}

int Knight(char B[8][8], int row1, int column1, int row2, int column2){
    int r = abs(row2 - row1);
    int c = abs(column2 - column1);
    if (!((r == 2 && c == 1) || (r == 1 && c == 2)))
        return 0;
    char start = B[row1][column1];
    char end = B[row2][column2];
    
    if (isupper(start) && isupper(end)) return 0;
    if (islower(start) && islower(end)) return 0;


    return 1;  
    
}
int King(char B[8][8], int row1, int column1, int row2, int column2){
    if(!( abs(row1-row2)<=1 && abs(column1-column2)<=1 )) return 0;
    if (row1==row2 && column1==column2) return 0;

    
    char start = B[row1][column1];
    char end = B[row2][column2];
    
    if (isupper(start) && isupper(end)) return 0;
    if (islower(start) && islower(end)) return 0;

    return 1;

}
void readmove(int *r1,int *c1,int *r2,int *c2,char *prom){
    while(1){
        char line[100];
        fgets(line,100,stdin);
        line[strcspn(line,"\n")]='\0';
        int len=strlen(line);
        if(!(len==4 || len==5)){
            printf("Invalid Input format, e.g. \"E2E4\"\n");
            continue;
        }
        if(!(toupper (line[0]) >='A' && toupper (line[0]) <='H' &&
            line[1] >= '1' && line[1] <= '8' &&
            toupper (line[2]) >='A' && toupper (line[2]) <='H' &&
            line[3] >= '1' && line[3] <= '8' &&
            ((line[4]=='\0') || (toupper(line[4])=='B') ||
            (toupper(line[4])=='Q') || (toupper(line[4])=='R') ||
            (toupper(line[4])=='N'))
            ))
            {
                printf("Invalid Input format, e.g. \"E2E4\"\n");
                continue;
            }
        *r1='8'-line[1];
        *c1=toupper(line[0])-'A';
        *r2='8'-line[3];
        *c2=toupper(line[2])-'A';
        *prom=(len==5)?toupper(line[4]):'0';
        break;
    }
}

int isValid(char b[8][8],int r1,int c1,int r2,int c2,char prom,char turn,int *validprom){
    if(isupper(b[r1][c1]) && turn==0) return 0;  // turn 0 for white
    if(islower(b[r1][c1]) && turn==1) return 0;  // turn 1 for black
    if(prom!='0' && toupper(b[r1][c1])!='P') return 0;
    if( prom!='0') *validprom =1;
        switch (toupper(b[r1][c1])){
        case '.':
           return 0;
        case '-':
            return 0;
        case 'B':
           return Bishop(b,r1,c1,r2,c2);
        case ('N'):
            return Knight(b,r1,c1,r2,c2);
        case ('R'):
            return Rook(b,r1,c1,r2,c2);
        case 'P':
            if ((turn==0 && r2==0) || (turn==1 && r2==7)) {
                if (prom == '0') return 0;
                *validprom=1;
                return Pawn(b, r1, c1, r2, c2);
            }
            if (prom != '0') return 0;
                return Pawn(b, r1, c1, r2, c2);
        case ('Q'):
            return Queen(b,r1,c1,r2,c2);
        case ('K'):
            return King(b,r1,c1,r2,c2);
    }
    
    return 0;
}

void findKing(char B[8][8], char king, int *kr, int *kc)
{
    for (int r = 0; r < 8; r++) {
        for (int c = 0; c < 8; c++) {
            if (B[r][c] == king) {
                *kr = r;
                *kc = c;
                return;
            }
        }
    }
}

int squareUnderAttack(char B[8][8], int r, int c, char turn)
{
    char attacker = 1 - turn;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {

            if (B[i][j] == '.' || B[i][j] == '-') continue;

            if (attacker == 0 && isupper(B[i][j])) continue;
            if (attacker == 1 && islower(B[i][j])) continue;

            int validprom = 0;

            if (tolower(B[i][j]) == 'p') {
            if (islower(B[i][j])) {
            if (r == i - 1 && (c == j - 1 || c == j + 1))
                return 1;
            } else {
            if (r == i + 1 && (c == j - 1 || c == j + 1))
                return 1;
            }
                continue;
            }
            if (isValid(B, i, j, r, c, '0', attacker, &validprom))
                return 1;
        }
    }
    return 0;
}

int isCheck(char B[8][8], char turn)
{
    int kr, kc;

    if (turn == 0)
        findKing(B, 'k', &kr, &kc);
    else
        findKing(B, 'K', &kr, &kc);

    return squareUnderAttack(B, kr, kc, turn);
}

void copyBoard(char src[8][8], char dst[8][8])
{
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
            dst[i][j] = src[i][j];
}


int isCheckMate(char B[8][8], char turn)
{
    if (!isCheck(B, turn)) return 0;

    char temp[8][8];

    for (int r1 = 0; r1 < 8; r1++) {
        for (int c1 = 0; c1 < 8; c1++) {

            if (B[r1][c1] == '.' || B[r1][c1] == '-') continue;

            if (turn == 0 && isupper(B[r1][c1])) continue;
            if (turn == 1 && islower(B[r1][c1])) continue;

            for (int r2 = 0; r2 < 8; r2++) {
                for (int c2 = 0; c2 < 8; c2++) {

                   
                    int validprom = 0;
                    char promotion ='0';
                    if(tolower(B[r1][c1])=='p' && (r2==0||r2==7)){
                        promotion ='Q';
                    }
                    if (!isValid(B, r1, c1, r2, c2, promotion, turn, &validprom))
                        continue;

                    copyBoard(B, temp);

                    temp[r2][c2] = temp[r1][c1];
                    temp[r1][c1] = ((r1 + c1) % 2 == 0) ? '-' : '.';

                    if (!isCheck(temp, turn))
                        return 0;  
                }
            }
        }
    }
    return 1; 
}

int isStaleMate(char B[8][8],char turn){
    if (isCheck(B, turn)) return 0;
    char temp[8][8];
    int validprom=0;
    for (int r1 = 0; r1 < 8; r1++) {
        for (int c1 = 0; c1 < 8; c1++) {

            if (B[r1][c1] == '.' || B[r1][c1] == '-') continue;
            if (turn == 0 && isupper(B[r1][c1])) continue;
            if (turn == 1 && islower(B[r1][c1])) continue;

            for (int r2 = 0; r2 < 8; r2++) {
                for (int c2 = 0; c2 < 8; c2++) {
                    char prom = '0';
                    if (tolower(B[r1][c1])=='p' && (r2==0||r2==7))
                        prom = 'Q';

                    if (!isValid(B, r1, c1, r2, c2, prom, turn, &validprom))
                        continue;

                    copyBoard(B, temp);

                    
                    temp[r2][c2] = temp[r1][c1];

                    temp[r1][c1] = '.';

                    if (!isCheck(temp, turn))
                        return 0;
                }
            }
        }
    }

    return 1;
}

int main(){

    int row1,col1,row2,col2,counterB=0,counterW=0,validprom,checkflag=0,checkmateflag=0,stalemateflag=0;
    char turn=0,prom,board[8][8],captureW[16]={},captureB[16]={};

    Board(board);

    while(1){

        showBoard(board,captureW,captureB);
        if (checkmateflag==1){
                printf("------GAME OVER------\nCheckmate! %s Wins",1-turn==0?"White":"Black");
                break;
            }
        if(stalemateflag==1){
                printf("------GAME OVER------\nStalemate! Draw");
        }
        printf("%s's Turn\n",turn==0?"White":"Black");
        if(checkflag==1){
            printf("Check!\n");
            checkflag=0;
        }

        while(1){
            validprom=0;
            readmove(&row1,&col1,&row2,&col2,&prom);

            if (!isValid(board,row1,col1,row2,col2,prom,turn,&validprom)) {
                printf("Invalid move, Try again!\n");
                continue;
            }

            char temp[8][8];
            copyBoard(board, temp);
            temp[row2][col2] = temp[row1][col1];
            temp[row1][col1] = ((row1 + col1) % 2 == 0) ? '-' : '.';

            if (isCheck(temp, turn)) {
                printf("Illegal move: King in check!\n");
                continue;
            }

            break;
        }

        move(board,row1,col1,row2,col2,
             captureW,captureB,&counterW,&counterB,
             prom,turn,validprom);

        turn = 1-turn;
        if (isCheck(board, turn)) {
            checkflag=1;
        }
        checkmateflag = isCheckMate(board, turn);
        stalemateflag = isStaleMate(board,turn);
    }
    
    return 0;
}