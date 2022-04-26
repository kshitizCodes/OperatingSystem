#include <stdio.h>
#include <stdlib.h>

void sort_processes_by_at(int *pid, int *at, int *bt, int n)
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
    }
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

int find_shortest_active(int *at, int *bt, int time, int n) // returns index of shortest job, returns -1 if there are no active jobs
{
    int i, shortest;
    int active = check_active(at, time, n);

    if (active == 0)
    {
        return -1;
    }

    shortest = 0;

    for (i = shortest + 1; i < active; i++)
    {
        if ((bt[i] != -1) && ((bt[i] < bt[shortest]) || (bt[shortest] == -1)))
        {
            shortest = i;
        }
    }

    if (bt[shortest] == -1)
    {
        return -1;
    }

    return shortest;
}

int main()
{
    int n, i, *pid, *at, *bt, ct, tat, wt, awt = 0, time, completed = 0, s;

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

    sort_processes_by_at(pid, at, bt, n);

    printf("PID\tAT\tBT\tCT\tTAT\tWT\n");

    time = at[0]; // fast-forward to first relevant time
    while (completed < n)
    {
        s = find_shortest_active(at, bt, time, n);
        if (s != -1)
        {
            time += bt[s];
            ct = time; // solely representational
            tat = ct - at[s];
            wt = tat - bt[s];
            awt += wt;

            printf("%d\t%d\t%d\t%d\t%d\t%d\n", pid[s], at[s], bt[s], ct, tat, wt);

            bt[s] = -1;

            completed++;
        }
        else
        {
            time++;
        }
    }

    awt /= n;

    printf("Average waiting time = %d\n", awt);

    return 0;
}