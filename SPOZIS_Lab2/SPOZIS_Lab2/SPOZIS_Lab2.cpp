#define _CRT_SECURE_NO_WARNINGS
#include <conio.h>
#include <windows.h>
#include "winbase.h"
#include "tlhelp32.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <locale>
using namespace std;

#define cout wcout
#define cin wcin
#define STRING_LENGTH 256

//int fTask1() //принимая дескриптор, имя или полное имя модуля, возвращает другие два элемента  в своих выходных параметрах 
//{
//	int m = 0;
//	HANDLE handle;
//	HMODULE hModule;
//	LPCWSTR Name;
//	DWORD FName;
//
//	std::cout << GetCurrentProcessId() << std::endl;
//
//	//hModule = GetModuleHandle(longName);
//
//	//Vivod(hModule, longName);
//
//	//break;
//	//std::cout << OpenProcess(PROCESS_ALL_ACCESS, 1, GetCurrentProcessId()) << std::endl;
//	//std::cout << GetModuleFileName(OpenProcess(PROCESS_ALL_ACCESS, 1, GetCurrentProcessId()), )
//	//CloseHandle(OpenProcess(PROCESS_ALL_ACCESS, 1, GetCurrentProcessId()));
//
//
//
//	printf("1. Handle | 2. Name | 3. FName\n");
//	cin >> m;
//	
//	//scanf_s("Select mode: %i\n", m);
//	switch (m)
//	{
//	case 1: {
//		printf("Mode 'Handle' selected\nInput Handle:\n");
//		//scanf("Input Handle: %", handle)
//		cin >> handle;
//		break;
//	}
//	case 2: {
//		printf("Mode 'Name' selected\nInput Name:\n");
//		//scanf("Input Name: %", handle)
//		//std::cin >> std::istream::Name >> std:enbl;
//		std::cout << GetModuleHandle(TEXT("C:\\Learn and Design\\University\\Третий курс\\Второй семестр\\СПОЗИС\\Лабораторные\\Lab2\\SPOZIS_Lab2\\Debug\\SPOZIS_Lab2.exe")) << std::endl;
//		break;
//	}
//	case 3: {
//		printf("Mode 'FName' selected\nInput FName:\n");
//		//scanf("Input Name: %", handle)
//		cin >> FName;
//		break;
//	}
//	default: {
//		printf("Invalid mode\n");
//		break;
//	}
//	}
//
//	system("pause");
//	return 0;
//}

int GetFileName(wchar_t* outName, wchar_t* fullName, const int bufferLength)
{
	wchar_t* name = wcsrchr(fullName, L'\\');
	if (name == NULL)
	{
		wcsncpy(outName, fullName, bufferLength);
		return 0;
	}
	else
	{
		wcsncpy(outName, name + 1, bufferLength);
		return 1;
	}
}

void Out(HMODULE hModule, wchar_t* longName)
{
	wchar_t* shortName = new wchar_t[STRING_LENGTH];
	GetFileName(shortName, longName, STRING_LENGTH);
	cout << "\nHandle: " << hModule << endl << "Name: " << shortName << endl << "FName: " << longName << endl;
	delete shortName;
}

int fTask2()
{
	DWORD dCurrentId = GetCurrentProcessId();
	HANDLE hCurrentPseudo = GetCurrentProcess();
	HANDLE hCurrentIdDup;
	DuplicateHandle(hCurrentPseudo, hCurrentPseudo, hCurrentPseudo, &hCurrentIdDup, 0, FALSE, DUPLICATE_SAME_ACCESS);
	HANDLE hCurrentIdOpen = OpenProcess(PROCESS_DUP_HANDLE, TRUE, dCurrentId);
	BOOL fClosedDup = CloseHandle(hCurrentIdDup);
	BOOL fClosedOpen = CloseHandle(hCurrentIdOpen);
	cout << "\nCurrent ID: " << dCurrentId
		<< "\nCurrent Pseudo: " << hCurrentPseudo
		<< "\nCurrent ID from DuplicateHandle: " << hCurrentIdDup
		<< "\nCurrent ID from OpenProcess: " << hCurrentIdOpen
		<< "\nClosing Handle from OpenProcess: " << fClosedOpen
		<< "\nClosing Handle from DuplicateHandle: " << fClosedDup << endl;
	system("pause");
	return 0;
}

void ShowProcessEntry(PROCESSENTRY32& entry)
{
	cout << "\n\nth32ProcessID = " << entry.th32ProcessID;
	cout << "\nth32DefaultHeapID = " << entry.th32DefaultHeapID;
	cout << "\nth32ModuleID = " << entry.th32ModuleID;
	cout << "\nth32ParentProcessID = " << entry.th32ParentProcessID;
	cout << "\ncntUsage = " << entry.cntUsage;
	cout << "\ncntThreads = " << entry.cntThreads;
	cout << "\npcPriClassBase = " << entry.pcPriClassBase;
	cout << "\ndwFlags = " << entry.dwFlags;
	cout << "\nszExeFile = " << entry.szExeFile;
}

