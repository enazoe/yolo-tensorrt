#pragma once
#include "maputil.hpp"
int transportYoloGroundTruth() 
{
	char FilePath[255], path[256], resultPath[256], initLalePath[256];
	GetModuleFileName(NULL, FilePath, 255); 
	(strrchr(FilePath, '\\'))[1] = 0; 
	sprintf(path, "%smap\\img\\", FilePath); 						 
	sprintf(resultPath, "%smap\\\input\\ground-truth", FilePath);
	sprintf(initLalePath, "%smap\\testLables\\", FilePath);

	if (_access(resultPath, 00) == -1)
	{
		try
		{
			_mkdir(resultPath);
		}
		catch (const std::exception& e)
		{
			std::cout << e.what() << std::endl;
		}


	}
	std::string rewritePath = FilePath + std::string("map\\input\\ground-truth");
	transportYoloLable(initLalePath, rewritePath, path);
	return 1;
}


void getIniKeyString(char* title, char* key, char* filename, char* output1)
{
	FILE *fp;
	int flag = 0;
	char sTitle[32] = { 0 };
	char sLine[1024] = { 0 };
	char *output = NULL;
	sprintf(sTitle, "[%s]", title);
	if (NULL == (fp = fopen(filename, "r"))) {
		perror("fopen");
		return;
	}
	while (NULL != fgets(sLine, 1024, fp)) {
		//ÕâÊÇ×¢ÊÍÐÐ
		if (0 == strncmp("//", sLine, 2))    continue;
		if ('#' == sLine[0]) continue;
		std::cout << sLine << std::endl;
		output = strchr(sLine, '=');
		if ((NULL != output) && (1 == flag)) {
			if (0 == strncmp(key, sLine, output - sLine)) {
				// std::cout << output << std::endl;
				sLine[strlen(sLine) - 1] = '\0';
				fclose(fp);
				output++;
			}
		}
		else {
			if (0 == strncmp(sTitle, sLine, strlen(sLine) - 1)) {
				flag = 1;
			}
		}
	}
	fclose(fp);
	memcpy(output1, output, strlen(output));
}

void getFiles(std::string path, std::string path2, std::vector<std::string> &files)
{
	long long hFile = 0; // 32bit long, 64bit long long
	struct _finddata_t fileinfo;

	std::string p, p2;
	if ((path[strlen(path.c_str()) - 1] == '\\') || (path.back() == '/')) 
	{
		path.pop_back();
	}
	if ((hFile = _findfirst(p.assign(path).append(path2).append("\\*").c_str(), &fileinfo)) != -1)
	{
		do
		{
			if (fileinfo.attrib & _A_SUBDIR)
			{
				if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, ".") != 0)
					getFiles(p.assign(path), p2.assign(fileinfo.name).append("\\"), files);
			}
			else
			{
				files.push_back(p.assign(path2).append(fileinfo.name));
			}
		} while (_findnext(hFile, &fileinfo) == 0);
		_findclose(hFile);
	}
}

bool   CheckFolderExist(const std::string   & strPath)
{
	WIN32_FIND_DATA  wfd;
	bool  rValue = false;
	HANDLE hFind = FindFirstFile(strPath.c_str(), &wfd);
	if ((hFind != INVALID_HANDLE_VALUE) && (wfd.dwFileAttributes  &  FILE_ATTRIBUTE_DIRECTORY))
	{
		rValue = true;
	}
	FindClose(hFind);
	return  rValue;
}
void getFiles(std::string path, std::vector<std::string>& files) 
{
 
	long long  hFile; 
	struct _finddata_t fileinfo;
	std::string p;
	if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1)
	{
		do
		{
			if ((fileinfo.attrib &  _A_SUBDIR))
			{
				if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
					getFiles(p.assign(path).append("\\").append(fileinfo.name), files);
			}
			else
			{
				files.push_back(p.assign(path).append("\\").append(fileinfo.name));
			}
		} while (_findnext(hFile, &fileinfo) == 0);
		_findclose(hFile);
	}
}


