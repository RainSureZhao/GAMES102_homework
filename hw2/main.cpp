#include<iostream>
#include<vector>
#include<algorithm>
#include<future>

#include "glad/glad.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "imgui_internal.h"
#include "GLFW/glfw3.h"

#include "Utils.h"
#include "Eigen/Eigen"
#include "Python/include/Python.h"
#include "RbfNetWork.h"

GLFWwindow *g_window = nullptr;
const int g_width = 1600;
const int g_height = 1200;

ImVec2 g_canvas_pos_ul = {0, 0};
ImVec2 g_canvas_pos_br = {0, 0};

RbfNetWork rbf_nn;

struct {
    std::vector<Eigen::Vector2f> points;
    bool visible = false;
} polygon_inter;

struct {
    std::vector<Eigen::Vector2f> points;
    int m = 0;
    int m_temp = 0;
    float sigma2 = 50.f;
    float sigma2_temp = 50.0f;
    bool visible = false;
    bool update = false;
} gauss_inter;

struct {
    std::vector<Eigen::Vector2f> points;
    int m = 0;
    int m_temp = 0;
    bool visible = false;
    bool update = false;
} approach_poly;

struct {
    std::vector<Eigen::Vector2f> points;
    int m = 0;
    int m_temp = 0;
    float lambda = 0.5f;
    float lambda_temp = 0.5f;
    bool visible = false;
    bool update = false;
}approach_norm_poly ;

struct {
    std::vector<Eigen::Vector2f> points;
    int num_middle = 4;
    int num_middle_temp = 4;
    int epochs = 3000;
    int epochs_temp = 3000;
    bool visible = false;
    bool update = false;
    bool training = false;
    bool finished = true;
    std::future<std::vector<Eigen::Vector2f>> future;
}RBF_NN;

void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

std::vector<Eigen::Vector2f> 
TrainRbfNetWork(const std::vector<Eigen::Vector2f> &in_pos, int num_middle, int epochs, float l, float r, float step, bool &training)
{
    auto res = rbf_nn.Train(in_pos, num_middle, epochs, l, r, step);
    training = false;
    return res;
}

bool init()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    g_window = glfwCreateWindow(g_width, g_height, "GAMES102 hw1", nullptr, nullptr);
    if(g_window == nullptr) {
        std::cerr << "Failed to create GLFW window" << "\n";
        glfwTerminate();
        return false;
    }
    glfwMakeContextCurrent(g_window);
    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return false;
    }
    glViewport(0, 0, g_width, g_height);
    std::cout << "GL_VERSION: " << glGetString(GL_VERSION) <<  std::endl;
    std::cout << "GL_VENDOR: " << glGetString(GL_VENDOR) <<  std::endl;
    std::cout << "GL_RENDERER: " << glGetString(GL_RENDERER) <<  std::endl;

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    (void) io;
    ImFontConfig font_config;
    font_config.SizePixels = 24.0f;
    io.Fonts->AddFontDefault(&font_config);
    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(g_window, true);
    ImGui_ImplOpenGL3_Init("#version 330 core");

    Py_Initialize();
    if (!rbf_nn.Initialize()) {
        std::cout << "Failed to initialize RBF Network" << std::endl;
        return false;
    }

    return true;
}

void BeginFrame()
{
    glfwPollEvents();
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}

void EndFrame()
{
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    glfwSwapBuffers(g_window);
}

void Finalize()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(g_window);
    glfwTerminate();


    rbf_nn.Finalize();
    if(Py_FinalizeEx() < 0) {
        std::cout << "Failed when Py_FinalizeEx" << "\n";
    }
}

void PlotLineSegments(const std::vector<Eigen::Vector2f> &pass, ImDrawList *drawList, ImU32 line_col, ImU32 point_col)
{   // draw lines
    for(int i = 1; i < pass.size(); i ++) {
        drawList->AddLine({g_canvas_pos_ul.x + pass[i - 1].x(), g_canvas_pos_br.y - pass[i - 1].y()},
                          {pass[i].x() + g_canvas_pos_ul.x, g_canvas_pos_br.y - pass[i].y()}, line_col, 2.0f);
    }
    for(auto x : pass) {
        drawList->AddCircle({g_canvas_pos_ul.x + x.x(), g_canvas_pos_br.y - x.y()}, 5.0f, point_col);
        drawList->AddCircleFilled({g_canvas_pos_ul.x + x.x(), g_canvas_pos_br.y - x.y()}, 5.0f, point_col);
    }
}

