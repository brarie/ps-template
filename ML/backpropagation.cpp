#include <bits/stdc++.h>

using namespace std;

const int DATA_ROW = 5;
const int DATA_COL = 6;
const int RABEL_SZ = 3;

using Vector = vector<double>;
using Matrix = vector<vector<double>>;

Matrix A_data = {
    {
        0, 0, 1, 1, 0, 0,
        0, 1, 0, 0, 1, 0,
        1, 1, 1, 1, 1, 1,
        1, 0, 0, 0, 0, 1,
        1, 0, 0, 0, 0, 1
    }
};

Matrix B_data = {
    {
        0, 1, 1, 1, 1, 0,
        0, 1, 0, 0, 1, 0,
        0, 1, 1, 1, 1, 0,
        0, 1, 0, 0, 1, 0,
        0, 1, 1, 1, 1, 0
    }
};

Matrix C_data = {
    {
        0, 1, 1, 1, 1, 0,
        0, 1, 0, 0, 0, 0,
        0, 1, 0, 0, 0, 0,
        0, 1, 0, 0, 0, 0,
        0, 1, 1, 1, 1, 0
    }
};

Matrix A_test = {
    {
        0, 0, 1, 1, 0, 0,
        0, 1, 0, 0, 1, 0,
        1, 1, 0, 1, 0, 1,
        1, 0, 1, 0, 0, 1,
        1, 0, 0, 0, 0, 1
    }
};

Matrix B_test = {
    {
        0, 1, 1, 1, 1, 0,
        0, 1, 0, 1, 1, 0,
        0, 1, 1, 1, 1, 0,
        0, 1, 0, 1, 1, 0,
        0, 1, 1, 1, 1, 0,
    }
};

Matrix C_test = {
    {
        0, 0, 0, 1, 1, 0,
        0, 1, 0, 0, 0, 0,
        0, 1, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0,
        0, 1, 1, 1, 1, 0
    }
};

Matrix y = {
    {1, 0, 0},
    {0, 1, 0},
    {0, 0, 1}
};

Matrix new_Matrix(int N, int M) {
    return vector<vector<double>>(N, vector<double>(M, 0));
}

Matrix operator * (const Matrix x, const Matrix y) {
    int N = x.size();
    int M = y.size();
    int K = y[0].size();
    assert(x[0].size() == M);
    Matrix ret = new_Matrix(N, K);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            for (int k = 0; k < K; k++) {
                ret[i][k] += x[i][j] * y[j][k];
            }
        }
    }

    return ret;
}

void printMatrix(Matrix x) {
    cout << "Matrix Print: " << "\n";
    for (Vector &vec : x) {
        for (auto &elem : vec) {
            cout << elem << " ";
        }
        cout << "\n";
    }
}

double sigmoid(double x) {
    return 1. / (1. + exp(-x));
}

Vector sigmoid(Vector x) {
    for (auto &elem : x) {
        elem = sigmoid(elem);
    }
    return x;
}

Matrix sigmoid(Matrix x) {
    for (auto &vec : x) {
        vec = sigmoid(vec);
    }
    return x;
}

Vector f_forward(Matrix X, Matrix W1, Matrix W2) {
    Matrix Z1 = X * W1;
    Matrix A1 = sigmoid(Z1);

    Matrix Z2 = A1 * W2;
    Matrix A2 = sigmoid(Z2);
    return A2[0];
}

default_random_engine gen;
uniform_real_distribution<double> distribution(-3.0, 3.0);

double random_number_generator() {
    return distribution(gen);
}

Matrix generate_random_weight(int N, int M) {
    Matrix ret = new_Matrix(N, M);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            ret[i][j] = random_number_generator();
        }
    }

    return ret;
}

double loss(Vector out, Vector Y) {
    int N = Y.size();
    double S = 0;
    for (int i = 0; i < N; i++) {
        S += (out[i] - Y[i]) * (out[i] - Y[i]);
    }
    return S / N;
}

void predict(Matrix X, Matrix W1, Matrix W2) {
    Vector result = f_forward(X, W1, W2);
    for (int i = 0; i < 3; i++) {
        cout << result[i] << " \n"[i == 2];
    }
    int maximum_index = max_element(result.begin(), result.end()) - result.begin();
    if (maximum_index == 0) {
        cout << "Image is of letter A." << "\n";
    } else if (maximum_index == 1) {
        cout << "Image is of letter B." << "\n";
    } else if (maximum_index == 2) {
        cout << "Image is of letter C." << "\n";
    } else {
        assert(0);
    }
}

