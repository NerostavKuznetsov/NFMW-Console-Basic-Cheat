#include "includes.h"

void ManageNever_Busted(HANDLE hProcess) 
{
    uintptr_t Instruction_Address = 0x00443BB8;
    BYTE NOP_Bytes[6] = { 0x90, 0x90, 0x90, 0x90, 0x90, 0x90 };
    BYTE Original_Bytes[6] = { 0xD8, 0x86, 0x1C, 0x01, 0x00, 0x00 }; 
    BYTE Current_Bytes[6] = { 0 };
    SIZE_T bytesRead;
    bool BYTE_NOP = false;

    std::wcout << L"╔══════════════════════════════════════╗\n";
    std::wcout << L"║             Never Busted             ║\n";
    std::wcout << L"╚══════════════════════════════════════╝\n\n";

    // Detecta estado inicial lendo a memória
    if (ReadProcessMemory(hProcess, (LPCVOID)Instruction_Address, Current_Bytes, sizeof(Current_Bytes), &bytesRead) && bytesRead == sizeof(Current_Bytes)) {
        if (memcmp(Current_Bytes, NOP_Bytes, sizeof(NOP_Bytes)) == 0) {
            BYTE_NOP = true;
            std::wcout << L"[!] Never Busted está ATIVADO!\n";
        }
        else {
            std::wcout << L"[!] Never Busted está DESATIVADO!\n";
        }
    }
    else {
        std::wcout << L"[!] Falha ao ler a memória para detectar estado!\n";
        return;
    }

    std::wcout << L"[!] Pressione INSERT para ativar/desativar Never Busted. DELETE para sair.\n";

    while (true) {
        if (GetAsyncKeyState(VK_DELETE) & 1) {
            return; // sai da função
        }

        if (GetAsyncKeyState(VK_INSERT) & 1) {
            SIZE_T written;
            DWORD oldProtect;

            if (VirtualProtectEx(hProcess, (LPVOID)Instruction_Address, sizeof(NOP_Bytes), PAGE_EXECUTE_READWRITE, &oldProtect)) {
                if (!BYTE_NOP) {
                    if (WriteProcessMemory(hProcess, (LPVOID)Instruction_Address, NOP_Bytes, sizeof(NOP_Bytes), &written) && written == sizeof(NOP_Bytes)) {
                        std::wcout << L"[+] Never Busted ativado com sucesso!\n";
                        BYTE_NOP = true;
                    }
                    else {
                        std::wcout << L"[!] Falha ao ativar Never Busted!\n";
                    }
                }
                else {
                    if (WriteProcessMemory(hProcess, (LPVOID)Instruction_Address, Original_Bytes, sizeof(Original_Bytes), &written) && written == sizeof(Original_Bytes)) {
                        std::wcout << L"[+] Never Busted desativado com sucesso!\n";
                        BYTE_NOP = false;
                    }
                    else {
                        std::wcout << L"[!] Falha ao desativar Never Busted!\n";
                    }
                }
                VirtualProtectEx(hProcess, (LPVOID)Instruction_Address, sizeof(NOP_Bytes), oldProtect, &oldProtect);
            }
            else {
                std::wcout << L"[!] Falha ao alterar a proteção da memória!\n";
            }
        }
    }
}
