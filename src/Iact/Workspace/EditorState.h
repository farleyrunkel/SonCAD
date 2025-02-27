// Copyright [2024] SunCAD

#ifndef IACT_WORKSPACE_EDITORSTATE_H_
#define IACT_WORKSPACE_EDITORSTATE_H_

// Qt includes
#include <QObject>
#include <QString>



class EditorState final : public QObject 
{
public:
	 EditorState();
private:
	QString _ActiveTool;
};

#endif // IACT_WORKSPACE_EDITORSTATE_H_
