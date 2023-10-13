#pragma once

class Engine
{
private:	

protected:
	static Engine* singleton;
public:
	Engine();
	~Engine();
	static Engine* GetSingleton(bool);
};
