#include <stdio.h>
#include <stdlib.h>
void sort_by_at(int *pid, int *at, int *bt, int n) {
    int i, j, temp, min;
    for (i = 0; i < n; i++) {
        min = i;
        for (j = i + 1; j < n; j++) {
            if (at[j] < at[min]) {
                min = j;
            }
        }

        temp = at[i]; at[i] = at[min]; at[min] = temp;
        temp = bt[i]; bt[i] = bt[min]; bt[min] = temp;
        temp = pid[i]; pid[i] = pid[min]; pid[min] = temp;
    }
}

int main() {
    int n, i, *pid, *at, *bt, ct, tat, wt, time, awt = 0;

    printf("Enter number of processes : ");
    scanf("%d", &n);

    pid = (int *)malloc(sizeof(int) * n);
    at = (int *)malloc(sizeof(int) * n);
    bt = (int *)malloc(sizeof(int) * n);

    printf("Enter pid<space>at<space>bt for each process\n");

    for (i = 0; i < n; i++)
    {
        scanf("%d", &pid[i]);
        scanf("%d", &at[i]);
        scanf("%d", &bt[i]);
    }

    sort_by_at(pid, at, bt, n);

    printf("PID\tAT\tBT\tCT\tTAT\tWT\n");

    time = 0;
    for (i = 0; i < n; i++) {
        if (time >= at[i]) {
            time += bt[i]; // not adding 1 like RR program because here, current time is calculated by using bt of previously completed process
            ct = time;
            tat = ct - at[i];
            wt = tat - bt[i];
            awt += wt;
            printf("%d\t%d\t%d\t%d\t%d\t%d\n", pid[i], at[i], bt[i], ct, tat, wt);
        } else {
            time++;
            i--;
        }
    }

    awt /= n;
    printf("Average waiting time = %d\n", awt);

    return 0;
}