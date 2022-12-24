#include<iostream>
#include<vector>
#include<algorithm>

#include "glad/glad.h"
#include "imgui.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_glfw.h"
#include "imgui_internal.h"
#include "GLFW/glfw3.h"

#include "Eigen/Eigen"
#include "Utils.h"
GLFWwindow *g_window = nullptr;
int g_width = 1800;
int g_height = 900;

ImVec2 g_canvas_pos_ul = {0.0f, 0.0f};
ImVec2 g_canvas_pos_br = {0.0f, 0.0f};

void PlotLineSegments(const std::vector<float> &pos_x, const std::vector<float> &pos_y, ImDrawList *drawList,
   ImU32 line_col, ImU32 point_col, ImVec2 ul = g_canvas_pos_ul, ImVec2 br = g_canvas_pos_br )
{
    int n = pos_x.size();
    for(int i = 1; i < n; i ++) {
        drawList->AddLine({ul.x + pos_x[i - 1], br.y - pos_y[i - 1]},
                          {ul.x + pos_x[i], br.y - pos_y[i]} , line_col, 2.0f                 );
    }
    for(int i = 0; i < n; i ++) {
        drawList->AddCircleFilled({ul.x + pos_x[i], br.y - pos_y[i]}, 5.0f, point_col);
        drawList->AddCircle({ul.x + pos_x[i], br.y - pos_y[i]}, 5.0f, point_col);
    }
}
bool init()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    g_window = glfwCreateWindow(g_width, g_height, "GAMES102 hw3", nullptr, nullptr);
    if(g_window == nullptr) {
        std::cerr << "Failed to create GLFW window" << "\n";
        glfwTerminate();
        return false;
    }

    glfwMakeContextCurrent(g_window);
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cout << "Failed to load glad" << std::endl;
        glfwTerminate();
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

    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(g_window, true);
    ImGui_ImplOpenGL3_Init("#version 330 core");

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
}

struct CurveData
{
    ImU32 line_color = 0;
    ImU32 point_color = 0;
    std::vector<float> pos_x;
    std::vector<float> pos_y;
    std::vector<float> in_pos_t;
    bool visible = false;
    
    void Clear()
    {
        pos_x.clear();
        pos_y.clear();
        in_pos_t.clear();
    }
    
    void Plot(ImDrawList *drawList) {
        if(visible && !pos_x.empty()) {
            PlotLineSegments(pos_x, pos_y, drawList, line_color, point_color);
        }
    }
    
    void PlotXT(const std::vector<float> &pos_t, ImDrawList *drawList, ImVec2 canvas_ul, ImVec2 canvas_br) {
        int n = pos_x.size();
        if(!visible || n == 0) return;
        std::vector<float> pos_x_t = pos_x;
        std::vector<float> pos_t_t = pos_t;
        for(int i = 0; i < n; i ++) {
            pos_x_t[i] = pos_x_t[i] / (g_canvas_pos_br.x - g_canvas_pos_ul.x) * (canvas_br.y - canvas_ul.y);
            pos_t_t[i] = pos_t_t[i] * (canvas_br.x - canvas_ul.x);
        }
        PlotLineSegments(pos_t_t, pos_x_t, drawList, line_color, point_color, canvas_ul, canvas_br);
    }
    
    void PlotYT(const std::vector<float> &pos_t, ImDrawList *drawList, ImVec2 canvas_ul, ImVec2 canvas_br) {
        int n = pos_y.size();
        if(!visible || n == 0) return;
        std::vector<float> pos_x_t = pos_y;
        std::vector<float> pos_t_t = pos_t;
        for(int i = 0; i < n; i ++) {
            pos_x_t[i] = pos_x_t[i] / (g_canvas_pos_br.y - g_canvas_pos_ul.y) * (canvas_br.y - canvas_ul.y);
            pos_t_t[i] = pos_t_t[i] * (canvas_br.x - canvas_ul.x);
        }
        PlotLineSegments(pos_t_t, pos_x_t, drawList, line_color, point_color, canvas_ul, canvas_br);
    }
};

