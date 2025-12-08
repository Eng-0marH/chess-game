#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

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
        int k='A';
        k=k+i;
        printf("%c ",k);
    }
    printf("\n");
}

void move(char B[8][8], int row1, int column1, int row2, int column2)
{
    char temp;

    temp = B[row1][column1];

    B[row2][column2] = temp;  /*  If B[row2][column2] allready a  piece will capure
                                  later add logic to save the captured piece to a list  */
    B[row1][column1] = (row1 + column1) % 2 == 0 ? '-' : '.'; 
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
int Rook(char B[8][8], int row1, int column1, int row2, int column2){
    if (row1 != row2 && column1!=column2)
        return 0;
    int row_direction = (row2 > row1) ? 1 : -1;
    int column_direction = (column2 > column1) ? 1 : -1;
    if (row1==row2) row_direction=0;
    else column_direction=0;

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
void readmove(int *r1,int *c1,int *r2,int *c2,char *prom){
    char from[3],to[4];
    int ch;
    while(1){
        scanf("%2s %3s",from,to);
        while ((ch = getchar()) != '\n' && ch != EOF);  // clean buffer
        *r1='8'-from[1];
        *c1=toupper(from[0])-'A';
        *r2='8'-to[1];
        *c2=toupper(to[0])-'A';
        *prom=(to[2]=='\0')?'\0':toupper(to[2]);
        if(*r1 >=0 && *r1 <8 && *r2 >=0 && *r2 <8 && *c1 >=0 && *c1 <8 && *c2 >=0 && *c2 <8\
        && (*prom=='\0' ||*prom=='B' ||*prom=='N' ||*prom=='Q' ||*prom=='R')){
            break;
        }
        else
        printf("Invalid move, try again!\n");
}
}

int isValid(char b[8][8],int r1,int c1,int r2,int c2,char prom,char turn){
    if(isupper(b[r1][c1]) && turn==1) return 0;  // turn 0 for white
    if(islower(b[r1][c1]) && turn==0) return 0;  // turn 1 for black
    if(prom!='\0'&& toupper(b[r1][c1])=='P') return Promotion(b,r1,c1,r2,c2);
    else{
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
        case ('P'):
            return Pawn(b,r1,c1,r2,c2);
        case ('Q'):
            return Queen(b,r1,c1,r2,c2);
        case ('K'):
            return King(b,r1,c1,r2,c2);
        }
    }
    return 0;
}

int main(){
    int row1,col1,row2,col2;
    char prom;
    char turn=0;
    char board[8][8];
    Board(board);
    //while(1){
        char *a=turn==0?"White":"Black";
        showBoard(board);
        printf("%s's Turn\n",a);
        /*while(1){
            readmove(&row1,&col1,&row2,&col2,&prom);
            if(isValid(board,row1,col1,row2,col2,prom,turn)) break;
            else printf("Invalid move, Try again!\n");
        }
        move(board,row1,col1,row2,col2);
        turn=1-turn;*/
    //}
    return 0;
}