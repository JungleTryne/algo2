#pragma clang diagnostic push
#pragma ide diagnostic ignored "modernize-use-nodiscard"
//Мишин Данила, Б05-927
//Задача по ООП B-"Геометрия"

#include <algorithm>
#include <cmath>
#include <exception>
#include <iostream>
#include <vector>

const double eps = 1e-9;
const double pi = 3.14159265358979323;

//Структура точки
struct Point {
    double x;
    double y;

    explicit Point(double x=0, double y=0) : x(x), y(y) {};
    Point(const Point& other) = default;
    ~Point() = default;

    bool operator==(const Point& other) const;
    bool operator!=(const Point& other) const;

    double getLength() const;
    double getScalar(const Point& other) const;
    void rotate(double angle);
};

//Класс прямой
class Line {
private:
    Point one;
    Point two;
public:
    Line(const Point& first, const Point& second);
    Line(double angle, double height);
    Line(const Point& point, double angle);

    bool operator==(const Line& other) const;
    bool operator!=(const Line& other) const;

    Point getNormalVector() const;
};

//Абстрактный класс фигуры
class Shape {
public:
    virtual double perimeter() const = 0;
    virtual double area() const = 0;
    virtual bool containsPoint(const Point& point) const = 0;

    virtual bool operator==(const Shape& other) const = 0;
    virtual bool operator!=(const Shape& other) const = 0;
    virtual bool isCongruentTo(const Shape& other) const = 0;
    virtual bool isSimilarTo(const Shape& other) const = 0;

    virtual ~Shape() = default;

    virtual void rotate(const Point& center, double angle) = 0;
    virtual void reflex(const Line& axis) = 0;
    virtual void scale(const Point& center, double coefficient) = 0;
};

//Класс многоугольника
class Polygon : public Shape {
protected:
    std::vector<Point> vertices;
    static bool verticesVectorsEqual(std::vector<Point>& thisCopy, std::vector<Point>& otherCopy) ;
    static bool scalarAndEdgesEqual(std::vector<double>& scalarThis, std::vector<double>& scalarOther,
            std::vector<double>& edgesThis, std::vector<double>& edgesOther);
public:
    Polygon(const Polygon& other);
    explicit Polygon(const std::vector<Point>& points);
    explicit Polygon(const Point& first);

    template<typename... T>
    explicit Polygon(const Point& first, const T&... other);

    double perimeter() const override;
    double area() const override;
    bool operator==(const Shape& other) const override;
    bool operator!=(const Shape& other) const override;
    bool isCongruentTo(const Shape& other) const override;
    bool isSimilarTo(const Shape& other) const override;
    bool containsPoint(const Point& point) const override;
    bool isConvex() const;
    std::vector<Point> getVertices() const;

    void rotate(const Point& center, double angle) override;
    void reflex(const Line& axis) override;
    void scale(const Point& center, double coefficient) override;
};

//Класс эллипса
class Ellipse : public Shape {
protected:
    std::pair<Point, Point> _focuses;
    double constSum;
    std::pair<double, double> getAxis() const;
public:
    Ellipse(const Point& one, const Point& two, double constSum);
    double perimeter() const override;
    double area() const override;
    bool operator==(const Shape& other) const override;
    bool operator!=(const Shape& other) const override;
    bool isCongruentTo(const Shape& other) const override;
    bool isSimilarTo(const Shape& other) const override;
    bool containsPoint(const Point& point) const override;

    void rotate(const Point& center, double angle) override;
    void reflex(const Line& axis) override;
    void scale(const Point& center, double coefficient) override;

    std::pair<Point, Point> focuses() const;
    std::pair<Line, Line> directrices() const;
    double eccentricity() const;
    Point center() const;
};

//Класс круга
class Circle : public Ellipse {
private:
public:
    double radius() const;
    Circle(const Point& center, double radius);
};

