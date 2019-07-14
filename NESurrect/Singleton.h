#pragma once

class Singleton {
public:
	Singleton& instance() { static Singleton instance; return instance; }
private:
	Singleton();
	Singleton(const Singleton&);
	~Singleton();
};