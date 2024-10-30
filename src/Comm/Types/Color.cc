// Copyright [2024] SunCAD

#include "Comm/Types/Color.h"

// Define static colors
const Color Color::Black(0, 0, 0);
const Color Color::White(1, 1, 1);

Color::Color(float r, float g, float b) : Red(r), Green(g), Blue(b) {}

Color::Color(const std::string& s) {
    if ((s.length() == 7 || s.length() == 9) && s[0] == '#') {
        size_t i = 1;
        if (s.length() == 9) {
            // Ignore Alpha
            i += 2;
        }

        Red = static_cast<float>(std::stoi(s.substr(i, 2), nullptr, 16)) / 255.0f;
        i += 2;
        Green = static_cast<float>(std::stoi(s.substr(i, 2), nullptr, 16)) / 255.0f;
        i += 2;
        Blue = static_cast<float>(std::stoi(s.substr(i, 2), nullptr, 16)) / 255.0f;
        return;
    }

    throw std::invalid_argument("Color can not be decoded.");
}

std::string Color::toString() const {
    std::ostringstream oss;
    oss << "[" << Red << "," << Green << "," << Blue << "]";
    return oss.str();
}

std::string Color::toHexString() const {
    std::ostringstream oss;
    oss << "#" << std::hex << std::setfill('0')
        << std::setw(2) << static_cast<int>(Red * 255)
        << std::setw(2) << static_cast<int>(Green * 255)
        << std::setw(2) << static_cast<int>(Blue * 255);
    return oss.str();
}

Color Color::scaled(float scale) const {
    return Color(Red * scale, Green * scale, Blue * scale);
}

// Hash function for Color (example)

size_t Color::getHashCode() const {
    return static_cast<size_t>((static_cast<int>(Red * 255) << 16) |
        (static_cast<int>(Green * 255) << 8) |
        (static_cast<int>(Blue * 255)));
}
