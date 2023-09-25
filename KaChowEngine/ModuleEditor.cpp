#include "ModuleEditor.h"
#include "Application.h"
#include "ModuleWindow.h"
#include "ModuleRenderer3D.h"

#include "ImGui/imgui.h"
#include "ImGui/backends/imgui_impl_opengl3.h"
// "pilota" Hauria de ser imgui_impl_sdl2
#include "ImGui/backends/imgui_impl_sdl.h"

ModuleEditor::ModuleEditor(Application* app, bool start_enabled) : Module(app, start_enabled)
{

}

ModuleEditor::~ModuleEditor()
{

}

bool ModuleEditor::Init()
{
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // "pilota"

    //io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // Enable Docking
    //io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;       // Enable Multi-Viewport / Platform Windows

    // Setup Dear ImGui style

    // Canviar color de editor
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsLight();

    // Setup Platform/Renderer backends
    ImGui_ImplSDL2_InitForOpenGL(App->window->window, App->renderer3D->context);
    ImGui_ImplOpenGL3_Init();

	return true;
}


// Tot lo de ImGui ha de passar per aqui
void ModuleEditor::DrawEditor()
{
    // Start the Dear ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();

    // HERE ALL WINDOW RENDERS
    // Always EndMenu when Begin Menu
    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {
            ImGui::Text("Hello world!");
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }


    if (ImGui::Begin("Configuration"))
    {
        ImGui::PlotHistogram("FPS", &mFPSLog[0], mFPSLog.size());
        ImGui::End();
    }


    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

bool ModuleEditor::CleanUp()
{
    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();

	return true;
}

void ModuleEditor::AddFPS(const float aFPS)
{
    if (mFPSLog.size() < 30)
    {
        mFPSLog.push_back(aFPS);
    }
    else
    {
        std::vector<float> mTempFPS;
        mTempFPS.reserve(30);
        memcpy(&mTempFPS, &mFPSLog[1], 27);
        mTempFPS.push_back(aFPS);
        mFPSLog = mTempFPS;
    }
}

/*
    ImGui::Render();
    glViewport(0, 0, (int)io.DisplaySize.x, (int)io.DisplaySize.y);
    glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
    glClear(GL_COLOR_BUFFER_BIT);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
*/