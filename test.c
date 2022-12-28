#include "blockchain.h"
#include <stdbool.h>

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
}
    
