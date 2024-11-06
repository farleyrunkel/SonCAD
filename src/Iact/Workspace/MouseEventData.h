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
// ����¼������ӿ�
class IMouseEventHandler {
public:
    virtual ~IMouseEventHandler() = default;
    virtual bool onMouseMove(MouseEventData* data) = 0;
    virtual bool onMouseDown(MouseEventData* data) = 0;
    virtual bool onMouseUp(MouseEventData* data) = 0;
};

//--------------------------------------------------------------------------------------------------
// ���彻��ʽʵ��Ļ����ӿ�
class InteractiveEntity : public QObject {};
class AIS_InteractiveObject;
class TopoDS_Shape;
class Viewport;
//--------------------------------------------------------------------------------------------------
// ����¼����ݽṹ
class MouseEventData {
public:
    // ����Ԫ���࣬������������ʵ�����״��Ϣ
    struct Element {
        AIS_InteractiveObject* aisObject;
        InteractiveEntity* entity;
        TopoDS_Shape* brepShape;

        // ��ͬ�Ĺ��캯����֧�ֲ�ͬ���������
        Element(AIS_InteractiveObject* aisObj, InteractiveEntity* ent, TopoDS_Shape* brep)
            : aisObject(aisObj), entity(ent), brepShape(brep) {}

        Element(AIS_InteractiveObject* aisObj, TopoDS_Shape* brep = nullptr)
            : aisObject(aisObj), brepShape(brep) {}

        Element(InteractiveEntity* ent)
            : entity(ent) {}
    };

    // ����ѡ����
    class ReturnOptions {
    public:
        QList<Element> additionalHighlights;
        bool forceReDetection = false;
        bool removeHighlighting = false;

        // ��շ���ѡ������
        void clear() {
            additionalHighlights.clear();
            forceReDetection = false;
            removeHighlighting = false;
        }
    };

    // ����¼����ݵ���Ҫ����
    Viewport* viewport = nullptr;
    QPoint screenPoint;
    QVector3D pointOnPlane;
    Qt::KeyboardModifiers modifierKeys;
    QList<Element> detectedElements;
    ReturnOptions returnOptions;

    // ���캯��
    MouseEventData(Viewport* vp, const QPoint& sp, const QVector3D& pp, Qt::KeyboardModifiers mk)
        : viewport(vp), screenPoint(sp), pointOnPlane(pp), modifierKeys(mk) {}

    // ��⵽����Ҫʵ��
    InteractiveEntity* detectedEntity() const {
        return !detectedElements.isEmpty() ? detectedElements[0].entity : nullptr;
    }

    TopoDS_Shape* detectedBrepShape() const {
        return !detectedElements.isEmpty() ? detectedElements[0].brepShape : nullptr;
    }

    AIS_InteractiveObject* detectedAisObject() const {
        return !detectedElements.isEmpty() ? detectedElements[0].aisObject : nullptr;
    }

    // �����¼�����
    void clear() {
        viewport = nullptr;
        screenPoint = QPoint();
        pointOnPlane = QVector3D();
        detectedElements.clear();
        returnOptions.clear();
    }

    // �����¼�����
    void set(Viewport* vp, const QPoint& sp, const QVector3D& pp, Qt::KeyboardModifiers mk) {
        clear();
        viewport = vp;
        screenPoint = sp;
        pointOnPlane = pp;
        modifierKeys = mk;
    }

    // ���ü��Ԫ�ص��б�
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

    // ���õ������Ԫ��
    void setDetectedElement(AIS_InteractiveObject* aisObject, InteractiveEntity* entity, TopoDS_Shape* brepShape) {
        detectedElements.clear();
        detectedElements.append(Element(aisObject, entity, brepShape));
    }

    //// ��ȡʰȡ��
    //Ax1 pickAxis() const {
    //    return viewport->ViewAxis(screenPoint.x(), screenPoint.y());
    //}
};


#endif  // SRC_IACT_WORKSPACE_MOUSEEVENTDATA_H_