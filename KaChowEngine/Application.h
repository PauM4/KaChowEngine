#pragma once

#include "Globals.h"
#include "Timer.h"

#include "Module.h"
#include "ModuleCamera3D.h"
#include "ModuleEditor.h"
#include "ModuleInput.h"
#include "ModuleRenderer3D.h"
#include "ModuleWindow.h"

#include<vector>

// Aix� estalvia copiar els .h a tot arreu al compilar
class Modules;
class ModuleWindow;
class ModuleInput;
class ModuleRenderer3D;
class ModuleCamera3D;
class ModuleEditor;


class Application
{
public:
	ModuleWindow* window;
	ModuleInput* input;
	ModuleRenderer3D* renderer3D;
	ModuleCamera3D* camera;
	ModuleEditor* editor;

private:

	Timer	ms_timer;
	float	dt;
	std::vector<Module*> list_modules;

public:

	Application();
	~Application();

	bool Init();
	update_status Update();
	bool CleanUp();

	float GetDT();

private:

	void AddModule(Module* mod);
	void PrepareUpdate();
	void FinishUpdate();
};