#pragma once
#include "MeshLoader.h"

//!!! Инклуды нужно подключать там, где они нужны.
//!!! В данном случае везде, где подключается этот файл, они будут присутствовать.

/*#include <fstream>
#include <vector>
#include <iostream>
#include <fstream>*/

class AneuMeshLoader : public MeshLoader {
private:
	//ifstream m_File;           //!!! Нет смысла делать поток полем класса.
public:
	void loadMesh(const string &path) override;
};