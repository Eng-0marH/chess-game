#include "valid.h"

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

int Rook(char B[8][8], int row1, int column1, int row2, int column2){
    if(row1 != row2 && column1!=column2)
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
int Queen(char B[8][8], int row1, int column1, int row2, int column2)   
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
int whitecastle(char b[8][8],int r2,int c2);
int blackcastle(char b[8][8],int r2,int c2);

int isValid(char b[8][8],int r1,int c1,int r2,int c2,char prom,char turn,int *validprom){
    if(isupper(b[r1][c1]) && turn==0) return 0;  // turn 0 for white
    if(islower(b[r1][c1]) && turn==1) return 0;  // turn 1 for black
    if(prom!='0' && toupper(b[r1][c1])!='P') return 0;
    if( prom!='0') *validprom =1;
    if(r1==7 && c1==4 && b[7][4]=='k' && abs(c1-c2)==2) return whitecastle(b,r2,c2);
    if(r1==0 && c1==4 && b[0][4]=='K' && abs(c1-c2)==2) return blackcastle(b,r2,c2);

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