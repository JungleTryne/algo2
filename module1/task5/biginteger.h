//Мишин Данила. Б05-927. Задание BigInteger

#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

class BigInteger {
private:
    std::vector<char> number;
    short sign;
    static BigInteger changeSign(const BigInteger& other);

    void fillWithZeros(BigInteger& integer);
    void getRidOfZeros();
    void MultiplyBy10();

    void columnAddition(const BigInteger& right);
    void columnSubtraction(const BigInteger& right);

    bool optimizedMutiplication(const BigInteger& right, short& _sign);

public:
    BigInteger();
    BigInteger(long long n);
    BigInteger(std::vector<char> digits, short sign);
    BigInteger(const BigInteger& other);

    BigInteger& operator=(const BigInteger& right);
    BigInteger& operator+=(const BigInteger& right);
    BigInteger& operator-=(const BigInteger& right);
    BigInteger& operator*=(const BigInteger& right);
    BigInteger& operator/=(const BigInteger& right);
    BigInteger& operator%=(const BigInteger& right);

    BigInteger& operator++();
    BigInteger& operator--();

    const BigInteger operator++(int);
    const BigInteger operator--(int);
    BigInteger operator-() const;

    explicit operator bool();

    bool operator!=(const BigInteger& right) const;
    bool operator<(const BigInteger& right) const;
    bool operator==(const BigInteger& right) const;
    bool operator<=(const BigInteger& right) const;
    bool operator>=(const BigInteger& right) const;
    bool operator>(const BigInteger& right) const;

    friend std::ostream & operator << (std::ostream &out, const BigInteger &c);
    friend std::istream & operator >> (std::istream &in,  BigInteger &c);

    size_t getSize() const;
    short getSign() const;
    int shortInttoInt() const;

    std::string toString() const;

};

BigInteger operator+(const BigInteger& left, const BigInteger& right) {
    BigInteger newInteger = left;
    newInteger += right;
    return newInteger;
}

BigInteger operator-(const BigInteger& left, const BigInteger& right) {
    BigInteger newInteger = left;
    newInteger -= right;
    return newInteger;
}

BigInteger operator*(const BigInteger& left, const BigInteger& right) {
    BigInteger newInteger = left;
    newInteger *= right;
    return newInteger;
}

BigInteger operator/(const BigInteger& left, const BigInteger& right) {
    BigInteger newInteger = left;
    newInteger /= right;
    return newInteger;
}

BigInteger operator%(const BigInteger& left, const BigInteger& right) {
    BigInteger newInteger = left;
    newInteger %= right;
    return newInteger;
}

BigInteger::BigInteger(long long n) {
    sign = n >= 0 ? 1 : -1;

    long long copy = n;
    int numberOfDigits = 0;
    do {
        ++numberOfDigits;
        copy /= 10;
    } while (copy);

    n = std::abs(n);
    for(int i = 0; i < numberOfDigits; ++i) {
        this->number.push_back((n/(static_cast<long long>(pow(10, i))) % 10));
    }
}

BigInteger::BigInteger(const BigInteger &other) {
    this->sign = other.sign;
    if(other.number.size() == 1 && other.number[0] == 0) {
        this->sign = 1;
    }

    for(auto digit : other.number) {
        this->number.push_back(digit);
    }
}

void BigInteger::columnAddition(const BigInteger& right) {
    char buffer = 0;
    size_t digitPointer = 0;

    for(size_t i = 0; i < right.number.size(); ++i) {
        ++digitPointer;
        if(i < this->number.size()) {
            if(this->number[i] + right.number[i] + buffer > 9) {
                this->number[i] += (right.number[i] + buffer);
                this->number[i] -= 10;
                buffer = 1;
            } else {
                this->number[i] += (right.number[i] + buffer);
                buffer = 0;
            }

        } else {
            this->number.push_back(right.number[i]);
        }
    }
    //Если остаток есть, а число закончилось, то выполняется этот код
    while(buffer == 1) {
        if(digitPointer == this->number.size()) { //Если длины чисел совпадают
            number.push_back(1);
            buffer = 0;
        }
        else if(this->number[digitPointer] == 9) { //9999...+ 1 = 10000...
            this->number[digitPointer] = 0;        //  ^             ^
        } else {
            this->number[digitPointer] += 1; //9999...+ 1 = 10000...
            buffer = 0;                      //^            ^
        }
        ++digitPointer;
    }
}

