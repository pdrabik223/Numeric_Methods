//
// Created by studio25 on 29.05.2021.
//
#include <iostream>
#include <array>
#include <vector>

template<size_t H, size_t W>
class mat {
public:

    mat() {
        for (auto &i:data)
            i.fill(0.0);
    }


    mat(const mat<W, H> &other) {
        unsigned height = w < other.w ? w : other.w;
        unsigned width = w < other.w ? w : other.w;


        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                data[i][j] = other.data[i][j];
            }
        }
    }

    mat &operator=(const mat<H, W> &other) {
        if (this == &other) return *this;
        data = other.data;
        return *this;
    }

    void from_vec(std::vector<std::vector<double>> in_data) {
        for (size_t x = 0; x < h; x++) {
            for (size_t y = 0; y < w; y++)
                data[x][y] = in_data[x][y];
        }
    }

    template<size_t N, size_t M>
    void from_mat(const mat<N, M> &other) {
        unsigned height = w < other.w ? w : other.w;
        unsigned width = w < other.w ? w : other.w;


        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                data[i][j] = other.data[i][j];
            }
        }
    }


    double &at(size_t x, size_t y) {
        return data[x][y];
    }

    friend std::ostream &operator<<(std::ostream &out, const mat<H, W> &ref) {
        for (size_t x = 0; x < ref.h; x++) {
            for (size_t y = 0; y < ref.w; y++)
                out << ref.data[x][y] << '\t';
            out << '\n';
        }
        return out;
    }

    const size_t w = W;
    const size_t h = H;

    std::array<std::array<double, W>, H> data;
private:


};

template<size_t N>
std::array<double, N> gaussian_elim(mat<N, N> &matrix, std::array<double, N> &array);

int main() {

    mat<3, 3> matrix;
    matrix.from_vec({
                            {2, 3, 5},
                            {3, 1, -2},
                            {1, 3, 4}
                    });
    std::array<double, 3> b = {0, -2, -3};

    gaussian_elim(matrix, b);


    // std::cout << matrix;


    return 0;
}

template<size_t N>
std::array<double, N> gaussian_elim(mat<N, N> &matrix, std::array<double, N> &array) {

    mat<N, N + 1> mat;
    mat.from_mat(matrix);

    for (int i = 0; i < N; i++)
        mat.at(i, N) = array[i];

    std::cout << mat;

    std::array<double, N> solution{};

    /* performing Gaussian elimination */
    for (int i = 0; i < N - 1; i++) {

        for (int j = i + 1; j < N; j++) {
            double f = mat.at(j, i) / mat.at(i, i);

            for (int k = 0; k < N + 1; k++)
                mat.at(j, k) -= f * mat.at(i, k);

        }
    }

    std::cout << "after Gaussian elimination:\n" << mat;


    for (int i = N - 1; i >= 0; i--) {
        solution[i] = mat.at(i, N);

        for (int j = i + 1; j < N; j++) {
            if (i != j) {

                solution[i] -= mat.at(i, j) * solution[j];
            }
        }
        solution[i] /= mat.at(i, i);
    }

    std::cout << "result:";
    for (int i = 0; i < solution.size(); i++)
        std::cout << "\nx" << i + 1 << " = " << solution[i];

    return solution;
}
