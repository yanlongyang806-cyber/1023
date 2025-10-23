#ifndef SMARTVEHHANDLER_H
#define SMARTVEHHANDLER_H

#include <windows.h>
#include <string>
#include <vector>
#include "Logger.h"

// Helper function to format DWORD64 values as hex strings
std::string HexU64(DWORD64 v);

// Function to get the module size from the PE headers
DWORD64 GetModuleSizeFromPE(DWORD64 base);

// VEH exception handler function
LONG CALLBACK SmartVehHandler(EXCEPTION_POINTERS* ep);

#endif // SMARTVEHHANDLER_H