//Класс прямоугольника
class Rectangle : public Polygon {
public:
    explicit Rectangle(const std::vector<Point>& points);
    Rectangle(const Rectangle& other);
    Rectangle(const Point& one, const Point& three, double coefficient);
    double area() const override;
    Point center() const;
    std::pair<Line, Line> diagonals() const;
};

//Класс квадрата
class Square : public Rectangle{
public:
    explicit Square(const Point& one, const Point& two);
    Circle circumscribedCircle() const;
    Circle inscribedCircle() const;
};

//Класс треугольника
class Triangle : public Polygon {
public:
    explicit Triangle(const Point& one, const Point& two, const Point& three);
    Point orthocenter() const;
    Point centroid() const;
    Line EulerLine() const;
    Circle circumscribedCircle() const;
    Circle inscribedCircle() const;
    Circle ninePointsCircle() const;
};

//==================Point class methods========================//

bool Point::operator==(const Point &other) const {
    return std::abs(this->x - other.x) <= eps && std::abs(this->y - other.y) <= eps;
}

bool Point::operator!=(const Point &other) const {
    return !(*this==other);
}

double Point::getLength() const {
    return sqrt(this->x * this->x + this->y * this->y);
}

void Point::rotate(double angle) {
    //angle в радианах
    double newX = this->x*cos(angle) - this->y*sin(angle);
    double newY = this->x*sin(angle) + this->y*cos(angle);
    this->x = newX;
    this->y = newY;
}

double Point::getScalar(const Point& other) const {
    return this->x*other.x + this->y*other.y;
}

//Вычитаем точки как вектора
Point operator-(const Point& one, const Point& two) {
    Point newPoint(one.x - two.x, one.y - two.y);
    return newPoint;
}

//Складываем точки как вектора
Point operator+(const Point& one, const Point& two) {
    Point newPoint(one.x + two.x, one.y + two.y);
    return newPoint;
}

//Умножение на скаляр справа
Point operator*(const Point& one, double coefficient) {
    Point newPoint(one.x * coefficient, one.y*coefficient);
    return newPoint;
}

//Умножение на скаляр слева
Point operator*(double coefficient, Point& one) {
    return one*coefficient;
}

double GetVectorsAngle(const Point& one, const Point& two) {
    return acos((one.x*two.x + one.y*two.y)/(one.getLength()*two.getLength()));
}

//==================Line class methods========================//

//Класс выброса исклучения при невозможности создания прямой
class NoLineException : public std::exception {
    const char* what() const noexcept override;
};

const char *NoLineException::what() const noexcept {
    return "Нельзя провести прямую через одну точку";
}

Line::Line(const Point &first, const Point &second) {
    this->one = first;
    this->two = second;
    if (first == second) {
        throw NoLineException();
    }
}

Line::Line(double angle, double height) {
    this->one = Point(0, height);
    this->two = Point(-(height/angle), 0);
}

Line::Line(const Point &point, double angle) {
    this->one = point;
    this->two = Point(point.x + 1, point.y + angle);
}

bool Line::operator==(const Line& other) const {
    Point pointOne = other.one;
    Point pointTwo = other.two;

    //Условие 1: Первая точка второй прямой находится на первой прямой
    bool condOne = (this->one.x - this->two.x)*(pointOne.y - this->two.y)
                   - (pointOne.x - this->two.x)*(this->one.y - this->two.y) < eps;

    //Условие 2: Вторая точка второй прямой находится на первой прямой
    bool condTwo = (this->one.x - this->two.x)*(pointTwo.y - this->two.y)
                   - (pointTwo.x - this->two.x)*(this->one.y - this->two.y) < eps;

    //Оба условия должны выполняться
    return condOne && condTwo;
}

bool Line::operator!=(const Line& other) const {
    return !(*this == other);
}

Point Line::getNormalVector() const {
    return Point(this->one.y - this->two.y, this->two.x - this->one.x);
}

