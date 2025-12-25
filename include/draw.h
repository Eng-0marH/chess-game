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

countboard count_pieces(char b[8][8]);

int isinsufficientmat(char b[8][8]);

#endif