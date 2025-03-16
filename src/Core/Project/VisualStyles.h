#ifndef CORE_PROJECT_VISUALSTYLES_H_
#define CORE_PROJECT_VISUALSTYLES_H_

#include <string>
#include <array>
#include <vector>
#include <cstdint>

#include <Quantity_Color.hxx>

// Enum definitions
enum class PresentationMode
{
    Wireframe,
    Solid,
    SolidWithBoundary
};

enum class LineStyle
{
    Solid,
    Dash,
    ShortDash,
    Dot,
    DotDash
};

enum class FillMode
{
    None,
    Solid
};

enum class LineThickness
{
    Thin,
    Normal,
    Thick
};

// Static Colors class
class Colors
{
public:
    static const Quantity_Color Default;
    static const Quantity_Color Selection;
    static const Quantity_Color Highlight;
    static const Quantity_Color FilteredSubshapes;
    static const Quantity_Color FilteredSubshapesHot;
    static const Quantity_Color Ghost;
    static const Quantity_Color Auxillary;
    static const Quantity_Color Marker;
    static const Quantity_Color AttributeMarkerBackground;
    static const Quantity_Color AttributeMarkerSelection;
    static const Quantity_Color SketchEditorSegments;
    static const Quantity_Color SketchEditorHighlight;
    static const Quantity_Color SketchEditorSelection;
    static const Quantity_Color SketchEditorCreating;
    static const Quantity_Color SketchEditorAuxillary;
    static const Quantity_Color ActionBlue;
    static const Quantity_Color ActionRed;
    static const Quantity_Color ActionGreen;
    static const Quantity_Color ActionWhite;
};

// LineStyleDescription struct
struct LineStyleDescription
{
    LineStyle style;
    std::string Name;
    std::vector<double> pattern;

    LineStyleDescription(LineStyle s, const std::string& n, const std::vector<double>& p)
        : style(s), Name(n), pattern(p)
    {}
};

// LineThicknessDescription struct
struct LineThicknessDescription
{
    LineThickness thickness;
    std::string Name;
    double width;

    LineThicknessDescription(LineThickness t, const std::string& n, double w)
        : thickness(t), Name(n), width(w)
    {}
};

// StyleHelper class
//class StyleHelper {
//public:
//    static const std::array<LineStyleDescription, 5> LineStyleDescriptions;
//    static const std::array<LineThicknessDescription, 3> LineThicknessDescriptions;
//
//    //static const std::vector<double>& Pattern(LineStyle lineStyle) {
//    //    return LineStyleDescriptions[static_cast<int>(lineStyle)].pattern;
//    //}
//
//    //static void ApplyToAspect(LineStyle lineStyle, /* Prs3d_LineAspect aspect */) {
//    //    // Implementation for setting aspect
//    //}
//
//    //static double LineWidth(LineThickness thickness) {
//    //    return LineThicknessDescriptions[static_cast<int>(thickness)].width;
//    //}
//};
//
//// Initialize LineStyleDescriptions
//const std::array<LineStyleDescription, 5> StyleHelper::LineStyleDescriptions = { {
//    {LineStyle::Solid, "Solid", {10.0, 0.0}},
//    {LineStyle::Dash, "Dash", {4.0, 2.0}},
//    {LineStyle::ShortDash, "Short Dash", {2.0, 2.0}},
//    {LineStyle::Dot, "Dot", {1.0, 1.0}},
//    {LineStyle::DotDash, "Dot-Dash", {5.0, 2.0, 1.0, 2.0}},
//} };
//
//// Initialize LineThicknessDescriptions
//const std::array<LineThicknessDescription, 3> StyleHelper::LineThicknessDescriptions = { {
//    {LineThickness::Thin, "Thin", 1.0},
//    {LineThickness::Normal, "Normal", 2.0},
//    {LineThickness::Thick, "Thick", 3.0},
//} };

#endif  // CORE_PROJECT_VISUALSTYLES_H_