Point GetReflectedPoint(const Point& point, const Line& line) {
    Point normalVector = line.getNormalVector();
    double normalVectorLength = normalVector.getLength();
    normalVector.x /= normalVectorLength;
    normalVector.y /= normalVectorLength;

    double ortoVectorLength = 2 * (normalVector.x * point.x + normalVector.y * point.y);

    Point reflected(point.x - ortoVectorLength * normalVector.x, point.y - ortoVectorLength * normalVector.y);
    return reflected;
}

Point GetScaledPoint(const Point& point, const Point& center, double coefficient) {
    Point vector = point - center;
    vector = vector * coefficient;
    Point newPoint = vector + center;
    return newPoint;
}

double GetDeterminant(double x11, double x12, double x21, double x22) {
    return x11 * x22 - x12 * x21;
}

double GetAngle(const Point& firstVector, const Point& secondVector) {
    double angle = acos((firstVector.x*secondVector.x + firstVector.y*secondVector.y)/
                        (firstVector.getLength()* secondVector.getLength()));
    return angle;
}

//==================Polygon class methods========================//

double Polygon::perimeter() const {
    double sum = 0.0;
    for (size_t i = 0; i < this->vertices.size(); ++i) {
        sum += (this->vertices[(i+1) % this->vertices.size()] - this->vertices[i]).getLength();
    }
    return sum;
}

//Используется формула площади Гаусса
double Polygon::area() const {
    size_t pointer = 0;
    double area = 0;
    for (size_t i = 0; i < this->vertices.size(); ++i) {
        area += GetDeterminant(this->vertices[pointer].x,
                               this->vertices[pointer].y,
                               this->vertices[(pointer + 1) % this->vertices.size()].x,
                               this->vertices[(pointer + 1) % this->vertices.size()].y
        );
        pointer++;
    }
    return std::abs(area)*0.5;
}

bool Polygon::verticesVectorsEqual(std::vector<Point>& thisCopy, std::vector<Point>& otherCopy) {
    for (size_t j = 0; j < thisCopy.size()+1; ++j) {
        bool equal = true;
        for (size_t i = 0; i < thisCopy.size(); ++i) {
            if (thisCopy[i] != otherCopy[i]) {
                equal = false;
                break;
            }
        }
        std::rotate(thisCopy.begin(), thisCopy.begin() + 1, thisCopy.end());
        if (equal) {
            return true;
        }
    }
    return false;
}

bool Polygon::operator==(const Shape &otherShape) const {
    //Проверяем, что является многоугольником или ребенком класса Polygon
    const auto otherPointer = dynamic_cast<const Polygon*>(&otherShape);
    if (!otherPointer) {
        return false;
    }
    Polygon other = *otherPointer;

    if (this->vertices.size() != other.vertices.size()) {
        return false;
    }

    //Путем поворота проверяем, что вершины совпадают
    std::vector<Point> thisCopy = this->vertices;
    bool equal = this->verticesVectorsEqual(thisCopy, other.vertices);
    if(equal) {
        return true;
    }

    //Обходим в другую сторону
    std::reverse(thisCopy.begin(), thisCopy.end());
    equal = this->verticesVectorsEqual(thisCopy, other.vertices);

    return equal;
}


