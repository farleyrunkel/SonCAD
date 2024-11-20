// Copyright [2024] SunCAD

#include "Comm/Serialization/SerializationContext.h"

namespace Sun {
	// 构造函数
	SerializationContext::SerializationContext(SerializationScope Scope)
		: Scope(Scope), Result(SerializationResult::None) {}

	// 错误记录
	void SerializationContext::AddError(const QString& Message) {
		Errors.append(Message);
	}

	bool SerializationContext::HasErrors() const {
		return !Errors.isEmpty();
	}

	QList<QString> SerializationContext::GetErrors() const {
		return Errors;
	}

	// 参数管理
	template <typename T>
	void SerializationContext::SetParameter(const QString& Key, const T& Value) {
		Parameters[Key] = QVariant::fromValue(Value);
	}

	template <typename T>
	T SerializationContext::GetParameter(const QString& Key, const T& DefaultValue) const {
		if (Parameters.contains(Key)) {
			return Parameters[Key].value<T>();
		}
		return DefaultValue;
	}

	void SerializationContext::RemoveParameter(const QString& Key) {
		Parameters.remove(Key);
	}

	// 实例管理
	template <typename T>
	void SerializationContext::SetInstance(T* Instance) {
		const QString TypeName = QString::fromUtf8(typeid(T).name());
		Instances[TypeName] = Instance;
	}

	template <typename T>
	T* SerializationContext::GetInstance() const {
		const QString TypeName = QString::fromUtf8(typeid(T).name());
		if (Instances.contains(TypeName)) {
			return static_cast<T*>(Instances[TypeName]);
		}
		return nullptr;
	}

	template <typename T>
	void SerializationContext::RemoveInstance() {
		const QString TypeName = QString::fromUtf8(typeid(T).name());
		Instances.remove(TypeName);
	}
}
