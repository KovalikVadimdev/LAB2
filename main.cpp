#include <iostream>
#include <vector>

using namespace std;

class rationalFraction {
private:
    vector<int> coefficientsNum;
    vector<int> coefficientsDen;
public:
    // Default constructor
    rationalFraction() {
        coefficientsNum = {0};
        coefficientsDen = {1};
    };

    // Constructor
    rationalFraction(vector<int> &coeffsNum, vector<int> &coeffsDen) {
        // Assigning a value of coefficientsNum
        coefficientsNum = coeffsNum;
        // Assigning a value of coefficientsDen
        coefficientsDen = coeffsDen;
        // Calling a function of fractionSimplification
        fractionSimplification();
    }

    // Getter a value of coefficientsNum
    vector<int> getCoefficientsNum() const {
        return coefficientsNum;
    }

    // Getter a value of coefficientsDen
    vector<int> getCoefficientsDen() const {
        return coefficientsDen;
    }

    // Function for adding two polynomial fractional expressions
    rationalFraction operator+(const rationalFraction &other) const {
        // Creating a vector for the numerator and denominator
        vector<int> resultNum1(coefficientsNum.size()
                               + other.coefficientsDen.size() - 1, 0);
        vector<int> resultNum2(coefficientsDen.size()
                               + other.coefficientsNum.size() - 1, 0);
        vector<int> resultNum((resultNum1.size()
                               + resultNum2.size()) - resultNum1.size(), 0);
        vector<int> resultDen(coefficientsDen.size()
                              + other.coefficientsDen.size() - 1, 0);
        // Calculating the numerator and denominator
        for (int i = 0; i < coefficientsNum.size(); ++i) {
            for (int j = 0; j < other.coefficientsDen.size(); ++j) {
                resultNum1[i + j] += coefficientsNum[i]
                                     * other.coefficientsDen[j];
            }
        }
        for (int i = 0; i < coefficientsDen.size(); ++i) {
            for (int j = 0; j < other.coefficientsNum.size(); ++j) {
                resultNum2[i + j] += coefficientsDen[i]
                                     * other.coefficientsNum[j];
            }
        }
        for (int i = 0; i < resultNum1.size(); ++i) {
            resultNum[i] += resultNum1[i];
        }
        for (int i = 0; i < resultNum2.size(); ++i) {
            resultNum[i] += resultNum2[i];
        }
        for (int i = 0; i < coefficientsDen.size(); ++i) {
            for (int j = 0; j < other.coefficientsDen.size(); ++j) {
                resultDen[i + j] += coefficientsDen[i]
                                    * other.coefficientsDen[j];
            }
        }
        return {resultNum, resultDen};
    }

    // Function for multiplying two polynomial fractional expressions
    rationalFraction operator*(const rationalFraction &other) const {
        // Creating a vector for the numerator and denominator
        vector<int> resultNum(coefficientsNum.size()
                              + other.coefficientsNum.size() - 1, 0);
        vector<int> resultDen(coefficientsDen.size()
                              + other.coefficientsDen.size() - 1, 0);
        // Calculating the numerator and denominator
        for (int i = 0; i < coefficientsNum.size(); ++i) {
            for (int j = 0; j < other.coefficientsNum.size(); ++j) {
                resultNum[i + j] += coefficientsNum[i]
                                    * other.coefficientsNum[j];
            }
        }
        for (int i = 0; i < coefficientsDen.size(); ++i) {
            for (int j = 0; j < other.coefficientsDen.size(); ++j) {
                resultDen[i + j] += coefficientsDen[i]
                                    * other.coefficientsDen[j];
            }
        }
        return {resultNum, resultDen};
    }

    void fractionSimplification() {
        // Assigning a value of result
        int result = 0;
        // Finding the greatest common divisor for the numerator
        for (int i: coefficientsNum) {
            if (i == 0) {
                continue;
            } else {
                while (i != 0) {
                    int temp = i;
                    i = result % i;
                    result = temp;
                }
            }
            if (result == 1) {
                return;
            }
        }
        // Finding the greatest common divisor for the denominator
        for (int i: coefficientsDen) {
            if (i == 0) {
                continue;
            } else {
                while (i != 0) {
                    int temp = i;
                    i = result % i;
                    result = temp;
                }
            }
            if (result == 1) {
                return;
            }
        }
        // Dividing the numerator and denominator by the greatest common
        // divisor using a for-each loop
        for (int &num: coefficientsNum) {
            num /= result;
        }
        for (int &num: coefficientsDen) {
            num /= result;
        }
    }

    // Function for comparing two polynomial fractional expressions
    bool operator==(const rationalFraction &other) const {
        return (coefficientsNum == other.coefficientsNum) && (coefficientsDen
                                                              == other.coefficientsDen);
    }
};