bool Polygon::isSimilarTo(const Shape &otherShape) const {
    const auto otherPointer = dynamic_cast<const Polygon*>(&otherShape);
    if (!otherPointer) {
        return false;
    }
    Polygon other = *otherPointer;

    if (this->vertices.size() != other.vertices.size()) {
        return false;
    }

    std::vector<Point> edgesThis;
    std::vector<Point> edgesOther;

    for (size_t i = 0; i < this->vertices.size(); ++i) {
        Point firstEdge = this->vertices[i]-this->vertices[(i+1) % this->vertices.size()];
        Point firstEdgeOther = other.vertices[i]-other.vertices[(i+1) % other.vertices.size()];
        edgesThis.push_back(firstEdge);
        edgesOther.push_back(firstEdgeOther);
    }

    //Проходимся по каждому ребру данного многоугольника, и делим его длину на длину нулевого ребра
    //другого многоугольника. Потом на данный коэфициент меняем все ребра данного многоугольника
    //и выполняем проверку равенства. Если многоугольники подобны, то рано или поздно мы найдем ребро,
    //дающее походящий коэфициент подобия
    for (size_t i = 0; i < this->vertices.size(); ++i) {
        double koef = edgesThis[i].getLength() / edgesOther[0].getLength();

        std::vector<Point> otherCopy = edgesOther;
        for (size_t j = 0; j < edgesOther.size(); ++j) {
            otherCopy[j] = GetScaledPoint(otherCopy[j], Point(0,0), koef);
        }
        std::vector<Point> scaledPolygonVector{Point(0, 0)};
        for (size_t j = 0; j < edgesOther.size()-1; ++j) {
            Point nextPoint = scaledPolygonVector.back() + otherCopy[j];
            scaledPolygonVector.push_back(nextPoint);
        }
        Polygon scaledPolygon(scaledPolygonVector);
        if (this->isCongruentTo(scaledPolygon)) {
            return true;
        }
    }
    return false;
}

bool Polygon::scalarAndEdgesEqual(std::vector<double> &scalarThis, std::vector<double> &scalarOther,
                                  std::vector<double> &edgesThis, std::vector<double> &edgesOther)
{
    for (size_t i = 0; i < scalarOther.size(); ++i) {
        bool equal = true;
        for (size_t j = 0; j < scalarOther.size(); ++j) {
            if (! ((std::abs(scalarThis[j] - scalarOther[j]) < eps) &&
                   (std::abs(edgesThis[j]-edgesOther[j]) < eps)))
            {
                equal = false;
                break;
            }
        }
        if (equal) {
            return true;
        }
        std::rotate(scalarOther.begin(), scalarOther.begin() + 1, scalarOther.end());
        std::rotate(edgesOther.begin(), edgesOther.begin() + 1, edgesOther.end());
    }
    return false;
}

bool Polygon::isCongruentTo(const Shape &otherShape) const {
    const auto otherPointer = dynamic_cast<const Polygon*>(&otherShape);
    if (!otherPointer) {
        return false;
    }
    Polygon other = *otherPointer;

    if (this->vertices.size() != other.vertices.size()) {
        return false;
    }

    //Получаем списки скалярных произведений
    std::vector<double> scalarThis;
    std::vector<double> scalarOther;
    std::vector<double> edgesThis;
    std::vector<double> edgesOther;

    for (size_t i = 0; i < this->vertices.size(); ++i) {
        size_t firstPointer = i;
        size_t secondPointer = (i+1) % this->vertices.size();
        size_t thirdPointer = (i+2) % this->vertices.size();

        Point firstEdge = this->vertices[firstPointer] - this->vertices[secondPointer];
        Point secondEdge = this->vertices[secondPointer] - this->vertices[thirdPointer];

        Point firstEdgeOther = other.vertices[firstPointer]-other.vertices[secondPointer];
        Point secondEdgeOther = other.vertices[secondPointer] - other.vertices[thirdPointer];

        scalarThis.push_back((firstEdge).getScalar(secondEdge));
        scalarOther.push_back((firstEdgeOther).getScalar(secondEdgeOther));
        edgesThis.push_back(firstEdge.getLength());
        edgesOther.push_back(firstEdgeOther.getLength());
    }


    bool equal = this->scalarAndEdgesEqual(scalarThis, scalarOther, edgesThis, edgesOther);
    if (equal) {
        return true;
    }

    std::reverse(edgesOther.begin(), edgesOther.end());
    std::reverse(scalarOther.begin(), scalarOther.end());
    std::rotate(scalarOther.begin(), scalarOther.begin()+1, scalarOther.end());

    equal = this->scalarAndEdgesEqual(scalarThis, scalarOther, edgesThis, edgesOther);

    return equal;

}