BigInteger& BigInteger::operator+=(const BigInteger &right) {
    if(this->sign == right.sign) {
        if(*this >= right) {
            //Гарантируется, что знаки одинаковые, и левое число больше правого

            //Выполняем сложение в столбик
            columnAddition(right);

        } else {
            //Меняем правое и левое местами
            BigInteger newRight = right;
            newRight += *this;
            *this = newRight;
            return *this;
        }
    } else {
        //Прибавление отрицательного числа == Вычитание положительного
        if(this->sign == 1) {
            *this -= changeSign(right);
        } else {
            BigInteger newThis = changeSign(*this);
            BigInteger newRight = right;
            newRight -= newThis;
            *this = newRight;
        }
    }

    return *this;
}

bool BigInteger::operator<(const BigInteger &right) const {
    if(this->sign < right.sign) {
        return true;
    }
    if(this->sign > right.sign) {
        return false;
    }
    if(this->sign == -1) { //Отрицательные числа? Вычисляем для положительных и меняем результат
        BigInteger newThis = *this;
        newThis.sign = 1;
        BigInteger newRight = right;
        newRight.sign = 1;
        return !(newThis < newRight) && newThis != newRight;
    }
    if(this->number.size() < right.number.size()) {
        return true;
    }
    if(this->number.size() > right.number.size()) {
        return false;
    }
    for(long long i = this->number.size()-1; i > -1; --i) {
        if(this->number[i] < right.number[i]) {
            return true;
        } else if(this->number[i] > right.number[i]) {
            return false;
        }
    }
    return false;
}

bool BigInteger::operator==(const BigInteger &right) const {
    if(this->sign != right.sign || this->number.size() != right.number.size()) {
        return false;
    }
    for(size_t i = 0; i < this->number.size(); ++i) {
        if(this->number[i] != right.number[i]) {
            return false;
        }
    }
    return true;
}

bool BigInteger::operator<=(const BigInteger &right) const {
    return *this < right || *this == right;
}

bool BigInteger::operator>=(const BigInteger &right) const {
    return !(*this < right);
}

bool BigInteger::operator>(const BigInteger &right) const {
    return *this >= right && *this != right;
}

bool BigInteger::operator!=(const BigInteger &right) const {
    return !(*this == right);
}

BigInteger BigInteger::changeSign(const BigInteger &other) {
    if(other.number.size() == 1 && other.number[0] == 0 && other.sign == 1) return other;
    BigInteger otherSign(other);
    otherSign.sign = otherSign.sign == 1 ? -1 : 1;
    return otherSign;
}

void BigInteger::columnSubtraction(const BigInteger& right) {
    char buffer = 0;
    size_t digitPointer = 0;
    for(size_t i = 0; i < right.number.size(); ++i) {
        if(this->number[i] >= right.number[i] + buffer) {
            this->number[i] -= (right.number[i] + buffer);
            buffer = 0;
        } else {
            this->number[i] -= (right.number[i] + buffer);
            this->number[i] += 10;
            buffer = 1;
        }
        digitPointer = i;
    }
    ++digitPointer;

    while(buffer == 1) {
        if(this->number[digitPointer] > 0) {
            this->number[digitPointer] -= 1;
            buffer -= 1;
        } else {
            this->number[digitPointer] = 9;
            ++digitPointer;
        }
    }
}

