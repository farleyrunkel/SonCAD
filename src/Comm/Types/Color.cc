// Copyright [2024] SunCAD

#include "Comm/Types/Color.h"

// Define static colors
const Sun::Color Sun::Color::Black(0, 0, 0);
const Sun::Color Sun::Color::White(1, 1, 1);

Sun::Color::Color(float r, float g, float b) : Red(r), Green(g), Blue(b) {}

Sun::Color::Color(const std::string& s) {
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

std::string Sun::Color::toString() const {
    std::ostringstream oss;
    oss << "[" << Red << "," << Green << "," << Blue << "]";
    return oss.str();
}

std::string Sun::Color::toHexString() const {
    std::ostringstream oss;
    oss << "#" << std::hex << std::setfill('0')
        << std::setw(2) << static_cast<int>(Red * 255)
        << std::setw(2) << static_cast<int>(Green * 255)
        << std::setw(2) << static_cast<int>(Blue * 255);
    return oss.str();
}

Sun::Color Sun::Color::scaled(float scale) const {
    return Sun::Color(Red * scale, Green * scale, Blue * scale);
}

// Hash function for Color (example)

size_t Sun::Color::getHashCode() const {
    return static_cast<size_t>((static_cast<int>(Red * 255) << 16) |
        (static_cast<int>(Green * 255) << 8) |
        (static_cast<int>(Blue * 255)));
}