Matrix transpose(Matrix X) {
    int N = X.size();
    int M = X[0].size();
    Matrix ret = new_Matrix(M, N);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            ret[j][i] = X[i][j];
        }
    }
    return ret;
}

Matrix operator - (const Matrix x, const Matrix y) {
    int N = x.size();
    int M = x[0].size();
    assert(N == y.size() && M == y[0].size());
    Matrix ret = new_Matrix(N, M);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            ret[i][j] = x[i][j] - y[i][j];
        }
    }
    return ret;
}

Matrix multiplyMatrix(const Matrix x, const Matrix y) {
    int N = x.size(), M = x[0].size();
    assert(N == y.size() && M == y[0].size());
    Matrix ret = new_Matrix(N, M);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            ret[i][j] = x[i][j] * y[i][j];
        }
    }

    return ret;
}

Matrix multiplyMatrix(const Matrix x, const double d) {
    int N = x.size(), M = x[0].size();
    Matrix ret = new_Matrix(N, M);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            ret[i][j] = x[i][j] * d;
        }
    }

    return ret;
}

pair<Matrix, Matrix> back_propagation(Matrix X, Vector Y, Matrix W1, Matrix W2, double learning_rate) {
    /*
        X : 1 x 30 Matrix
        W1 : 30 x 5 Matrix
        W2 : 5 x 3 Matrix
        Z1, A1 : 1x5 Matrix
        Z2, A2 : 1x3 Matrix
        Y : 3 Vector, Not Matrix
        D2 : 1 x 3 Matrix
    */
    Matrix Z1 = X * W1;
    Matrix A1 = sigmoid(Z1);

    Matrix Z2 = A1 * W2;
    Matrix A2 = sigmoid(Z2);
    Matrix D2 = new_Matrix(1, Y.size());
    for (int i = 0; i < Y.size(); i++) {
        D2[0][i] = A2[0][i] - Y[i];
    }
    auto R1 = transpose(W2 * transpose(D2));
    auto R2 = multiplyMatrix(A1, (Matrix(1, Vector(A1[0].size(), 1.)) - A1));
    Matrix D1 = multiplyMatrix(R1, R2);
    
    Matrix W1_adj = transpose(X) * D1;
    Matrix W2_adj = transpose(A1) * D2;

    W1 = W1 - multiplyMatrix(W1_adj, learning_rate);
    W2 = W2 - multiplyMatrix(W2_adj, learning_rate);

    return {W1, W2};
}

struct trainStructure {
    Vector accVec;
    Vector lossVec;
    Matrix W1;
    Matrix W2;
};

trainStructure train(vector<Matrix> X, Matrix Y, Matrix W1, Matrix W2, double learning_rate = 0.01, int epoch = 10001) {
    Vector accVec, lossVec;
    for (int j = 0; j < epoch; j++) {
        Vector l;
        for (int i = 0; i < X.size(); i++) {
            Vector out = f_forward(X[i], W1, W2);
            l.push_back(loss(out, Y[i]));
            auto [TW1, TW2] = back_propagation(X[i], Y[i], W1, W2, learning_rate);
            if (j % 1000 == 0) {
                cout << "Epochs: " << j + 1 << " ======= acc: " << (1 - accumulate(l.begin(), l.end(), 0.) / int(X.size())) * 100 << "\n";
            }
            swap(W1, TW1);
            swap(W2, TW2);
        }
        accVec.push_back((1 - accumulate(l.begin(), l.end(), 0.) / X.size()) * 100);
        lossVec.push_back(accumulate(l.begin(), l.end(), 0.) / X.size());
    }

    return {accVec, lossVec, W1, W2};
}

int main() {
    gen.seed(std::chrono::system_clock::now().time_since_epoch().count());
    Matrix W1 = generate_random_weight(30, 5);
    Matrix W2 = generate_random_weight(5, 3);
    auto [accVec, lossVec, T_W1, T_W2] = train({A_data, B_data, C_data}, y, W1, W2);
    swap(T_W1, W1);
    swap(T_W2, W2);
    
    cout << "=== TRAIN ===" << "\n";
    predict(A_data, W1, W2);
    predict(B_data, W1, W2);
    predict(C_data, W1, W2);

    cout << "=== TEST ===" << "\n";
    predict(A_test, W1, W2);
    predict(B_test, W1, W2);
    predict(C_test, W1, W2);
    return 0;
}