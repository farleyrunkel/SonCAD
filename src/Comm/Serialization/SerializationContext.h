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

	// 枚举：序列化范围
	enum class SerializationScope
	{
		Storage,
		UndoRedo,
		CopyPaste
	};

	// 枚举：序列化结果
	enum class SerializationResult
	{
		None,
		VersionMismatch
	};

	class SerializationContext
	{
	public:
		SerializationContext(SerializationScope Scope = SerializationScope::Storage);

		// 错误记录
		void AddError(const QString& Message);
		bool HasErrors() const;
		QList<QString> GetErrors() const;

		// 参数管理
		template <typename T>
		void SetParameter(const QString& Key, const T& Value);

		template <typename T>
		T GetParameter(const QString& Key, const T& DefaultValue = T()) const;

		void RemoveParameter(const QString& Key);

		// 实例管理
		template <typename T>
		void SetInstance(T* Instance);

		template <typename T>
		T* GetInstance() const;

		template <typename T>
		void RemoveInstance();

	private:
		QMap<QString, QVariant> Parameters;  // 参数表
		QMap<QString, void*> Instances;     // 实例表
		QList<QString> Errors;              // 错误记录
		SerializationScope Scope;           // 序列化范围
		SerializationResult Result;         // 序列化结果
	};

}  // namespace Sun

#endif // SRC_COMM_SERIALIZATION_SERIALIZATIONCONTEXT_H
