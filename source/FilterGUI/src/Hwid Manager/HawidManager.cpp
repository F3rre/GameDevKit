#include "HawidManager.h"
#include "md5.h"
#include <algorithm>
#include <sstream>
#include <IPHlpApi.h>
#include <ctime>
#include <intrin.h>

#pragma comment(lib, "iphlpapi.lib")
#pragma comment(lib, "urlmon.lib")
#pragma comment(lib, "wininet.lib")
#pragma comment(lib,"ws2_32.lib")


using namespace std;

const char* HawidManager::GetMac()
{
    bool foundValidAdapter = false;
    bool prevent_send = false;

    PIP_ADAPTER_INFO adapterInfo;
    DWORD dwBufSize = sizeof(adapterInfo);
    char* mac = (char*)malloc(17);
    adapterInfo = (IP_ADAPTER_INFO*)malloc(sizeof(IP_ADAPTER_INFO));
    if (adapterInfo == NULL)
        return 0;

    if (GetAdaptersInfo(adapterInfo, &dwBufSize) == ERROR_BUFFER_OVERFLOW)
    {
        adapterInfo = (IP_ADAPTER_INFO*)malloc(dwBufSize);
        if (adapterInfo == NULL)
            return 0;
    }

    if (GetAdaptersInfo(adapterInfo, &dwBufSize) == NO_ERROR)
    {
        PIP_ADAPTER_INFO pInfo = adapterInfo;

        while (pInfo)
        {
            //Flash Net
            if (pInfo->Type == 23)
            {
                MessageBoxA(0, "You are not allowed to play with a VPN on our server", "Error", MB_OK);
                prevent_send = true;
                return 0;
            }

            //Ethernet
            if (pInfo->Type == 6)
            {
                if (!foundValidAdapter)
                {
                    sprintf(mac, "%02X-%02X-%02X-%02X-%02X-%02X",
                        pInfo->Address[0], pInfo->Address[1],
                        pInfo->Address[2], pInfo->Address[3],
                        pInfo->Address[4], pInfo->Address[5]);
                    foundValidAdapter = true;
                }
            }

            //Wireless
            if (pInfo->Type == 71)
            {
                if (!foundValidAdapter)
                {
                    sprintf(mac, "%02X-%02X-%02X-%02X-%02X-%02X",
                        pInfo->Address[0], pInfo->Address[1],
                        pInfo->Address[2], pInfo->Address[3],
                        pInfo->Address[4], pInfo->Address[5]);
                    foundValidAdapter = true;
                }
            }

            pInfo = pInfo->Next;
        }

        UINT32 cpuInfo[4];
        __cpuid((int*)cpuInfo, 1);
        if ((cpuInfo[2] >> 31) & 1)
        {
            MessageBoxA(0, "Virtual machines are not allowed to play on this server", "Error", MB_OK);
            prevent_send = true;
            return 0;
        }

        if (!foundValidAdapter)
        {
            MessageBoxA(0, "No suitable adapter found for HWID lib", "Error", MB_OK);
            return 0;
        }

        if (prevent_send)
        {
            MessageBoxA(0, "No suitable adapter found for HWID lib", "Error", MB_OK);
            return 0;
        }
        else
        {
            return mac;
        }
    }

    return 0;

}

const char* HawidManager::GetSerial()
{
    DWORD dwDiskSerial = 0;
    char* buffer = (char *)malloc(30);
    char* sysVolumeLetter = (char *)malloc(2);

    GetSystemWindowsDirectoryA(buffer, 30);

    for (int i = 0; i < 3; i++)
        sysVolumeLetter[i] = buffer[i];

    sysVolumeLetter[3] = '\0';


    GetVolumeInformationA(sysVolumeLetter, NULL, NULL, &dwDiskSerial, NULL, NULL, NULL, NULL);

    sprintf(buffer, "%d", dwDiskSerial);

    return buffer;
}
const char* HawidManager::GetPcName()
{
#define  ENV_VAR_STRING_COUNT  (sizeof(envVarStrings)/sizeof(TCHAR*))
#define INFO_BUFFER_SIZE 32767

    char*  infoBuf = (char*)malloc(MAX_COMPUTERNAME_LENGTH + 1);;
    DWORD  bufCharCount = INFO_BUFFER_SIZE;

    if( !GetComputerName( infoBuf, &bufCharCount ) )
        sprintf(infoBuf, "%d", infoBuf);
    return infoBuf;
}

std::string HawidManager::Xor(std::string data) {

    char key[128] = { 'd', '=', 'V', 'T', 'T', '!', 'G', '-', 'v', 'q', '9', 'P', '-', 'z', '4', 'z', '$', '!', 'a', 'C', 'x', 'c', 'S', '$', ';', 'S', 'u', 'j', '-', '7', 'v', 'a', '`', 'n', 'N', '3', '}', 'R', 'J', '(', 'f', '[', 'R', '=', 'K', 'f', 'R', 'k', 'D', 'a', 'R', '4', '.', 'n', '^', 'R', 'a', '<', '{', '$', '}', 'K', 'e', 'q', 'X', '9', 'M', 'Y', '4', 'x', 'e', ';', '?', 's', 'p', 'M', 's', '4', '=', 'Y', ')', '/', 'F', '}', 'G', '[', 'q', '(', 'N', '+', 'P', 'Y', '@', 'L', '>', 'k', 'e', '<', 'b', '6', 'q', 'e', ':', 't', '<', '4', 'L', 'q', 'g', '6', 'Y', ']', ';', '?', 'q', 'r', 'A', 'V', 'M', ')', 'p', '7', 'c', '{', 'u', '8', 'U', '/' };

    std::string output = data;

    for (int i = 0; i < data.size(); i++)
        output[i] = data[i] ^ key[i];
      //  output[i] = data[i] ^ key[i % (sizeof(key) / sizeof(char))];
    return output;
}

