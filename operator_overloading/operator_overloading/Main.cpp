#include <iostream>
#include "Vector.h"
#include "Matrix.h"
#include "OutOfRangeException.h"
#include "IncompatibleDimException.h"


int main()
{
    // ›“Œ œ–Œ¬≈– ¿ ¬≈ “Œ–¿
    cout << " ~~~~~~~~ Vector testing ~~~~~~~~ " << endl;
    int aSize, bSize, cSize;
    cout << "Enter size of vector A: ";
    cin >> aSize;
    cout << "Enter size of vector B: ";
    cin >> bSize;
    cout << "Enter size of vector C: ";
    cin >> cSize;
    Vector A(aSize);
    Vector B(bSize);
    Vector C(cSize);
    cout << "Input values of A(" << aSize << "), B(" << bSize << ") and C(" << cSize << "): " << endl;
    cin >> A >> B >> C;
    cout << endl << "    ~ Testing of overload operations ~    " << endl 
         << endl << "Vector A: " << A 
         << endl << "Vector B: " << B 
         << endl << "Vector C: " << C 
         << endl;
    Vector D(B);
    cout << endl << "           **Copy constructor**           " << endl
         << endl << "Vector D, copied from B: " << D << endl;
    Vector E(aSize);
    E = A;
    cout << endl << "               **Equality**               " << endl
         << endl << "E = A: " << E << endl;
    E += A;
    Vector N(aSize);
    cout << "Input values of N(" << aSize << "): " << endl;
    cin >> N;
    N -= A;
    cout << "Some unary and binary operations: " << endl;
    cout << "Operation -= (N -= A) " << N << endl;
    cout << "Operation += (E += A) " << E << endl;
    Vector res1 = -N;
    cout << "-N: " << res1 << endl; 
    Vector res = N + E;
    cout << "N + E: " << res << endl;
    cout << "A[3]: " << A[2] << " " << endl;
    cout << "Length: " << A.length() << endl;
    C = 4 * C;
    N = N * 0.5;
    cout << "4 * C: " << C << endl;
    cout << "N * 0.5: " << N << endl;
    try {
        cout << "A*B: " << A * B << endl;
        Vector complexEx = 0.5 * (A - 2 * C + 3 * B);
        cout << "1/2*(A - 2*C + 3*B): " << complexEx << endl;
    }
    catch (IncompatibleDimException& exception) {
        cout << exception.what() << endl;
    }
    // ›“Œ œ–Œ¬≈– ¿ Ã¿“–»÷€
    cout << " ~~~~~~~~ Matrix testing ~~~~~~~~ " << endl;
    CSRMatrix MatrixA;
    cout << "Matrix A: " << endl;
    cin >> MatrixA;
    cout << "A: " << MatrixA << endl;
    CSRMatrix MatrixB = MatrixA * 2;
    cout << "A * 2: " << MatrixB << endl;
    try {
        Vector multiply = MatrixA * A;
        cout << "MatrixA * A: " << multiply << endl;
        Vector complVec = MatrixA * A + 5 * A;
        cout << " MatrixA * A + 5 * A: " << complVec;
    }
    catch (IncompatibleDimException& exception) {
        cout << exception.what() << endl;
    }
    cout << "NonZero Elements: " << MatrixA.nonZeroElCount() << endl;
    cout << "Size of B: " << MatrixB.Size() << endl;
    return 0;
}