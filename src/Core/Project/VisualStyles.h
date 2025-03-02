#ifndef CORE_PROJECT_VISUALSTYLES_H_
#define CORE_PROJECT_VISUALSTYLES_H_

// std includes
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
    std::string name;
    std::vector<double> pattern;

    LineStyleDescription(LineStyle s, const std::string& n, const std::vector<double>& p)
        : style(s), name(n), pattern(p)
    {}
};

// LineThicknessDescription struct
struct LineThicknessDescription
{
    LineThickness thickness;
    std::string name;
    double width;

    LineThicknessDescription(LineThickness t, const std::string& n, double w)
        : thickness(t), name(n), width(w)
    {}
};

#endif  // CORE_PROJECT_VISUALSTYLES_H_
