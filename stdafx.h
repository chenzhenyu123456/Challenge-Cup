
// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�

#pragma once

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // �� Windows ͷ���ų�����ʹ�õ�����
#endif

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // ĳЩ CString ���캯��������ʽ��

// �ر� MFC ��ĳЩ�����������ɷ��ĺ��Եľ�����Ϣ������
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC ��������ͱ�׼���
#include <afxext.h>         // MFC ��չ


#include <afxdisp.h>        // MFC �Զ�����

#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // MFC �� Internet Explorer 4 �����ؼ���֧��
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>             // MFC �� Windows �����ؼ���֧��
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxcontrolbars.h>     // �������Ϳؼ����� MFC ֧��









#ifdef _UNICODE
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
#endif


extern char InputPath[MAX_PATH];     //��Ŷ����Ŀ¼·��   
extern char OutputPath[MAX_PATH];     //��������Ŀ¼·��

extern bool start;

extern int year;

#include <gl/gl.h>
#include <gl/glu.h>
#include <gl/glut.h>
#include <gl/glaux.h>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#include <windows.h>
#include <stdio.h>
#include <string.h>
#define LEN 1024
#define MAX_CHAR 1280
using namespace std;
typedef long long LL;
const int MAXN = 100000 + 10;
const int INF = 1000000000 + 7;
struct Data {
	int number; // ��վ��
	int year; // ��
	int month; // ��
	int day; // ��
	double water; // 20-20ʱ��ˮ��
	double Max; // ���������
	double Min; // ���������
	double aver; // ƽ������
};
//��������
//���    һ���Ը��£�35 �� - 38 �棩�� Σ���Ը��£�38 �� - 40 �棩��
//ǿΣ���Ը��£��� 40 �棩��   ����������£���̨վÿһ���ո������ֵ����
//��������  ����˳�������
struct Answer {
	int year; // ���
	int num1; // һ���Ը��£�35 �� - 38 �棩��
	int num2; // Σ���Ը��£�38 �� - 40 �棩��
	int num3; // ǿΣ���Ը��£��� 40 �棩��
	double Max; // ����������£���̨վÿһ���ո������ֵ����
	int day1; // ��������
	int day2; // ����˳�������
};