const char* HawidManager::GetHWID()
{
    unsigned short CpuHash = HawidManager::getCpuHash();
    std::stringstream cpuhash;
    cpuhash << CpuHash;

    std::string hwidinfo = getHWID();
    std::stringstream hwidhash;
    hwidhash << hwidinfo;
    //unsigned short VolumeHash = HawidManager::getVolumeHash();
    //const char* mac = HawidManager::GetMac();
    const char* PcName = HawidManager::GetPcName();
    //const char* Serial = HawidManager::GetSerial();
    const char* enc2 = "WSAStart";
    //std::stringstream ss;
    //ss << CpuHash;
    //ss << VolumeHash;
    //char* finalBuffer = (char*)malloc(strlen(getHWID().c_str()) + strlen(mac) + strlen(enc2));
    //sprintf(finalBuffer, "%s%s%s", getHWID().c_str(), mac, enc2);

    char* finalBuffer = (char*)malloc(strlen(hwidhash.str().c_str()) + strlen(PcName) + strlen(cpuhash.str().c_str())+strlen(enc2));
    sprintf(finalBuffer, "%s-%s-%s-%s", hwidhash.str().c_str(), PcName, cpuhash.str().c_str(), enc2);

    /*
    std::string HWID = finalBuffer;
    cout << HWID << std::endl;*/

  
    //cout << L"HWID " << HWID.c_str() << L" <Length> " << HWID.length() << std::endl;
    //std::cout << "GetCPUID() " << GetCPUID() << " Len " << GetCPUID().length() << std::endl;
    //std::cout << "Cpu Hash " << CpuHash << " Volume Hash " << VolumeHash<< " Mac "  << mac << " PcName " <<PcName<< " Serial  " << Serial<< std::endl;

    return finalBuffer;
}

const char* HawidManager::cpuId(void)
{
    unsigned long s1 = 0;
    unsigned long s2 = 0;
    unsigned long s3 = 0;
    unsigned long s4 = 0;
    __asm
    {
        mov eax, 00h
        xor edx, edx
        cpuid
        mov s1, edx
        mov s2, eax
    }
    __asm
    {
        mov eax, 01h
        xor ecx, ecx
        xor edx, edx
        cpuid
        mov s3, edx
        mov s4, ecx
    }

    static char buf[100];
    sprintf_s(buf, "%08X%08X%08X%08X", s1, s2, s3, s4);
    return buf;
}

std::string HawidManager::GetCPUID() {

    int CPUInfo[4] = { -1 };
    __cpuid(CPUInfo, 0);
    if (CPUInfo[0] < 4)
        return ""; //Error on retrieving

    stringstream st;
    for (int i = 0; i <= 3; i++) {
        st << CPUInfo[i];
    }

    return st.str();

}

std::string HawidManager::getHWID() {
    HW_PROFILE_INFO hwProfileInfo;
    GetCurrentHwProfile(&hwProfileInfo);
    std::string hwidWString = hwProfileInfo.szHwProfileGuid;

    return hwidWString;
}

unsigned short HawidManager::getCpuHash()
{
    int cpuinfo[4] = { 0, 0, 0, 0 };
    __cpuid(cpuinfo, 0);
    unsigned short hash = 0;
    unsigned short* ptr = (unsigned short*)(&cpuinfo[0]);
    for (unsigned int i = 0; i < 8; i++)
        hash += ptr[i];

    return hash;
}

unsigned short HawidManager::getVolumeHash()
{
    DWORD serialNum = 0;

    // Determine if this volume uses an NTFS file system.      
    GetVolumeInformation("c:\\", NULL, 0, &serialNum, NULL, NULL, NULL, 0);
    unsigned short hash = (unsigned short)((serialNum + (serialNum >> 16)) & 0xFFFF);

    return hash;
}
std::string HawidManager::GetRandomString(size_t length)
{
    srand(time(0));
    string str = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    string newstr;
    int pos;
    while (newstr.size() != length) {
        pos = ((rand() % (str.size() - 1)));
        newstr += str.substr(pos, 1);
    }
    return newstr;
}

std::string HawidManager::GetDate() {
    std::time_t now = std::time(0);
    std::tm* now_tm = std::gmtime(&now);
    char buf[42];
    std::strftime(buf, 42, "0001-%m-%d %H:%M", now_tm);
    return buf;
}

std::string HawidManager::GetDate2() {
    std::time_t now = std::time(0);
    std::tm* now_tm = std::gmtime(&now);
    char buf[42];
    std::strftime(buf, 42, "%Y-%m-%d %H:%M", now_tm);
    return buf;
}