int main()
{
    if(!init()) return -1;
    std::vector<Eigen::Vector2f> in_pos;

    while(!glfwWindowShouldClose(g_window)) {
        BeginFrame();
        processInput(g_window);

        if(ImGui::Begin("Config")) {
            ImGui::Checkbox("Polygon_inter(Red)", &polygon_inter.visible);
            ImGui::Checkbox("Gauss_inter(Green)", &gauss_inter.visible);
            ImGui::SameLine();
            ImGui::PushItemWidth(500.0f);
            ImGui::InputFloat("sigma", &gauss_inter.sigma2_temp);
            gauss_inter.sigma2_temp = std::max(gauss_inter.sigma2_temp, 1.0f);
            if(gauss_inter.sigma2_temp != gauss_inter.sigma2) {
                gauss_inter.sigma2 = gauss_inter.sigma2_temp;
                gauss_inter.update = true;
            }
            ImGui::Checkbox("Fitting(Blue)", &approach_poly.visible);
            ImGui::SameLine();
            ImGui::InputInt("m##2", &approach_poly.m_temp);
            approach_poly.m_temp = std::clamp(approach_poly.m_temp, 0, std::max(0, (int)approach_poly.points.size() - 1));
            if(approach_poly.m_temp != approach_poly.m) {
                approach_poly.m = approach_poly.m_temp;
                approach_poly.update = true;
            }

            ImGui::Checkbox("Fitting-norm(Yellow)", &approach_norm_poly.visible);
            ImGui::SameLine();
            ImGui::InputInt("m##3", &approach_norm_poly.m_temp);
            approach_norm_poly.m_temp = std::clamp(approach_norm_poly.m_temp, 0, std::max(0, (int)approach_norm_poly.points.size() - 1));
            if(approach_norm_poly.m_temp != approach_norm_poly.m) {
                approach_norm_poly.m = approach_norm_poly.m_temp;
                approach_norm_poly.update = true;
            }
            
            ImGui::SameLine();
            ImGui::InputFloat("lambda", &approach_norm_poly.lambda_temp);
            approach_norm_poly.lambda_temp = std::max(approach_norm_poly.lambda_temp, 0.0f);
            if(approach_norm_poly.lambda_temp != approach_norm_poly.lambda) {
                approach_norm_poly.lambda = approach_norm_poly.lambda_temp;
                approach_norm_poly.update = true;
            }
            
            ImGui::Checkbox("RBF NetWork (Pink)", &RBF_NN.visible);
            ImGui::SameLine();
            RBF_NN.update = ImGui::Button("Train");
            if(RBF_NN.training) {
                RBF_NN.update = false;
            }
            ImGui::SameLine();
            ImGui::LabelText("##1", "%s", RBF_NN.training ? "(training)" : "");
            ImGui::LabelText("##2", "# middle: %d", RBF_NN.num_middle);
            ImGui::SameLine();
            ImGui::InputInt("##3", &RBF_NN.num_middle_temp);
            RBF_NN.num_middle_temp = std::max(1, RBF_NN.num_middle_temp);
            ImGui::LabelText("##4", "# epochs %d", RBF_NN.epochs);
            ImGui::SameLine();
            ImGui::InputInt("##5", &RBF_NN.epochs_temp);
            RBF_NN.epochs_temp = std::max(1, RBF_NN.epochs_temp);
            ImGui::PopItemWidth();
            ImGui::End();
        }
        if(ImGui::Begin("Canvas")) {
            g_canvas_pos_ul = ImGui::GetCursorScreenPos();
            ImVec2 canvas_size = ImGui::GetContentRegionAvail();
            if(canvas_size.x < 50.0f) {
                canvas_size.x = 50.0f;
            }
            if(canvas_size.y < 50.0f) {
                canvas_size.y = 50.0f;
            }
            g_canvas_pos_br = ImVec2(g_canvas_pos_ul.x + canvas_size.x, g_canvas_pos_ul.y + canvas_size.y);
            ImGuiIO &io = ImGui::GetIO();
            ImDrawList *drawList = ImGui::GetWindowDrawList();
            drawList->AddRectFilled(g_canvas_pos_ul, g_canvas_pos_br, IM_COL32(50, 50, 50, 255));
            drawList->AddRect(g_canvas_pos_ul, g_canvas_pos_br, IM_COL32(255, 255, 255, 255));

            float step = 10.0f;
            float l = step;
            float r = g_canvas_pos_br.x - g_canvas_pos_ul.x;
            ImGui::InvisibleButton("canvas", canvas_size);
            const bool is_hovered = ImGui::IsItemHovered();
            if(is_hovered && ImGui::IsMouseClicked(ImGuiMouseButton_Left)) {
                in_pos.emplace_back(io.MousePos.x - g_canvas_pos_ul.x, g_canvas_pos_br.y - io.MousePos.y);
                std::sort(in_pos.begin(), in_pos.end(), [](const Eigen::Vector2f &a, Eigen::Vector2f &b){
                    return a.x() < b.x();
                });
                polygon_inter.points = Utils::Polygon_Inter(in_pos, l, r, step);
                gauss_inter.update = true;
                approach_poly.update = true;
                approach_norm_poly.update = true;
            } else if(is_hovered && ImGui::IsMouseClicked(ImGuiMouseButton_Right)) {
                Eigen::Vector2f position(io.MousePos.x - g_canvas_pos_ul.x, g_canvas_pos_br.y - io.MousePos.y);
                size_t index = 0;
                float min_dist = std::numeric_limits<float>::max();
                for(int i = 0; i < in_pos.size(); i ++) {
                    float dist = (position - in_pos[i]).squaredNorm();
                    if(dist < min_dist) {
                        min_dist = dist;
                        index = i;
                    }
                }
                if(min_dist <= 100.0f) {
                    in_pos.erase(in_pos.begin() + index);
                    polygon_inter.points = Utils::Polygon_Inter(in_pos, l, r, step);
                    gauss_inter.update = true;
                    approach_poly.update = true;
                    approach_norm_poly.update = true;
                }
            }
            if(gauss_inter.update) {
                gauss_inter.points = Utils::Gauss_Inter(in_pos, l, r, step, gauss_inter.sigma2);
                gauss_inter.update = false;
            }
            if(approach_poly.update) {
                approach_poly.points = Utils::Approach_Poly(in_pos, l, r, step, approach_poly.m);
                approach_poly.update = false;
            }
            if(approach_norm_poly.update) {
                approach_norm_poly.points = Utils::Approach_Poly_Norm(in_pos, l, r, step, approach_norm_poly.m, approach_norm_poly.lambda);
                approach_norm_poly.update = false;
            }
            if(RBF_NN.update) {
                RBF_NN.num_middle = RBF_NN.num_middle_temp;
                RBF_NN.epochs = RBF_NN.epochs_temp;
                RBF_NN.points = rbf_nn.Train(in_pos, RBF_NN.num_middle, RBF_NN.epochs, l, r, step);
                RBF_NN.update = false;
                RBF_NN.training = true;
                RBF_NN.finished = false;
                RBF_NN.future = std::async(std::launch::async, TrainRbfNetWork, in_pos,
                                           RBF_NN.num_middle, RBF_NN.epochs, l, r, step, std::ref(RBF_NN.training));
            }
            if(!RBF_NN.training && !RBF_NN.finished) {
                RBF_NN.points = RBF_NN.future.get();
                RBF_NN.finished = true;
            }
            
            
            
            if(polygon_inter.visible) {
                PlotLineSegments(polygon_inter.points, drawList, IM_COL32(255, 50, 50, 255), IM_COL32(255, 80, 80, 255));
            }
            if(gauss_inter.visible) {
                PlotLineSegments(gauss_inter.points, drawList, IM_COL32(50, 255, 50, 255), IM_COL32(80, 255, 80, 255));
            }
            if(approach_poly.visible) {
                PlotLineSegments(approach_poly.points, drawList, IM_COL32(50, 50, 255, 255), IM_COL32(80, 80, 255, 255));
            }
            if(approach_norm_poly.visible) {
                PlotLineSegments(approach_norm_poly.points, drawList, IM_COL32(255, 255, 50, 255), IM_COL32(255, 255, 80, 255));
            }
            if(RBF_NN.visible) {
                PlotLineSegments(RBF_NN.points, drawList, IM_COL32(255, 192, 203, 255), IM_COL32(255, 192, 203, 255));
            }
            PlotLineSegments(in_pos, drawList, IM_COL32(255, 255, 255, 0), IM_COL32(255, 255, 255, 255));
            ImGui::End();
        }
        EndFrame();
    }
    Finalize();
    return 0;

}
