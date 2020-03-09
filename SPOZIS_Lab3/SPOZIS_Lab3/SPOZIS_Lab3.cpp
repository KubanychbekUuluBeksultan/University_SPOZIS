#include <conio.h>
#include <windows.h>
#include "winbase.h"
#include "tlhelp32.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <locale>
using namespace std;

#define THREADS_NUMBER 5
#define ITERATIONS_NUMBER 5
#define PAUSE 10

DWORD dwCounter = 0;

CRITICAL_SECTION section = { 0 }; //Критическая секция

VOID CriticalSection(VOID);
DWORD WINAPI CriticalSectionFunction(LPVOID lpParam);

DWORD WINAPI CriticalSectionFunction(LPVOID lpParam)
{
	for (DWORD i = 0; i < ITERATIONS_NUMBER; ++i)
	{
		EnterCriticalSection(&section);
		std::wcout << L"Thread id is " << *(DWORD*)lpParam
			<< L" and i = " << i << std::endl;
		LeaveCriticalSection(&section);
	}

	ExitThread(0);
}

DWORD WINAPI MutexThreadFunction(LPVOID lpParam) {
	HANDLE hMutex = (HANDLE)lpParam;
	DWORD i;
	for (i = 0; i < ITERATIONS_NUMBER; i++) {
		WaitForSingleObject(hMutex, INFINITE);
		dwCounter++;
		ReleaseMutex(hMutex);
		Sleep(PAUSE);
	}
	ExitThread(0);
}

typedef struct  _STRUCT_DATA_
{
	int id;
	int tickets;
}_DATA, * _pDATA;

HANDLE g_hEvent;
DWORD WINAPI FirstThreadFunc(LPVOID lpParam);
DWORD WINAPI SecondThreadFunc(LPVOID lpParam);

DWORD WINAPI FirstThreadFunc(LPVOID lpParam)
{
	_pDATA data = (_pDATA)lpParam;
	while (TRUE)
	{
		WaitForSingleObject(g_hEvent, INFINITE);
		if (data->tickets > 0)
		{
			Sleep(1);
			cout << "Id of function: " << data->id++;
			cout << " | run thread 1 | ticket: " << data->tickets-- << endl;
			SetEvent(g_hEvent);
		}
		else {
			SetEvent(g_hEvent);
			break;
		}
	}
	return 0;
}

DWORD WINAPI SecondThreadFunc(LPVOID lpParam)
{
	_pDATA data = (_pDATA)lpParam;
	while (TRUE)
	{
		WaitForSingleObject(g_hEvent, INFINITE);
		if (data->tickets > 0)
		{
			Sleep(1);
			cout << "Id of function: " << data->id++;
			cout << " | run thread 2 | ticket: " << data->tickets-- << endl;
			SetEvent(g_hEvent);
		}
		else {
			SetEvent(g_hEvent);
			break;
		}
	}
	return 0;
}

int main()
{
	
	bool exit = true;
	while (exit)
	{
		cout << "\nSelect mode:" << endl
			<< "1. Selection counter" << endl
			<< "2. Mutex" << endl
			<< "3. Events" << endl
			<< "4. Exit" << endl
			<< "Select: ";
		int n = 0;
		cin >> n;
		HMODULE hModule;
		switch (n)
		{
		case 1:
		{
			HANDLE threads[THREADS_NUMBER];

			InitializeCriticalSection(&section);
			for (DWORD i = 0; i < THREADS_NUMBER; ++i)
			{
				DWORD* tmp = new DWORD;
				*tmp = i;
				threads[i] = CreateThread(NULL, 0, CriticalSectionFunction, tmp, 0, 0);
			}

			WaitForMultipleObjects(THREADS_NUMBER, threads, TRUE, INFINITE);
			DeleteCriticalSection(&section);

			for (size_t i = 0; i < THREADS_NUMBER; ++i)
			{
				if (threads[i] != INVALID_HANDLE_VALUE)
					CloseHandle(threads[i]);
			}
			break;
		}
		case 2:
		{
			DWORD i;
			HANDLE hThreads[THREADS_NUMBER];
			HANDLE hMutex = CreateMutex(NULL, FALSE, NULL);

			for (i = 0; i < THREADS_NUMBER; i++) {
				hThreads[i] = CreateThread(NULL, 0, MutexThreadFunction, hMutex, 0, NULL);
			}

			WaitForMultipleObjects(THREADS_NUMBER, hThreads, TRUE, INFINITE);
			cout << "Counter for " << THREADS_NUMBER << " threads and " << ITERATIONS_NUMBER << " iterations = " << dwCounter << endl;

			for (i = 0; i < THREADS_NUMBER; i++) {
				CloseHandle(hThreads[i]);
			}
			CloseHandle(hMutex);
			break;
		}
		case 3:
		{
			HANDLE hThread1;
			HANDLE hThread2;

			_DATA stru_data;
			stru_data.id = 0;
			stru_data.tickets = 20;

			g_hEvent = CreateEvent(NULL, FALSE, FALSE, L"Ticket");
			if (g_hEvent) {
				if (ERROR_ALREADY_EXISTS == GetLastError()) {
					cout << "the instance is exist!" << endl;
					break;
				}
			}

			hThread1 = CreateThread(NULL, 0, FirstThreadFunc, &stru_data, 0, NULL);
			hThread2 = CreateThread(NULL, 0, SecondThreadFunc, &stru_data, 0, NULL);

			CloseHandle(hThread1);
			CloseHandle(hThread2);

			SetEvent(g_hEvent);
			Sleep(1000);
			CloseHandle(g_hEvent);
			break;
		}
		case 4:
		{
			exit = false;
			break;
		}
		}
		//_getch();
	}
}