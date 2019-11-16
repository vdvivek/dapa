#include <bits/stdc++.h>
#include <pthread.h>

using namespace std;

struct data{
    int i;
    int j;
};

int mat[3][3] = {{1, 1, 2},
                 {2, 3, 4},
                 {2, 7, 5}};

int th_count = 0;

void* sub(void* x)
{
    struct data* d;
    d = (struct data*)x;
    int i = d->i;
    int j = d->j;

    int th = th_count++;
//    cout << th << "\t" << i << "\t" << j << "\t" << mat[i][j] << endl;
    int t = mat[i][j];
    mat[i][j] = mat[j][i];
    mat[j][i] = t;
}

int main()
{
    int n = 3;
    int no_of_processors = ((n*n) - n)/2;

    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
            cout << mat[i][j] << "\t";
        cout << endl;
    }

    pthread_t th[no_of_processors];
    int k = 0;
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < i; j++)
        {
            struct data d;
            d.i = i;
            d.j = j;
            struct data *x = &d;
            cout << "Thread created for mat[" << i <<  "][" << j << "] = " << mat[i][j] << endl;
            pthread_create(&th[k++], NULL, sub,(void *)x);
            for(int x = 0; x < 100; x++)
                cout << "Stalling" << endl;
        }
        cout << endl;
    }

    for(int i = 0; i < k; i++)
        pthread_join(th[i], NULL);

    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
            cout << mat[i][j] << "\t";
        cout << endl;
    }
}