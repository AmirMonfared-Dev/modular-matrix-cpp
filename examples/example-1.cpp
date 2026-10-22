```cpp
#include <cstdint>
#include <iostream>
#include "matrix.hpp"
using namespace std;

// Finding the nth Fibonacci number using matrix exponentiation
long long fibonacci(long long n)
{
    matrix<long long> base(2, 2);

    base[0][0] = 1;
    base[0][1] = 1;
    base[1][0] = 1;
    base[1][1] = 0;

    matrix<long long> result = base.power(n);
    return result[0][1];
}

// Finding pairs of vertices connected by a walk of length k
void printDistanceKGraph(int n, int m)
{
    matrix<long long> adjacency(n, n);

    for (int i = 1; i <= m; i++)
    {
        int u, v;
        cout << "Enter the endpoints of edge " << i << " (u v): ";

        if (!(cin >> u >> v) || u < 1 || u > n || v < 1 || v > n)
        {
            cout << "Invalid edge. Endpoints must be between 1 and n.\n";
            return;
        }

        adjacency[u - 1][v - 1] = 1;
        adjacency[v - 1][u - 1] = 1;
    }

    long long k;
    cout << "Enter k (walk length in edges): ";

    if (!(cin >> k) || k < 0)
    {
        cout << "Invalid k. It must be a non-negative integer.\n";
        return;
    }

    matrix<long long> paths = adjacency.power(k);

    cout << "Pairs connected by a walk of length " << k << ":\n";

    bool hasPair = false;

    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (paths[i][j] != 0)
            {
                cout << i + 1 << " " << j + 1 << '\n';
                hasPair = true;
            }
        }
    }

    if (!hasPair)
        cout << "No pairs found.\n";
}

int main()
{
    int op;
    cout << "1. Fibonacci number\n";
    cout << "2. Distance-k graph\n";
    cout << "Enter your choice: ";

    if (!(cin >> op))
    {
        cout << "Invalid choice.\n";
        return 0;
    }

    if (op == 1)
    {
        long long n;
        cout << "Enter n: ";

        if (!(cin >> n) || n < 0)
        {
            cout << "Invalid n. It must be a non-negative integer.\n";
            return 0;
        }

        cout << "F(n) = " << fibonacci(n) << '\n';
    }
    else if (op == 2)
    {
        int n, m;

        cout << "Enter the number of vertices: ";
        if (!(cin >> n) || n <= 0)
        {
            cout << "Invalid number of vertices. It must be positive.\n";
            return 0;
        }

        cout << "Enter the number of edges: ";
        if (!(cin >> m) || m < 0)
        {
            cout << "Invalid number of edges. It must be non-negative.\n";
            return 0;
        }

        printDistanceKGraph(n, m);
    }
    else
    {
        cout << "Invalid operation. Choose 1 or 2.\n";
    }

    return 0;
}
```
