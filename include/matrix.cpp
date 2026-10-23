#pragma once

#include <bits/stdc++.h>

const long long mod = 1e9 + 7;

template <typename T>
class matrix
{
private:
    std::vector<std::vector<T>> a;

public:
    matrix(int n, int m)
    {
        a = std::vector<std::vector<T>>(n, std::vector<T>(m, 0));
    }

    std::vector<T> &operator[](int index)
    {
        return a[index];
    }

    const std::vector<T> &operator[](int index) const
    {
        return a[index];
    }

    matrix<T> operator*(const matrix &b) const
    {
        int n = a.size();
        int m = b.a.size();

        if (n == 0 || m == 0)
        {
            throw std::invalid_argument("Error: Cannot multiply empty matrices.");
        }

        int p = a[0].size();
        int q = b[0].size();

        for (int i = 0; i < a.size(); i++)
        {
            if (a[i].size() != p)
            {
                throw std::invalid_argument("Error: Matrix rows have inconsistent column counts.");
            }
        }

        for (int i = 0; i < b.a.size(); i++)
        {
            if (b[i].size() != q)
            {
                throw std::invalid_argument("Error: Matrix rows have inconsistent column counts.");
            }
        }

        if (p != m)
        {
            throw std::invalid_argument("Error: Incompatible dimensions for matrix multiplication.");
        }

        matrix<T> ans(n, q);

        for (int i = 0; i < a.size(); i++)
        {
            for (int j = 0; j < b[0].size(); j++)
            {
                for (int k = 0; k < a[0].size(); k++)
                {
                    long long x = a[i][k] % mod;
                    long long y = b[k][j] % mod;
                    ans[i][j] = (ans[i][j] + (x * y) % mod) % mod;
                }
                ans[i][j] += (ans[i][j] < 0 ? mod : 0);
            }
        }

        return ans;
    }

    matrix<T> power(long long k) const
    {
        int n = a.size();

        if (n == 0)
        {
            throw std::invalid_argument("Cannot calculate power of an empty matrix.");
        }

        for (int i = 0; i < n; i++)
        {
            if (a[i].size() != n)
            {
                throw std::invalid_argument("Matrix must be square.");
            }
        }

        if (k < 0)
        {
            throw std::invalid_argument("Exponent must be non-negative.");
        }

        matrix<T> base(n, n), ans(n, n);

        for (int i = 0; i < n; i++)
        {
            base[i][i]++;
            for (int j = 0; j < n; j++)
            {
                ans[i][j] = a[i][j];
            }
        }

        while (k != 0)
        {
            if (k % 2 == 1)
            {
                base = base * ans;
            }

            k /= 2;
            ans = ans * ans;
        }

        return base;
    }
};