void ShowThreadEntry(THREADENTRY32& entry)
{
	cout << "\n\nth32ThreadID = " << entry.th32ThreadID;
	cout << "\nth32OwnerProcessID = " << entry.th32OwnerProcessID;
	cout << "\ncntUsage = " << entry.cntUsage;
	cout << "\ntpBasePri = " << entry.tpBasePri;
	cout << "\ntpDeltaPri = " << entry.tpDeltaPri;
	cout << "\ndwFlags = " << entry.dwFlags;
}

void ShowModuleEntry(MODULEENTRY32& entry)
{
	cout << "\n\nth32ModuleID \t= \t" << entry.th32ModuleID;
	cout << "\nth32ProcessID \t= \t" << entry.th32ProcessID;
	cout << "\nGlblcntUsage \t= \t" << entry.GlblcntUsage;
	cout << "\nProccntUsage \t= \t" << entry.ProccntUsage;
	cout << "\nmodBaseAddr \t= \t" << entry.modBaseAddr;
	cout << "\nmodBaseSize \t= \t" << entry.modBaseSize;
	cout << "\nhModule \t= \t" << entry.hModule;
	cout << "\nszModule \t= \t" << entry.szModule;
	cout << "\nszExePath \t= \t" << entry.szExePath;
}

void ShowProcesses()
{
	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	cout << "\nSnapshot ID = " << hSnapshot;
	PROCESSENTRY32 entry;
	entry.dwSize = sizeof(PROCESSENTRY32);
	BOOL fRepeat = Process32First(hSnapshot, &entry);
	int i = 0;
	while (fRepeat)
	{
		i++;
		ShowProcessEntry(entry);
		fRepeat = Process32Next(hSnapshot, &entry);
	}
	CloseHandle(hSnapshot);
	cout << "\n\n|End of processes|\n\n";
}

void ShowThreads()
{
	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0);
	cout << "\nSnapshot ID = " << hSnapshot;
	THREADENTRY32 entry;
	entry.dwSize = sizeof(THREADENTRY32);
	BOOL fRepeat = Thread32First(hSnapshot, &entry);
	DWORD dwCurentProcessId = GetCurrentProcessId();
	while (fRepeat)
	{
		if (entry.th32OwnerProcessID == dwCurentProcessId)
		{
			ShowThreadEntry(entry);
		}
		fRepeat = Thread32Next(hSnapshot, &entry);
	}
	CloseHandle(hSnapshot);
	cout << "\n\n|End of Threads|\n\n";
}

void ShowModules()
{
	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, 0);
	cout << "\nSnapshot ID = " << hSnapshot;
	MODULEENTRY32 entry;
	entry.dwSize = sizeof(MODULEENTRY32);
	BOOL fRepeat = Module32First(hSnapshot, &entry);
	while (fRepeat)
	{
		ShowModuleEntry(entry);
		fRepeat = Module32Next(hSnapshot, &entry);
	}
	CloseHandle(hSnapshot);
	cout << "\n\n|End of Modules|\n\n";
}

int fTask3()
{
	cout << "\n\n|Processes|\n";
	ShowProcesses();
	cout << "\n\n|Threads|\n";
	_getch();
	ShowThreads();
	cout << "\n\n|Modules|\n";
	_getch();
	ShowModules();
	system("pause");
	return 0;
}

int main(int argv, char** argc)
{
	setlocale(LC_ALL, "rus");

	cout.imbue(locale("rus_rus.1251"));
	char* param = new char[STRING_LENGTH];
	wchar_t* longName = new wchar_t[STRING_LENGTH];
	strcpy(param, argc[0]);
	wchar_t* shortName = new wchar_t[STRING_LENGTH];
	bool exit = true;
	while (exit)
	{
		cout << "\nSelect mode:" << endl
			<< "0. Handle, Name, Full Name" << endl
			<< "1. Input Name" << endl
			<< "2. Input FName" << endl
			<< "3. Input Handle" << endl
			<< "4. Task 2" << endl
			<< "5. Task 3" << endl
			<< "6. Exit" << endl
			<< "Select: ";
		int n = 0;
		cin >> n;
		HMODULE hModule;
		switch (n)
		{
		case 0:
		{
			mbstowcs(longName, param, STRING_LENGTH);
			hModule = GetModuleHandle(longName);
			Out(hModule, longName);
			break;
		}
		case 1:
		{
			cout << endl << "Input Name: ";
			cin >> shortName;
			GetModuleFileName(GetModuleHandle(shortName), longName, STRING_LENGTH);
			hModule = GetModuleHandle(longName);
			Out(hModule, longName);
			break;
		}
		case 2:
		{
			cout << endl << "Input FName: ";
			cin >> longName;
			GetFileName(shortName, longName, STRING_LENGTH);
			hModule = GetModuleHandle(longName);
			Out(hModule, longName);
			break;
		}
		case 3:
		{
			cout << endl << "Input Handle: ";
			wchar_t* temp = new wchar_t[10];
			cin >> temp;
			wchar_t* endptr;
			long num = wcstoul(temp, &endptr, 16);
			hModule = (HMODULE)num;
			GetModuleFileName(hModule, longName, STRING_LENGTH);
			Out(hModule, longName);
			delete[] temp;
			break;
		}
		case 4:
		{
			fTask2();
			break;
		}
		case 5:
		{
			fTask3();
			break;
		}
		case 6:
		{
			exit = false;
			break;
		}
		}
		_getch();
	}
	delete[] param;
	delete[] longName;
	delete[] shortName;
}