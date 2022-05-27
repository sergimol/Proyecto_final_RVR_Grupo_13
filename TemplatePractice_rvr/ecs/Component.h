#ifndef COMPONENT_H_
#define COMPONENT_H_

class Entity;

class Component {
public:

	Component() : entity_(nullptr) {}

	virtual ~Component() {}

	inline void setEntity(Entity *e) {
		entity_ = e;
	}

	inline Entity* getEntity() {
		return entity_;
	}

	virtual void init() {}

	virtual void update() {}

	virtual void render() {}

protected:

	Entity *entity_;
};
#endif