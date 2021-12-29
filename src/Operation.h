#pragma once
#include <vector>
#include <string>

class Operation
{
public:
	// Basic method that all operations should have
	virtual bool Process(const std::vector<std::string>& inputFiles,
		const std::string& outputDir) = 0;

	// Get the filename from a path, with/without the extension
	std::string GetFileName(const std::string& filePath, bool withExtension = true)
	{
		std::string fileName = "";
		if (filePath.find_last_of('/') != std::string::npos)
		{
			fileName = filePath.substr(filePath.find_last_of('/') + 1, filePath.size());
		}
		else if (filePath.find_last_of('\\') != std::string::npos)
		{
			fileName = filePath.substr(filePath.find_last_of('\\') + 1, filePath.size());
		}
		if (fileName != "" && !withExtension)
		{
			return fileName.substr(0, fileName.find_last_of('.'));
		}
		return fileName;
	}
};
