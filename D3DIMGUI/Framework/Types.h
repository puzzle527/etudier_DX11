#pragma once
//씬타입으로는 객체를만들수 없다.
class Scene
{
public:
	virtual ~Scene() {};
	//선언만 해놓은 함수
	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual void ResizeScreen() = 0;
};
