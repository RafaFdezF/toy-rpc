/*
    autor: Rafael Fernandez Fleites
*/

/*
    LCS(longest common subsequence)
    Ej: abcde ace -> 3 (ace)
    N_MAX = 5000
*/

#include "../rpc.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX 5000

typedef struct {
    reportable_t parent;
    char s[MAX+1];
    char t[MAX+1];
    int dp[MAX+1][MAX+1];
    int res;
} my_struct_t;

void *parse_parameters(void *data) {
    const char *buf = (const char *)(data);
    my_struct_t *d = (my_struct_t *)(malloc(sizeof(my_struct_t)));

    if (d) {
        sscanf(buf, "%s %s", d->s+1, d->t+1);
    }

    return (void *)d;
}

void *do_work(void *data) {
    my_struct_t *d = (my_struct_t *)(data);

    int n = strlen(d->s+1);
    int m = strlen(d->t+1);

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (d->s[i] == d->t[j]) {
                d->dp[i][j] = d->dp[i-1][j-1] + 1;
            } else {
                d->dp[i][j] = (d->dp[i-1][j] > d->dp[i][j-1]) ? d->dp[i-1][j] : d->dp[i][j-1];
            }
        }
    }

    d->res = d->dp[n][m];

    return data;
}

reportable_t *report(void *data) {
    my_struct_t *d = (my_struct_t *)(data);

    d->parent.data = (char *)(malloc(255 * sizeof(char)));

    snprintf(d->parent.data, 255, "Longest common subsequence length = %d\n", d->res);
    d->parent.len = strlen(d->parent.data);

    return (reportable_t *)(data);
}

void clean_up(void *params, void *result, reportable_t *report) {
    if (report && report->data) {
        free(report->data);
    }

    if (params) {
        free(params);
    }
}
