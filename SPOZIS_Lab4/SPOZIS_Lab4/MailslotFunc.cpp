#include <conio.h>
#include <windows.h>
#include "winbase.h"
#include "tlhelp32.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "Header.h"
using namespace std;

DWORD WINAPI ServerThreadMailslot(LPVOID lpParam) // Функция Серверной части Mailslot
{
	HANDLE hMailslotServer = CreateMailslot(lpszMailslotNameServer, 0,
		MAILSLOT_WAIT_FOREVER, NULL);
	if (hMailslotServer == INVALID_HANDLE_VALUE)
	{
		cout << "Create CreateMailslot: Error N-" << GetLastError() << endl;
		_getch();
		return 0;
	}
	cout << "MailslotMaster has been created" << endl;
	cout << "You should open Slave process" << endl;
		//_getch();
	int i, j;
	int j11, j12, j21, j22;
	int C[2][2];
	bool exit = true;
	while (exit)
	{
		for (int i = 0; i < 2; i++)
		{
			for (int j = 0; j < 2; j++)
			{
				
				BOOL bReadfile = ReadFile(
					hMailslotServer,
					szReadFileBuffer,
					dwReadFileBufferSize,
					&dwNoBytesRead,
					NULL);
				if (bReadfile == FALSE)
				{
					cout << "Readfile Failed = " << GetLastError() << endl;
					exit = false;
				}
				cout << "Readfile Success" << endl;
				C[i][j] = atoi(szReadFileBuffer);
				cout << "C["<<i<<"]["<<j<<"] = " << C[i][j] << endl;
				
			}
		}
		exit = false;
	}
	cout << "===============" << endl;
	cout << "Matrix C =" << endl;
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
			cout << C[i][j] << " ";
			cout << endl;
	}
	CloseHandle(hMailslotServer);
	return 0;
}

DWORD WINAPI FirstThread11Mailslot(LPVOID lpParam) // Функция Клиента 1 Mailslot
{
	HANDLE hMailslotClient1 = CreateFile(
		lpszMailslotNameServer, GENERIC_WRITE,
		FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);

	if (hMailslotClient1 == INVALID_HANDLE_VALUE)
	{
		cout << "CreateFile 1: Error N-" << GetLastError() << endl;
		_getch();
		return 0;
	}
	cout << "File 1 Creation Success" << endl;
	cout << "Calculating C[0][0]" << endl;

	int i1 = A[0][0] * B[0][0] + A[0][1] * B[1][0];
	char szWriteFileBuffer[1023];
	sprintf_s(szWriteFileBuffer, "%d", i1);
	DWORD dwWriteFileBufferSize = sizeof(szWriteFileBuffer);

	BOOL bWritefile = WriteFile(
		hMailslotClient1,
		szWriteFileBuffer,
		dwWriteFileBufferSize,
		&dwNoBytesWrite,
		NULL);
	if (bWritefile == FALSE)
	{
		cout << "Writefile 1 Failed = " << GetLastError() << endl;
	}
	cout << "Writefile 1 Success" << endl;

	CloseHandle(hMailslotClient1);
	return 0;
}

DWORD WINAPI SecondThread12Mailslot(LPVOID lpParam) // Функция Клиента 2 Mailslot
{
	HANDLE hMailslotClient2 = CreateFile(
		lpszMailslotNameServer, GENERIC_WRITE,
		FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);

	if (hMailslotClient2 == INVALID_HANDLE_VALUE)
	{
		cout << "CreateFile 2: Error N-" << GetLastError() << endl;
		_getch();
		return 0;
	}
	cout << "File 2 Creation Success" << endl;
	cout << "Calculating C[0][1]" << endl;

	int i2 = A[0][0] * B[0][1] + A[0][1] * B[1][1];
	char szWriteFileBuffer[1023];
	sprintf_s(szWriteFileBuffer, "%d", i2);
	DWORD dwWriteFileBufferSize = sizeof(szWriteFileBuffer);

	BOOL bWritefile = WriteFile(
		hMailslotClient2,
		szWriteFileBuffer,
		dwWriteFileBufferSize,
		&dwNoBytesWrite,
		NULL);
	if (bWritefile == FALSE)
	{
		cout << "Writefile 2 Failed = " << GetLastError() << endl;
	}
	cout << "Writefile 2 Success" << endl;

	CloseHandle(hMailslotClient2);
	return 0;
}

DWORD WINAPI ThirdThread21Mailslot(LPVOID lpParam) // Функция Клиента 3 Mailslot
{
	HANDLE hMailslotClient3 = CreateFile(
		lpszMailslotNameServer, GENERIC_WRITE,
		FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);

	if (hMailslotClient3 == INVALID_HANDLE_VALUE)
	{
		cout << "CreateFile 3: Error N-" << GetLastError() << endl;
		_getch();
		return 0;
	}
	cout << "File 3 Creation Success" << endl;
	cout << "Calculating C[1][0]" << endl;

	int i3 = A[1][0] * B[0][0] + A[1][1] * B[1][0];
	char szWriteFileBuffer[1023];
	sprintf_s(szWriteFileBuffer, "%d", i3);
	DWORD dwWriteFileBufferSize = sizeof(szWriteFileBuffer);

	BOOL bWritefile = WriteFile(
		hMailslotClient3,
		szWriteFileBuffer,
		dwWriteFileBufferSize,
		&dwNoBytesWrite,
		NULL);
	if (bWritefile == FALSE)
	{
		cout << "Writefile 3 Failed = " << GetLastError() << endl;
	}
	cout << "Writefile 3 Success" << endl;

	CloseHandle(hMailslotClient3);
	return 0;
}

DWORD WINAPI FourthThread22Mailslot(LPVOID lpParam) // Функция Клиента 4 Mailslot
{
	HANDLE hMailslotClient4 = CreateFile(
		lpszMailslotNameServer, GENERIC_WRITE,
		FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);

	if (hMailslotClient4 == INVALID_HANDLE_VALUE)
	{
		cout << "CreateFile 4: Error N-" << GetLastError() << endl;
		_getch();
		return 0;
	}
	cout << "File 4 Creation Success" << endl;

	cout << "Calculating C[1][1]" << endl;

	int i4 = A[1][0] * B[0][1] + A[1][1] * B[1][1];
	char szWriteFileBuffer[1023];
	sprintf_s(szWriteFileBuffer, "%d", i4);
	DWORD dwWriteFileBufferSize = sizeof(szWriteFileBuffer);

	BOOL bWritefile = WriteFile(
		hMailslotClient4,
		szWriteFileBuffer,
		dwWriteFileBufferSize,
		&dwNoBytesWrite,
		NULL);
	if (bWritefile == FALSE)
	{
		cout << "Writefile 4 Failed = " << GetLastError() << endl;
	}
	cout << "Writefile 4 Success" << endl;

	CloseHandle(hMailslotClient4);
	return 0;
}