#ifndef SRC_COMMON_TYPES_COLOR_H_
#define SRC_COMMON_TYPES_COLOR_H_

#include <cassert>
#include <sstream>
#include <iomanip>
#include <string>
#include <array>
#include <stdexcept>

#include <QColor>

#include <Quantity_Color.hxx>

class Color : public QColor {
 public:
    static const Color Black;
    static const Color White;

    Color(Qt::GlobalColor color) : QColor(color) {}
    Color(float r, float g, float b);
    Color(const std::string& s);
    //--------------------------------------------------------------------------------------------------

    float Red;
    float Green;
    float Blue;

    //--------------------------------------------------------------------------------------------------
        // Convert Color to Quantity_Color
    Quantity_Color toQuantityColor() const {
        return Quantity_Color(Red, Green, Blue, Quantity_TOC_sRGB);
    }

    std::string toString() const;

    //--------------------------------------------------------------------------------------------------

    std::string toHexString() const;

    //--------------------------------------------------------------------------------------------------

    bool operator==(const Color& other) const {
        return (Red == other.Red) && (Green == other.Green) && (Blue == other.Blue);
    }

    //--------------------------------------------------------------------------------------------------

    bool operator!=(const Color& other) const {
        return !(*this == other);
    }

    //--------------------------------------------------------------------------------------------------

    Color scaled(float scale) const;

    //--------------------------------------------------------------------------------------------------

    Color Lerp(const Color& other, float f) const {
        return Color(
            Red + (other.Red - Red) * f,
            Green + (other.Green - Green) * f,
            Blue + (other.Blue - Blue) * f
        );
    }

    // Hash function for Color (example)
    size_t getHashCode() const;
};

#endif // SRC_COMMON_TYPES_COLOR_H_
