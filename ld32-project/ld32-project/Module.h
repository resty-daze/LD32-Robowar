#pragma once

class Module {
public:
	virtual ~Module() {}
	virtual void Update() = 0;
	virtual void Render() = 0;
};