int main() {
    // Creating vectors for the first fraction
    vector<int> numerator_first = {-5, 3, 2};
    vector<int> denominator_first = {-4, 0, 1};
    // Creating vectors for the second fraction
    vector<int> numerator_second = {-15, 9, 6};
    vector<int> denominator_second = {-12, 0, 3};
    // Creating objects of the class rationalFraction
    rationalFraction poly1(numerator_first, denominator_first);
    rationalFraction poly2(numerator_second, denominator_second);
    // Outputting the input data
    cout << "Input data first fraction: (";
    for (int i = numerator_first.size() - 1; i >= 0; --i) {
        if (numerator_first[i] != 0) {
            if (i < numerator_first.size() - 1) {
                if (numerator_first[i] > 0) {
                    cout << " + ";
                } else {
                    cout << " - ";
                }
            }
            int coeff = abs(numerator_first[i]);
            if (i > 0) {
                if (coeff == 1) {
                    cout << "x^" << i;
                } else if (i == 1) {
                    cout << coeff << "x";
                } else {
                    cout << coeff << "x^" << i;
                }
            } else {
                cout << coeff;
            }
        }
    }
    cout << ") / (";
    for (int i = denominator_first.size() - 1; i >= 0; --i) {
        if (denominator_first[i] != 0) {
            if (i < denominator_first.size() - 1) {
                if (denominator_first[i] > 0)
                    cout << " + ";
                else
                    cout << " - ";
            }
            int coeff = abs(denominator_first[i]);
            if (i > 0) {
                if (coeff == 1) {
                    cout << "x^" << i;
                } else if (i == 1) {
                    cout << coeff << "x";
                } else {
                    cout << coeff << "x^" << i;
                }
            } else {
                cout << coeff;
            }
        }
    }
    cout << ")" << endl;
    cout << "Input data second fraction: (";
    for (int i = numerator_second.size() - 1; i >= 0; --i) {
        if (numerator_second[i] != 0) {
            if (i < numerator_second.size() - 1) {
                if (numerator_second[i] > 0) {
                    cout << " + ";
                } else {
                    cout << " - ";
                }
            }
            int coeff = abs(numerator_second[i]);
            if (i > 0) {
                if (coeff == 1) {
                    cout << "x^" << i;
                } else if (i == 1) {
                    cout << coeff << "x";
                } else {
                    cout << coeff << "x^" << i;
                }
            } else {
                cout << coeff;
            }
        }
    }
    cout << ") / (";
    for (int i = denominator_second.size() - 1; i >= 0; --i) {
        if (denominator_second[i] != 0) {
            if (i < denominator_second.size() - 1) {
                if (denominator_second[i] > 0)
                    cout << " + ";
                else
                    cout << " - ";
            }
            int coeff = abs(denominator_second[i]);
            if (i > 0) {
                if (coeff == 1) {
                    cout << "x^" << i;
                } else if (i == 1) {
                    cout << coeff << "x";
                } else {
                    cout << coeff << "x^" << i;
                }
            } else {
                cout << coeff;
            }
        }
    }
    cout << ")" << endl;
    // Outputting the result of adding two polynomial fractional expressions
    rationalFraction resultAdd = poly1 + poly2;
    cout << "Addition Result: (";
    const vector<int> &resultAddNum = resultAdd.getCoefficientsNum();
    const vector<int> &resultAddDen = resultAdd.getCoefficientsDen();
    for (int i = resultAddNum.size() - 1; i >= 0; --i) {
        if (resultAddNum[i] != 0) {
            if (i < resultAddNum.size() - 1) {
                if (resultAddNum[i] > 0) {
                    cout << " + ";
                } else {
                    cout << " - ";
                }
            }
            int coeff = abs(resultAddNum[i]);
            if (i > 0) {
                if (coeff == 1) {
                    cout << "x^" << i;
                } else if (i == 1) {
                    cout << coeff << "x";
                } else {
                    cout << coeff << "x^" << i;
                }
            } else {
                cout << coeff;
            }
        }
    }
    cout << ") / (";
    for (int i = resultAddDen.size() - 1; i >= 0; --i) {
        if (resultAddDen[i] != 0) {
            if (i < resultAddDen.size() - 1) {
                if (resultAddDen[i] > 0)
                    cout << " + ";
                else
                    cout << " - ";
            }
            int coeff = abs(resultAddDen[i]);
            if (i > 0) {
                if (coeff == 1) {
                    cout << "x^" << i;
                } else if (i == 1) {
                    cout << coeff << "x";
                } else {
                    cout << coeff << "x^" << i;
                }
            } else {
                cout << coeff;
            }
        }
    }
    cout << ")" << endl;
    // Outputting the result of multiplying two polynomial fractional
    // expressions
    rationalFraction resultMultiply = poly1 * poly2;
    cout << "Multiplication Result: (";
    const vector<int> &resultMultiplyNum =
            resultMultiply.getCoefficientsNum();
    const vector<int> &resultMultiplyDen =
            resultMultiply.getCoefficientsDen();
    for (int i = resultMultiplyNum.size() - 1; i >= 0; --i) {
        if (resultMultiplyNum[i] != 0) {
            if (i < resultMultiplyNum.size() - 1) {
                if (resultMultiplyNum[i] > 0)
                    cout << " + ";
                else
                    cout << " - ";
            }
            int coeff = abs(resultMultiplyNum[i]);
            if (i > 0) {
                if (coeff == 1) {
                    cout << "x^" << i;
                } else if (i == 1) {
                    cout << coeff << "x";
                } else {
                    cout << coeff << "x^" << i;
                }
            } else {
                cout << coeff;
            }
        }
    }
    cout << ") / (";
    for (int i = resultMultiplyDen.size() - 1; i >= 0; --i) {
        if (resultMultiplyDen[i] != 0) {
            if (i < resultMultiplyDen.size() - 1) {
                if (resultMultiplyDen[i] > 0)
                    cout << " + ";
                else
                    cout << " - ";
            }
            int coeff = abs(resultMultiplyDen[i]);
            if (i > 0) {
                if (coeff == 1) {
                    cout << "x^" << i;
                } else if (i == 1) {
                    cout << coeff << "x";
                } else {
                    cout << coeff << "x^" << i;
                }
            } else {
                cout << coeff;
            }
        }
    }
    cout << ")" << endl;
    // Outputting the result of comparing two polynomial fractional
    // expressions
    if (poly1 == poly2) {
        cout << "Fraction 1 is equal to fraction 2";
    } else {
        cout << "Fraction 1 is not equal to fraction 2";
    }
    return 0;
}
