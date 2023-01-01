#include <stdbool.h>
#include "blockchain.h"

void get_winner(chain, candidates[num_candidates][30]){
    
}

void election(struct Blockchain * chain, int num_candidates, char candidates[num_candidates][30]){
    char vote[30] = "";
    char name[30] = "";
    do{
        printf("Enter your name: ");
        fgets(name, 30, stdin);
        printf("%s", name);
        if(strcmp(name, "END\n") == 0){
            printf("List of votes...\n");
            printf_blockchain(chain);
            printf("\n");
            verify(chain);
            break;
        }

        printf("Cast your vote...\n");
        printf("Candidates:\n");
        
        for(int i = 0; i < num_candidates; i++){
            printf("%s", candidates[i]);
        }
        fgets(vote, 30, stdin);
        // check if valid candidate
        if(strcmp(vote, "END\n") == 0){
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


int main(void){
    char position[30];
    printf("What is the name of the position for this election?\n");
    if(fgets(position, 30, stdin) == NULL){
        printf("Position name is too long");
    }
    //scanf("%[^\n]s", position);
    printf("The position is called %s", position);
    
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
    printf("%d candidates are running\n", num_candidates);  

    // Collect candidates names
    char candidates[num_candidates][30];
    int count = 1;
    for(int i = 0; i <= num_candidates - 1; i++){
        printf("What is candidate %d's name? ", count);
        fgets(candidates[i], 30, stdin);
        count++;
    }
    printf("%s\n", candidates[0]);
    struct Blockchain* chain = initialize();
    election(chain, num_candidates, candidates);
}
    
