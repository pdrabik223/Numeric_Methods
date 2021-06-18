//
// Created by studio25 on 29.05.2021.
//
#include <array>
#include <iostream>
#include <vector>

template <size_t H, size_t W> class Mat {
public:
  Mat() {
    for (auto &i : data_)
      i.fill(0.0);
  }

  Mat(const Mat<W, H> &other) {
    unsigned height = w_ < other.w_ ? w_ : other.w_;
    unsigned width = w_ < other.w_ ? w_ : other.w_;

    for (int i = 0; i < height; i++) {
      for (int j = 0; j < width; j++) {
        data_[i][j] = other.data_[i][j];
      }
    }
  }

  Mat &operator=(const Mat<H, W> &other) {
    if (this == &other)
      return *this;
    data_ = other.data_;
    return *this;
  }

  void FromVec(std::vector<std::vector<double>> in_data) {
    for (size_t x = 0; x < h_; x++) {
      for (size_t y = 0; y < w_; y++)
        data_[x][y] = in_data[x][y];
    }
  }

  template <size_t N, size_t M> void FromMat(const Mat<N, M> &other) {
    unsigned height = w_ < other.w_ ? w_ : other.w_;
    unsigned width = w_ < other.w_ ? w_ : other.w_;

    for (int i = 0; i < height; i++) {
      for (int j = 0; j < width; j++) {
        data_[i][j] = other.data_[i][j];
      }
    }
  }

  double &At(size_t x, size_t y) { return data_[x][y]; }

  friend std::ostream &operator<<(std::ostream &out, const Mat<H, W> &ref) {
    for (size_t x = 0; x < ref.h_; x++) {
      for (size_t y = 0; y < ref.w_; y++)
        out << ref.data_[x][y] << '\t';
      out << '\n';
    }
    return out;
  }

  const size_t w_ = W;
  const size_t h_ = H;

  std::array<std::array<double, W>, H> data_;

private:
};

template <size_t N>
std::array<double, N> GaussianElim(Mat<N, N> &matrix,
                                   std::array<double, N> &array);

int main() {

  Mat<3, 3> matrix;

  matrix.FromVec({{2, 3, 5}, {3, 1, -2}, {1, 3, 4}});

  std::array<double, 3> b = {0, -2, -3};

  auto solution = GaussianElim(matrix, b);

  std::cout << "result:";
  for (int i = 0; i < solution.size(); i++)
    std::cout << "\nx" << i + 1 << " = " << solution[i];

  return 0;
}

template <size_t N>
std::array<double, N> GaussianElim(Mat<N, N> &matrix,
                                   std::array<double, N> &array) {

  Mat<N, N + 1> mat;
  mat.FromMat(matrix);

  for (int i = 0; i < N; i++)
    mat.At(i, N) = array[i];

  std::cout << mat;

  std::array<double, N> solution{};

  /* performing Gaussian elimination */
  for (int i = 0; i < N - 1; i++) {

    for (int j = i + 1; j < N; j++) {
      double f = mat.At(j, i) / mat.At(i, i);

      for (int k = 0; k < N + 1; k++)
        mat.At(j, k) -= f * mat.At(i, k);
    }
  }

  std::cout << "after Gaussian elimination:\n" << mat;

  for (int i = N - 1; i >= 0; i--) {
    solution[i] = mat.At(i, N);

    for (int j = i + 1; j < N; j++) {
      if (i != j) {

        solution[i] -= mat.At(i, j) * solution[j];
      }
    }
    solution[i] /= mat.At(i, i);
  }

  return solution;
}