//Испускаем луч, проверяем, сколько раз пересечет грани многоугольника
bool Polygon::containsPoint(const Point& point) const {
    bool inside = false;
    for (size_t i = 0, j = this->vertices.size()-1; i < this->vertices.size(); j = i++) {
        if ((this->vertices[i].y > point.y) != (this->vertices[j].y > point.y) &&
            (point.x < (this->vertices[j].x-this->vertices[i].x) * (point.y-this->vertices[i].y) /
                       (this->vertices[j].y-this->vertices[i].y) +this->vertices[i].x)
                )
        {
            inside = !inside;
        }
    }
    return inside;
}

void Polygon::rotate(const Point &center, double angle) {
    for (Point& vertex : this->vertices) {
        Point vector = vertex - center;
        vector.rotate((angle/360)*2*pi);
        vertex = vector + center;
    }
}

void Polygon::reflex(const Line &axis) {
    for (Point& vertex : this->vertices) {
        vertex = GetReflectedPoint(vertex, axis);
    }
}

void Polygon::scale(const Point& center, double coefficient) {
    for (Point& vertex : this->vertices) {
        vertex = GetScaledPoint(vertex, center, coefficient);
    }
}

Polygon::Polygon(const Polygon& other) {
    this->vertices = other.vertices;
}

Polygon::Polygon(const std::vector<Point>& points) {
    this->vertices = points;
}

bool Polygon::operator!=(const Shape& otherShape) const {
    const auto otherPointer = dynamic_cast<const Polygon*>(&otherShape);
    if (!otherPointer) {
        return false;
    }
    Polygon other = *otherPointer;
    return !(*this == other);
}

//Узнаем, совершен ли был поворот вектора при обходе многоугольника по часовой стрелке и против часовой
//Если оба поворота были совершены, то значит многоугольник невыпуклый
bool Polygon::isConvex() const {
    bool positive = false;
    bool negative = false;
    for (size_t i = 0; i < this->vertices.size(); ++i) {
        size_t firstIndex = i;
        size_t secondIndex = (i + 1) % this->vertices.size();
        size_t thirdIndex = (i + 2) % this->vertices.size();

        double deltaxOne = this->vertices[secondIndex].x - this->vertices[firstIndex].x;
        double deltaxTwo = this->vertices[thirdIndex].x - this->vertices[secondIndex].x;
        double deltayOne = this->vertices[secondIndex].y - this->vertices[firstIndex].y;
        double deltayTwo = this->vertices[thirdIndex].y - this->vertices[secondIndex].y;
        double zComponentProduct = deltaxOne*deltayTwo - deltayOne*deltaxTwo;
        if (zComponentProduct > 0) {
            positive = true;
        }
        if (zComponentProduct < 0) {
            negative = true;
        }
    }
    return positive ^ negative;
}

std::vector<Point> Polygon::getVertices() const {
    return this->vertices;
}

Polygon::Polygon(const Point& first) {
    this->vertices.insert(this->vertices.begin(), first);
}

template<typename... T>
Polygon::Polygon(const Point &first, const T &... other) : Polygon(other...) {
    this->vertices.insert(this->vertices.begin(), first);
}

//==================Ellipse class methods========================//

Ellipse::Ellipse(const Point& one, const Point& two, double constSum) {
    this->_focuses = std::make_pair(one, two);
    this->constSum = constSum;
}

//Функция получения полуосей эллипса
std::pair<double, double> Ellipse::getAxis() const {
    double cathet = (_focuses.first - _focuses.second).getLength() / 2;
    double hypotenuse = constSum/2;
    double smallAxis = sqrt(hypotenuse*hypotenuse - cathet*cathet);
    double bigAxis = sqrt(smallAxis*smallAxis + cathet*cathet);
    return std::make_pair(smallAxis, bigAxis);
}

