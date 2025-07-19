#include "includes.h"
 
void ManageNitrous(HANDLE hProcess) 
{
    uintptr_t Instruction_Address = 0x00692B01;
    BYTE NOP_Bytes[4] = { 0x90, 0x90, 0x90, 0x90 };
    BYTE Original_Bytes[4] = { 0xD8, 0x64, 0x24, 0x2C };
    BYTE Currenty_Bytes[4] = { 0 };
    SIZE_T bytesRead;
    bool BYTE_NOP = false;

    std::wcout << L"╔══════════════════════════════════════╗\n";
    std::wcout << L"║           Infinite Nitrous           ║\n";
    std::wcout << L"╚══════════════════════════════════════╝\n\n";

    // Detecta estado inicial
    if (ReadProcessMemory(hProcess, (LPCVOID)Instruction_Address, &Currenty_Bytes, sizeof(Currenty_Bytes), &bytesRead)) {
        if (memcmp(Currenty_Bytes, NOP_Bytes, 4) == 0) {
            BYTE_NOP = true;
            std::wcout << L"[!] Infinite Nitrous is activated!\n";
        }
        else {
            std::wcout << L"[!] Infinite Nitrous is deactivated!\n";
        }
    }
    else {
        std::wcout << L"[!] Memory read failed!\n";
    }

    std::wcout << L"[!] Press INSERT to activate/deactivate. DELETE to return to the main menu.\n";

    while (true) {
        if (GetAsyncKeyState(VK_DELETE) & 1) {
            return;
        }

        if (GetAsyncKeyState(VK_INSERT) & 1) {
            SIZE_T written;
            DWORD oldProtect;

            if (VirtualProtectEx(hProcess, (LPVOID)Instruction_Address, 4, PAGE_EXECUTE_READWRITE, &oldProtect)) {
                if (!BYTE_NOP) {
                    if (WriteProcessMemory(hProcess, (LPVOID)Instruction_Address, NOP_Bytes, sizeof(NOP_Bytes), &written)) {
                        std::wcout << L"[+] Infinite Nitrous successfully activated!\n";
                        BYTE_NOP = true;
                    }
                    else {
                        std::wcout << L"[!] Failed to ACTIVATED Infinite Nitrous!\n";
                    }
                }
                else {
                    if (WriteProcessMemory(hProcess, (LPVOID)Instruction_Address, Original_Bytes, sizeof(Original_Bytes), &written)) {
                        std::wcout << L"[+] Infinite Nitrous successfully deactivated!\n";
                        BYTE_NOP = false;
                    }
                    else {
                        std::wcout << L"[!] Failed to DEACTIVATED Infinite Nitrous\n";
                    }
                }
                // Restaura a proteção original da memória
                VirtualProtectEx(hProcess, (LPVOID)Instruction_Address, 4, oldProtect, &oldProtect);
            }
            else {
                std::wcout << L"[!] Failed to change memory protection!\n";
            }
        }
    }
}


