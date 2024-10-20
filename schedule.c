#include <stdio.h>

struct Process {
    int pid; // Process ID
    int arrivalTime;
    int burstTime;
    int waitingTime;
    int turnaroundTime;
    int completionTime;
};

void calculateTimes(struct Process p[], int n) {
    int currentTime = 0;
    
    for (int i = 0; i < n; i++) {
        if (currentTime < p[i].arrivalTime) {
            currentTime = p[i].arrivalTime;  // CPU is idle until process arrives
        }
        p[i].completionTime = currentTime + p[i].burstTime;
        p[i].turnaroundTime = p[i].completionTime - p[i].arrivalTime;
        p[i].waitingTime = p[i].turnaroundTime - p[i].burstTime;
        currentTime = p[i].completionTime; // Update current time
    }
}

void displayResults(struct Process p[], int n) {
    printf("\nPID\tArrival\tBurst\tCompletion\tTurnaround\tWaiting\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t\t%d\t\t%d\n", p[i].pid, p[i].arrivalTime, p[i].burstTime, 
                p[i].completionTime, p[i].turnaroundTime, p[i].waitingTime);
    }
}

void displayGanttChart(struct Process p[], int n) {
    printf("\nGantt Chart:\n");
    
    // Print top bar of Gantt chart
    printf(" ");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < p[i].burstTime; j++) {
            printf("--");
        }
        printf(" ");
    }
    printf("\n|");

    // Print process IDs in the middle
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < p[i].burstTime - 1; j++) {
            printf(" ");
        }
        printf("P%d", p[i].pid);
        for (int j = 0; j < p[i].burstTime - 1; j++) {
            printf(" ");
        }
        printf("|");
    }
    printf("\n ");

    // Print bottom bar of Gantt chart
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < p[i].burstTime; j++) {
            printf("--");
        }
        printf(" ");
    }
    printf("\n");

    // Print time indices
    printf("0");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < p[i].burstTime; j++) {
            printf("  ");
        }
        if (p[i].completionTime > 9) {
            printf("\b"); // Remove extra space for time index > 9
        }
        printf("%d", p[i].completionTime);
    }
    printf("\n");
}

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    
    struct Process p[n];
    
    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("Enter arrival time and burst time for process %d: ", p[i].pid);
        scanf("%d %d", &p[i].arrivalTime, &p[i].burstTime);
    }
    
    // Sort processes by arrival time
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (p[j].arrivalTime > p[j + 1].arrivalTime) {
                struct Process temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }
    
    calculateTimes(p, n);
    displayResults(p, n);
    displayGanttChart(p, n);
    
    return 0;
}