double Ellipse::perimeter() const {
    std::pair<double, double> axis = this->getAxis();
    double smallAxis = axis.first;
    double bigAxis = axis.second;
    double finalPerimeter = pi*(3*(smallAxis+bigAxis) - sqrt((3*smallAxis+bigAxis)*(smallAxis+3*bigAxis)));
    return finalPerimeter;
}

double Ellipse::area() const {
    std::pair<double, double> axis = this->getAxis();
    double smallAxis = axis.first;
    double bigAxis = axis.second;
    double finalArea = pi*smallAxis*bigAxis;
    return finalArea;
}

bool Ellipse::operator==(const Shape &otherShape) const {
    const auto otherPointer = dynamic_cast<const Ellipse*>(&otherShape);
    if (!otherPointer) {
        return false;
    }
    Ellipse other = *otherPointer;
    return ((this->_focuses == other._focuses ||
             this->_focuses == std::make_pair(other._focuses.second, other._focuses.first)) &&
            std::abs(this->constSum - other.constSum) < eps);
}

bool Ellipse::isCongruentTo(const Shape &otherShape) const {
    const auto otherPointer = dynamic_cast<const Ellipse*>(&otherShape);
    if (!otherPointer) {
        return false;
    }
    Ellipse other = *otherPointer;
    return std::abs((this->_focuses.first - this->_focuses.second).getLength() -
                    (other._focuses.first - other._focuses.second).getLength()) < eps &&
           std::abs(this->constSum - other.constSum) < eps;
}

bool Ellipse::isSimilarTo(const Shape &otherShape) const {
    const auto otherPointer = dynamic_cast<const Ellipse*>(&otherShape);
    if (!otherPointer) {
        return false;
    }
    Ellipse other = *otherPointer;
    double lengthOne = (this->_focuses.first - this->_focuses.second).getLength();
    double lengthTwo = (other._focuses.first - other._focuses.second).getLength();
    if (std::abs(lengthOne - lengthTwo) < eps && std::abs(lengthTwo) < eps) {
        return true;
    }
    return std::abs(this->eccentricity() - other.eccentricity()) < eps;
}

bool Ellipse::containsPoint(const Point& point) const {
    return (this->_focuses.first - point).getLength() + (this->_focuses.second - point).getLength() <= this->constSum;
}

void Ellipse::rotate(const Point &center, double angle) {
    angle = (angle / 360) * 2 * pi; //переводим в радианы
    Point vectorOne = this->_focuses.first - center;
    Point vectorTwo = this->_focuses.second - center;
    vectorOne.rotate(angle);
    vectorTwo.rotate(angle);
    this->_focuses.first = vectorOne + center;
    this->_focuses.second = vectorTwo + center;
}

void Ellipse::reflex(const Line &axis) {
    Point newFocusOne = GetReflectedPoint(this->_focuses.first, axis);
    Point newFocusTwo = GetReflectedPoint(this->_focuses.second, axis);
    this->_focuses = std::make_pair(newFocusOne, newFocusTwo);
}

void Ellipse::scale(const Point &center, double coefficient) {
    Point newFocusOne = GetScaledPoint(this->_focuses.first, center, coefficient);
    Point newFocusTwo = GetScaledPoint(this->_focuses.second, center, coefficient);
    this->_focuses = std::make_pair(newFocusOne, newFocusTwo);
    this->constSum = (this->constSum)*coefficient;
}

std::pair<Point, Point> Ellipse::focuses() const {
    return this->_focuses;
}

std::pair<Line, Line> Ellipse::directrices() const {
    Point centerVector = this->center();

    Point unitVector = this->_focuses.first - this->_focuses.second;
    unitVector.x /= unitVector.getLength();
    unitVector.y /= unitVector.getLength();

    Point unitNormalVector(-unitVector.y, unitVector.x);

    Point firstLineFirstPoint = unitVector * this->eccentricity() + centerVector;
    Point firstLineSecondPoint = unitVector*this->eccentricity() + centerVector + unitNormalVector;
    Line firstLine = Line(firstLineFirstPoint, firstLineSecondPoint);

    Point secondLineFirstPoint = unitVector * (-this->eccentricity()) + centerVector;
    Point secondLineSecondPoint = unitVector * (-this->eccentricity()) + centerVector;
    Line secondLine = Line(secondLineFirstPoint, secondLineSecondPoint);

    return std::make_pair(firstLine, secondLine);
}

