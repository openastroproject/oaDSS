#include "dss_common.h"

#include <time.h>

#include "File.h"

bool GetFileCreationDateTime(LPCTSTR szFileName, struct timespec& FileTime)
{
	bool			bResult = false;
	HANDLE			hFind;
	WIN32_FIND_DATA	FindData;

	hFind = FindFirstFile(szFileName, &FindData);
	if (hFind != INVALID_HANDLE_VALUE)
	{
		FileTime = FindData.ftLastWriteTime;
		FindClose(hFind);
		bResult = true;
	};

	return bResult;
}
