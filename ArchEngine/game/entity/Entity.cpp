#include "Entity.h"

namespace arch {
	Entity::Entity(const std::string& name, Entity* parent) : m_name(name), m_parent(parent) { }

	/**
	 * Create a new Entity from an old one. Does NOT copy over the children, 
	 * only the name, transform and parent reference.
	 * @param	other The source Entity to copy from.
	 */
	Entity::Entity(const Entity& other) : m_name(other.m_name),
	                                      m_transform(other.m_transform),
	                                      m_parent(other.m_parent) { }

	/**
	 * Set two Entitys equal, does NOT copy over the children, only the name, transform and parent reference.
	 * @param	other The source Entity to copy from.
	 * @return	The new entity with it'd children un changed.
	 */
	Entity& Entity::operator=(const Entity& other) {
		if (this == &other)
			return *this;

		m_name = other.m_name;
		m_transform = other.m_transform;
		m_parent = other.m_parent;

		return *this;
	}

	Entity::~Entity() {
		// Delete all children
		// Delete this
	}

	TransformComponent Entity::GetTransform() const {
		return m_transform;
	}

	void Entity::SetTransform(const TransformComponent& transform) {
		m_transform = transform;
	}

	Entity* Entity::GetParent() const {
		return m_parent;
	}

	void Entity::SetParent(Entity* parent) {
		if (m_parent != parent)
			m_parent = parent;
	}

	const std::string& Entity::GetName() const {
		return m_name;
	}

	void Entity::SetName(const std::string& name) {
		m_name = name;
	}

	/**
	 * Add a child to this Entity, the child will be reparented.  Reparenting
	 * removes the child from the old parent's child list, sets the parent to this
	 * and adds it to this' child list.  This will result in this Entity OWNING the
	 * child Entity.  It's memeory will be managed and it will be deleted when its
	 * parent is deleted.
	 * @child	Pointer to the Entity to add and reparent.
	 */
	void Entity::AddChild(Entity* child) {
		if (child) {
			// Reparent
			auto oldParent = child->GetParent();
			if (oldParent)
				oldParent->RemoveChild(child);
			child->SetParent(this);

			// Take ownership
			m_children[child->GetName()].reset(child);
		}
	}

	/**
	 * Remove a child from this Entity by name, this does NOT result in the child's 
	 * parent being reset or it being deleted.  The memory of the child will be unmanaged
	 * after this operation.
	 * @param	name	Name of the Entity to remove
	 * @return	true if the Entity was found and removed, false otherwise.
	 */
	bool Entity::RemoveChild(const std::string& name) {
		auto iter = m_children.find(name);
		if (iter != m_children.end()) {
			iter->second.release();
			m_children.erase(iter);
			return true;
		}

		return false;
	}

	/**
	 * Remove a child from this Entity by address, this does NOT result in the child's 
	 * parent being reset or it being deleted.  The memory of the child will be unmanaged
	 * after this operation.
	 * @param	child	Pointer to the Entity to remove
	 * @return	true if the Entity was found and removed, false otherwise.
	 */
	bool Entity::RemoveChild(Entity* child) {
		for (auto iter = m_children.begin(); iter != m_children.end(); ++iter) {
			if (iter->second.get() == child) {
				iter->second.release();
				m_children.erase(iter);
				return true;
			}
		}

		return false;
	}

	/**
	 * Search the immediate children of this Entity to locate one by name.  This will return a
	 * non-owning pointer to the Child.
	 * @param	name	Name of the Entity to find
	 * @return	The Entity or nullptr if not found.
	 */
	Entity* Entity::GetChild(const std::string& name) {
		auto iter = m_children.find(name);
		if (iter != m_children.end()) {
			return iter->second.get();
		}

		return nullptr;
	}

	/**
	 * Search the immediate children of this Entity to locate one by name.  This will return an
	 * OWNING pointer to the Child.  The memory of the child will be unmanaged
	 * after this operation.
	 * @param	name	Name of the Entity to find
	 * @return	The Entity or nullptr if not found.
	 */
	Entity* Entity::TakeChild(const std::string& name) {
		auto iter = m_children.find(name);
		if (iter != m_children.end()) {
			auto kid = iter->second.get();
			iter->second.release();
			m_children.erase(iter);
			return kid;
		}

		return nullptr;
	}
}