BigInteger& BigInteger::operator-=(const BigInteger &right) {
    if(this->sign == right.sign) {
        if(this->sign == 1) {
            if(*this < right) {
                BigInteger newRight = right;
                newRight -= *this;
                *this = changeSign(newRight);
                return *this;
            } else {
                //Гарантируется, что на вход приходят числа с одинаковыми знаками |*this| >= |right|
                //Вычитаем в столбик
                columnSubtraction(right);

                //Избавляемся от лишних нулей
                while(this->number.back() == 0 && this->number.size() != 1) {
                    this->number.pop_back();
                    this->sign = 1;
                }

                //Если возвращаем 0, то не отрицательный
                if(this->number.size() == 1 && this->number[0] == 0) {
                    this->sign = 1;
                }

                return *this;
            }
        } else {
            //Меняем местами меньшее с большим
            BigInteger newThis = changeSign(*this);
            BigInteger newRight = changeSign(right);
            newRight -= newThis;
            *this = newRight;
            return *this;
        }
    } else {
        if(this->sign == 1) {
            *this += changeSign(right);
            return *this;
        } else {
            BigInteger newThis = changeSign(*this);
            newThis += right;
            *this = changeSign(newThis);
            return *this;
        }
    }

}

BigInteger& BigInteger::operator=(const BigInteger &right) {
    this->sign = right.sign;
    this->number = right.number;
    return *this;
}

std::string BigInteger::toString() const {
    std::string string;
    if(this->sign == -1) string += '-';
    for(long long i = this->number.size()-1; i > -1; --i) {
        string += (number[i] + '0');
    }
    return string;
}

std::ostream& operator<<(std::ostream &out, const BigInteger &c) {
    out << c.toString();
    return out;
}

std::istream& operator>>(std::istream &in, BigInteger &c) {
    std::string input;
    in >> input;

    int threshhold = -1;
    if(input[0] == '-') {
        c.sign = -1;
        threshhold = 0;
    }
    else {
        c.sign = 1;
    }

    c.number.clear();

    while(input[threshhold+1] == '0' && static_cast<size_t>(threshhold+1) < input.size()-1) {
        ++threshhold;
    }

    for(long long i = input.size()-1; i > threshhold; --i) {
        c.number.push_back(input[i] - '0');
    }

    if(c.number.size() == 1 && c.number[0] == 0) {
        c.sign = 1;
    }

    return in;
}

BigInteger::BigInteger() {
    this->sign = 1;
    this->number.push_back(0);
}

BigInteger BigInteger::operator-() const {
    BigInteger negative = changeSign(*this);
    return negative;
}

BigInteger& BigInteger::operator++() {
    *this += 1;
    return *this;
}

BigInteger& BigInteger::operator--() {
    *this -= 1;
    return *this;
}

const BigInteger BigInteger::operator--(int) {
    const BigInteger newOne = *this;
    --(*this);
    return newOne;
}

const BigInteger BigInteger::operator++(int) {
    const BigInteger newOne = *this;
    ++(*this);
    return newOne;
}

BigInteger::operator bool() {
    return !(this->number.size() == 1 && this->number[0] == 0);
}

size_t BigInteger::getSize() const {
    return this->number.size();
}

short BigInteger::getSign() const {
    return this->sign;
}

bool BigInteger::optimizedMutiplication(const BigInteger& right, short& _sign) {
    //Оптимизация №1: Если это умножение на 10
    if(right.number.size() == 2 && right.number[0] == 0 && right.number[1] == 1) {
        this->MultiplyBy10();
        this->sign = _sign;
        return true;
    }

    //Оптимизация №2: если это умножение на [1, ... ,9]
    if(right.number.size() == 1) {
        BigInteger result = 0;
        for(int i = 0; i < right.number[0]; ++i) {
            result += *this;
        }
        *this = result;
        this->sign = _sign;
        return true;
    }
    return false;
}

