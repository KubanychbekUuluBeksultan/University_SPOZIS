#include <conio.h>
#include <windows.h>
#include "winbase.h"
#include "tlhelp32.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "Header.h"
#include <strsafe.h>
#include <tchar.h>
using namespace std;
#define BUFSIZE 512

HANDLE hFileMap;

DWORD WINAPI ServerThreadMap(LPVOID lpParam) {
	LPCWSTR szMsg = TEXT("Привет"); TCHAR  fnBuf[BUFSIZE]; LPVOID lpFileMap;
	HANDLE hFileMap = CreateFileMapping((HANDLE)0xFFFFFFFF, NULL, PAGE_READWRITE, 0, BUFSIZE, lpFileShre);
	if (hFileMap == 0) { _tprintf(TEXT("CreateFileMapping провалилась,из-за ошибки (%d)\n"), GetLastError()); }
	else  cout << "Run process\n";
	lpFileMap = MapViewOfFile(hFileMap,
		FILE_MAP_ALL_ACCESS,
		0, 0, BUFSIZE);
	if (lpFileMap == 0) { _tprintf(TEXT("MapViewOfFile провалилась,из-за ошибки (%d)\n"), GetLastError()); }
	//CopyMemory(fnBuf, lpFileMap, sizeof(fnBuf));//считываие данных из файла
	//if (fnBuf != 0) { cout << "Read the file\n"; }

	int i, j;
	int C[2][2];
	Sleep(600);
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{

			CopyMemory(fnBuf, lpFileMap, sizeof(fnBuf));//считываие данных из файла
			if (fnBuf != 0) { cout << "Read the file\n"; }
			else
			{
				cout << "Readfile Failed = " << GetLastError() << endl;
				break;
			}
			C[i][j] = _tstoi(fnBuf);
			cout << "C[" << i << "][" << j << "] = " << C[i][j] << endl;
			Sleep(100);

		}
	}

	cout << "===============" << endl;
	cout << "Matrix C =" << endl;
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
			cout << C[i][j] << " ";
		cout << endl;
	}
	UnmapViewOfFile(lpFileMap);
	CloseHandle(hFileMap); cout << "End of the process";

	return 0;
}

DWORD WINAPI FirstThread11Map(LPVOID lpParam) {
	TCHAR  fnBuf[BUFSIZE]; LPVOID lpFileMap;
	Sleep(500);
	hFileMap = OpenFileMapping(FILE_MAP_ALL_ACCESS,  
		FALSE,              
		lpFileShre);             
	if (hFileMap == 0) { _tprintf(TEXT("OpenFileMapping провалилась,из-за ошибки (%d)\n"), GetLastError()); }
	lpFileMap = MapViewOfFile(hFileMap, FILE_MAP_ALL_ACCESS, 0, 0, BUFSIZE);
	if (lpFileMap == 0) { _tprintf(TEXT("MapViewOfFile провалилась,из-за ошибки (%d)\n"), GetLastError()); }

	cout << "Calculating C[0][0]" << endl;
	int i1 = A[0][0] * B[0][0] + A[0][1] * B[1][0];
	wchar_t stri1[256];
	_itow_s(i1, stri1, 10);
	LPCWSTR szMsg = stri1;

	CopyMemory(lpFileMap, szMsg, sizeof(szMsg));//запись данных в файл
	_tprintf(TEXT("\nC[0][0] send:  %s"), szMsg);
	UnmapViewOfFile(lpFileMap);

	return 0;
}

DWORD WINAPI SecondThread12Map(LPVOID lpParam) {
	LPCWSTR szMsg; TCHAR  fnBuf[BUFSIZE]; LPVOID lpFileMap;
	Sleep(500);
	hFileMap = OpenFileMapping(FILE_MAP_ALL_ACCESS,  
		FALSE,            
		lpFileShre);        
	if (hFileMap == 0) { _tprintf(TEXT("OpenFileMapping провалилась,из-за ошибки (%d)\n"), GetLastError()); }
	lpFileMap = MapViewOfFile(hFileMap, FILE_MAP_ALL_ACCESS, 0, 0, BUFSIZE);
	if (lpFileMap == 0) { _tprintf(TEXT("MapViewOfFile провалилась,из-за ошибки (%d)\n"), GetLastError()); }

	cout << "Calculating C[0][1]" << endl;
	int i2 = A[0][0] * B[0][1] + A[0][1] * B[1][1];
	wchar_t stri2[256];
	_itow_s(i2, stri2, 10);
	szMsg = stri2;

	CopyMemory(lpFileMap, szMsg, sizeof(szMsg));//запись данных в файл
	_tprintf(TEXT("\nC[0][1] send:  %s"), szMsg);
	UnmapViewOfFile(lpFileMap);

	return 0;
}

DWORD WINAPI ThirdThread21Map(LPVOID lpParam) {
	LPCWSTR szMsg; TCHAR  fnBuf[BUFSIZE]; LPVOID lpFileMap;
	Sleep(500);
	hFileMap = OpenFileMapping(FILE_MAP_ALL_ACCESS,  
		FALSE,               
		lpFileShre);          
	if (hFileMap == 0) { _tprintf(TEXT("OpenFileMapping провалилась,из-за ошибки (%d)\n"), GetLastError()); }
	lpFileMap = MapViewOfFile(hFileMap, FILE_MAP_ALL_ACCESS, 0, 0, BUFSIZE);
	if (lpFileMap == 0) { _tprintf(TEXT("MapViewOfFile провалилась,из-за ошибки (%d)\n"), GetLastError()); }

	cout << "Calculating C[1][0]" << endl;
	int i3 = A[1][0] * B[0][0] + A[1][1] * B[1][0];
	wchar_t stri3[256];
	_itow_s(i3, stri3, 10);
	szMsg = stri3;

	CopyMemory(lpFileMap, szMsg, sizeof(szMsg));//запись данных в файл
	_tprintf(TEXT("\nC[1][0] send:  %s"), szMsg);
	UnmapViewOfFile(lpFileMap);

	return 0;
}

DWORD WINAPI FourthThread22Map(LPVOID lpParam) {
	LPCWSTR szMsg; TCHAR  fnBuf[BUFSIZE]; LPVOID lpFileMap;
	Sleep(500);
	hFileMap = OpenFileMapping(FILE_MAP_ALL_ACCESS,  
		FALSE,               
		lpFileShre);            
	if (hFileMap == 0) { _tprintf(TEXT("OpenFileMapping провалилась,из-за ошибки (%d)\n"), GetLastError()); }
	lpFileMap = MapViewOfFile(hFileMap, FILE_MAP_ALL_ACCESS, 0, 0, BUFSIZE);
	if (lpFileMap == 0) { _tprintf(TEXT("MapViewOfFile провалилась,из-за ошибки (%d)\n"), GetLastError()); }

	cout << "Calculating C[1][1]" << endl;
	int i4 = A[1][0] * B[0][1] + A[1][1] * B[1][1];
	wchar_t stri4[256];
	_itow_s(i4, stri4, 10);
	szMsg = stri4;

	CopyMemory(lpFileMap, szMsg, sizeof(szMsg));//запись данных в файл
	_tprintf(TEXT("\nC[1][1] send:  %s"), szMsg);
	UnmapViewOfFile(lpFileMap);

	return 0;
}