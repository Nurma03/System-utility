#include <iostream>
#include <Windows.h>
#include <tlhelp32.h>
#include <string>

using namespace std;

void printProcessInfo()
{
    // To gain acccess for information
    HANDLE hProcessSnap;
    PROCESSENTRY32 pe32;

    // It take a snapshot of all processes in the system
    hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hProcessSnap == INVALID_HANDLE_VALUE) {
        cout << "Failed to get process snapshot\n";
        return;
    }

    // This set the size of the structure before using it
    pe32.dwSize = sizeof(PROCESSENTRY32);

    // After retrieve information about the first process
    if (!Process32First(hProcessSnap, &pe32)) {
        cout << "Failed to get process info\n";
        CloseHandle(hProcessSnap);
        return;
    }

    // Print processes
    int count = 0;
    do {
        cout << "Process name:" << pe32.szExeFile << " (PID:" << pe32.th32ProcessID << ")" << endl;
        count++;
    } while (Process32Next(hProcessSnap, &pe32));

    cout << "Total number of processes: " << count << endl;

    // Close the snapshot
    CloseHandle(hProcessSnap);
}

void printWindowInfo()
{
    HWND hwnd = GetForegroundWindow();

    if (hwnd == NULL)
    {
        std::cout << "No active window found." << std::endl;
        return;
    }

    wchar_t title[256];
    GetWindowText(hwnd, title, sizeof(title));

    RECT rect;
    GetWindowRect(hwnd, &rect);

    std::cout << "Window Title: " << title << std::endl;
    std::cout << "Window Position: (" << rect.left << ", " << rect.top << ")" << std::endl;
    std::cout << "Window Size: " << (rect.right - rect.left) << " x " << (rect.bottom - rect.top) << std::endl;

    return;
}

int main()
{
    int choice;

    while (true) {
        cout << "Choose an option:\n";
        cout << "1. Get the number of active processes and their names\n";
        cout << "2. Get the title of the currently active window\n";
        cout << "3. Exit\n";
        cin >> choice;

        if (choice == 1) {
            printProcessInfo();
        }
        else if (choice == 2) {
            printWindowInfo();
        }
        else if (choice == 3) {
            break;
        }
        else {
            cout << "Invalid option\n";
        }
    }

    return 0;
}