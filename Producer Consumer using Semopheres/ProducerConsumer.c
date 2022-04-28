#include<stdio.h>
int main()
{
    int buffer[10], buffsize, in, out, produce, consume, choice = 0;
    in = 0; out = 0;
    buffsize = 10;
    while(choice!=3){
        printf("1. Produce\t2. Consume\t3. Exit\n");
        printf("Enter your choice : ");
        scanf("%d", &choice);
        switch(choice){
            case 1:
                if((in+1) % buffsize == out){
                    printf("Buffer is full\n");
                } else {
                    printf("Enter the value to be produced : ");
                    scanf("%d", &produce);
                    buffer[in] = produce;
                    in = (in+1) % buffsize;
                    printf("%d is produced\n", produce);
                }
                break;
            case 2:
                if(in == out){
                    printf("Buffer is empty\n");
                } else {
                    consume = buffer[out];
                    out = (out+1) % buffsize;
                    printf("%d is consumed\n", consume);
                }
                break;
        }
    }
}