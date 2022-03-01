//card : 4 bits for rank, 2 bits for suit
//       --ssrrrr

typedef unsigned char card;

card make_card(int suit, int rank){

    //char is 8 bits and we are representing it in binary
    char suit_bits = suit & 0x3; // 00000011
    char rank_bits = rank & 0xF; // 00001111

    // rank & (( 1 << 4) - 1)

    return(suit_bits << 4) | rank_bits;
}

int get_rank(card c){
    return c & 0xF;
}

int get_suit(card c){
    return c >> 4;
}

/* bitwise & op

makes it 0 unless top and bottom are both 1

10001010
00001111
--------
00001010

*/
