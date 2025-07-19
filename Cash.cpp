#include "includes.h"

uintptr_t CASH_BASE_ADDRESS = 0x51CF90;
std::vector <unsigned int> CASH_OFFSETS = { 0x10, 0xB4 };

// Resolve a cadeia de ponteiros para encontrar o endereço final
uintptr_t ResolvePointerChain(HANDLE hProcess, uintptr_t baseAddress, const std::vector<unsigned int>& offsets) 
{
    uintptr_t address = baseAddress;
    for (unsigned int offset : offsets) 
    {
        uintptr_t temp = 0;
        ReadProcessMemory(hProcess, (LPCVOID)address, &temp, sizeof(temp), nullptr);
        address = temp + offset;
    }
    return address;
}

void ManageCash(HANDLE hProcess)
{
    const uintptr_t BaseAddress = 0x400000; // Endereço base (fixo) do módulo speed.exe! 5 zeros = (00000)
    uintptr_t address = ResolvePointerChain(hProcess, BaseAddress + CASH_BASE_ADDRESS, CASH_OFFSETS);

    while (true) 
    {
        system("cls");
        std::wcout << L"╔══════════════════════════════════════╗\n";
        std::wcout << L"║                 Cash                 ║\n";
        std::wcout << L"╚══════════════════════════════════════╝\n";

		unsigned int currentMoney = 0; // money que ja está cadastrado no jogo 
        if (!ReadProcessMemory(hProcess, (LPCVOID)address, &currentMoney, sizeof(currentMoney), nullptr)) 
        {
            std::wcout << L"\n[!] Memory read failed!\n";
			Sleep(700);
            break;
        }

        std::wcout << L"\n[*] Current money: " << currentMoney;
        std::wcout << L"\n[*] Enter a new value or press DELETE to go back: ";

        std::wstring input;
        while (true) {
            wchar_t ch = _getwch();

            if (ch == 27) return;         // ESC
            if (ch == L'\r') break;       // ENTER
            if (ch == L'\b' && !input.empty()) {
                input.pop_back();
                std::wcout << L"\b \b";
            }
            else if (iswdigit(ch)) {
                input += ch;
                std::wcout << ch;
            }
        }

        if (input.empty()) {
            std::wcout << L"\n[-] Nenhum valor digitado.\n";
            Sleep(700);
            continue;
        }

        int novoDinheiro = 0;
        try {
            novoDinheiro = std::stoi(input);
        }
        catch (...) {
            std::wcout << L"\n[-] Valor inválido.\n";
            Sleep(700);
            continue;
        }

        if (!WriteProcessMemory(hProcess, (LPVOID)address, &novoDinheiro, sizeof(novoDinheiro), nullptr)) {
            std::wcout << L"\n[-] Falha ao escrever o novo valor.\n";
        }
        else {
            std::wcout << L"\n[*] Dinheiro alterado para: " << novoDinheiro << L"\n";
        }

        std::wcout << L"\nPressione qualquer tecla para continuar ou ESC para sair...\n";
        wchar_t ch = _getwch();
        if (ch == 27) return;
    }
}