double Ellipse::eccentricity() const {
    std::pair<double, double> axis = this->getAxis();
    double smallAxis = axis.first;
    double bigAxis = axis.second;
    return sqrt(1 - (smallAxis*smallAxis)/(bigAxis*bigAxis));
}

Point Ellipse::center() const {
    return (this->_focuses.first - this->_focuses.second) * 0.5 + this->_focuses.second;
}

bool Ellipse::operator!=(const Shape &otherShape) const {
    const auto otherPointer = dynamic_cast<const Ellipse*>(&otherShape);
    if (!otherPointer) {
        return false;
    }
    Ellipse other = *otherPointer;
    return !(other == *this);
}

//==================Circle class methods========================//

double Circle::radius() const {
    return this->constSum/2;
}

Circle::Circle(const Point& _center, double radius) : Ellipse(_center, _center, 2*radius) {}

//==================Rectangle class methods========================//

Point Rectangle::center() const {
    return (this->vertices[2] - this->vertices[0])*0.5 + this->vertices[0];
}

std::pair<Line, Line> Rectangle::diagonals() const {
    return std::make_pair(
            Line(this->vertices[0], this->vertices[2]),
            Line(this->vertices[1], this->vertices[3])
    );
}

std::vector<Point> getRectangleFromTwoPoints(const Point& one, const Point& three, double coefficient) {
    Point vector = three - one;
    double angle = std::max(atan(coefficient), pi/2 - atan(coefficient));
    Point side1 = vector;
    side1.rotate(angle);
    side1 = side1 * (1/side1.getLength()) * vector.getLength()*cos(angle);

    Point side2 = vector;
    side2.rotate(angle-pi/2);
    side2 = side2 * (1/side2.getLength()) * vector.getLength()*sin(angle);

    Point two = one + side1;
    Point four = one + side2;
    return std::vector<Point>{one, two, three, four};
}

Rectangle::Rectangle(const Point& one, const Point& three, double coefficient) :
        Polygon(getRectangleFromTwoPoints(one, three, coefficient)){}

Rectangle::Rectangle(const std::vector<Point> &points) : Polygon(points) {}

double Rectangle::area() const {
    double halfP = this->perimeter()/2;
    double first = (this->vertices[0] - this->vertices[1]).getLength();
    double second = (this->vertices[1] - this->vertices[2]).getLength();
    double third = (this->vertices[2] - this->vertices[1]).getLength();
    return sqrt(halfP*(halfP-first)*(halfP-second)*(halfP-third));
}

Rectangle::Rectangle(const Rectangle& other) = default;

//==================Square class methods========================//

Circle Square::circumscribedCircle() const {
    Circle circle(this->center(), ((this->vertices[2] - this->vertices[0]).getLength())/2);
    return circle;
}

Circle Square::inscribedCircle() const {
    Circle circle(this->center(), (((this->vertices[2] - this->vertices[1]).getLength())/2));
    return circle;
}

std::vector<Point> GetSquare(const Point& one, const Point& two) {
    Point vector = two - one;
    vector.rotate(pi/4);
    vector = vector * (1/sqrt(2)) + one;
    Point vector2 = two - one;
    vector2 = vector2 * (1/sqrt(2));
    vector2.rotate(-pi/4);
    vector2 = vector2 + one;
    std::vector<Point> result = {one, vector, two, vector2};
    return result;
}

Square::Square(const Point& one, const Point& two) : Rectangle(GetSquare(one, two)){}

//==================Triangle class methods========================//

Triangle::Triangle(const Point& one, const Point& two, const Point& three) :
        Polygon(std::vector<Point>{one, two, three}) {}