//Функция перемножения больших чисел. Используется алгоритм Карацубы
BigInteger& BigInteger::operator*=(const BigInteger &right) {
    short _sign = this->sign * right.sign;
    if(optimizedMutiplication(right, _sign)) {
        return *this;
    }

    //Делаем положительную копию правого числа
    BigInteger rightCopy = right;
    rightCopy.sign = 1;
    this->sign = 1;

    //Дополняем нулями
    fillWithZeros(*this);
    fillWithZeros(rightCopy);

    //Делаем так, чтобы числа были одинаковых размеров
    while(this->getSize() < rightCopy.getSize()) {
        this->number.push_back(0);
    }
    while(this->getSize() > rightCopy.getSize()) {
        rightCopy.number.push_back(0);
    }

    //Числа маленькие? Можно умножить и стандартным умножением
    if(this->getSize() <= 4) {
        int thisNumber = this->shortInttoInt();
        int rightNumber = rightCopy.shortInttoInt();
        thisNumber *= rightNumber;
        _sign = this->sign * right.sign;
        *this = BigInteger(thisNumber);
        this->sign = _sign;
        return *this;
    }

    BigInteger numberB; 
    numberB.sign = this->sign;
    numberB.number.resize(this->number.size()/2);
    for(size_t i = 0; i < numberB.number.size(); ++i) {
        numberB.number[i] = this->number[i];
    }

    BigInteger numberA; 
    numberA.sign = this->sign;
    numberA.number.resize(this->number.size()/2);
    for(size_t i = numberA.number.size(); i < 2*numberA.number.size(); ++i) {
        numberA.number[i-numberA.number.size()] = this->number[i];
    }

    BigInteger numberD; 
    numberD.sign = rightCopy.sign;
    numberD.number.resize(this->number.size()/2);
    for(size_t i = 0; i < numberD.number.size(); ++i) {
        numberD.number[i] = rightCopy.number[i];
    }

    BigInteger numberC; 
    numberC.sign = rightCopy.sign;
    numberC.number.resize(this->number.size()/2);
    for(size_t i = numberC.number.size(); i < 2*numberC.number.size(); ++i) {
        numberC.number[i-numberC.number.size()] = rightCopy.number[i];
    }

    numberD.getRidOfZeros();
    numberC.getRidOfZeros();
    numberB.getRidOfZeros();
    numberA.getRidOfZeros();

    BigInteger numberAC = numberA;
    numberAC *= numberC; //a*c

    BigInteger numberBD = numberB;
    numberBD *= numberD; //b*d

    BigInteger numberABCD = numberB + numberA; //a+b
    BigInteger numberTemp = (numberD + numberC); //(c+d)
    numberABCD *= numberTemp;//(a+b)(c+d)
    numberABCD = numberABCD - numberAC - numberBD; //(a+b)(c+d) - ac - bd

    BigInteger firstProduct = 0;

    for(size_t i = 0; i < this->getSize()-1; ++i) { //Умножение на BASE^2
        firstProduct.number.push_back(0);
    }

    for(size_t i = 0; i < numberAC.getSize(); ++i) {
        firstProduct.number.push_back(numberAC.number[i]);
    }

    BigInteger secondProduct;
    for(size_t i = 0; i < this->getSize()/2-1; ++i) { //Умножение на BASE
        secondProduct.number.push_back(0);
    }
    for(size_t i = 0; i < numberABCD.getSize(); ++i) {
        secondProduct.number.push_back(numberABCD.number[i]);
    }

    BigInteger thirdProduct;
    thirdProduct.number.resize(numberBD.getSize());
    for(size_t i = 0; i < numberBD.getSize(); ++i) {
        thirdProduct.number[i] = numberBD.number[i];
    }

    firstProduct.getRidOfZeros();
    secondProduct.getRidOfZeros();
    thirdProduct.getRidOfZeros();

    BigInteger finalNumber = firstProduct + secondProduct + thirdProduct;
    finalNumber.getRidOfZeros();

    *this = finalNumber;
    this->sign = _sign;
    return *this;
}