void transportYoloLable(std::string  lablePath, std::string rewritePath, std::string imgRootPath)
{
	if (_access(lablePath.c_str(), 00) == -1)
	{
		throw("Wrong path and check it");
	}

	std::vector<std::string> lableFiles; // 
	getFiles(lablePath, "", lableFiles);
	for (auto lablefile_ : lableFiles) 
	{
		checkPathEnd(lablePath);
		std::string lablefile = lablePath + lablefile_;
		std::ifstream ifile;
		std::ofstream ofile;
		if (_access(rewritePath.c_str(), 00) == -1)
		{
			try
			{
				_mkdir(rewritePath.c_str());
			}
			catch (const std::exception& e)
			{
				throw(e.what());
			}
		}
		checkPathEnd(rewritePath);
		std::string ofilename = rewritePath + lablefile_;
		ifile.open(lablefile);
		ofile.open(ofilename);
		if (!ifile.is_open())
		{
			throw("read Failed");
		}
		std::string linecontent;

		cv::Size imgSize = getImgSize(lablefile, imgRootPath);
		while (std::getline(ifile, linecontent))
		{
			vectorString lineInfo = checkLine(linecontent, " ");
			std::string lineInfoAfterTransport = transportToRealSize(lineInfo, imgSize);
			ofile << lineInfoAfterTransport << std::endl;

		}
		ifile.close();
		ofile.close();
	}
}

vectorString checkLine(std::string lineContent, char * delim) 
{
	char * content = const_cast<char * >(lineContent.c_str());
	std::vector<std::string> vectorResult;
	char * token;
	char * next_token = NULL;
	char * getSplit = strtok_s(content, delim, &next_token);

	while (getSplit)
	{
		std::cout << getSplit << std::endl;
		vectorResult.push_back(getSplit);
		getSplit = strtok_s(NULL, delim, &next_token);
	}
	return vectorResult;
}


std::string transportToRealSize(vectorString lineInfo_, cv::Size imgSize) 
{
	char result[128];
	int classid = atof(lineInfo_[0].data());
	float xcenter = atof(lineInfo_[1].data());
	float ycenter = atof(lineInfo_[2].data());
	float width = atof(lineInfo_[3].data());
	float height = atof(lineInfo_[4].data());
	float imgwidth = imgSize.width;
	float imgheight = imgSize.height;
	std::cout << "width and heigtht:" << width << height << std::endl;
	float xleft_ = xcenter - width / 2;
	if (xleft_ < 0)
		xleft_ = 0;
	float yleft_ = ycenter - height / 2;
	if (yleft_ < 0)
		yleft_ = 0;
	float xright_ = xcenter + width / 2;

	float yright_ = ycenter + height / 2;

	int xleft = int(imgwidth * (xleft_));
	if (xleft == 0)
		xleft = 1;
	int yleft = int(imgheight * (yleft_));
	if (yleft == 0)
		yleft = 1;
	int xright = int(imgwidth * (xright_));

	xright = xright > int(imgwidth) ? int(imgwidth) - 1 : xright;
	int yright = int(imgheight * (yright_));
	yright = yright > int(imgheight) ? int(imgheight) - 1 : yright;

	sprintf(result, "%d %d %d %d %d", classid, xleft, yleft, xright, yright);

	return result;

}

cv::Size getImgSize(std::string txtPath, std::string imgRootPath)
{

	const char* txtfilename = txtPath.data();
	char *ptrtxt = const_cast<char *>(txtfilename);
	char * fileName = strrchr(ptrtxt, '\\') + 1;
	printf("%s", fileName);
	char imgPath[256];
	strrchr(fileName, '.')[1] = 0;
	strcat(fileName, "jpg");
	sprintf(imgPath, "%s%s", imgRootPath.data(), fileName);
	cv::Mat img = cv::imread(imgPath);
	cv::Size imgSize;
	imgSize = img.size();
	return imgSize;
}

int checkPathEnd(std::string& pathFile)
{
	std::cout << pathFile.back() << std::endl;
	if (pathFile.back() != '\\')
	{
		pathFile.push_back('\\');

	}
	return 1;
}