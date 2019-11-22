#include <bits/stdc++.h>
#include <thread>

using namespace std;

struct data
{
    int i;
    int j;
    int mid;
};

int a[2][2] = {{1,2}, {3,4}};
int b[2][2] = {{5,6},{7,8}};
int c[2][2] = {0};

void *crcw(void* x)
{
    struct data *d;
    d = (struct data*)x;
    int i = d->i;
    int j = d->j;
    int k = d->mid;

    c[i][j] += a[i][k] * b[k][j];
}

int main()
{
    int n = 2;
    int no_of_threads = n * n * n;

    pthread_t thr[no_of_threads];

    int l = 0;

    for(int i = 0; i < 2; i++)
    {
        for(int j = 0; j < 2; j++)
        {
            for(int k = 0; k < 2; k++)
            {
                struct data t;
                t.i = i;
                t.j = j;
                t.mid = k;
                struct data * d = &t;
                pthread_create(&thr[l++], NULL, crcw, (void*)d);
                for(int x = 0; x < 100; x++)
                    cout << "Stalling" << endl;
            }
        }
    }

    for(int i = 0; i < l; i++)
        pthread_join(thr[i], NULL);

    for(int i = 0; i < 2; i++)
    {
        for(int j = 0; j < 2; j++)
            cout << c[i][j] << "\t";
        cout << endl;
    }
}