//Заполняется число нулями так, чтобы его длина была степенью двойки
void BigInteger::fillWithZeros(BigInteger &integer) {
    size_t digitsInSecondBaseLeftNumber = 1 << (static_cast<int>(ceil(log2(static_cast<double_t> (integer.getSize())))));
    size_t delta = digitsInSecondBaseLeftNumber - integer.number.size();
    for(size_t i = 0; i < delta; ++i) {
        integer.number.push_back(0);
    }
}

//Если BigInteger небольшой, то можно перевести в Int
int BigInteger::shortInttoInt() const {
    int thisNumber = 0;
    int counter = 0;
    for(auto digit : this->number) {
        thisNumber += digit * static_cast<int>(pow(10, counter));
        ++counter;
    }
    return thisNumber;
}

//Избавляется от нулей в начале
void BigInteger::getRidOfZeros() {
    for(int i = this->getSize()-1; i > 0; --i) {
        if(this->number[i] != 0) {
            break;
        }
        this->number.pop_back();
    }
}

//Промежуточная функция для деления BigInteger столбиком. Делит подчисло на делитель
char getProductOfSubDivision(const BigInteger& divided, const BigInteger& dividable) {
    BigInteger min = divided;
    char product = 0;
    for(int i = 1; i < 10; ++i) {
        BigInteger subtraction = 0;
        for(int j = 0; j < i; ++j) {
            subtraction += dividable;
        }
        BigInteger remain = divided - subtraction;
        if(min > remain && remain >= 0) {
            min = remain;
            product = i;
        } else if(remain < 0) {
            break;
        }
    }
    return product;
}

//Функция деления больших чисел. Использует алгоритм деления в столбик
BigInteger &BigInteger::operator/=(const BigInteger &right) {
    short thisSign = this->sign;
    short rightSign = right.sign;

    BigInteger rightCopy = right;
    rightCopy.sign = 1;
    this->sign = 1;

    //Оптимизация №1. Если число меньше делителя, то ответ 0
    if(*this < rightCopy) {
        *this = BigInteger(0);
        this->sign = 1;
        return *this;
    }

    //Оптимизация №2. Если числа равны, то ответ 1
    if(*this == rightCopy) {
        *this = BigInteger(1);
        this->sign = rightSign*thisSign;
        return *this;
    }

    BigInteger divided;
    divided.number = {};

    int leftpos = this->getSize() - 1;
    int rightpos = this->getSize() - rightCopy.getSize() + 1;

    for(int i = rightpos; i < leftpos + 1; ++i) {
        divided.number.push_back(this->number[i]);
    }

    std::vector<char> result;

    //Делим столбиком
    while(rightpos > 0) {
        --rightpos;
        divided.number.push_back(this->number[rightpos]);
        std::rotate(divided.number.begin(), divided.number.end()-1, divided.number.end());
        divided.getRidOfZeros();
        int product = getProductOfSubDivision(divided, rightCopy);
        result.push_back(product);
        BigInteger subtraction = 0;
        for(int i = 0; i < product; ++i) {
            subtraction += rightCopy;
        }
        divided -= subtraction;
    }

    //Возвращаем результат
    std::reverse(result.begin(), result.end());
    BigInteger bigResult;
    bigResult.number = result;
    *this = bigResult;
    this->sign = thisSign*rightSign;
    this->getRidOfZeros();

    return *this;
}

BigInteger &BigInteger::operator%=(const BigInteger &right) {
    BigInteger product = *this / right;
    *this -= right*product;
    return *this;
}

BigInteger::BigInteger(std::vector<char> digits, short sign) {
    this->number = digits;
    this->sign = sign;
    if(this->number.size() == 1 && this->number[0] == 0) this->sign = 1;
}

void BigInteger::MultiplyBy10() {
    this->number.push_back(0);
    std::rotate(this->number.begin(), this->number.end()-1, this->number.end());
}

