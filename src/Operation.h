#pragma once
#include <vector>
#include <string>

class Operation
{
public:
	// Basic method that all operations should have
	virtual bool Process(const std::vector<std::string>& inputFiles,
		const std::string& outputDir) = 0;
};
