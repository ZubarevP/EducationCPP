#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <cmath>
#include <iomanip>
#include <sstream>

using namespace std;


class Figure { 
public:
    virtual string Name() const {
        return name_all;
    };
    virtual double Perimeter() const = 0;
    virtual double Area() const = 0;   
private:
    const string name_all;
};

class Rect : public Figure {
public:
    Rect (const string& name, const double& l, const double& h) : name_(name), l_(l), h_(h) {}
    string Name() const override {
        return name_;
    }
    double Perimeter() const override {
        return 2 * (l_ +  h_);
    }
    double Area() const override {
        return l_ * h_;
    }
private:
    const string name_;
    const double l_, h_;
};

class Triangle : public Figure {
public:
    Triangle(const string& name, const double& a, const double& b, const double& c) : name_(name), a_(a), b_(b), c_(c) {}
    string Name() const override {
        return name_;
    }
    double Perimeter() const override {
        return a_ + b_ + c_;
    }
    double Area() const override {
        double p;
        p = (a_ + b_ + c_) / 2;
        return sqrt(p * (p - a_) * (p - b_) * (p - c_));
    }

private:
    const string name_;
    const double a_, b_, c_;
};

class Circle : public Figure {
public:
    Circle (const string& name, double r) : name_(name), r_(r) {}
    string Name() const override {
        return name_;
    }
    double Perimeter() const override {
        return 2 * Pi * r_;
    }
    double Area() const override {
        double p;
        return Pi * r_ * r_;
    }
private:
    const string name_;
    const double r_;
    const double Pi = 3.14;
};

shared_ptr<Figure> CreateFigure (istringstream& stream) {
    string code;
    stream >> code;
    if (code == "RECT") {
        double a, b;
        stream >> a >> b;
        return  make_shared<Rect>(code, a, b);
    }
    else if (code == "TRIANGLE") {
        double a, b, c;
        stream >> a >> b >> c;
        return make_shared<Triangle>(code, a, b, c);
    } else if (code == "CIRCLE") {
        double a;
        stream >> a;
        return make_shared<Circle>(code, a);
    }
}

int main() {
  vector<shared_ptr<Figure>> figures;
  for (string line; getline(cin, line); ) {
    istringstream is(line);

    string command;
    is >> command;
    if (command == "ADD") {
      // Пропускаем "лишние" ведущие пробелы.
      // Подробнее об std::ws можно узнать здесь:
      // https://en.cppreference.com/w/cpp/io/manip/ws
      is >> ws;
      figures.push_back(CreateFigure(is));
    } else if (command == "PRINT") {
      for (const auto& current_figure : figures) {
        cout << fixed << setprecision(3)
             << current_figure->Name() << " "
             << current_figure->Perimeter() << " "
             << current_figure->Area() << endl;
      }
    }
  }
  return 0;
}

/*
ADD RECT 2 3
ADD TRIANGLE 3 4 5
ADD RECT 10 20
ADD CIRCLE 5
PRINT

RECT 10.000 6.000
TRIANGLE 12.000 6.000
RECT 60.000 200.000
CIRCLE 31.400 78.500
*/