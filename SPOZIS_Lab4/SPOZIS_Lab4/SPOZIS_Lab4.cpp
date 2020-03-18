#pragma once

#include <conio.h>
#include <windows.h>
#include "winbase.h"
#include "tlhelp32.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <locale>
#include "time.h"
#include "Header.h"
#include <strsafe.h>
#include <tchar.h>//для print_f
using namespace std;


int main()
{
	bool exit = true;
	while (exit)
	{
		cout << "\nSelect mode:" << endl
			<< "1. Mailslot" << endl
			<< "2. Pipe" << endl
			<< "3. Memory-mapped file" << endl
			<< "4. Exit" << endl
			<< "Select: ";
		int n = 0;
		cin >> n;
		HMODULE hModule;
		switch (n)
		{
		case 1:
		{
			//HANDLE hThread0; hThreads в Хэдере
			//HANDLE hThread1;
			//HANDLE hThread2;
			//HANDLE hThread3;
			//HANDLE hThread4;

			HANDLE hThread0 = CreateThread(NULL, 0, ServerThreadMailslot, NULL, 0, NULL);
			Sleep(100);
			HANDLE hThread1 = CreateThread(NULL, 0, FirstThread11Mailslot, NULL, 0, NULL);
			Sleep(100);
			HANDLE hThread2 = CreateThread(NULL, 0, SecondThread12Mailslot, NULL, 0, NULL);
			Sleep(100);
			HANDLE hThread3 = CreateThread(NULL, 0, ThirdThread21Mailslot, NULL, 0, NULL);
			Sleep(100);
			HANDLE hThread4 = CreateThread(NULL, 0, FourthThread22Mailslot, NULL, 0, NULL);
			CloseHandle(hThread0);
			CloseHandle(hThread1);
			CloseHandle(hThread2);
			CloseHandle(hThread3);
			CloseHandle(hThread4);
			//_getch();
			Sleep(100);
			
			break;
		}
		case 2:
		{
			HANDLE hThread0 = CreateThread(NULL, 0, ServerThreadPipe, NULL, 0, NULL);
			HANDLE hThread1 = CreateThread(NULL, 0, FirstThread11Pipe, NULL, 0, NULL);
			Sleep(100);
			HANDLE hThread2 = CreateThread(NULL, 0, SecondThread12Pipe, NULL, 0, NULL);
			Sleep(100);
			HANDLE hThread3 = CreateThread(NULL, 0, ThirdThread21Pipe, NULL, 0, NULL);
			Sleep(100);
			HANDLE hThread4 = CreateThread(NULL, 0, FourthThread22Pipe, NULL, 0, NULL);

			CloseHandle(hThread0);
			CloseHandle(hThread1);
			CloseHandle(hThread2);
			CloseHandle(hThread3);
			CloseHandle(hThread4);
			Sleep(10000);
			break;
		}
		case 3:
		{
			HANDLE hThread0 = CreateThread(NULL, 0, ServerThreadMap, NULL, 0, NULL);
			HANDLE hThread1 = CreateThread(NULL, 0, FirstThread11Map, NULL, 0, NULL);
			Sleep(100);
			HANDLE hThread2 = CreateThread(NULL, 0, SecondThread12Map, NULL, 0, NULL);
			Sleep(100);
			HANDLE hThread3 = CreateThread(NULL, 0, ThirdThread21Map, NULL, 0, NULL);
			Sleep(100);
			HANDLE hThread4 = CreateThread(NULL, 0, FourthThread22Map, NULL, 0, NULL);

			CloseHandle(hThread0);
			CloseHandle(hThread1);
			CloseHandle(hThread2);
			CloseHandle(hThread3);
			CloseHandle(hThread4);
			Sleep(10000);
			break;
		}
		case 4:
		{
			exit = false;
		}
		}
		//_getch();
	}
}
