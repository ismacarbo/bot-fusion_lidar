#define SDL_MAIN_HANDLED
#include <iostream>
#include <cmath>
#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include "../../third_party/imgui/imgui.h"
#include "../../third_party/implot/implot.h"
#include "../../third_party/imgui/backends/imgui_impl_sdl2.h"
#include "../../third_party/imgui/backends/imgui_impl_opengl3.h"
#include <../../third_party/gl3w/include/GL/gl3w.h>  

#include "../../sdk/include/sl_lidar.h" 
#include "../../sdk/include/sl_lidar_driver.h"
using namespace sl;

bool ctrl_c_pressed = false;

void sigint_handler(int sig) {
    ctrl_c_pressed = true;
}

int main() {
    
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = SDL_CreateWindow("Test Window",
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          800, 600, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
    SDL_GLContext gl_context = SDL_GL_CreateContext(window);
    SDL_GL_MakeCurrent(window, gl_context);
    gl3wInit(); 

    
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImPlot::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui_ImplSDL2_InitForOpenGL(window, gl_context);
    ImGui_ImplOpenGL3_Init("#version 130");

    signal(SIGINT, sigint_handler);

    int channelType=CHANNEL_TYPE_SERIALPORT;
    const char* port="/dev/ttyUSB0";
    ILidarDriver * drv = *createLidarDriver();

    if(!drv){
        fprintf(stderr,"no memory,exit\n");
        exit(-2);
    }
    IChannel* channel;
    sl_result res;
    sl_lidar_response_device_info_t devinfo;
    bool connected=false;

    if(channelType==CHANNEL_TYPE_SERIALPORT){
        channel = *createSerialPortChannel(port, 115200);
        if(SL_IS_OK(drv->connect(channel))){
            res=drv->getDeviceInfo(devinfo);
            if(SL_IS_OK(res)){
                connected=true;
            }
            else{
                delete drv;
                drv=NULL;
            }
        }
    }

    sl_lidar_response_device_health_t health;
    if (!SL_IS_OK(drv->getHealth(health)) || health.status == SL_LIDAR_STATUS_ERROR) {
        std::cerr << "Lidar non in salute\n";
        delete drv;
        return -1;
    }
    drv->setMotorSpeed();
    drv->startScan(0, 1);

    ImGui::NewFrame();
    if(connected){
        ImGui::Text("Connected to LiDAR");
    }else{
        ImGui::Text("Not connected to LiDAR");
    }
    ImGui::Render();


        

    
    bool running = true;
    while (running) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            ImGui_ImplSDL2_ProcessEvent(&event);
            if (event.type == SDL_QUIT) running = false;
        }

        
        ImGui_ImplSDL2_NewFrame();    
        ImGui_ImplOpenGL3_NewFrame();       // nessun argomento
        ImGui::NewFrame();

        // 3) La tua UI:
        if (connected) {
            ImGui::Text("Connected to LiDAR");
        } else {
            ImGui::Text("Not connected to LiDAR");
        }
        // … eventuale ImPlot, altri ImGui::XXX …

        // 4) Render:
        ImGui::Render();
        
        


        
        SDL_GL_MakeCurrent(window, gl_context);
        glViewport(0, 0, (int)io.DisplaySize.x, (int)io.DisplaySize.y);
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        SDL_GL_SwapWindow(window);
    }

    
    ImPlot::DestroyContext();
    ImGui::DestroyContext();
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    SDL_GL_DeleteContext(gl_context);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