//Нахождение наибольшего общего делителя. Используется алгоритм Евклида
BigInteger GCD(const BigInteger& one, const BigInteger& two) {
    BigInteger copyOne = std::max(one, two);
    BigInteger copyTwo = std::min(one, two);
    while(copyOne % copyTwo != 0) {
        copyOne %= copyTwo;
        std::swap(copyOne, copyTwo);
    }
    return copyTwo;
}

class Rational {
private:
    std::pair<BigInteger, BigInteger> rational;
    short sign;
    void subtractRational();
public:
    Rational();
    Rational(int one);
    Rational(const BigInteger& one);
    Rational(int one, int two);
    Rational(const BigInteger& one, const BigInteger& two);
    Rational(const Rational& rat) = default;

    std::string toString();

    Rational& operator+=(const Rational& right);
    Rational& operator-=(const Rational& right);
    Rational& operator*=(const Rational& right);
    Rational& operator/=(const Rational& right);

    Rational operator-() const;

    bool operator!=(const Rational& right) const;
    bool operator<(const Rational& right) const;
    bool operator==(const Rational& right) const;
    bool operator<=(const Rational& right) const;
    bool operator>=(const Rational& right) const;
    bool operator>(const Rational& right) const;

    std::string asDecimal(size_t precision = 0, char separator = '.') const;

    explicit operator double();
};

Rational::Rational(const BigInteger& one, const BigInteger& two) {
    rational.first = one;
    rational.second = two;
    if(rational.first.getSign() == -1) rational.first = -rational.first;
    if(rational.second.getSign() == -1) rational.second = -rational.second;
    this->sign = one.getSign() * two.getSign();
    this->subtractRational();
}

//Сокращение дроби
void Rational::subtractRational() {
    BigInteger subtraction = GCD(this->rational.first, this->rational.second);
    this->rational.first /= subtraction;
    this->rational.second /= subtraction;
}

//Перевод числа в строку
std::string Rational::toString() {
    std::string output = "";
    if(this->sign == -1) {
        output += '-';
    }
    output += this->rational.first.toString();
    if(this->rational.second != 1) {
        output += '/';
        output += this->rational.second.toString();
    }
    return output;
}

Rational::Rational(int one, int two) {
    this->sign = (one*two > 0) ? 1 : -1;
    if(one < 0) one = -one;
    if(two < 0) two = -two;
    rational.first = one;
    rational.second = two;
    this->subtractRational();
}

Rational operator+(const Rational& left, const Rational& right) {
    Rational newRational = left;
    newRational += right;
    return newRational;
}

Rational operator-(const Rational& left, const Rational& right) {
    Rational newRational = left;
    newRational -= right;
    return newRational;
}

Rational operator*(const Rational& left, const Rational& right) {
    Rational newRational = left;
    newRational *= right;
    return newRational;
}

Rational operator/(const Rational& left, const Rational& right) {
    Rational newRational = left;
    newRational /= right;
    return newRational;
}

Rational &Rational::operator+=(const Rational &right) {
    if(this->sign != right.sign) {
        Rational copyRight = right;
        copyRight.sign = this->sign;
        *this -= copyRight;
        return *this;
    }
    short _sign = this->sign;
    Rational result(this->rational.first*right.rational.second + this->rational.second*right.rational.first,
                    this->rational.second*right.rational.second);
    *this = result;
    this->sign = _sign;
    this->subtractRational();
    return *this;
}

Rational &Rational::operator-=(const Rational& right) {
    if(this->sign != right.sign) {
        Rational copyRight = right;
        copyRight.sign = this->sign;
        *this += copyRight;
        return *this;
    }
    short _sign = this->sign;
    Rational result(this->rational.first*right.rational.second - this->rational.second*right.rational.first,
                    this->rational.second*right.rational.second);
    *this = result;
    this->sign = _sign;
    this->subtractRational();
    return *this;
}