static int D[13] = { 0, 31, 0, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
static bool judge(int y) {
	return y % 400 == 0 || (y % 4 == 0 && y % 100);
}

static Data num[MAXN];
static Answer ans[MAXN];
static double rec[MAXN]; // �洢1961 - 1990������������¶�
static bool cmp(Data a, Data b) {
	if (a.year != b.year) {
		return a.year < b.year;
	}
	else {
		return a.month != b.month ? a.month < b.month : a.day < b.day;
	}
}

// ����һ���ļ�������
// ÿ��ʡ����һ���ļ���
// ÿ��ʡ�����������ļ���in �� out
// in�ļ�����������վ̨1961 - 2015�����������
// out�ļ�����������վ̨ÿ���Լ�1961 - 1990 �� 1991 - 2015�ľ�ֵ



/*
Ҫ��
InputPath -> ���������ļ���·��
OutputPath -> ��InputPath һ��
*/
class Work_Station {
public:
	void Work1(LPCSTR FullPathName, LPCSTR outputPath1) { // ÿ��վÿһ���ƽ������
		freopen(FullPathName, "r", stdin);
		freopen(outputPath1, "w", stdout);
		char str[1000];
		for (int i = 1; i <= 8; i++) {
			scanf("%s", str);
		}
		int N = 0; int M = 0;
		int res = 0;
		while (scanf("%d%d%d%d%lf%lf%lf%lf", &num[N].number, &num[N].year, &num[N].month, &num[N].day,
			&num[N].water, &num[N].Max, &num[N].Min, &num[N].aver) != EOF) {
			if (num[N].year >= 1961 && num[N].year <= 1990) {
				rec[M++] = num[N].Max;
			}
			N++;
		}
		//������������ û�а��������ϸ�����
		sort(num, num + N, cmp);

		//�ж�1961-2016������ȫ��ȫ
		int s = -1;
		for (int i = 0; i < N; i++) {
			if (num[i].year == 1961) {
				s = i; break;
			}
		}
		if (s == -1) {
			printf("���ݲ�ȫ\n");
			return;
		}
		bool flag = true;
		for (int i = 1961; i <= year; i++) {
			if (judge(i)) {
				D[2] = 29;
			}
			else {
				D[2] = 28;
			}
			for (int j = 1; j <= 12; j++) {
				for (int k = 1; k <= D[j]; k++) {
					if (s < N && num[s].year == i && num[s].month == j && num[s].day == k) {
						s++;
					}
					else {
						printf("%d %d %d\n", i, j, k);
						flag = false; break;
					}
				}
				if (!flag) break;
			}
			if (!flag) break;
		}
		if (num[N - 1].year == year && num[N - 1].month == 12 && num[N - 1].day == 31) {

		}
		else {
			flag = false;
		}
		if (!flag) {
			printf("���ݲ�ȫ\n");
			return;
		}

		// ����ȱ������
		for (int i = 0; i < N; i++) {
			if (num[i].Max >= 30000) {
				num[i].Max = 0;
			}
		}
		int j = 0; // ��1961�꿪ʼ
		for (int i = 0; i < N; i++) {
			if (num[i].year == 1961) {
				j = i; break;
			}
		}
		for (int i = 1961; i <= year; i++) {
			ans[i].year = i;
			ans[i].num1 = 0; ans[i].num2 = 0; ans[i].num3 = 0;
			ans[i].Max = -100000000;
			for (; j < N; j++) {
				if (num[j].year != i) break;

				ans[i].Max = max(ans[i].Max, num[j].Max); // ���ÿ�꼫���������

				if (num[j].Max >= 350 && num[j].Max < 380) {
					ans[i].num1++;
				} // ���һ���Ը��£�35 �� - 38 �棩��

				if (num[j].Max >= 380 && num[j].Max < 400) {
					ans[i].num2++;
				} // ���Σ���Ը��£�38 �� - 40 �棩��

				if (num[j].Max >= 400) {
					ans[i].num3++;
				} // ���ǿΣ���Ը��£��� 40 �棩��

			}
		}
		double mark = 320; // ���˵��ٽ��¶�ֵ
		//������˵��ٽ��¶�ֵ
		sort(rec, rec + M); // ��������
		//�ҵ�95�ٷ�λ �¶�ֵ
		if ((M * 95) % 100 == 0) {
			mark = max(mark, 1.0 * rec[(M * 95) / 100 - 1]);
		}
		else {
			int pos = (M * 95) / 100 - 1;
			mark = max(mark, 1.0 * (rec[pos] + rec[pos + 1]) / 2);
		} // ȡƽ��ֵ

		j = 0;
		for (int i = 0; i < N; i++) {
			if (num[i].year == 1961) {//��1961��
				j = i; break;
			}
		}
		for (int i = 1961; i <= year; i++) {
			ans[i].day1 = 0; ans[i].day2 = 0;
			int s = -1; // ��¼���˵���ʼ��
			for (; j < N; j++) {
				if (num[j].year != i) break;
				if (num[j].Max >= mark) {
					if (s == -1) { // δ�������
						s = j;
					}
				}
				else { // ����
					if (s != -1) { // �Ƿ�������
						int cnt = j - s; // ��������
						if (cnt >= 3) { // ��������
							ans[i].day1 += cnt;
							ans[i].day2 = max(ans[i].day2, cnt);
						}
					}
					s = -1;
				}
			}
			if (s != -1) {
				int cnt = j - s;
				if (cnt >= 3) {
					ans[i].day1 += cnt;
					ans[i].day2 = max(ans[i].day2, cnt);
				}
			}
		}
		printf("���    ");
		printf(" һ���Ը��£�35��-38�棩��    ");
		printf(" Σ���Ը��£�38��-40�棩��    ");
		printf("ǿΣ���Ը��£���40�棩��   ");
		printf(" ����������£���̨վÿһ���ո������ֵ����");
		printf("     ��������          ");
		printf(" ����˳�������\n");

		for (int i = 1961; i <= year; i++) {
			printf("%-1d                       ", ans[i].year);
			printf("%-1d                         ", ans[i].num1);
			printf("%-1d                         ", ans[i].num2);
			printf("  %-1d                         ", ans[i].num3);
			printf("     %-1.0lf                      ", ans[i].Max);
			printf("        %-1d                        ", ans[i].day1);
			printf("%-1d                         \n", ans[i].day2);
		}

		//1961 - 1990 ��ֵ
		printf("1961-1990��ֵ              ");
		double sum1 = 0, sum2 = 0, sum3 = 0, sum4 = 0, sum5 = 0, sum6 = 0;
		for (int i = 1961; i <= 1990; i++) {
			sum1 += ans[i].num1;
			sum2 += ans[i].num2;
			sum3 += ans[i].num3;
			sum4 += ans[i].Max;
			sum5 += ans[i].day1;
			sum6 += ans[i].day2;
		}
		printf("%-1.2lf                      ", sum1 / 30);
		printf("%-1.2lf                      ", sum2 / 30);
		printf("  %-1.2lf                      ", sum3 / 30);
		printf("     %-1.2lf                   ", sum4 / 30);
		printf("        %-1.2lf                      ", sum5 / 30);
		printf("%-1.2lf                       \n", sum6 / 30);

		//1991 - year ��ֵ
		printf("1991-%d��ֵ              ", year);
		sum1 = 0, sum2 = 0, sum3 = 0, sum4 = 0, sum5 = 0, sum6 = 0;
		for (int i = 1991; i <= year; i++) {
			sum1 += ans[i].num1;
			sum2 += ans[i].num2;
			sum3 += ans[i].num3;
			sum4 += ans[i].Max;
			sum5 += ans[i].day1;
			sum6 += ans[i].day2;
		}
		printf("%-1.2lf                      ", sum1 / (year - 1991 + 1));
		printf("%-1.2lf                      ", sum2 / (year - 1991 + 1));
		printf("  %-1.2lf                      ", sum3 / (year - 1991 + 1));
		printf("     %-1.2lf                   ", sum4 / (year - 1991 + 1));
		printf("        %-1.2lf                      ", sum5 / (year - 1991 + 1));
		printf("%-1.2lf                       \n", sum6 / (year - 1991 + 1));
	}
	BOOL DirectoryList(LPCSTR Path) {
		WIN32_FIND_DATA FindData;
		HANDLE hError;
		char FilePathName[LEN];
		// ����·��
		char FullPathName[LEN];
		strcpy(FilePathName, Path);
		strcat(FilePathName, "\\*.*");
		hError = FindFirstFile(FilePathName, &FindData);
		if (hError == INVALID_HANDLE_VALUE) {
			printf("����ʧ��!");
			return 0;
		}
		while (::FindNextFile(hError, &FindData)) {
			// ����.��..
			if (strcmp(FindData.cFileName, ".") == 0
				|| strcmp(FindData.cFileName, "..") == 0) {
				continue;
			}
			// ��������·��
			sprintf(FullPathName, "%s\\%s", Path, FindData.cFileName);

			bool Stop = false;

			int len = strlen(FullPathName);
			if (FullPathName[len - 1] != 't') {
				Stop = true;
			}
			if (!(FullPathName[len - 5] >= 0 && FullPathName[len - 5] <= '9')) {
				Stop = true;
			}
			if (FullPathName[len - 11] != 'n') {
				Stop = true;
			}
			if (!Stop) { // in/xxxxx.txt
				char outputPath1[LEN]; // Work1������ļ���·��
				strcpy(outputPath1, Path);
				int len = strlen(outputPath1);
				outputPath1[len] = 't';
				outputPath1[len - 1] = 'u';
				outputPath1[len - 2] = 'o';
				outputPath1[len + 1] = 0;
				strcat(outputPath1, "\\");
				strcat(outputPath1, FindData.cFileName);
				// cout << FullPathName << endl;
				// cout << outputPath1 << endl;
				Work1(FullPathName, outputPath1); // ͳ�����л�����Ϣ
			}
			if (FindData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
				DirectoryList(FullPathName);
			}
		}
		return 0;
	}
};

/*
ɸѡҪ��
InputPath -> �洢�������ݵ��ļ���·��
OutputPath -> Ҫ������ĵ�·������Ҫ�½�һ���ĵ���
*/
class Work_Total {
public:
	char outputPath2[LEN]; // ÿ��ʡ����ļ���·��
	void Work2_Init() { // ����Work2
		// ��� ��ֵ�������·��
		freopen(OutputPath, "a", stdout);
		printf("��վ��    ");
		printf("��һ�׶�   ");
		printf(" һ���Ը��£�35��-38�棩��    ");
		printf(" Σ���Ը��£�38��-40�棩��    ");
		printf("ǿΣ���Ը��£���40�棩��   ");
		printf(" ����������£���̨վÿһ���ո������ֵ����");
		printf("     ��������          ");
		printf(" ����˳�������        ");

		printf("�ڶ��׶�   ");
		printf(" һ���Ը��£�35��-38�棩��    ");
		printf(" Σ���Ը��£�38��-40�棩��    ");
		printf("ǿΣ���Ը��£���40�棩��   ");
		printf(" ����������£���̨վÿһ���ո������ֵ����");
		printf("     ��������          ");
		printf(" ����˳�������\n");
	}

	void Work2(LPCSTR FullPathName, char *s) {
		freopen(FullPathName, "r", stdin);
		freopen(OutputPath, "a", stdout);
		char ss[1000]; scanf("%s", ss);
		bool First = false;
		if (ss[0] >= '0' && ss[0] <= '9') {
			First = true;
		}
		for (int i = 2; i <= 7; i++) {
			scanf("%s", ss);
		}
		if (First) {
			for (int i = 1962; i <= year; i++) {
				for (int j = 1; j <= 7; j++) {
					scanf("%s", ss);
				}
			}
		}
		else {
			for (int i = 1961; i <= year; i++) {
				for (int j = 1; j <= 7; j++) {
					scanf("%s", ss);
				}
			}
		}
		printf("%s    ", s);
		for (int i = 1; i <= 2; i++) {
			for (int j = 1; j <= 7; j++) {
				scanf("%s", ss);
				printf("%s           ", ss);
			}
		}

		printf("\n");
	}
	BOOL DirectoryList(LPCSTR Path) {
		WIN32_FIND_DATA FindData;
		HANDLE hError;
		char FilePathName[LEN];
		// ����·��
		char FullPathName[LEN];
		strcpy(FilePathName, Path);
		strcat(FilePathName, "\\*.*");
		hError = FindFirstFile(FilePathName, &FindData);
		if (hError == INVALID_HANDLE_VALUE) {
			printf("����ʧ��!");
			return 0;
		}
		while (::FindNextFile(hError, &FindData)) {
			// ����.��..
			if (strcmp(FindData.cFileName, ".") == 0
				|| strcmp(FindData.cFileName, "..") == 0) {
				continue;
			}
			// ��������·��
			sprintf(FullPathName, "%s\\%s", Path, FindData.cFileName);

			bool Stop = false;

			int len = strlen(FullPathName);
			if (FullPathName[len - 1] != 't') {
				Stop = true;
			}
			if (!(FullPathName[len - 5] >= 0 && FullPathName[len - 5] <= '9')) {
				Stop = true;
			}
			if (FullPathName[len - 11] != 't') {
				Stop = true;
			}
			// �����վ��
			char number[1000];
			for (int i = 0; i <= 4; i++) {
				number[i] = FindData.cFileName[i];
			}
			number[5] = 0;

			if (!Stop) {
				//cout << FullPathName << endl;
				Work2(FullPathName, number); // ͳ�ƾ�ֵ
			}
			if (FindData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
				DirectoryList(FullPathName);
			}
		}
		return 0;
	}
};

/*
ɸѡҪ��
InputPath -> ��ǰʡ��ǰ�������վ̨���ݵ��ĵ�·��
OutputPath -> ��ǰʡ��in�ļ��е�·��
*/
class Work_Screen {
public:
	void Work3(LPCSTR Path, char *s) { // ɸѡ��վ��Ϊs��������ݵ�վ�����ݣ�·��ΪPath
		freopen(InputPath, "r", stdin); // �򿪸�ʡ�����������վ��������ļ�
		freopen(Path, "a", stdout); //���·����׷��
		char str[100];
		for (int i = 1; i <= 20; i++) {
			scanf("%s", str);
		}
		int val = 0;
		for (int i = 0; i < 5; i++) {
			val = val * 10 + s[i] - '0';
		}
		int a[30];
		while (scanf("%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d",
			&a[1], &a[2], &a[3], &a[4], &a[5], &a[6], &a[7], &a[8], &a[9], &a[10],
			&a[11], &a[12], &a[13], &a[14], &a[15], &a[16], &a[17], &a[18], &a[19], &a[20]) != EOF) {
			if (a[1] == val) {
				printf("%d %d %d %d %d %d %d\n", a[1], a[2], a[3], a[4], a[20], a[15], a[16], a[14]);
			}
		}
	}
	BOOL DirectoryList(LPCSTR Path) {
		WIN32_FIND_DATA FindData;
		HANDLE hError;
		char FilePathName[LEN];
		// ����·��
		char FullPathName[LEN];
		strcpy(FilePathName, Path);
		strcat(FilePathName, "\\*.*");
		hError = FindFirstFile(FilePathName, &FindData);
		if (hError == INVALID_HANDLE_VALUE) {
			printf("����ʧ��!");
			return 0;
		}
		while (::FindNextFile(hError, &FindData)) {
			// ����.��..
			if (strcmp(FindData.cFileName, ".") == 0
				|| strcmp(FindData.cFileName, "..") == 0) {
				continue;
			}
			// ��������·��
			sprintf(FullPathName, "%s\\%s", Path, FindData.cFileName);
			// �����վ��
			char number[1000];
			for (int i = 0; i <= 4; i++) {
				number[i] = FindData.cFileName[i];
			}
			number[5] = 0;
			Work3(FullPathName, number); // ɸѡ��վ��Ϊnumber��·��ΪFullPathName������
			if (FindData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
				DirectoryList(FullPathName);
			}
		}
		return 0;
	}
};

// ���������ݵ�ʱ��
// ��������
// һ�� �Ȱ�������վÿ���ƽ�����ݴ浽һ���ĵ�����
// ���� �ٶ����ĵ�����һ�δ�����

// ���ڵ�һ����
// InputPath -> �洢���ݵ����ļ���
// OutputPath -> Ҫ������ĵ�·��
class Work_First {
public:
	void Work4(LPCSTR FullPathName, char *s) {
		freopen(FullPathName, "r", stdin);
		freopen(OutputPath, "a", stdout);
		char ss[1000]; scanf("%s", ss);
		bool First = false;
		if (ss[0] >= '0' && ss[0] <= '9') {
			First = true;
		}
		if (First) {
			printf("%s", ss);
			for (int i = 2; i <= 7; i++) {
				scanf("%s", ss);
				printf(" %s", ss);
			}
			printf("\n");

			for (int i = 1962; i <= year; i++) {
				scanf("%s", ss);
				printf("%s", ss);
				for (int j = 2; j <= 7; j++) {
					scanf("%s", ss);
					printf(" %s", ss);
				}
				printf("\n");
			}
		}
		else {
			for (int i = 2; i <= 7; i++) {
				scanf("%s", ss);
			}
			for (int i = 1961; i <= year; i++) {
				scanf("%s", ss);
				printf("%s", ss);
				for (int j = 2; j <= 7; j++) {
					scanf("%s", ss);
					printf(" %s", ss);
				}
				printf("\n");
			}
		}
		scanf("%s", ss); printf("%d", 0);
		for (int j = 2; j <= 7; j++) {
			scanf("%s", ss);
			printf(" %s", ss);
		}
		printf("\n");
		
		scanf("%s", ss); printf("%d", 1);
		for (int j = 2; j <= 7; j++) {
			scanf("%s", ss);
			printf(" %s", ss);
		}
		printf("\n");
	}
	BOOL DirectoryList(LPCSTR Path) {
		WIN32_FIND_DATA FindData;
		HANDLE hError;
		char FilePathName[LEN];
		// ����·��
		char FullPathName[LEN];
		strcpy(FilePathName, Path);
		strcat(FilePathName, "\\*.*");
		hError = FindFirstFile(FilePathName, &FindData);
		if (hError == INVALID_HANDLE_VALUE) {
			printf("����ʧ��!");
			return 0;
		}
		while (::FindNextFile(hError, &FindData)) {
			// ����.��..
			if (strcmp(FindData.cFileName, ".") == 0
				|| strcmp(FindData.cFileName, "..") == 0) {
				continue;
			}
			// ��������·��
			sprintf(FullPathName, "%s\\%s", Path, FindData.cFileName);

			bool Stop = false;

			int len = strlen(FullPathName);
			if (FullPathName[len - 1] != 't') {
				Stop = true;
			}
			if (!(FullPathName[len - 5] >= 0 && FullPathName[len - 5] <= '9')) {
				Stop = true;
			}
			if (FullPathName[len - 11] != 't') {
				Stop = true;
			}
			if (!Stop) {
				Work4(FullPathName, OutputPath);
			}
			if (FindData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
				DirectoryList(FullPathName);
			}
		}
		return 0;
	}
};

class Work_Second {
public:
	double Total[4001][7];
	void Last() {
		freopen(InputPath, "r", stdin);
		freopen(OutputPath, "w", stdout);
		double a, b, c, d, e, f, g;
		memset(Total, 0, sizeof(Total));
		int cnt = 0;
		while (scanf("%lf%lf%lf%lf%lf%lf%lf", &a, &b, &c, &d, &e, &f, &g) != EOF) {
			Total[(int)a][1] += b;
			Total[(int)a][2] += c;
			Total[(int)a][3] += d;
			Total[(int)a][4] += e;
			Total[(int)a][5] += f;
			Total[(int)a][6] += g;
			if (a == 1961) {
				cnt++;
			}
		}
		for (int i = 1961; i <= year; i++) {
			printf("%d", i);
			for (int j = 1; j <= 6; j++) {
				printf(" %.2lf", Total[i][j] / cnt);
			}
			printf("\n");
		}

		printf("1961-1990 ");
		for (int i = 1; i <= 6; i++) {
			printf(" %.2lf", Total[0][i] / cnt);
		}
		printf("\n");

		printf("1991-%d ", year);
		for (int i = 1; i <= 6; i++) {
			printf(" %.2lf", Total[1][i] / cnt);
		}
		printf("\n");
	}
};


// ��ʾ������ʾ״̬�� ��������
class Show_State { 
public:
	void drawString(const char* str) {
		static int isFirstCall = 1;
		static GLuint lists;
		if (isFirstCall)
		{ // ����ǵ�һ�ε��ã�ִ�г�ʼ��
			// Ϊÿһ��ASCII�ַ�����һ����ʾ�б�
			isFirstCall = 0;
			// ����MAX_CHAR����������ʾ�б���
			lists = glGenLists(MAX_CHAR);
			// ��ÿ���ַ��Ļ������װ����Ӧ����ʾ�б���
			wglUseFontBitmaps(wglGetCurrentDC(), 0, MAX_CHAR, lists);
		}
		// ����ÿ���ַ���Ӧ����ʾ�б�����ÿ���ַ�
		for (; *str != '\0'; ++str) {
			glCallList(lists + *str);
		}
	}

	void drawCNString(const char* str) {
		int len, i;
		wchar_t* wstring;
		HDC hDC = wglGetCurrentDC();
		GLuint list = glGenLists(1);
		// �����ַ��ĸ���
		// �����˫�ֽ��ַ��ģ����������ַ����������ֽڲ���һ���ַ�
		// ����һ���ֽ���һ���ַ�
		len = 0;
		for (i = 0; str[i] != '\0'; ++i) {
			if (IsDBCSLeadByte(str[i])) {
				++i;
			}
			++len;
		}

		// ������ַ�ת��Ϊ���ַ�
		wstring = (wchar_t*)malloc((len + 1) * sizeof(wchar_t));
		MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, str, -1, wstring, len);
		wstring[len] = L'\0';

		// �������ַ�
		for (i = 0; i<len; ++i) {
			wglUseFontBitmapsW(hDC, wstring[i], 1, list);
			glCallList(list);
		}

		// ����������ʱ��Դ
		free(wstring);
		glDeleteLists(list, 1);
	}

	void selectFont(int size, int charset, const char* face) {
		HFONT hFont = CreateFontA(size, 0, 0, 0, FW_MEDIUM, 0, 0, 0,
			charset, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
			DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, face);
		HFONT hOldFont = (HFONT)SelectObject(wglGetCurrentDC(), hFont);
		DeleteObject(hOldFont);
	}

	void Display(int op) {
		glClear(GL_COLOR_BUFFER_BIT);

		/*selectFont(48, ANSI_CHARSET, "Comic Sans MS");
		glColor3f(1.0f, 0.0f, 0.0f);
		glRasterPos2f(-0.7f, 0.4f);
		drawString("Hello, World!");*/

		/* selectFont(48, GB2312_CHARSET, "��������");
		glColor3f(1.0f, 1.0f, 0.0f);
		glRasterPos2f(cx / 2, cy / 2);
		drawCNString(""); */

		/* selectFont(48, GB2312_CHARSET, "����_GB2312");
		//selectFont(48, DEFAULT_CHARSET, "���ķ���");
		glColor3f(0.0f, 1.0f, 0.0f);
		glRasterPos2f(-0.7f, 0.0f);
		drawCNString("���y���Ї��h��"); */

		if (op == 1) {
			selectFont(80, GB2312_CHARSET, "�����п�");
			//selectFont(48, DEFAULT_CHARSET, "���ķ���");
			glColor3f(0.0f, 1.0f, 1.0f);
			glRasterPos2f(3.9, 5);
			drawCNString("��ӭʹ�ã�");
		}
		else if (op == 2) {
			// selectFont(60, GB2312_CHARSET, "����_GB2312");
			selectFont(80, DEFAULT_CHARSET, "���ķ���");
			glColor3f(1.0f, 1.0f, 0.0f);
			glRasterPos2f(3.6, 5);
			drawCNString("����ִ����...");
		}
		else {
			selectFont(80, GB2312_CHARSET, "���ķ���");
			glColor3f(0.0f, 1.0f, 0.0f);
			glRasterPos2f(3.9, 5);
			drawCNString("ִ����ϣ�"); 
		}
	}
};