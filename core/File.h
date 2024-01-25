#pragma once

#include <time.h>

bool GetFileCreationDateTime(LPCTSTR szFileName, struct timespec& FileTime);
