// Copyright [2024] SunCAD

#ifndef SRC_IACT_WORKSPACE_MOUSEEVENTDATA_H_
#define SRC_IACT_WORKSPACE_MOUSEEVENTDATA_H_

#include <QList>
#include <QPoint>
#include <QGraphicsView>
#include <QMouseEvent>
#include <optional>

class MouseEventData;
//--------------------------------------------------------------------------------------------------
// 鼠标事件处理接口
class IMouseEventHandler {
public:
    virtual ~IMouseEventHandler() = default;
    virtual bool onMouseMove(MouseEventData* data) = 0;
    virtual bool onMouseDown(MouseEventData* data) = 0;
    virtual bool onMouseUp(MouseEventData* data) = 0;
};

//--------------------------------------------------------------------------------------------------
// 定义交互式实体的基本接口
class InteractiveEntity : public QObject {};
class AIS_InteractiveObject;
class TopoDS_Shape;
class Viewport;
//--------------------------------------------------------------------------------------------------
// 鼠标事件数据结构
class MouseEventData {
public:
    // 定义元素类，包含交互对象、实体和形状信息
    struct Element {
        AIS_InteractiveObject* aisObject;
        InteractiveEntity* entity;
        TopoDS_Shape* brepShape;

        // 不同的构造函数，支持不同的输入组合
        Element(AIS_InteractiveObject* aisObj, InteractiveEntity* ent, TopoDS_Shape* brep)
            : aisObject(aisObj), entity(ent), brepShape(brep) {}

        Element(AIS_InteractiveObject* aisObj, TopoDS_Shape* brep = nullptr)
            : aisObject(aisObj), brepShape(brep) {}

        Element(InteractiveEntity* ent)
            : entity(ent) {}
    };

    // 返回选项类
    class ReturnOptions {
    public:
        QList<Element> additionalHighlights;
        bool forceReDetection = false;
        bool removeHighlighting = false;

        // 清空返回选项数据
        void clear() {
            additionalHighlights.clear();
            forceReDetection = false;
            removeHighlighting = false;
        }
    };

    // 鼠标事件数据的主要属性
    Viewport* viewport = nullptr;
    QPoint screenPoint;
    QVector3D pointOnPlane;
    Qt::KeyboardModifiers modifierKeys;
    QList<Element> detectedElements;
    ReturnOptions returnOptions;

    // 构造函数
    MouseEventData(Viewport* vp, const QPoint& sp, const QVector3D& pp, Qt::KeyboardModifiers mk)
        : viewport(vp), screenPoint(sp), pointOnPlane(pp), modifierKeys(mk) {}

    // 检测到的主要实体
    InteractiveEntity* detectedEntity() const {
        return !detectedElements.isEmpty() ? detectedElements[0].entity : nullptr;
    }

    TopoDS_Shape* detectedBrepShape() const {
        return !detectedElements.isEmpty() ? detectedElements[0].brepShape : nullptr;
    }

    AIS_InteractiveObject* detectedAisObject() const {
        return !detectedElements.isEmpty() ? detectedElements[0].aisObject : nullptr;
    }

    // 重置事件数据
    void clear() {
        viewport = nullptr;
        screenPoint = QPoint();
        pointOnPlane = QVector3D();
        detectedElements.clear();
        returnOptions.clear();
    }

    // 设置事件数据
    void set(Viewport* vp, const QPoint& sp, const QVector3D& pp, Qt::KeyboardModifiers mk) {
        clear();
        viewport = vp;
        screenPoint = sp;
        pointOnPlane = pp;
        modifierKeys = mk;
    }

    // 设置检测元素的列表
    void setDetectedElements(const QList<AIS_InteractiveObject*>& aisObjects,
        const QList<InteractiveEntity*>& entities,
        const QList<TopoDS_Shape*>& brepShapes) {
        detectedElements.clear();
        auto e1 = aisObjects.begin();
        auto e2 = entities.begin();
        auto e3 = brepShapes.begin();

        while (e1 != aisObjects.end() || e2 != entities.end() || e3 != brepShapes.end()) {
            AIS_InteractiveObject* c1 = (e1 != aisObjects.end()) ? *e1++ : nullptr;
            InteractiveEntity* c2 = (e2 != entities.end()) ? *e2++ : nullptr;
            TopoDS_Shape* c3 = (e3 != brepShapes.end()) ? *e3++ : nullptr;
            detectedElements.append(Element(c1, c2, c3));
        }
    }

    // 设置单个检测元素
    void setDetectedElement(AIS_InteractiveObject* aisObject, InteractiveEntity* entity, TopoDS_Shape* brepShape) {
        detectedElements.clear();
        detectedElements.append(Element(aisObject, entity, brepShape));
    }

    //// 获取拾取轴
    //Ax1 pickAxis() const {
    //    return viewport->ViewAxis(screenPoint.x(), screenPoint.y());
    //}
};


#endif  // SRC_IACT_WORKSPACE_MOUSEEVENTDATA_H_