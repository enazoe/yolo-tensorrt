#pragma once
#include<iostream>
#include<string>
#include<ostream>
#include<fstream>
#include<Windows.h>
#include<direct.h>
#include<io.h>
#include<vector>
#include<opencv2/opencv.hpp>
struct my_Detectbox
{
	// topleft-bottomright∏Ò Ω
	int x; // left
	int y; // right
	int w; // right
	int h; // bottom
	int classIndex;
};
using vectorString = std::vector<std::string>;
int transportYoloGroundTruth();
void getIniKeyString(char* title, char* key, char* filename, char* output1);
void getFiles(std::string path, std::string path2, std::vector<std::string> &files);
bool   CheckFolderExist(const std::string   & strPath);
void getFiles(std::string path, std::vector<std::string>& files);
void transportYoloLable(std::string  lablePath, std::string rewritePath, std::string imgRootPath);
vectorString checkLine(std::string lineContent, char * delim);
std::string transportToRealSize(vectorString lineInfo_, cv::Size imgSize);
cv::Size getImgSize(std::string txtPath, std::string imgRootPath);
int checkPathEnd(std::string& pathFile);