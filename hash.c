
#include "hash.h"

/**
 * @brief Hash function. Generates unique hash from given data. 
 * 
 * @param msg data to give to hash function
 * @param height more data to give to hash function(makes sure hash is unique)
 * @param length length of the msg
 * @return unsigned* char return Digest
 */
unsigned char* SHA_40(char* msg, int height, size_t length){
    // turn height into unsigned char
    unsigned char ID[5];
    snprintf((char*)ID, 5, "%d", height);
    //unsigned char* unsignedmsg = (unsigned char *) msg;
    //unsigned char* unsignedID = (unsigned char *) ID;

    // concatenate ID and msg
    unsigned char message[length + 4];
    snprintf((char*)message, length, "%s", msg); 

    int j = length;
    for(int i = 0; i < length; i++){
        message[j] = ID[i];
        j++;
    }
    //printf("%s\n", message);

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

            A = E + F + (A >> 3) + message[i] + j;
            E = D;
            D = C;
            C = (B<<1);
            B = old_A;
            
        }
    }
    unsigned char * digest = (unsigned char*)malloc(5*sizeof(unsigned char));
    digest[0] = A;
    digest[1] = B;
    digest[2] = C;
    digest[3] = D;
    digest[4] = E;
    return digest;


} 
/**
 * @brief Checks if two hashes are equal
 * 
 * @param digest1 one digest to compare
 * @param digest2 another digest to compare
 * @return int return 1 if true or 0 if false
 */
int digest_equal(struct Digest* digest1, struct Digest* digest2){
    return digest1->hash0 == digest2->hash0 && digest1->hash1 == digest2->hash1 &&
    digest1->hash2 == digest2->hash2 && digest1->hash3 == digest2->hash3 && 
    digest1->hash4 == digest2->hash4;
} 
/**
 * @brief Prints hash value 
 * 
 * @param digest hash value to print
 */
void print_hash(struct Digest* digest){
    printf("%d ", digest->hash0);
	printf("%d ", digest->hash1);
	printf("%d ", digest->hash2);
	printf("%d ", digest->hash3);
	printf("%d\n", digest->hash4);
} 
/**
int main(void){
    char* str = "Carmelo";
    int ID = 56;
    unsigned char* digest1 = SHA_40(str, ID, strlen(str));

    print_hash((struct Digest*)digest1);
    //unsigned char* str2 = "Rob";
    //unsigned char* digest1 = SHA_40(str, strlen(str));
    //unsigned char* digest2 = SHA_40(str2, strlen(str2));
    //print_hash((struct Digest*)digest2);
    
    
    return 0;
}
*/