#ifndef DRAW_H
#define DRAW_H

typedef struct {

    int count_r;
    int count_q;
    int count_n;
    int count_b;
    int count_R;
    int count_Q;
    int count_N;
    int count_B;
    int count_p;
    int count_P;
    int count_total;
} countboard;

countboard count_pieces(char b[8][8]){
    // this function doesn't count kings
    countboard c;
    c.count_r=0;
    c.count_p=0;
    c.count_P=0;
    c.count_b=0;
    c.count_n=0;
    c.count_q=0;
    c.count_R=0;
    c.count_B=0;
    c.count_N=0;
    c.count_Q=0;
    c.count_total=0;
    for(int i=0;i<8;i++){
        for(int j=0;j<8;j++){
            if(b[i][j]=='.'||b[i][j]=='-'){
                continue;
            }
            switch (b[i][j])
            {
            case 'r':
                c.count_r++;
                break;
            case 'n':
                c.count_n++;
                break;
            case 'b':
                c.count_b++;
                break;
            case 'q':
                c.count_q++;
                break;
            case 'R':
                c.count_R++;
                break;
            case 'N':
                c.count_N++;
                break;
            case 'B':
                c.count_B++;
                break;
            case 'Q':
                c.count_Q++;
            case 'P':
                c.count_P++;
                break;
            case 'p':
                c.count_p++;
                break;

            default: 
                break;
            }

        }
    }
    c.count_total=c.count_B+c.count_b+c.count_N+c.count_n+c.count_r+c.count_R+c.count_Q+c.count_q;
    return c;
}

int isinsufficientmat(char b[8][8]){
    countboard c= count_pieces(b);
    if(c.count_total>=2) return 0;
    if(c.count_P || c.count_p || c.count_Q || c.count_q || c.count_r || c.count_R) return 0;
    if(c.count_total==0) return 1;
    if(c.count_total==1){
        if(c.count_b || c.count_B || c.count_n || c.count_N) return 1;
    }
    return 0;
}

#endif