int main()
{
    if(!init()) return -1;
    
    std::vector<float> in_pos_x;
    std::vector<float> in_pos_y;
    
    bool inter_update = false;
    CurveData inter_uniform{IM_COL32(255, 50, 50, 255), IM_COL32(255, 80, 80, 255)};
    CurveData inter_chordal{IM_COL32(50, 255, 50, 255), IM_COL32(80, 255, 80, 255)};
    CurveData inter_centripetal{IM_COL32(50, 50, 255, 255), IM_COL32(80, 80, 255, 255)};
    CurveData inter_foley{IM_COL32(150, 150, 255, 255), IM_COL32(180, 180, 255, 255)};

    bool approx_update = false;
    int approx_m = 0;
    int approx_m_temp = 0;
    CurveData approx_uniform{IM_COL32(50, 255, 255, 255), IM_COL32(80, 255, 255, 255)};
    CurveData approx_chordal{IM_COL32(50, 255, 100, 255), IM_COL32(80, 255, 130, 255)};
    CurveData approx_centripetal{IM_COL32(100, 50, 255, 255), IM_COL32(130, 80, 255, 255)};
    CurveData approx_foley{IM_COL32(170, 255, 170, 255), IM_COL32(200, 255, 200, 255)};

    bool spline_update = false;
    CurveData spline_uniform { IM_COL32(255, 100, 50, 255), IM_COL32(255, 130, 80, 255) };
    CurveData spline_chordal { IM_COL32(50, 255, 100, 255), IM_COL32(80, 255, 130, 255) };
    CurveData spline_centripetal { IM_COL32(100, 50, 255, 255), IM_COL32(130, 80, 255, 255) };
    CurveData spline_foley { IM_COL32(170, 255, 170, 255), IM_COL32(200, 255, 200, 255) };


    float l = 0.0f;
    float r = 1.0f;
    float step = (r - l) / 60.0f;
    std::vector<float> out_pos_t;
    for(float x = l; x <= r; x += step) out_pos_t.push_back(x);
    ImGuiIO &io = ImGui::GetIO();
    ImFontConfig font_config;
    font_config.SizePixels = 24.0f;
    io.Fonts->AddFontDefault(&font_config);
    
    while(!glfwWindowShouldClose(g_window)) {
        BeginFrame();
        if(glfwGetKey(g_window, GLFW_KEY_ESCAPE) == GLFW_PRESS) break;
        
        if(ImGui::Begin("Config")) {
            ImGui::Text("Interpolation");
            ImGui::ColorButton("##1", ImColor(inter_uniform.line_color).Value);
            ImGui::SameLine();
            ImGui::Checkbox("Uniform##1", &inter_uniform.visible);
            ImGui::ColorButton("##2", ImColor(inter_chordal.line_color).Value);
            ImGui::SameLine();
            ImGui::Checkbox("Chordal##1", &inter_chordal.visible);
            ImGui::ColorButton("##3", ImColor(inter_centripetal.line_color).Value);
            ImGui::SameLine();
            ImGui::Checkbox("Centripetal##1", &inter_centripetal.visible);
            ImGui::ColorButton("##4", ImColor(inter_foley.line_color).Value);
            ImGui::SameLine();
            ImGui::Checkbox("Foley##1", &inter_foley.visible);
            
            ImGui::Separator();
            ImGui::Text("Fitting");
            ImGui::ColorButton("##5", ImColor(approx_uniform.line_color).Value);
            ImGui::SameLine();
            ImGui::Checkbox("Uniform##2", &approx_uniform.visible);
            ImGui::ColorButton("##6", ImColor(approx_chordal.line_color).Value);
            ImGui::SameLine();
            ImGui::Checkbox("Chordal##2", &approx_chordal.visible);
            ImGui::ColorButton("##7", ImColor(approx_centripetal.line_color).Value);
            ImGui::SameLine();
            ImGui::Checkbox("Centripetal##2", &approx_centripetal.visible);
            ImGui::ColorButton("##8", ImColor(approx_foley.line_color).Value);
            ImGui::SameLine();
            ImGui::Checkbox("Foley##2", &approx_foley.visible);
            ImGui::InputInt("m", &approx_m_temp);
            approx_m_temp = std::clamp(approx_m_temp, 0, std::max<int>(0, in_pos_x.size() - 1));
            if(approx_m_temp != approx_m) {
                approx_m = approx_m_temp;
                approx_update = true;
            }
            
            ImGui::Separator();
            ImGui::Text("Cubic Spline");
            ImGui::ColorButton("##9", ImColor(spline_uniform.line_color).Value);
            ImGui::SameLine();
            ImGui::Checkbox("Uniform##3", &spline_uniform.visible);
            ImGui::ColorButton("##10", ImColor(spline_chordal.line_color).Value);
            ImGui::SameLine();
            ImGui::Checkbox("Chordal##3", &spline_chordal.visible);
            ImGui::ColorButton("##11", ImColor(spline_centripetal.line_color).Value);
            ImGui::SameLine();
            ImGui::Checkbox("Centripetal##3", &spline_centripetal.visible);
            ImGui::ColorButton("##12", ImColor(spline_foley.line_color).Value);
            ImGui::SameLine();
            ImGui::Checkbox("Foley##3", &spline_foley.visible);
            
            ImGui::Separator();
            bool reset = ImGui::Button("Reset");
            if (reset) {
                in_pos_x.clear();
                in_pos_y.clear();
                inter_uniform.Clear();
                inter_chordal.Clear();
                inter_centripetal.Clear();
                inter_foley.Clear();
                approx_uniform.Clear();
                approx_chordal.Clear();
                approx_centripetal.Clear();
                approx_foley.Clear();
                spline_uniform.Clear();
                spline_chordal.Clear();
                spline_centripetal.Clear();
                spline_foley.Clear();
            }
            ImGui::End();
        }
        if(ImGui::Begin("Canvas")) {
            g_canvas_pos_ul = ImGui::GetCursorScreenPos();
            ImVec2 canvas_size = ImGui::GetContentRegionAvail();
            if(canvas_size.x < 50.0f) canvas_size.x = 50.0f;
            if(canvas_size.y < 50.0f) canvas_size.y = 50.0f;

            g_canvas_pos_br = ImVec2(g_canvas_pos_ul.x + canvas_size.x, g_canvas_pos_ul.y + canvas_size.y);

            ImGuiIO &io = ImGui::GetIO();
            ImDrawList *draw_list = ImGui::GetWindowDrawList();
            draw_list->AddRectFilled(g_canvas_pos_ul, g_canvas_pos_br, IM_COL32(50, 50, 50, 255));
            draw_list->AddRect(g_canvas_pos_ul, g_canvas_pos_br, IM_COL32(255, 255, 255, 255));

            ImGui::InvisibleButton("canvas", canvas_size);
            const bool is_hovered = ImGui::IsItemHovered();

            if (is_hovered && ImGui::IsMouseClicked(ImGuiMouseButton_Left)) {
                in_pos_x.push_back(io.MousePos.x - g_canvas_pos_ul.x);
                in_pos_y.push_back(g_canvas_pos_br.y - io.MousePos.y);
                inter_update = true;
                approx_update = true;
                spline_update = true;
            } else if (is_hovered && ImGui::IsMouseClicked(ImGuiMouseButton_Right)) {
                Eigen::Vector2f pos(io.MousePos.x - g_canvas_pos_ul.x, g_canvas_pos_br.y - io.MousePos.y);
                int index = 0;
                float min_dist = std::numeric_limits<float>::max();
                for (int i = 0; i < in_pos_x.size(); i ++) {
                    float dist = (pos - Eigen::Vector2f(in_pos_x[i], in_pos_y[i])).squaredNorm();
                    if (dist < min_dist) {
                        min_dist = dist;
                        index = i;
                    }
                }
                if (min_dist <= 100.0f) {
                    in_pos_x.erase(in_pos_x.begin() + index);
                    in_pos_y.erase(in_pos_y.begin() + index);
                    inter_update = true;
                    approx_update = true;
                    spline_update = true;
                }
            }
            if(inter_update) {
                inter_uniform.in_pos_t = Utils::ParameterizationUniform(in_pos_x, in_pos_y);
                inter_uniform.pos_x = Utils::InterpolationPolygon(inter_uniform.in_pos_t, in_pos_x, l, r, step);
                inter_uniform.pos_y = Utils::InterpolationPolygon(inter_uniform.in_pos_t, in_pos_y, l, r, step);
                
                inter_chordal.in_pos_t = Utils::ParameterizationChoral(in_pos_x, in_pos_y);
                inter_chordal.pos_x = Utils::InterpolationPolygon(inter_chordal.in_pos_t, in_pos_x, l, r, step);
                inter_chordal.pos_y = Utils::InterpolationPolygon(inter_chordal.in_pos_t, in_pos_y, l, r, step);
                
                inter_centripetal.in_pos_t = Utils::ParameterizationCentripetal(in_pos_x, in_pos_y);
                inter_centripetal.pos_x = Utils::InterpolationPolygon(inter_centripetal.in_pos_t, in_pos_x, l, r, step);
                inter_centripetal.pos_y = Utils::InterpolationPolygon(inter_centripetal.in_pos_t, in_pos_y, l, r, step);
                
                inter_foley.in_pos_t = Utils::ParameterizationFoley(in_pos_x, in_pos_y);
                inter_foley.pos_x = Utils::InterpolationPolygon(inter_foley.in_pos_t, in_pos_x, l, r, step);
                inter_foley.pos_y = Utils::InterpolationPolygon(inter_foley.in_pos_t, in_pos_y, l, r, step);
                
                
                inter_update = false;
            }
            
            if(approx_update) {
                approx_uniform.in_pos_t = Utils::ParameterizationUniform(in_pos_x, in_pos_y);
                approx_uniform.pos_x = Utils::ApproximationPolygon(approx_uniform.in_pos_t, in_pos_x,
                                                                   approx_m, l, r, step);
                approx_uniform.pos_y = Utils::ApproximationPolygon(approx_uniform.in_pos_t, in_pos_y,
                                                                   approx_m, l, r, step);
                
                approx_chordal.in_pos_t = Utils::ParameterizationChoral(in_pos_x, in_pos_y);
                approx_chordal.pos_x = Utils::ApproximationPolygon(approx_chordal.in_pos_t, in_pos_x, 
                                                                   approx_m, l, r, step);
                approx_chordal.pos_y = Utils::ApproximationPolygon(approx_chordal.in_pos_t, in_pos_y,
                                                                   approx_m, l, r, step);
                
                approx_centripetal.in_pos_t = Utils::ParameterizationCentripetal(in_pos_x, in_pos_y);
                approx_centripetal.pos_x = Utils::ApproximationPolygon(approx_centripetal.in_pos_t, in_pos_x,
                                                                       approx_m, l, r, step);
                approx_centripetal.pos_y = Utils::ApproximationPolygon(approx_centripetal.in_pos_t, in_pos_y,
                                                                       approx_m, l, r, step);
                
                approx_foley.in_pos_t = Utils::ParameterizationFoley(in_pos_x, in_pos_y);
                approx_foley.pos_x = Utils::ApproximationPolygon(approx_foley.in_pos_t, in_pos_y,
                                                                 approx_m, l, r, step);
                approx_foley.pos_y = Utils::ApproximationPolygon(approx_foley.in_pos_t, in_pos_x, 
                                                                 approx_m, l, r, step);
                approx_update = false;
            }
            
            if(spline_update) {
                spline_uniform.in_pos_t = Utils::ParameterizationUniform(in_pos_x, in_pos_y);
                spline_uniform.pos_x = Utils::CubicSpline(spline_uniform.in_pos_t, in_pos_x, l, r, step);
                spline_uniform.pos_y = Utils::CubicSpline(spline_uniform.in_pos_t, in_pos_y, l, r, step);
                
                spline_chordal.in_pos_t = Utils::ParameterizationChoral(in_pos_x, in_pos_y);
                spline_chordal.pos_x = Utils::CubicSpline(spline_chordal.in_pos_t, in_pos_x, l, r, step);
                spline_chordal.pos_y = Utils::CubicSpline(spline_chordal.in_pos_t, in_pos_y, l, r, step);
            
                spline_centripetal.in_pos_t = Utils::ParameterizationCentripetal(in_pos_x, in_pos_y);
                spline_centripetal.pos_x = Utils::CubicSpline(spline_centripetal.in_pos_t, in_pos_x, l, r, step);
                spline_centripetal.pos_y = Utils::CubicSpline(spline_centripetal.in_pos_t, in_pos_y, l, r, step);
                
                spline_foley.in_pos_t = Utils::ParameterizationFoley(in_pos_x, in_pos_y);
                spline_foley.pos_x = Utils::CubicSpline(spline_foley.in_pos_t, in_pos_x, l, r, step);
                spline_foley.pos_y = Utils::CubicSpline(spline_foley.in_pos_t, in_pos_y, l, r, step);

                spline_update = false;
            }
            inter_uniform.Plot(draw_list);
            inter_chordal.Plot(draw_list);
            inter_centripetal.Plot(draw_list);
            inter_foley.Plot(draw_list);
            
            approx_uniform.Plot(draw_list);
            approx_chordal.Plot(draw_list);
            approx_centripetal.Plot(draw_list);
            approx_foley.Plot(draw_list);
            
            spline_uniform.Plot(draw_list);
            spline_chordal.Plot(draw_list);
            spline_centripetal.Plot(draw_list);
            spline_foley.Plot(draw_list);

            PlotLineSegments(in_pos_x, in_pos_y, draw_list, IM_COL32(255, 255, 255, 0), IM_COL32(255, 255, 255, 255));
            ImGui::End();
        }
        if(ImGui::Begin("X-T")) {
            ImVec2 canvas_pos_ul = ImGui::GetCursorScreenPos();
            ImVec2 canvas_size = ImGui::GetContentRegionAvail();
            canvas_size.x = std::max(canvas_size.x, 50.0f);
            canvas_size.y = std::max(canvas_size.y, 50.0f);
            ImVec2 canvas_pos_br = ImVec2(canvas_pos_ul.x + canvas_size.x, canvas_pos_ul.y + canvas_size.y);
            
            ImDrawList *drawList = ImGui::GetWindowDrawList();
            drawList->AddRectFilled(canvas_pos_ul, canvas_pos_br, IM_COL32(50, 50, 50, 255));
            drawList->AddRect(canvas_pos_ul, canvas_pos_br, IM_COL32(255, 255, 255, 255));
            
            inter_uniform.PlotXT(out_pos_t, drawList, canvas_pos_ul, canvas_pos_br);
            inter_chordal.PlotXT(out_pos_t, drawList, canvas_pos_ul, canvas_pos_br);
            inter_centripetal.PlotXT(out_pos_t, drawList, canvas_pos_ul, canvas_pos_br);
            inter_foley.PlotXT(out_pos_t, drawList, canvas_pos_ul, canvas_pos_br);
            
            approx_uniform.PlotXT(out_pos_t, drawList, canvas_pos_ul, canvas_pos_br);
            approx_chordal.PlotXT(out_pos_t, drawList, canvas_pos_ul, canvas_pos_br);
            approx_centripetal.PlotXT(out_pos_t, drawList, canvas_pos_ul, canvas_pos_br);
            approx_foley.PlotXT(out_pos_t, drawList, canvas_pos_ul, canvas_pos_br);
            
            spline_uniform.PlotXT(out_pos_t, drawList, canvas_pos_ul, canvas_pos_br);\
            spline_chordal.PlotXT(out_pos_t, drawList, canvas_pos_ul, canvas_pos_br);
            spline_centripetal.PlotXT(out_pos_t, drawList, canvas_pos_ul, canvas_pos_br);
            spline_foley.PlotXT(out_pos_t, drawList, canvas_pos_ul, canvas_pos_br);
            
            ImGui::End();
        }

        if(ImGui::Begin("Y-T")) {
            ImVec2 canvas_pos_ul = ImGui::GetCursorScreenPos();
            ImVec2 canvas_size = ImGui::GetContentRegionAvail();
            canvas_size.x = std::max(canvas_size.x, 50.0f);
            canvas_size.y = std::max(canvas_size.y, 50.0f);
            ImVec2 canvas_pos_br = ImVec2(canvas_pos_ul.x + canvas_size.x, canvas_pos_ul.y + canvas_size.y);

            ImDrawList *drawList = ImGui::GetWindowDrawList();
            drawList->AddRectFilled(canvas_pos_ul, canvas_pos_br, IM_COL32(50, 50, 50, 255));
            drawList->AddRect(canvas_pos_ul, canvas_pos_br, IM_COL32(255, 255, 255, 255));

            inter_uniform.PlotYT(out_pos_t, drawList, canvas_pos_ul, canvas_pos_br);
            inter_chordal.PlotYT(out_pos_t, drawList, canvas_pos_ul, canvas_pos_br);
            inter_centripetal.PlotYT(out_pos_t, drawList, canvas_pos_ul, canvas_pos_br);
            inter_foley.PlotYT(out_pos_t, drawList, canvas_pos_ul, canvas_pos_br);

            approx_uniform.PlotYT(out_pos_t, drawList, canvas_pos_ul, canvas_pos_br);
            approx_chordal.PlotYT(out_pos_t, drawList, canvas_pos_ul, canvas_pos_br);
            approx_centripetal.PlotYT(out_pos_t, drawList, canvas_pos_ul, canvas_pos_br);
            approx_foley.PlotYT(out_pos_t, drawList, canvas_pos_ul, canvas_pos_br);

            spline_uniform.PlotYT(out_pos_t, drawList, canvas_pos_ul, canvas_pos_br);\
            spline_chordal.PlotYT(out_pos_t, drawList, canvas_pos_ul, canvas_pos_br);
            spline_centripetal.PlotYT(out_pos_t, drawList, canvas_pos_ul, canvas_pos_br);
            spline_foley.PlotYT(out_pos_t, drawList, canvas_pos_ul, canvas_pos_br);

            ImGui::End();
        }
        EndFrame();
    }
    Finalize();
    return 0;
}