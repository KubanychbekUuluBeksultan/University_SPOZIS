#pragma once
#include <conio.h>
#include <windows.h>
#include "winbase.h"
#include "tlhelp32.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <locale>
using namespace std;


extern HANDLE hThread0;
extern HANDLE hThread1;
extern HANDLE hThread2;
extern HANDLE hThread3;
extern HANDLE hThread4;

//Матрицы для задачи
//extern int i, j, k;

static int A[2][2] = { {2, 2}, {1, 2} };
static int B[2][2] = { {3, 4}, {2, 3} };
//extern double C[2][2];

// Функции Mailslot
DWORD WINAPI ServerThreadMailslot(LPVOID lpParam);
DWORD WINAPI FirstThread11Mailslot(LPVOID lpParam);
DWORD WINAPI SecondThread12Mailslot(LPVOID lpParam);
DWORD WINAPI ThirdThread21Mailslot(LPVOID lpParam);
DWORD WINAPI FourthThread22Mailslot(LPVOID lpParam);

extern HANDLE hMailslotServer;
extern HANDLE hMailslotClient1;
extern HANDLE hMailslotClient2;
extern HANDLE hMailslotClient3;
extern HANDLE hMailslotClient4;
static LPCTSTR lpszMailslotNameServer = TEXT("\\\\.\\mailslot\\server_mailslot");
static LPCTSTR lpszMailslotNameClient1 = TEXT("\\\\.\\mailslot\\client1_mailslot");
//LPCTSTR lpszMailslotNameClient2 = TEXT("\\\\.\\mailslot\\client1_mailslot");
//LPCTSTR lpszMailslotNameClient3 = TEXT("\\\\.\\mailslot\\client1_mailslot");
//LPCTSTR lpszMailslotNameClient4 = TEXT("\\\\.\\mailslot\\client1_mailslot");
//--ReadFile Local Variable
extern BOOL bReadfile;
static DWORD dwNoBytesRead;
static char szReadFileBuffer[1023];
static DWORD dwReadFileBufferSize = sizeof(szReadFileBuffer);
//--WriteFile Local Variable
extern BOOL bWritefile;
static DWORD dwNoBytesWrite;
//static char szWriteFileBuffer[1023];
//static DWORD dwWriteFileBufferSize = sizeof(szWriteFileBuffer);


// Функции Pipe
DWORD WINAPI ServerThreadPipe(LPVOID lpParam);
DWORD WINAPI FirstThread11Pipe(LPVOID lpParam);
DWORD WINAPI SecondThread12Pipe(LPVOID lpParam);
DWORD WINAPI ThirdThread21Pipe(LPVOID lpParam);
DWORD WINAPI FourthThread22Pipe(LPVOID lpParam);

//HANDLE  hNamedPipe2;//глобальные переменные
static LPCTSTR LpPipeName = TEXT("\\\\.\\pipe\\MyPipe");

static BOOL fConnected; 
static DWORD cbRead;
static DWORD cbWritten;
static TCHAR  fnBuf[512]; //LPCWSTR szBuf = TEXT("Привет");

// Функции Memory-mapped file
DWORD WINAPI ServerThreadMap(LPVOID lpParam);
DWORD WINAPI FirstThread11Map(LPVOID lpParam);
DWORD WINAPI SecondThread12Map(LPVOID lpParam);
DWORD WINAPI ThirdThread21Map(LPVOID lpParam);
DWORD WINAPI FourthThread22Map(LPVOID lpParam);

//extern HANDLE hFileMap; 
static LPCTSTR lpFileShre = TEXT("MyFileShre"); 
static LPVOID lpFileMap;