    #include "includes.h"

    using namespace std;

    DWORD GetProcessIdByName(const std::wstring& processName)
    {
        DWORD processId = 0;
        HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

        if (hSnapshot != INVALID_HANDLE_VALUE) 
        {
            PROCESSENTRY32W PE32;
            PE32.dwSize = sizeof(PROCESSENTRY32);

            if (Process32FirstW(hSnapshot, &PE32)) 
            {
                do 
                {
                    if (processName == PE32.szExeFile) 
                    {
                        processId = PE32.th32ProcessID;
                        break;
                    }
                } while (Process32NextW(hSnapshot, &PE32));
            }
            CloseHandle(hSnapshot);
        }
        return processId;
    }

    void ShowMenu() 
    
{

system("cls");
wcout << R"(
_____   _______________________  _____       __              _________                         ______          ________              _____           ______________             _____ 
___  | / /__  ____/_  ___/__   |/  /_ |     / /              __  ____/____________________________  /____      ___  __ )_____ __________(_)______    __  ____/__  /____________ __  /_
__   |/ /__  /_   _____ \__  /|_/ /__ | /| / /  ________     _  /    _  __ \_  __ \_  ___/  __ \_  /_  _ \     __  __  |  __ `/_  ___/_  /_  ___/    _  /    __  __ \  _ \  __ `/  __/
_  /|  / _  __/   ____/ /_  /  / / __ |/ |/ /   _/_____/     / /___  / /_/ /  / / /(__  )/ /_/ /  / /  __/     _  /_/ // /_/ /_(__  )_  / / /__      / /___  _  / / /  __/ /_/ // /_  
/_/ |_/  /_/      /____/ /_/  /_/  ____/|__/                 \____/  \____//_/ /_//____/ \____//_/  \___/      /_____/ \__,_/ /____/ /_/  \___/      \____/  /_/ /_/\___/\__,_/ \__/                                                                                             
    )";

    wcout << "\n";
    wcout << "                                                                                                                                                                          by: Nerostav Kuznetsov\n";
    wcout << "https://github.com/NerostavKuznetsov/NFSMW-NK-Cheats\n";
    wcout << "??????????????????????????????              \n";
    wcout << " \n";
    wcout << L"╔═════════════════════════════════════╗\n";
    wcout << L"║              MAIN MENU              ║\n";
    wcout << L"╠═════════════════════════════════════╣\n";
    wcout << L"║ 1  ➤  Cash                          ║\n";
    wcout << L"║ 2  ➤  Infinite Nitrous              ║\n";
    wcout << L"║ 3  ➤  Never Busted                  ║\n";
    wcout << L"║ 4  ➤  ?                             ║\n";
    wcout << L"║ 5  ➤  ?                             ║\n";
    wcout << L"║ 6  ➤  ?                             ║\n";
    wcout << L"║ 7  ➤  ?                             ║\n";
    wcout << L"╚═════════════════════════════════════╝\n";
                                                                                                            
    }

    int main() 
    {
        setlocale(LC_ALL, "PT_BR.UTF-8");
        SetConsoleOutputCP(CP_UTF8);                    // Força a saída UTF-8
        SetConsoleTitleA("NFSMW - NK Cheats");

        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        DWORD PID = 0;

        // Código que espera pelo processo "speed.exe"
        while (PID == 0) {
            system("cls");
            SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE);

            std::wcout << L"[~] Waiting for speed.exe";
            for (int i = 0; i < 6; i++) {
                std::wcout << L".";
                Sleep(666);
            }

            PID = GetProcessIdByName(L"speed.exe");
            if (PID != 0)
                break;
        }

        HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, PID);
        bool options = true;
        char choose;

        while (options) {
            ShowMenu();
            std::wcout << L"\nChoose an option: ";
            std::cin >> choose;

            switch (choose) {
            case '1':
                ManageCash(hProcess);
                break;
            case '2':
                system("cls");
                ManageNitrous(hProcess);
                break;
            case '3':
                system("cls");
                ManageNever_Busted(hProcess);
                break;
			case '4':
				system("cls");
                ManageProfile(hProcess);
                std::wcout << L"[!] This option is not implemented yet!\n";
                Sleep(1000);
                break;
			case '5':
				system("cls");
                std::wcout << L"[!] This option is not implemented yet!\n";
                Sleep(1000);
				break;
            case '7':
                system("cls");
                std::wcout << L"[!] This option is not implemented yet!\n";
                Sleep(1000);
                break;
            case '6':
                system("cls");
                std::wcout << L"[!] This option is not implemented yet!\n";
				Sleep(1000);
                break;



            default:
                std::wcout << L"[!] Invalid option!\n";
                Sleep(666);
                break;
            }
        }

        CloseHandle(hProcess);
        return 0;
    }
