#include "SmartVehHandler.h"

std::string HexU64(DWORD64 v) {
    std::ostringstream oss;
    oss << "0x" << std::hex << v;
    return oss.str();
}

DWORD64 GetModuleSizeFromPE(DWORD64 base) {
    if (!base) return 0;
    auto dos = reinterpret_cast<PIMAGE_DOS_HEADER>(base);
    if (!dos || dos->e_magic != IMAGE_DOS_SIGNATURE) return 0;
    auto nt = reinterpret_cast<PIMAGE_NT_HEADERS>(base + dos->e_lfanew);
    if (!nt || nt->Signature != IMAGE_NT_SIGNATURE) return 0;
    return static_cast<DWORD64>(nt->OptionalHeader.SizeOfImage);
}

static std::vector<DWORD64> crashAddresses = { 0x00000000088CB07A };

LONG CALLBACK SmartVehHandler(EXCEPTION_POINTERS* ep) {
    if (!ep || !ep->ExceptionRecord || !ep->ContextRecord) return EXCEPTION_CONTINUE_SEARCH;

    const auto code = ep->ExceptionRecord->ExceptionCode;
    if (code != EXCEPTION_ACCESS_VIOLATION &&
        code != EXCEPTION_ILLEGAL_INSTRUCTION &&
        code != EXCEPTION_STACK_OVERFLOW) {
        return EXCEPTION_CONTINUE_SEARCH;
    }

    const DWORD64 crashAddr = reinterpret_cast<DWORD64>(ep->ExceptionRecord->ExceptionAddress);
    if (std::find(crashAddresses.begin(), crashAddresses.end(), crashAddr) != crashAddresses.end()) {
        const DWORD64 ripBefore = ep->ContextRecord->Rip;

        if (gModuleBase && gModuleSize &&
            crashAddr >= gModuleBase && crashAddr < (gModuleBase + gModuleSize)) {

            DWORD64 advance = 2;  // Default byte advancement

            ep->ContextRecord->Rip += advance;

            Logger::Instance().Log("[VEH] 捕获异常(code=" + std::to_string(code) +
                ") @" + HexU64(crashAddr) +
                " RIP " + HexU64(ripBefore) + " -> " + HexU64(ep->ContextRecord->Rip) +
                "，已尝试跳过指令继续执行。", LogLevel::INFO);

            return EXCEPTION_CONTINUE_EXECUTION;
        }
    }

    return EXCEPTION_CONTINUE_SEARCH;
}