Rational &Rational::operator*=(const Rational& right) {
    Rational result(this->rational.first*right.rational.first,
                    this->rational.second*right.rational.second);
    short _sign = this->sign * right.sign;
    *this = result;
    this->subtractRational();
    this->sign = _sign;
    if(this->rational.first == 0) this->sign = 1;
    return *this;
}

Rational &Rational::operator/=(const Rational& right) {
    Rational result(this->rational.first*right.rational.second,
                    this->rational.second*right.rational.first);
    short _sign = this->sign * right.sign;
    *this = result;
    this->subtractRational();
    this->sign = _sign;
    return *this;
}

Rational Rational::operator-() const {
    Rational otherSign = *this;
    otherSign.sign = (this->sign == 1) ? -1 : 1;
    return otherSign;
}

bool Rational::operator==(const Rational &right) const {
    return this->rational.first*right.rational.second == this->rational.second*right.rational.first;
}

bool Rational::operator>=(const Rational &right) const {
    return (*this - right).sign == 1;
}

bool Rational::operator<(const Rational &right) const {
    return !(*this >= right);
}

bool Rational::operator<=(const Rational &right) const {
    return *this < right || *this == right;
}

bool Rational::operator>(const Rational &right) const {
    return !(*this <= right);
}

bool Rational::operator!=(const Rational &right) const {
    return !(*this == right);
}

std::string Rational::asDecimal(size_t precision, char separator) const {
    std::string result;
    if(this->sign == -1) {
        result += "-";
    }

    //Узнаем, сколько нулей после запятой будет стоять при определенной точности
    BigInteger tempFirst = this->rational.first;
    tempFirst *= 10;
    std::string zeroAfterDecimal = "";
    while(tempFirst < this->rational.second) {
        tempFirst *= 10;
        zeroAfterDecimal += "0";
    }

    BigInteger product = this->rational.first / this->rational.second;
    result += product.toString();
    BigInteger remain = this->rational.first % this->rational.second;

    //Остаток умножаем на 10^точность
    std::vector<char> newRemain;
    for(size_t i = 0; i < precision; ++i) {
        newRemain.push_back(0);
    }
    std::string remainString = remain.toString();
    for(long long i = remainString.size()-1; i > -1; --i) {
        newRemain.push_back(remainString[i]-'0');
    }
    BigInteger BNewRemain(newRemain, 1);

    //Получили BNewRamain. Делим его в столбик

    std::string afterDecimal = "";
    std::string afterZeros = (BNewRemain / this->rational.second).toString();

    if(precision > 0) {
        result += separator;
        while(afterDecimal.size() + afterZeros.size() < precision) {
            afterDecimal += "0";
        }
        afterDecimal += afterZeros;
    }

    //Финальный результат
    std::string final = result + afterDecimal;

    //Проверяем, число ноль и нет
    bool notOnlyZeros = false;
    for(auto i : final) {
        if(i != '0' && i != ',' && i != '-') {
            notOnlyZeros = true;
            break;
        }
    }

    //Если число 0, то знак не добавляем
    if(!notOnlyZeros && this->sign == -1) {
        std::string newFinal = "";
        for(size_t i = 1; i < final.size(); ++i) {
            newFinal += final[i];
        }
        final = newFinal;
    }

    return final;
}

Rational::operator double() {
    return std::stod(this->asDecimal(320, '.'));
}

Rational::Rational() {
    BigInteger one = 0;
    BigInteger two = 1;
    this->rational = std::make_pair(one, two);
    this->sign = 1;
}

Rational::Rational(int one) {
    this->sign = (one > 0) ? 1 : -1;
    if(one < 0) one = -one;
    rational.first = one;
    rational.second = 1;
}

Rational::Rational(const BigInteger& one) {
    BigInteger oneCopy = one;
    this->sign = (oneCopy > 0) ? 1 : -1;
    if(oneCopy < 0) oneCopy = -oneCopy;
    rational.first = oneCopy;
    rational.second = 1;
}
