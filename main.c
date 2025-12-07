#include <stdio.h>
#include <ctype.h>
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
        int k='a';
        k=k+i;
        printf("%c ",k);
    }
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