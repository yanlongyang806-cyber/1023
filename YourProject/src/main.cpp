#include <windows.h>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "Logger.h"
#include "SmartVehHandler.h"

static DWORD64 gModuleBase = 0;
static DWORD64 gModuleSize = 0;

BOOL APIENTRY DllMain(HMODULE hMod, DWORD reason, LPVOID) {
    if (reason == DLL_PROCESS_ATTACH) {
        DisableThreadLibraryCalls(hMod);

        HMODULE hMain = GetModuleHandleA("worldserver.exe");
        if (hMain) {
            gModuleBase = reinterpret_cast<DWORD64>(hMain);
            gModuleSize = GetModuleSizeFromPE(gModuleBase);
            Logger::Instance().Log("veh_patch_smart.dll 注入成功。worldserver.exe 基址=" +
                                   HexU64(gModuleBase) + " 大小=" + std::to_string(gModuleSize) + " bytes", LogLevel::INFO);

            PVOID handle = AddVectoredExceptionHandler(1, SmartVehHandler);
            if (handle) {
                Logger::Instance().Log("VEH 异常处理程序安装完成。", LogLevel::INFO);
            } else {
                Logger::Instance().Log("安装 VEH 失败！", LogLevel::ERROR);
            }
        } else {
            Logger::Instance().Log("获取 worldserver.exe 模块失败，未安装 VEH。", LogLevel::ERROR);
        }
    }
    return TRUE;
}
