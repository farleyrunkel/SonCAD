// Copyright [2024] SunCAD

#include "Iact/HudElements/Cursors.h"

QCursor Cursors::Wait() { return Qt::WaitCursor; }

QCursor Cursors::Move() { return GetOrCreate("Move"); }

QCursor Cursors::Rotate() { return GetOrCreate("Rotate"); }

QCursor Cursors::SelectShape() { return GetOrCreate("SelectShape"); }

QCursor Cursors::SelectVertex() { return GetOrCreate("SelectVertex"); }

QCursor Cursors::SelectEdge() { return GetOrCreate("SelectEdge"); }

QCursor Cursors::SelectWire() { return GetOrCreate("SelectWire"); }

QCursor Cursors::SelectFace() { return GetOrCreate("SelectFace"); }

QCursor Cursors::SetPoint() { return GetOrCreate("SetPoint"); }

QCursor Cursors::SetRadius() { return GetOrCreate("SetRadius"); }

QCursor Cursors::SetHeight() { return GetOrCreate("SetHeight"); }

QCursor Cursors::WorkingPlane() { return GetOrCreate("_WorkingPlane"); }

QCursor Cursors::Plus() { return GetOrCreate("Plus"); }

QCursor Cursors::Minus() { return GetOrCreate("Minus"); }

QMap<QString, QCursor> Cursors::s_cursors;

QCursor Cursors::GetOrCreate(const QString& cursorId)
{
    if(!s_cursors.contains(cursorId))
    {

        QString path = ":/Cursors/" + cursorId + ".cur";
        QFile file(path);

        if(!file.exists())
        {
            qWarning() << "Cursor file not found:" << path;
            return Qt::ArrowCursor;
        }

        QPixmap pixmap(path);
        QCursor cursor(pixmap);
        s_cursors.insert(cursorId, cursor);
    }

    return s_cursors.value(cursorId, Qt::ArrowCursor);
}
