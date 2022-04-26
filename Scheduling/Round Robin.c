#include <stdio.h>
#include <stdlib.h>

void sort_processes_by_at(int *pid, int *at, int *bt, int *remt, int n)
{
    int i, j, temp, min;
    for (i = 0; i < n; i++)
    {
        min = i;
        for (j = i + 1; j < n; j++)
        {
            if (at[j] < at[min])
            {
                min = j;
            }
        }

        temp = at[i];
        at[i] = at[min];
        at[min] = temp;

        temp = bt[i];
        bt[i] = bt[min];
        bt[min] = temp;

        temp = pid[i];
        pid[i] = pid[min];
        pid[min] = temp;

        remt[i] = bt[i]; // since both are initially equal, extra steps are not required
        remt[min] = bt[min];
    }
}

void move_front(int *pid, int *at, int *bt, int *remt, int index) // puts value from front to another index
{
    int i, tp, ta, tb, tr;
    tp = pid[0];
    ta = at[0];
    tb = bt[0];
    tr = remt[0];

    for (i = 0; i <= index; i++)
    {
        pid[i] = pid[i + 1];
        at[i] = at[i + 1];
        bt[i] = bt[i + 1];
        remt[i] = remt[i + 1];
    }

    pid[index] = tp;
    at[index] = ta;
    bt[index] = tb;
    remt[index] = tr;
}

int check_active(int *at, int time, int n)
{
    int i, active = 0;
    for (i = 0; i < n; i++)
    {
        if (at[i] > time)
        {
            break;
        }
        else
        {
            active++;
        }
    }

    return active;
}

int main()
{
    int n, i, *pid, *at, *bt, *remt, ct, tat, wt, awt = 0, qt, time, active, last;

    printf("Enter number of processes : ");
    scanf("%d", &n);

    pid = (int *)malloc(sizeof(int) * n);
    at = (int *)malloc(sizeof(int) * n);
    bt = (int *)malloc(sizeof(int) * n);
    remt = (int *)malloc(sizeof(int) * n);

    printf("Enter pid<space>at<space>bt for each process\n");

    for (i = 0; i < n; i++)
    {
        scanf("%d", &pid[i]);
        scanf("%d", &at[i]);
        scanf("%d", &bt[i]);
        remt[i] = bt[i];
    }

    printf("Enter quantum time : ");
    scanf("%d", &qt);

    sort_processes_by_at(pid, at, bt, remt, n);

    printf("PID\tAT\tBT\tCT\tTAT\tWT\n");

    time = at[0]; // fast-forward to first relevant time
    last = n;
    active = check_active(at, time, last);
    while (last > 0)
    {
        if (active > 0)
        {
            remt[0] -= qt;
            // printf("%d\t%d\t%d\t%d\t%d\t%d\n", pid[0], at[0], bt[0], ct[0], tat, wt);
            if (remt[0] <= 0)
            {
                ct = time + remt[0] + 1; // subtracts the negative value and gives correct completion time
                // added 1 as process completes at the end of the clock cycle

                tat = ct - at[0];
                wt = tat - bt[0];
                awt += wt;
                printf("%d\t%d\t%d\t%d\t%d\t%d\n", pid[0], at[0], bt[0], ct, tat, wt);
                move_front(pid, at, bt, remt, n - 1);
                last--;
                time += qt;
                active = check_active(at, time, last);
            } // We have moved the completed process to the end of the array and reduced the number of processes we monitor by 1
            else
            {
                time += qt;
                active = check_active(at, time, last);
                move_front(pid, at, bt, remt, active - 1);
            }
        }

        else
        {
            time += qt;
            active = check_active(at, time, last);
        }
    }

    awt /= n;
    printf("Average waiting time = %d\n", awt);

    return 0;
}