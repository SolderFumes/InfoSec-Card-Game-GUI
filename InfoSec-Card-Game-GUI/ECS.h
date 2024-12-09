#ifndef ECS_H
#define ECS_H

#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>

//An entity keeps a list of components (like position and stuff) and a manager will keep a list of entities :)
class Component;
class Entity;

//basically saying that every time we type ComponentID, we mean a size_t variable.
//This is for readability and basically creating a "new data type" that is really just a named size_t.
using ComponentID = std::size_t;

inline ComponentID getComponentTypeID() {
	//every time we call this function, it will return the next component ID after the previous call
	//2nd call will get 2, 3rd will get 3, etc.
	static ComponentID lastID = 0;
	return lastID++;
}

template <typename T> inline ComponentID getComponentTypeID() noexcept {
	static ComponentID typeID = getComponentTypeID();
	return typeID;
}

//max amt of components an entity can hold
constexpr std::size_t maxComponents = 32;

//this bitset will allow us to check if an entity has a component or not
using ComponentBitSet = std::bitset<maxComponents>;
using ComponentArray = std::array<Component*, maxComponents>;

class Component {
public:
	//reference to the components owner
	Entity* entity;

	virtual void init() {};
	virtual void update() {};
	virtual void draw() {};
	
	virtual ~Component() {};

};

class Entity {
public:
	void update() {
		for (auto& c : components) c->update();
	};
	void draw() {
		for (auto& c : components) c->draw();
	};
	
	bool isActive() const { return active; };
	//any given component can use it's reference to it's owner to call the entity's destroy function
	void destroy() { active = false; };

	template <typename T> bool hasComponent() const {
		//if the bit we are checking is one, that means that the component is there, and will return true.
		return componentBitSet[getComponentTypeID<T>];
	}

	template <typename T, typename... TArgs> 
	// the && denotes that an argument is an r-value, which is like the number 6 
	//in that it doesn't have a spot in memory (need more info)
	T& addComponent(TArgs&&... mArgs) {
		T* c(new T(std::forward<TArgs>(mArgs)...));
		c->entity = this;
		std::unique_ptr<Component> uPtr(c);
		components.emplace_back(std::move(uPtr));

		componentArray[getComponentTypeID<T>()] = c;
		componentBitSet[getComponentTypeID<T>()] = true;

		c->init();
		return *c;
	}

	template <typename T> T& getComponent() const {
		auto ptr(componentArray[getComponentTypeID<T>()]);
		return *static_cast<T*>(ptr);
	}
	//example use of this system
	//gameObject.getComponent<PositionComponent>().setXpos(25);
private:
	//if false we can remove entity
	bool active = true;
	std::vector<std::unique_ptr<Component>> components;

	ComponentArray componentArray;
	ComponentBitSet componentBitSet;

};

class Manager {
public:
	void update() {
		//for all entities in our vector of entities, update them
		for (auto& e : entities) e->update();
	} 
	void draw() {
		for (auto& e : entities) e->draw();
	}

	void refresh() {
		//check all entities and remove those that aren't there anymore
		entities.erase(std::remove_if(std::begin(entities), std::end(entities),
			[](const std::unique_ptr<Entity>& mEntity) {
				return !mEntity->isActive();
			}),
				std::end(entities));
	}

	Entity& addEntity() {
		Entity* e = new Entity();
		std::unique_ptr<Entity> uPtr(e);
		entities.emplace_back(std::move(uPtr));
		return *e;
	}
private:
	std::vector<std::unique_ptr<Entity>> entities;
};

#endif /* ECS_H */