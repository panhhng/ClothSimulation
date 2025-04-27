#include "Shape.h"

// void Shape::draw() const {
    
// }

Shape::~Shape() {
    delete texture;
    delete mask;
    delete bump;
}

istream& Shape::readAppearance(istream& is) {
    string str;

    while (is >> str) {
        if (str == "end") {
            break;
        } 

        if (str == "solid") {
            is >> col;
            cout << col << endl;
        }

        if (str == "texture") {
            is >> str;
            texture = new Image(str);
        }

        if (str == "material") {
            is >> mat;
        }

        if (str == "bump_map") {
            is >> str;
            bump = new Image(str);
        }

        if (str == "mask") {
            is >> str;
            mask = new Image(str);
        }
    }

    return is;
}

pair<float, float> Shape::solveEquation(float a, float b, float c) const {
    float delta = b * b - 4 * a * c;

    if (delta < 0) {
        return {};
    }

    float delta_sqrt = sqrt(delta);

    float t1 = (-b + delta_sqrt) / (2 * a);
    float t2 = (-b - delta_sqrt) / (2 * a);

    if (t1 < t2) {
        return {t1, t2};
    }
    
    return {t2, t1};
}

bool Shape::isVisible(float u, float v) const {
    if (mask == nullptr) {
        return true;
    }
    
    return gt_zero(mask->gray_uv(u, v));
}

Color Shape::selectColor(float u, float v) const {
    if (texture == nullptr) {
        return col;
    }

    return texture->rgb_uv(u, v);
}