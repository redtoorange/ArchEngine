#pragma once
#include "TransformComponent.h"
#include <map>
#include <memory>

namespace arch {
	class Entity {
	public:
		Entity(const std::string& name, Entity* parent);

		Entity(const Entity& other);

		Entity& operator=(const Entity& other);

		virtual ~Entity();

		TransformComponent GetTransform() const;

		void SetTransform(const TransformComponent& transform);

		Entity* GetParent() const;

		void SetParent(Entity* parent);

		const std::string& GetName() const;

		void SetName(const std::string& name);

		void AddChild(Entity* child);

		bool RemoveChild(const std::string& name);

		bool RemoveChild(Entity* child);

		Entity* GetChild( const std::string& name );

		Entity* TakeChild( const std::string& name );

	private:
		std::string m_name;
		TransformComponent m_transform;

		Entity* m_parent;
		std::map<std::string, std::unique_ptr<Entity>> m_children;
	};

}
