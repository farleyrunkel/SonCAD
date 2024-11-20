// Copyright [2024] SunCAD

#ifndef SRC_COMM_SERIALIZATION_SERIALIZATIONCONTEXT_H
#define SRC_COMM_SERIALIZATION_SERIALIZATIONCONTEXT_H

#include <QMap>
#include <QVariant>
#include <QString>
#include <QList>
#include <QStack>
#include <QDebug>

namespace Sun {

	// ö�٣����л���Χ
	enum class SerializationScope
	{
		Storage,
		UndoRedo,
		CopyPaste
	};

	// ö�٣����л����
	enum class SerializationResult
	{
		None,
		VersionMismatch
	};

	class SerializationContext
	{
	public:
		SerializationContext(SerializationScope Scope = SerializationScope::Storage);

		// �����¼
		void AddError(const QString& Message);
		bool HasErrors() const;
		QList<QString> GetErrors() const;

		// ��������
		template <typename T>
		void SetParameter(const QString& Key, const T& Value);

		template <typename T>
		T GetParameter(const QString& Key, const T& DefaultValue = T()) const;

		void RemoveParameter(const QString& Key);

		// ʵ������
		template <typename T>
		void SetInstance(T* Instance);

		template <typename T>
		T* GetInstance() const;

		template <typename T>
		void RemoveInstance();

	private:
		QMap<QString, QVariant> Parameters;  // ������
		QMap<QString, void*> Instances;     // ʵ����
		QList<QString> Errors;              // �����¼
		SerializationScope Scope;           // ���л���Χ
		SerializationResult Result;         // ���л����
	};

}  // namespace Sun

#endif // SRC_COMM_SERIALIZATION_SERIALIZATIONCONTEXT_H
