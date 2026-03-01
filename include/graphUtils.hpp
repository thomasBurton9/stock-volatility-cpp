#pragma once


#include "imgui.h"

#include <vector>
#include <string>


int startGraphing(std::vector<double> x, std::vector<double> y, std::string title);
int graphData(std::vector<double> x, std::vector<double> y, std::string title, ImGuiIO &io); 