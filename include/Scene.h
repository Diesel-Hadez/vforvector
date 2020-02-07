#ifndef SCENE_H
#define SCENE_H
#include <string>

class Scene
{
protected:
public:
	std::string m_SceneName;
	bool m_End;
	virtual void Update() = 0;
	virtual void Render() = 0;
	Scene();
	virtual ~Scene();
};
#endif
