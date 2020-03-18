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

DWORD WINAPI ServerThreadPipe(LPVOID lpParam) {

	HANDLE hNamedPipe = CreateNamedPipe(LpPipeName, PIPE_ACCESS_DUPLEX, PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT, PIPE_UNLIMITED_INSTANCES, 512, 512, 5000, NULL);
	if (hNamedPipe == INVALID_HANDLE_VALUE) { _tprintf(TEXT("CreateNamedPipe провалилась,из-за ошибки (%d)\n"), GetLastError()); }

	int i, j;
	int C[2][2];
	
	fConnected = ConnectNamedPipe(hNamedPipe, NULL);
	if (!fConnected) {
		_tprintf(TEXT("ConnectNamedPipe провалилась,из-за ошибки (%d)\n"), GetLastError());
		CloseHandle(hNamedPipe);
	}
	LPCWSTR szBuf = TEXT("Available");
	WriteFile(hNamedPipe,   
		szBuf,  
		sizeof(szBuf) + 1, 
		&cbWritten,   
		NULL);        
	_tprintf(TEXT("\nPipe:  %s\n"), szBuf);
	Sleep(1000);
	ReadFile(hNamedPipe, fnBuf, BUFSIZE * sizeof(TCHAR), &cbRead, NULL);
	
	cout << "\nReadfile Success\n" << endl;
	C[0][0] = _tstoi(fnBuf);
	cout << "C[0][0] = " << C[0][0] << endl;
	DisconnectNamedPipe(hNamedPipe);
	fConnected = ConnectNamedPipe(hNamedPipe, NULL);
	if (!fConnected) {
		_tprintf(TEXT("\nConnectNamedPipe провалилась,из-за ошибки (%d)\n"), GetLastError());
		CloseHandle(hNamedPipe);
	}
	szBuf = TEXT("Available");
	WriteFile(hNamedPipe,      
		szBuf,   
		sizeof(szBuf) + 1, 
		&cbWritten, 
		NULL);        
	_tprintf(TEXT("\nPipe:  %s\n"), szBuf);
	Sleep(1000);
	ReadFile(hNamedPipe, fnBuf, BUFSIZE * sizeof(TCHAR), &cbRead, NULL);
	
	cout << "\nReadfile Success" << endl;
	C[0][1] = _tstoi(fnBuf);
	cout << "C[0][1] = " << C[0][1] << endl;
	DisconnectNamedPipe(hNamedPipe);
	fConnected = ConnectNamedPipe(hNamedPipe, NULL);
	if (!fConnected) {
		_tprintf(TEXT("ConnectNamedPipe провалилась,из-за ошибки (%d)\n"), GetLastError());
		CloseHandle(hNamedPipe);
	}
	szBuf = TEXT("Available");
	WriteFile(hNamedPipe,       
		szBuf,     
		sizeof(szBuf) + 1,  
		&cbWritten,   
		NULL);        
	_tprintf(TEXT("\nPipe:  %s"), szBuf);
	Sleep(1000);
	ReadFile(hNamedPipe, fnBuf, BUFSIZE * sizeof(TCHAR), &cbRead, NULL);
	
	cout << "\nReadfile Success" << endl;
	C[1][0] = _tstoi(fnBuf);
	cout << "C[1][0] = " << C[1][0] << endl;
	DisconnectNamedPipe(hNamedPipe);
	fConnected = ConnectNamedPipe(hNamedPipe, NULL);
	if (!fConnected) {
		_tprintf(TEXT("ConnectNamedPipe провалилась,из-за ошибки (%d)\n"), GetLastError());
		CloseHandle(hNamedPipe);
	}
	szBuf = TEXT("Available");
	WriteFile(hNamedPipe,     
		szBuf,   
		sizeof(szBuf) + 1, 
		&cbWritten,   
		NULL);       
	_tprintf(TEXT("\nPipe:  %s"), szBuf);
	Sleep(1000);
	ReadFile(hNamedPipe, fnBuf, BUFSIZE * sizeof(TCHAR), &cbRead, NULL);
	
	cout << "\nReadfile Success" << endl;
	C[1][1] = _tstoi(fnBuf);
	cout << "C[1][1] = " << C[1][1] << endl;
	DisconnectNamedPipe(hNamedPipe);
	cout << "===============" << endl;
	cout << "Matrix C =" << endl;
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
			cout << C[i][j] << " ";
		cout << endl;
	}
	CloseHandle(hNamedPipe);
	return 0;
}

