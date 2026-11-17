#include <stdio.h>

int main() {
    int n, m, i, j, k;
    int nfa[10][10][10];
    int dfa[10][10];
    int count[10];

    printf("Enter number of states: ");
    scanf("%d", &n);

    printf("Enter number of symbols: ");
    scanf("%d", &m);

    printf("Enter NFA transition table:\n");

    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            printf("Number of states from q%d on symbol %d: ", i, j);
            scanf("%d", &count[i]);

            for (k = 0; k < count[i]; k++) {
                scanf("%d", &nfa[i][j][k]);
            }
        }
    }

    printf("\nDFA Transition Table:\n");

    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            printf("q%d --%d--> ", i, j);

            for (k = 0; k < count[i]; k++) {
                printf("q%d ", nfa[i][j][k]);
            }

            printf("\n");
        }
    }

    return 0;
}
