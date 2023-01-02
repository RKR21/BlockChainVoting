#include <stdbool.h>
#include "blockchain.h"
/**
 * @brief Print winner of election
 * 
 * @param chain chain that represents election votes
 * @param num_candidates number of candidates 
 * @param candidates candidates names
 */
void get_winner(struct Blockchain * chain, int num_candidates, char candidates[num_candidates][30]){
    int num_votes[6];
    struct Block * current = chain -> head;
    
    while(current -> height != 0){
        for(int i = 0; i < num_candidates; i++){
            if(strcmp(current -> data, candidates[i]) == 0){
                num_votes[i] += 1;
                
            }
            
        }
        current = current -> prev_block;
    }
    
    int winner = 0;
    int highest = 0;
    for(int j = 0; j < num_candidates; j++){
        for(int k = j; k <= num_candidates; k++){
            if(num_votes[k] > highest){
                winner = k;
                highest = num_votes[k];
            }
        }
        
    }
    printf("Winner is %s with %d votes!\n", candidates[winner], highest);
}
/**
 * @brief Runs election. Repeatedly asks for voter name and vote.
 * 
 * @param chain chain representing election votes
 * @param num_candidates number of candidates in election
 * @param candidates names of candidates
 */
void election(struct Blockchain * chain, int num_candidates, char candidates[num_candidates][30]){
    char vote[30] = "";
    char name[30] = "";
    add(chain, "Junk", "Junk"); // Not counting the first block
    do{
        printf("Enter your name: ");
        fgets(name, 30, stdin);
        name[strlen(name) - 1] = '\0';
        printf("%s. ", name);
        if(strcmp(name, "END") == 0){
            printf("List of votes...\n");
            printf_blockchain(chain);
            printf("\n");
            verify(chain);
            break;
        }

        printf("Cast your vote...\n");
        printf("Candidates:\n");
        
        for(int i = 0; i < num_candidates; i++){
            if(i == num_candidates - 1){
                printf("%s\n", candidates[i]);
            } else{
                printf("%s, ", candidates[i]);
            }
            
        }
        fgets(vote, 30, stdin);
        vote[strlen(vote) - 1] = '\0';
        printf("%s\n", vote);
        // check if valid candidate
        if(strcmp(vote, "END") == 0){
            printf("List of votes...\n");
            printf_blockchain(chain);
            printf("\n");
            verify(chain);
            break;
        }
        
        if(strcmp(vote, candidates[0])==0||strcmp(vote, candidates[1])==0||strcmp(vote, candidates[2])==0
        ||strcmp(vote, candidates[3])==0||strcmp(vote, candidates[4])==0||strcmp(vote, candidates[5]) == 0){
            add(chain, vote, name);
            printf("Thank you for voting. Type <END> to end this election.\n");
        } else{
            printf("Invalid candidate... Recast vote.\n");
        }
        } while(strcmp(vote, "END") != 0 || strcmp(name, "END") != 0);
    }

/**
 * @brief runs election and calls election functions
 * 
 * @return int 
 */
int main(void){
    char position[30];
    printf("What is the name of the position for this election?\n");
    if(fgets(position, 30, stdin) == NULL){
        printf("Position name is too long");
    }
    //scanf("%[^\n]s", position);
    
    
    char num[3];
    int num_candidates;
    do{
        printf("How many candidates are running?\n");
        fgets(num, 3, stdin);
        num_candidates = atoi(num);
        
        if(num_candidates > 6){
            printf("Error: Too many candidates. Six or less.\n");
        } 

    } while (num_candidates > 6);
      

    // Collect candidates names
    char candidates[num_candidates][30];
    int count = 1;
    for(int i = 0; i <= num_candidates - 1; i++){
        printf("What is candidate %d's name? ", count);
        fgets(candidates[i], 30, stdin);
        candidates[i][strlen(candidates[i]) - 1] = '\0';
        count++;
    }
    struct Blockchain* chain = initialize();
    election(chain, num_candidates, candidates);
    get_winner(chain, num_candidates, candidates);
}
    