DWORD WINAPI FirstThread11Pipe(LPVOID lpParam) {
	
	Sleep(1500);
	HANDLE hNamedPipe1 = CreateFile(LpPipeName, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
	if (hNamedPipe1 == INVALID_HANDLE_VALUE) { _tprintf(TEXT("C[0][0] не доступен из-за ошибки (%d)\n"), GetLastError()); }
	while (1) {
		if (ReadFile(hNamedPipe1, fnBuf, BUFSIZE * sizeof(TCHAR), &cbRead, NULL)) {
			
			cout << "Connection Success" << endl;
			cout << "Calculating C[0][0]" << endl;

			int i1 = A[0][0] * B[0][0] + A[0][1] * B[1][0];
			wchar_t stri1[256];
			_itow_s(i1, stri1, 10);
			LPCWSTR szBuf = stri1;

			WriteFile(hNamedPipe1, szBuf, sizeof(szBuf) + 1, &cbWritten, NULL);
			_tprintf(TEXT("\nC[0][0] send:  %s"), szBuf);
			
			break;
		}
		else { _tprintf(TEXT("WriteFile failed провалилась,из-за ошибки (%d)\n"), GetLastError()); break; }
	}
	CloseHandle(hNamedPipe1); //_getch();
	return 0;
}

DWORD WINAPI SecondThread12Pipe(LPVOID lpParam) {
	
	Sleep(3000);
	HANDLE hNamedPipe2 = CreateFile(LpPipeName, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
	if (hNamedPipe2 == INVALID_HANDLE_VALUE) { _tprintf(TEXT("C[0][1] не доступен из-за ошибки (%d)\n"), GetLastError()); }
	while (1) {
		if (ReadFile(hNamedPipe2, fnBuf, BUFSIZE * sizeof(TCHAR), &cbRead, NULL)) {
			
			cout << "Connection Success" << endl;
			cout << "Calculating C[0][1]" << endl;

			int i2 = A[0][0] * B[0][1] + A[0][1] * B[1][1];
			wchar_t stri2[256];
			_itow_s(i2, stri2, 10);
			LPCWSTR szBuf = stri2;

			WriteFile(hNamedPipe2, szBuf, sizeof(szBuf) + 1, &cbWritten, NULL);
			_tprintf(TEXT("\nC[0][1] send:  %s"), szBuf);
			
			break;
		}
		else { _tprintf(TEXT("WriteFile failed 2 провалилась,из-за ошибки (%d)\n"), GetLastError()); break; }
	}
	CloseHandle(hNamedPipe2); //_getch();
	return 0;
}

DWORD WINAPI ThirdThread21Pipe(LPVOID lpParam) {
	
	Sleep(4500);
	HANDLE hNamedPipe3 = CreateFile(LpPipeName, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
	if (hNamedPipe3 == INVALID_HANDLE_VALUE) { _tprintf(TEXT("C[1][0] не доступен из-за ошибки (%d)\n"), GetLastError()); }
	while (1) {
		if (ReadFile(hNamedPipe3, fnBuf, BUFSIZE * sizeof(TCHAR), &cbRead, NULL)) {
			
			cout << "Connection Success" << endl;
			cout << "Calculating C[1][0]" << endl;

			int i3 = A[1][0] * B[0][0] + A[1][1] * B[1][0];
			wchar_t stri3[256];
			_itow_s(i3, stri3, 10);
			LPCWSTR szBuf = stri3;

			WriteFile(hNamedPipe3, szBuf, sizeof(szBuf) + 1, &cbWritten, NULL);
			_tprintf(TEXT("\nC[1][0] send:  %s"), szBuf);
			//Sleep(100);
			break;
		}
		else { _tprintf(TEXT("WriteFile failed 3 провалилась,из-за ошибки (%d)\n"), GetLastError()); break; }
	}
	CloseHandle(hNamedPipe3); //_getch();
	return 0;
}

DWORD WINAPI FourthThread22Pipe(LPVOID lpParam) {
	
	Sleep(6000);
	HANDLE hNamedPipe4 = CreateFile(LpPipeName, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
	if (hNamedPipe4 == INVALID_HANDLE_VALUE) { _tprintf(TEXT("C[1][1] не доступен из-за ошибки (%d)\n"), GetLastError()); }
	while (1) {
		if (ReadFile(hNamedPipe4, fnBuf, BUFSIZE * sizeof(TCHAR), &cbRead, NULL)) {
			//Sleep(1000);
			cout << "Connection Success" << endl;
			cout << "Calculating C[1][1]" << endl;

			int i4 = A[1][0] * B[0][1] + A[1][1] * B[1][1];
			wchar_t stri4[256];
			_itow_s(i4, stri4, 10);
			LPCWSTR szBuf = stri4;

			WriteFile(hNamedPipe4, szBuf, sizeof(szBuf) + 1, &cbWritten, NULL);
			_tprintf(TEXT("\nC[1][1] send:  %s"), szBuf);
			//Sleep(100);
			break;
		}
		else { _tprintf(TEXT("WriteFile failed 4 провалилась,из-за ошибки (%d)\n"), GetLastError()); break; }
	}
	CloseHandle(hNamedPipe4); //_getch();
	return 0;
}