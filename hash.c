#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"


unsigned char* SHA_40(const unsigned char* msg, size_t length){
    unsigned char A;
	unsigned char B;
	unsigned char C;
	unsigned char D;
	unsigned char E;

    A = 11;
    B = 22;
    C = 33;
    D = 44;
    E = 55;

    for(int i = 0; i < length; i++){
        for(int j = 0; j < 12; j++){
            unsigned char F = (B & C) ^ D;
            int old_A = A;

            A = E + F + (A >> 3) + msg[i] + j;
            E = D;
            D = C;
            C = (B<<1);
            B = B = old_A;
            
        }
    }
    unsigned char * digest = (unsigned char*)malloc(5*sizeof(unsigned char));
    digest[0] = A;
    digest[1] = B;
    digest[2] = C;
    digest[3] = D;
    digest[4] = E;
    return digest;


} //SHA_40 hash function

int digest_equal(struct Digest* digest1, struct Digest* digest2){
    return digest1->hash0 == digest2->hash0 && digest1->hash1 == digest2->hash1 &&
    digest1->hash2 == digest2->hash2 && digest1->hash3 == digest2->hash3 && 
    digest1->hash4 == digest2->hash4;
} //Returns 1 (true) or 0 (false)

void print_hash(struct Digest* digest){
    printf("%d ", digest->hash0);
	printf("%d ", digest->hash1);
	printf("%d ", digest->hash2);
	printf("%d ", digest->hash3);
	printf("%d\n", digest->hash4);
} //Prints hash

int main(void){
    unsigned char* str = "Rob";
    unsigned char* str2 = "Rob";
    unsigned char* digest1 = SHA_40(str, strlen(str));
    unsigned char* digest2 = SHA_40(str2, strlen(str2));
    print_hash((struct Digest*)digest2);
    
    
    return 0;
}