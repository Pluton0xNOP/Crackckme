#include <Windows.h>
#include <iostream>
#include <TlHelp32.h>
#include <string.h>
#define PEPITO 0x00007FF7B398727F

DWORD ProcId = 0;

void Get_proces_id(const char* _proces_Name);

int main()
{
    const char* _process_name = "ckme_3.exe";
    Get_proces_id(_process_name);

    BYTE _byte_new = 0x75;

    HANDLE _process = OpenProcess(PROCESS_ALL_ACCESS, false, ProcId);
    WriteProcessMemory(_process,(LPVOID)PEPITO,&_byte_new,sizeof(_byte_new),NULL);

    getchar();
    getchar();
    getchar();
    getchar();


    
  
   

   

    return 0;
}

void Get_proces_id(const char* _proces_Name) {

    PROCESSENTRY32 pe32;
    HANDLE hSnapshot = NULL;

    pe32.dwSize = sizeof(PROCESSENTRY32);
    hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

    if (hSnapshot == INVALID_HANDLE_VALUE) {
        std::cerr << "Failed to create snapshot" << std::endl;
        return;
    }

    if (Process32First(hSnapshot, &pe32))
    {
        do {
            if (strcmp(pe32.szExeFile, _proces_Name) == 0) {
                ProcId = pe32.th32ProcessID;
                break;
            }
        } while (Process32Next(hSnapshot, &pe32));
    }

    CloseHandle(hSnapshot);
}