Point Triangle::orthocenter() const {
    double x1 = this->vertices[0].x;
    double x2 = this->vertices[1].x;
    double x3 = this->vertices[2].x;

    double y1 = this->vertices[0].y;
    double y2 = this->vertices[1].y;
    double y3 = this->vertices[2].y;

    double orthoX = ((x2*(x1-x3) + y2*(y1-y3))*(y3-y2) - (y3-y1)*(x1*(x2-x3) +
                                                                  y1*(y2-y3)))/((x3-x2)*(y3-y1) - (y3-y2)*(x3-x1));

    double orthoY = ((x2*(x1-x3) + y2*(y1-y3))*(x3-x2) - (x3-x1)*(x1*(x2-x3) +
                                                                  y1*(y2-y3)))/((y3-y2)*(x3-x1) - (x3-x2)*(y3-y1));

    return Point(orthoX, orthoY);

}

Point Triangle::centroid() const {
    return (this->vertices[0] + this->vertices[1] + this->vertices[2])*(0.3333333333333);
}

Line Triangle::EulerLine() const {
    Point _orthocenter = this->orthocenter();
    Point _centroid = this->centroid();
    if (_orthocenter == _centroid) {
        throw NoLineException();
    }
    Line line(this->orthocenter(), this->centroid());
    return line;
}

Circle Triangle::circumscribedCircle() const {
    Point vectorOne = this->vertices[1] - this->vertices[0];
    Point vectorTwo = this->vertices[2] - this->vertices[0];
    Point vectorThree = this->vertices[2] - this->vertices[1];
    double radius = vectorOne.getLength()*vectorTwo.getLength()*vectorThree.getLength()/(4*this->area());

    double x1 = this->vertices[0].x;
    double x2 = this->vertices[1].x;
    double x3 = this->vertices[2].x;

    double y1 = this->vertices[0].y;
    double y2 = this->vertices[1].y;
    double y3 = this->vertices[2].y;

    double D = 2*(x1*(y2-y3)+x2*(y3-y1)+x3*(y1-y2));
    double centerX = (1/D)*((x1*x1+y1*y1)*(y2-y3) + (x2*x2+y2*y2)*(y3-y1) + (x3*x3+y3*y3)*(y1-y2));
    double centerY = (1/D)*((x1*x1+y1*y1)*(x3-x2) + (x2*x2+y2*y2)*(x1-x3) + (x3*x3+y3*y3)*(x2-x1));

    Circle circle(Point(centerX, centerY), radius);
    return circle;
}

Circle Triangle::inscribedCircle() const {
    Point vectorOne = this->vertices[1] - this->vertices[0];
    Point vectorTwo = this->vertices[2] - this->vertices[0];
    Point vectorThree = this->vertices[2] - this->vertices[1];

    double oneLength = vectorOne.getLength();
    double twoLength = vectorTwo.getLength();
    double threeLength = vectorThree.getLength();

    double halfPerimeter = 0.5*(oneLength + twoLength + threeLength);
    double radius = this->area()/halfPerimeter;

    Point center((oneLength*this->vertices[2].x + twoLength*this->vertices[1].x + threeLength*this->vertices[0].x)/
                 (oneLength + twoLength + threeLength),
                 ((oneLength*this->vertices[2].y + twoLength*this->vertices[1].y + threeLength*this->vertices[0].y)/
                  (oneLength + twoLength + threeLength)));

    Circle circle(center, radius);
    return circle;
}

Circle Triangle::ninePointsCircle() const {
    Point circumscribedCircleCenter = this->circumscribedCircle().center();

    Point _orthocenter = this->orthocenter();
    Point center = (_orthocenter - circumscribedCircleCenter)*0.5 + circumscribedCircleCenter;
    double radius = this->circumscribedCircle().radius();
    radius /= 2;
    Circle circle(center, radius);
    return circle;
}


#pragma clang diagnostic pop