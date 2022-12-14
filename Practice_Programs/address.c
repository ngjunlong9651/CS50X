# include <stdio.h>

int main(void)
{
    int n = 50;
    int *p = &n;
    printf("%p\n", p); //Need to change %p if you wanna print pointer
}