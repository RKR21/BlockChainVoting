#include <stdbool.h>
#include "blockchain.h"

int main(void){
    char position[30];
    printf("What is the name of the position for this election?\n");
    if(fgets(position, 30, stdin) == NULL){
        printf("Position name is too long");
    }
    //scanf("%[^\n]s", position);
    printf("The position is called %s", position);
    int n = 0;
    n++;
    printf("%d\n", n);
}
    
