#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <cstddef>
#include <cstdint>
#include <initializer_list>
#include <stdexcept>
#include <type_traits>
#include <vector>

// Header-only matrix utilities for modular arithmetic.
// Values are normalized modulo Mod after construction and every operation.
// Example:
//     Matrix<long long> a{{1, 1}, {1, 0}};
//     auto result = a.pow(10);
//     auto value = result[0][1];
template <typename T, std::int64_t Mod = 1'000'000'007>
class Matrix
{
    static_assert(std::is_integral<T>::value, "Matrix requires an integral value type.");
    static_assert(Mod > 0, "Mod must be positive.");
    static_assert(Mod <= 3'037'000'499LL, "Mod is too large for safe 64-bit multiplication.");

public:
    using value_type = T;
    using row_type = std::vector<T>;
    using size_type = std::size_t;
    static constexpr std::int64_t modulus = Mod;

    Matrix() = default;

    Matrix(size_type rows, size_type columns)
        : values_(rows, row_type(columns, T{}))
    {
    }

    Matrix(std::initializer_list<std::initializer_list<T>> values)
    {
        if (values.size() == 0)
            return;

        const size_type columns = values.begin()->size();
        values_.reserve(values.size());
        for (const auto &row : values)
        {
            if (row.size() != columns)
                throw std::invalid_argument("All matrix rows must have the same length.");

            values_.emplace_back(row);
            for (T &value : values_.back())
                value = normalize(value);
        }
    }

    size_type rows() const noexcept { return values_.size(); }
    size_type columns() const noexcept { return values_.empty() ? 0 : values_.front().size(); }
    bool empty() const noexcept { return values_.empty(); }
    bool is_square() const noexcept { return rows() != 0 && rows() == columns(); }

    row_type &operator[](size_type row) { return values_.at(row); }
    const row_type &operator[](size_type row) const { return values_.at(row); }

    Matrix operator*(const Matrix &other) const
    {
        if (columns() != other.rows())
            throw std::invalid_argument("Matrix dimensions are incompatible for multiplication.");

        Matrix result(rows(), other.columns());
        for (size_type i = 0; i < rows(); ++i)
        {
            for (size_type k = 0; k < columns(); ++k)
            {
                const std::int64_t left = normalize(values_[i][k]);
                for (size_type j = 0; j < other.columns(); ++j)
                {
                    const std::int64_t right = normalize(other.values_[k][j]);
                    const std::int64_t current = normalize(result.values_[i][j]);
                    result.values_[i][j] = static_cast<T>((current + (left * right) % Mod) % Mod);
                }
            }
        }
        return result;
    }

    Matrix pow(std::uint64_t exponent) const
    {
        if (!is_square())
            throw std::invalid_argument("Only non-empty square matrices can be exponentiated.");

        Matrix result(rows(), columns());
        Matrix base = *this;
        for (size_type i = 0; i < rows(); ++i)
            result[i][i] = static_cast<T>(1 % Mod);

        while (exponent > 0)
        {
            if (exponent & 1U)
                result = result * base;
            exponent >>= 1U;
            if (exponent > 0)
                base = base * base;
        }
        return result;
    }

private:
    std::vector<row_type> values_;

    static std::int64_t normalize(T value) noexcept
    {
        std::int64_t result = static_cast<std::int64_t>(value) % Mod;
        if (result < 0)
            result += Mod;
        return result;
    }
};

// Lowercase alias keeps the original struct matrix<T> spelling available.
template <typename T, std::int64_t Mod = 1'000'000'007>
using matrix = Matrix<T, Mod>;

#endif // MATRIX_HPP
