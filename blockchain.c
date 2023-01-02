#include "blockchain.h"


//void set_digest(struct Digest* digest, struct Block* block);


/**
 * @brief Initializes a chain
 * 
 * @return struct Blockchain* 
 */
struct Blockchain* initialize(){
    struct Blockchain* chain = (struct Blockchain*)malloc(sizeof(struct Blockchain));
    chain -> position = malloc(20*sizeof(char));
    chain -> head = NULL;
    chain -> size = 0;
    chain -> position = "";
    return chain;
}

/**
 * @brief Adds blocks to chain
 * 
 * @param chain the struct Blockchain* to add a block to
 * @param candidate the name of the person who was voted for
 * @param voter the name of the person who voted
 */
void add(struct Blockchain* chain, char * candidate, char * voter){
    struct Block* newBlock = malloc(sizeof(struct Block));
    //chain -> size++;
    newBlock -> height = chain -> size;
    // increment chains size
    chain -> size++;
    strncpy(newBlock -> data, candidate, 30);
    strncpy(newBlock -> name, voter, 30);

    // if this block is the first block, set prev_hash to zeros
    if(chain -> size == 1){
        struct Digest prevHash = {0, 0, 0, 0, 0};
        newBlock -> prev_hash = prevHash;
    } else{
        // get copy of head block
        struct Block * headOfChain = chain -> head;
        // get data of head and store in variable to pass to SHA
        char * header_candidate = headOfChain -> data;
        // calculate hash of head
        const unsigned char * digest = SHA_40(header_candidate, newBlock -> height, strlen(header_candidate));
        // store hash of head in prevHash, then give it to newBlock -> prev_hash
        struct Digest prevHash;
        prevHash.hash0 = digest[0];
        prevHash.hash1 = digest[1];
        prevHash.hash2 = digest[2];
        prevHash.hash3 = digest[3];
        prevHash.hash4 = digest[4];
        newBlock -> prev_hash = prevHash;

    }
    // make newest blocks previous block the head of the chain, then make newest block the head
    newBlock -> prev_block = chain -> head;
    chain -> head = newBlock;
}

void verify(struct Blockchain* chain){
    printf("Verifying...\n");
    int pass_fail = 0;
    struct Block * current = chain -> head;
    for(int i = current -> height; i > 0; i--){
        struct Block * previous = current -> prev_block;
        
        // collect calculated hash of previous block
        unsigned char * calculate = SHA_40(previous -> data, previous -> height, strlen(previous -> data));
        struct Digest temp;
        struct Digest * calculated;
        temp.hash0 = calculate[0];
        temp.hash1 = calculate[1];
        temp.hash2 = calculate[2];
        temp.hash3 = calculate[3];
        temp.hash4 = calculate[4];
        calculated = &temp;
        
        // collect stored hash of previous block
        struct Digest prevHash = current -> prev_hash;
        struct Digest * stored = &prevHash;
        int n = digest_equal(stored, calculated);
        
        // check if calculated and stored hashes are the same
        if(digest_equal(stored, calculated) == 1){
            printf("Block %d passed\n", i);
        } else if(digest_equal(stored, calculated) == 0){
            printf("Block %d failed\n", i);
            printf("Block %d and/or block %d may have been tampered with\n", i, i - 1);
            pass_fail++;
        }
        if(pass_fail == 0){printf("All blocks have been verified\n");}
        current = current -> prev_block;

    }
}

//void delete_at(struct Blockchain* chain, int height, char * name);



void printf_blockchain(struct Blockchain* chain){
    printf("Printing...\n");
    struct Block * current = chain -> head;
    while(current){
        printf("{ID: %d, vote: %s, name: %s, prev_hash: %d %d %d %d %d}\n", current -> height,
        current -> data, current -> name, current -> prev_hash.hash0, current -> prev_hash.hash1,
        current -> prev_hash.hash2, current -> prev_hash.hash3, current -> prev_hash.hash4);

        current = current -> prev_block;
    }


} // print all info in each block of the blockchain
/**
int main(void){
    struct Blockchain* blockchain = initialize();
    add(blockchain, "Donald J. Trump", "Reggie Kaustas");
    add(blockchain, "Nairo Quazada", "Joe Joplin");
    printf_blockchain(blockchain);
    verify(blockchain);
    
}
*/