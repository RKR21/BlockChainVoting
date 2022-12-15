/**
 * @file blockchain.h
 * @author Rohan Rao 
 * @brief .h file for blockchain.c
 * @version 0.1
 * @date 2022-12-13
 * 
 * @copyright Copyright (c) 2022
 * 
 */

/**
 * 
 * @brief header file for blockchain
 * 
 */
#include "hash.h"

struct Block{
    int height;
    int data[10];
    struct Digest prev_hash;
    struct Block* prev_block;
};

struct Blockchain{
    struct Block* head;
    int size;
};

void set_digest(struct Digest* digest, struct Block* block);

struct Blockchain* initialize();

void add(struct Blockchain* chain, int data);

void verify(struct Blockchain* chain);

void delete_at(struct Blockchain* chain, int height);

void printf_blockchain(struct Blockchain* chain);
