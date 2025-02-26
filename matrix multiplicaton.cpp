#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <random>
#include <cassert>

class Matrix {
private:
    int rows_;
    int cols_;
    std::vector<double> data_;

public:
    Matrix(int rows, int cols) : rows_(rows), cols_(cols), data_(rows * cols) {}

    double& operator()(int i, int j) { return data_[i * cols_ + j]; }
    const double& operator()(int i, int j) const { return data_[i * cols_ + j]; }

    int rows() const { return rows_; }
    int cols() const { return cols_; }
    std::vector<double>& data() { return data_; }
    const std::vector<double>& data() const { return data_; }
};

Matrix multiply_single_thread(const Matrix& A, const Matrix& B) {
    assert(A.cols() == B.rows());
    Matrix C(A.rows(), B.cols());
    for (int i = 0; i < A.rows(); ++i) {
        for (int j = 0; j < B.cols(); ++j) {
            double sum = 0;
            for (int k = 0; k < A.cols(); ++k) {
                sum += A(i, k) * B(k, j);
            }
            C(i, j) = sum;
        }
    }
    return C;
}

void multiply_partial(const Matrix& A, const Matrix& B, Matrix& C, int start_row, int end_row) {
    for (int i = start_row; i < end_row; ++i) {
        for (int j = 0; j < B.cols(); ++j) {
            double sum = 0;
            for (int k = 0; k < A.cols(); ++k) {
                sum += A(i, k) * B(k, j);
            }
            C(i, j) = sum;
        }
    }
}

Matrix multiply_multi_thread(const Matrix& A, const Matrix& B, int num_threads) {
    assert(A.cols() == B.rows());
    Matrix C(A.rows(), B.cols());

    std::vector<std::thread> threads;
    int rows_per_thread = A.rows() / num_threads;
    int remaining_rows = A.rows() % num_threads;

    int start_row = 0;
    for (int i = 0; i < num_threads; ++i) {
        int end_row = start_row + rows_per_thread + (i < remaining_rows ? 1 : 0);
        threads.emplace_back(multiply_partial, std::cref(A), std::cref(B), std::ref(C), start_row, end_row);
        start_row = end_row;
    }

    for (auto& thread : threads) {
        thread.join();
    }

    return C;
}

void fill_matrix_random(Matrix& M) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.0, 10.0);
    for (int i = 0; i < M.rows(); ++i) {
        for (int j = 0; j < M.cols(); ++j) {
            M(i, j) = dis(gen);
        }
    }
}

int main() {
    int size = 500; // Set large size for benchmarking
    Matrix A(size, size);
    Matrix B(size, size);
    fill_matrix_random(A);
    fill_matrix_random(B);

    auto start = std::chrono::high_resolution_clock::now();
    Matrix C_single = multiply_single_thread(A, B);
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "Single-threaded multiplication time: " 
              << std::chrono::duration<double>(end - start).count() << " seconds\n";

    int num_threads = std::thread::hardware_concurrency();
    start = std::chrono::high_resolution_clock::now();
    Matrix C_multi = multiply_multi_thread(A, B, num_threads);
    end = std::chrono::high_resolution_clock::now();
    std::cout << "Multi-threaded multiplication time (" << num_threads << " threads): " 
              << std::chrono::duration<double>(end - start).count() << " seconds\n";

    return 0;
}

