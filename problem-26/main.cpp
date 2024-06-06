#include <iostream>
#include <cmath>
#include <memory>
#include <algorithm>
#include <limits>
#include <vector>


class Shape {
public:
    virtual double area() const = 0;
    virtual double perimeter() const = 0;
    virtual std::shared_ptr<Shape> clone() const = 0;
    virtual ~Shape() = default;
};

class Circle : public Shape {

private:
    double radius;
public:
    explicit Circle(double r) : radius(r) { if(r <= 0) throw::std::invalid_argument("Radius must be positive."); }
    virtual double area() const override;
    virtual double perimeter() const override;
    virtual std::shared_ptr<Shape> clone() const override;
};

class Rectangle : public Shape {
private:
    double width, height;
public:
    Rectangle(double w, double h) : width(w), height(h) {}
    virtual double area() const override;
    virtual double perimeter() const override;
    virtual std::shared_ptr<Shape> clone() const override;
};

class ShapeCollection {
private:
    std::vector<std::shared_ptr<Shape>> shapes;
public:
    ShapeCollection() = default;
    ShapeCollection(const ShapeCollection& other);
    ShapeCollection(ShapeCollection&& other);
    ShapeCollection& operator=(const ShapeCollection& other);
    ShapeCollection& operator=(ShapeCollection&& other);
    void addShape(std::shared_ptr<Shape> shape);
    double totalArea() const;
    void printShapes() const {
        for (const auto& shape : shapes) {
            std::cout << "Area: " << shape->area() << ", Perimeter: " << shape->perimeter() << std::endl;
        }
    }
    std::shared_ptr<Shape> shapeWithMinArea() const;
    int countShapesWithAreaGreaterThan(double t) const;
};

ShapeCollection::ShapeCollection(const ShapeCollection &other) {
//    shapes.reserve(other.shapes.size());
    for (const auto& shape : other.shapes) {
        shapes.push_back(shape->clone());
    }
}

// move constructor
ShapeCollection::ShapeCollection(ShapeCollection &&other) {
    shapes = std::move(other.shapes);
}

// copy assignment operator
ShapeCollection& ShapeCollection::operator=(const ShapeCollection &other) {
    if (this != &other) {
        shapes.clear(); // brisanje trenutnih elemenata, size == 0
        for (const auto& shape : other.shapes) {
            shapes.push_back(shape->clone());
        }
    }
    return *this;
}

// move assignment operator
ShapeCollection& ShapeCollection::operator=(ShapeCollection &&other) {
    if (this != &other) {
        shapes = std::move(other.shapes);
    }
    return *this;
}

// add shape to collection
void ShapeCollection::addShape(std::shared_ptr<Shape> shape) {
    shapes.push_back(shape);
}

// total area of all shapes in collection
double ShapeCollection::totalArea() const {
    double total = 0;
    for (const auto& shape : shapes) total += shape->area();
    return total;
}

// minimum area shape in collection
std::shared_ptr<Shape> ShapeCollection::shapeWithMinArea() const {
    if (shapes.empty()) return nullptr;
    return *std::min_element(shapes.begin(), shapes.end(), [](const std::shared_ptr<Shape>& a, const std::shared_ptr<Shape>& b) {
        return a->area() < b->area();
    });
//    auto min = shapes[0];
//    for (const auto& shape : shapes) {
//        if (shape->area() < min->area()) min = shape;
//    }
//    return min;
}

// count shapes with area greater
int ShapeCollection::countShapesWithAreaGreaterThan(double t) const {
//    int count = 0;
//    for (const auto& shape : shapes) {
//        if (shape->area() > t) count++;
//    }
//    return count;
    return std::count_if(shapes.begin(), shapes.end(), [t](const std::shared_ptr<Shape>& shape) {
        return shape->area() > t;
    });

}

void printArea(const std::shared_ptr<Shape>& shape) {
    std::cout << "The area is: " << shape->area() << std::endl;
}

void printPerimeter(const std::shared_ptr<Shape>& shape) {
    std::cout << "The perimeter is: " << shape->perimeter() << std::endl;
}

// CIRCLE
double Circle::area() const {
    return radius * radius * M_PI;
}

double Circle::perimeter() const {
    return 2 * radius * M_PI;
}

std::shared_ptr<Shape> Circle::clone() const {
    return std::make_shared<Circle>(*this);
}

// RECTANGLE
double Rectangle::area() const {
    return width * height;
}

double Rectangle::perimeter() const {
    return 2 * (width + height);
}

std::shared_ptr<Shape> Rectangle::clone() const {
    return std::make_shared<Rectangle>(*this);
}


int main() {
    auto circle = std::make_shared<Circle>(5.0);
    auto rectangle = std::make_shared<Rectangle>(4.0, 6.0);

    ShapeCollection collection;
    collection.addShape(circle);
    collection.addShape(rectangle);

    std::cout << "Individual Shapes:" << std::endl;
    printArea(circle);
    printPerimeter(circle);
    printArea(rectangle);
    printPerimeter(rectangle);

    std::cout << "\nShape Collection:" << std::endl;
    collection.printShapes();

    std::cout << "\nTotal Area: " << collection.totalArea() << std::endl;
    ShapeCollection collectionCopy = collection;

    std::cout << "\nCopied Shape Collection:" << std::endl;
    collectionCopy.printShapes();

    ShapeCollection collectionMove = std::move(collection);
    std::cout << "\nMoved Shape Collection:" << std::endl;
    collectionMove.printShapes();

    auto minAreaShape = collectionMove.shapeWithMinArea();

    if (minAreaShape) {
        std::cout << "\nShape with Minimum Area:" << std::endl;
        printArea(minAreaShape);
        printPerimeter(minAreaShape);
    } else {
        std::cout << "\nNo shapes in the collection." << std::endl;
    }

    double threshold = 30.0;
    int count = collectionMove.countShapesWithAreaGreaterThan(threshold);
    std::cout << "\nNumber of shapes with area greater than " << threshold << ": " << count << std::endl;

    return 0;
}
