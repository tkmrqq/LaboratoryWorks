#include <stdio.h>
#include <stdlib.h>
#include <time.h>

char* IsMyLifeTrash()
{
    int rnd = rand() % 2;
    return (rnd == 0) ? "Not trash" : "Trash";
    //why u reading this? (0-0)
}

int main(){
    srand(time(0));
    printf("%s", IsMyLifeTrash());
}