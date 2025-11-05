#include<stdio.h>
int main() {
    int n, i, time = 0, count = 0, at[20], bt[20], temp[20], ct[20], wt[20], tat[20];
    float avgwt = 0, avgtat = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        printf("Arrival & Burst time of P%d: ", i + 1);
        scanf("%d%d", &at[i], &bt[i]);
        temp[i] = bt[i];
    }

    while (count < n) {
        int min = -1;
        for (i = 0; i < n; i++)
            if (at[i] <= time && bt[i] > 0 && (min == -1 || bt[i] < bt[min]))
                min = i;

        if (min == -1) { time++; continue; }

        bt[min]--; time++;
        if (bt[min] == 0) {
            count++;
            ct[min] = time;
            tat[min] = ct[min] - at[min];
            wt[min] = tat[min] - temp[min];
            avgwt += wt[min];
            avgtat += tat[min];
        }
    }

    printf("\nP\tAT\tBT\tCT\tTAT\tWT\n");
    for (i = 0; i < n; i++)
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n", i + 1, at[i], temp[i], ct[i], tat[i], wt[i]);

    printf("\nAvg WT=%.2f  Avg TAT=%.2f\n", avgwt/n, avgtat/n);
    return 0;
}
