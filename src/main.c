#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#include "board.h"
#include "valid.h"

typedef struct {
    char board[8][8];
    char captureW[16];
    char captureB[16];
    int counterW;
    int counterB;
    char turn;

    int whitekingmoved;
    int whiteleftrook;
    int whiterightrook;
    int blackkingmoved;
    int blackleftrook;
    int blackrightrook;

} GameState;


#define MAX_HISTORY 200
GameState history[MAX_HISTORY];
int historyCount = 0;
int currentState = 0;

int whitekingmoved=0;
int whiteleftrook=0;
int whiterightrook=0;
int blackkingmoved=0;
int blackleftrook=0;
int blackrightrook=0;
int castlew=0;
int castleb=0;

void move(char B[8][8], int row1, int column1, int row2, int column2,char w[16], char b[16],
    int *cW,int *cB,char prom,char turn,int validprom)
{
    if((row1==0 && column1==0) || (row2==0 && column2==0)) blackleftrook=1;
    if((row1==0 && column1==7) || (row2==0 && column2==7)) blackrightrook=1;
    if((row1==7 && column1==0) || (row2==7 && column2==0)) whiteleftrook=1;
    if((row1==7 && column1==7) || (row2==7 && column2==7)) whiterightrook=1;
    if(row1==7 && column1==4) whitekingmoved=1;
    if(row1==0 && column1==4) blackkingmoved=1;
    if(castlew){
        if(column2>column1){
            B[7][7]='-';
            B[7][5]='r';}
        else{
            B[7][0]='.';
            B[7][3]='r';
        }
        castlew=0;
    }
    if(castleb){
        if(column2>column1){
            B[0][7]='.';
            B[0][5]='R';}
        else{
            B[0][0]='-';
            B[0][3]='R';
        }
        castleb=0;
    }
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

void readmove(int *r1,int *c1,int *r2,int *c2,char *prom, int *undoFlag){
    while(1){
        char line[100];
        fgets(line,100,stdin);
        line[strcspn(line,"\n")]='\0';
        
        // Check for ( u , U ) undo command
        if(strcmp(line, "u") == 0 || strcmp(line, "U") == 0){
            *undoFlag = 1;
            return;
        }
        if(strcmp(line, "r") == 0 || strcmp(line, "R") == 0){
            *undoFlag = 2; //1 for undo 2 for redo
            return;
        }
        int len=strlen(line);
        if(!(len==4 || len==5)){
            printf("Invalid Input format, e.g. \"E2E4\" or type \"u\" to undo, \"r\" to redo\n");
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
                printf("Invalid Input format, e.g. \"E2E4\" or type \"u\" to undo last move\n");
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

void saveState(char board[8][8], char captureW[16], char captureB[16], 
               int counterW, int counterB, char turn) {
    historyCount = currentState;
    if (historyCount >= MAX_HISTORY) {
        printf("History full! Cannot save more states.\n");
        return;
    }

    copyBoard (board, history[historyCount].board);
    memcpy(history[historyCount].captureW, captureW, 16);
    memcpy(history[historyCount].captureB, captureB, 16);
    history[historyCount].counterW = counterW;
    history[historyCount].counterB = counterB;
    history[historyCount].turn = turn;
    history[historyCount].whitekingmoved = whitekingmoved;
    history[historyCount].whiterightrook = whiterightrook;
    history[historyCount].whiteleftrook = whiteleftrook;
    history[historyCount].blackkingmoved = blackkingmoved;
    history[historyCount].blackrightrook = blackrightrook;
    history[historyCount].blackleftrook = blackleftrook;
    historyCount++;
    currentState++;
}


int UNDO (char board[8][8], char captureW[16], char captureB[16], 
                 int *counterW, int *counterB, char *turn) {
    if (currentState <= 1) {
        printf("No moves to undo!\n");
        return 0;
    }
    
    currentState--;
    copyBoard(history[currentState-1].board, board);
    memcpy(captureW, history[currentState-1].captureW, 16);
    memcpy(captureB, history[currentState-1].captureB, 16);
    *counterW = history[currentState-1].counterW;
    *counterB = history[currentState-1].counterB;
    *turn = history[currentState-1].turn;
    whitekingmoved = history[currentState-1].whitekingmoved;
    whiterightrook = history[currentState-1].whiterightrook;
    whiteleftrook = history[currentState-1].whiteleftrook;
    blackkingmoved = history[currentState-1].blackkingmoved;
    blackrightrook = history[currentState-1].blackrightrook;
    blackleftrook = history[currentState-1].blackleftrook;
    
    return 1;
}
int REDO(char board[8][8], char captureW[16], char captureB[16], 
         int *counterW, int *counterB, char *turn) {
    if (currentState >= historyCount) {
        printf("No moves to redo!\n");
        return 0;
    }

    copyBoard(history[currentState].board, board);
    memcpy(captureW, history[currentState].captureW, 16);
    memcpy(captureB, history[currentState].captureB, 16);
    *counterW = history[currentState].counterW;
    *counterB = history[currentState].counterB;
    *turn = history[currentState].turn;
    whitekingmoved = history[currentState].whitekingmoved;
    whiterightrook = history[currentState].whiterightrook;
    whiteleftrook = history[currentState].whiteleftrook;
    blackkingmoved = history[currentState].blackkingmoved;
    blackrightrook = history[currentState].blackrightrook;
    blackleftrook = history[currentState].blackleftrook;


    currentState++;
    return 1;
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

                    temp[r1][c1] = ((r1 + c1) % 2 == 0) ? '-' : '.';

                    if (!isCheck(temp, turn))
                        return 0;
                }
            }
        }
    }

    return 1;
}
int whitecastle(char b[8][8],int r1,int c1,int r2,int c2){
    if(whitekingmoved) return 0;
    if(isCheck(b,0)) return 0;
    char temp[8][8];
    copyBoard(b,temp);
    if(r2==7 && c2==6 && !whiterightrook && (b[7][5]== '.' || b[7][5]== '-') && (b[7][6]== '.' || b[7][6]== '-')){
        temp[7][5]='k';
        temp[7][4]='-';
        if(isCheck(temp,0)) return 0;
        temp[7][6]='k';
        temp[7][5]='-';
        if(isCheck(temp,0)) return 0;
        whitekingmoved=1;
        whiterightrook=1;
        castlew=1;
        return 1;
    } 
    if(r2==7 && c2==2 && !whiteleftrook && (b[7][3]== '.' || b[7][3]== '-' ) && (b[7][2]== '.' || b[7][2]== '-' )){
        temp[7][3]='k';
        temp[7][4]='-';
        if(isCheck(temp,0)) return 0;
        temp[7][2]='k';
        temp[7][3]='-';
        if(isCheck(temp,0)) return 0;
        whitekingmoved=1;
        whiteleftrook=1;
        castlew=1;
        return 1;
    } 
    return 0;

}
int blackcastle(char b[8][8],int r1,int c1,int r2,int c2){
    if(blackkingmoved) return 0;
    if(isCheck(b,1)) return 0;
    char temp[8][8];
    copyBoard(b,temp);
    if(r2==0 && c2==6 && !blackrightrook && (b[0][5]== '.' || b[0][5]== '-') && (b[0][6]== '.' || b[0][6]== '-')){
        temp[0][5]='K';
        temp[0][4]='-';
        if(isCheck(temp,1)) return 0;
        temp[0][6]='K';
        temp[0][5]='-';
        if(isCheck(temp,1)) return 0;
        blackkingmoved=1;
        blackrightrook=1;
        castleb=1;
        return 1;
    } 
    if(r2==0 && c2==2 && !blackleftrook && (b[0][3]== '.' || b[0][3]== '-' ) && (b[0][2]== '.' || b[0][2]== '-' )){
        temp[0][3]='K';
        temp[0][4]='-';
        if(isCheck(temp,1)) return 0;
        temp[0][2]='K';
        temp[0][3]='-';
        if(isCheck(temp,1)) return 0;
        blackkingmoved=1;
        blackleftrook=1;
        castleb=1;
        return 1;
    } 
    return 0;

}
int main(){

    int row1,col1,row2,col2,counterB=0,counterW=0,validprom,checkflag=0,checkmateflag=0,stalemateflag=0,undoFlag=0;
    char turn=0,prom,board[8][8],captureW[16]={},captureB[16]={};

    Board(board);

    
    saveState(board, captureW, captureB, counterW, counterB, turn);

    while(1){

        showBoard(board,captureW,captureB);
        if (checkmateflag==1){
                printf("------GAME OVER------\nCheckmate! %s Wins",1-turn==0?"White":"Black");
                break;
            }
        if(stalemateflag==1){
                printf("------GAME OVER------\nStalemate! Draw");
                break;
        }
        printf("%s's Turn\n",turn==0?"White":"Black");
        if(checkflag==1){
            printf("Check!\n");
            checkflag=0;
        }

        while(1){
            validprom=0;
            readmove(&row1,&col1,&row2,&col2,&prom,&undoFlag);
            
            if(undoFlag == 1){
                if(UNDO(board, captureW, captureB, &counterW, &counterB, &turn)){
                showBoard(board,captureW,captureB);
                printf("Move undone!\n");
                printf("%s's Turn\n",turn==0?"White":"Black");}

            }
            if(undoFlag == 2){
                if(REDO(board, captureW, captureB, &counterW, &counterB, &turn)){
                showBoard(board,captureW,captureB);
                printf("Move redone!\n");
                printf("%s's Turn\n",turn==0?"White":"Black");}

            }
            if(undoFlag){
                undoFlag = 0;
                continue;
            }
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

        saveState(board, captureW, captureB, counterW, counterB, turn);

        if (isCheck(board, turn)) {
            checkflag=1;
        }
        checkmateflag = isCheckMate(board, turn);
        stalemateflag = isStaleMate(board,turn);
    }
    
    return 0;
}