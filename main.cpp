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

    // Overloading the addition operation to add two polynomial fractions
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

    // Overloading the multiplication operation to multiply two polynomial
    // fractions
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

    // Function for simplifying a fraction
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

    // Overloading the [] operator to access the coefficients of the numerator
    // and denominator
    void operator[](int index) {
        if (index >= 0 && index < coefficientsNum.size()) {
            cout << "Numerator: " << coefficientsNum[index] << endl;
        } else {
            cout << "Index outside the array" << endl;
        }
        if (index >= 0 && index < coefficientsDen.size()) {
            cout << "Denominator: " << coefficientsDen[index] << endl;
        } else {
            cout << "Index outside the array" << endl;
        }
    }

    // Overloading the == operator to compare two polynomial fraction
    bool operator==(const rationalFraction &other) const {
        return (coefficientsNum == other.coefficientsNum) && (coefficientsDen
        == other.coefficientsDen);
    }

    // Overloading the != operator to compare two polynomial fractions
    bool operator!=(const rationalFraction &other) const {
        return (coefficientsNum != other.coefficientsNum) && (coefficientsDen
        != other.coefficientsDen);
    }

    // Overloading the >> operator to input a polynomial fraction
    friend istream &operator>>(istream &input, rationalFraction &fraction) {
        cout << "Enter coefficients for numerator: ";
        int num;
        vector<int> &numCoeffs = fraction.coefficientsNum;
        numCoeffs.pop_back();
        while (input >> num) {
            numCoeffs.push_back(num);
            if (cin.get() == '\n') {
                break;
            }
        }

        cout << "Enter coefficients for denominator: ";
        vector<int> &denCoeffs = fraction.coefficientsDen;
        denCoeffs.pop_back();
        while (input >> num) {
            denCoeffs.push_back(num);
            if (cin.get() == '\n') {
                break;
            }
        }

        fraction.fractionSimplification();

        return input;
    }

    // Overloading the << operator to output a polynomial fraction
    friend ostream &operator<<(ostream &output,
            const rationalFraction &fraction) {
        output << "(";
        for (int i = fraction.coefficientsNum.size() - 1; i >= 0; --i) {
            if (fraction.coefficientsNum[i] != 0) {
                if (i < fraction.coefficientsNum.size() - 1) {
                    if (fraction.coefficientsNum[i] > 0) {
                        output << " + ";
                    } else {
                        output << " - ";
                    }
                }
                int coeff = abs(fraction.coefficientsNum[i]);
                if (i > 0) {
                    if (coeff == 1) {
                        output << "x^" << i;
                    } else if (i == 1) {
                        output << coeff << "x";
                    } else {
                        output << coeff << "x^" << i;
                    }
                } else {
                    output << coeff;
                }
            }
        }
        output << ") / (";
        for (int i = fraction.coefficientsDen.size() - 1; i >= 0; --i) {
            if (fraction.coefficientsDen[i] != 0) {
                if (i < fraction.coefficientsDen.size() - 1) {
                    if (fraction.coefficientsDen[i] > 0)
                        output << " + ";
                    else
                        output << " - ";
                }
                int coeff = abs(fraction.coefficientsDen[i]);
                if (i > 0) {
                    if (coeff == 1) {
                        output << "x^" << i;
                    } else if (i == 1) {
                        output << coeff << "x";
                    } else {
                        output << coeff << "x^" << i;
                    }
                } else {
                    output << coeff;
                }
            }
        }
        output << ")" << endl;

        return output;
    }
};

int main() {
    cout << "Enter first fraction" << endl;
    rationalFraction poly1;
    cin >> poly1;
    cout << "Enter second fraction" << endl;
    rationalFraction poly2;
    cin >> poly2;
    cout << "First fraction: " << poly1;
    cout << "Second fraction: " << poly2;
    rationalFraction resultAdd = poly1 + poly2;
    cout << "Addition Result: " << resultAdd;
    rationalFraction resultMultiply = poly1 * poly2;
    cout << "Multiplication Result: " << resultMultiply;
    cout << "Specify the area code of the number you want to receive: ";
    int index;
    cin >> index;
    poly1[index];
    cout << "Operation overload ==:" << endl;
    if (poly1 == poly2) {
        cout << "Fractions are equal" << endl;
    } else {
        cout << "Fractions are not equal" << endl;
    }
    cout << "Operation overload !=:" << endl;
    if (!(poly1 != poly2)) {
        cout << "Fractions are equal" << endl;
    } else {
        cout << "Fractions are not equal" << endl;
    }
    return 0;
}