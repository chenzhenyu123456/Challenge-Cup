
// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件

#pragma once

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // 从 Windows 头中排除极少使用的资料
#endif

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // 某些 CString 构造函数将是显式的

// 关闭 MFC 对某些常见但经常可放心忽略的警告消息的隐藏
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC 核心组件和标准组件
#include <afxext.h>         // MFC 扩展


#include <afxdisp.h>        // MFC 自动化类

#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // MFC 对 Internet Explorer 4 公共控件的支持
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>             // MFC 对 Windows 公共控件的支持
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxcontrolbars.h>     // 功能区和控件条的 MFC 支持









#ifdef _UNICODE
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
#endif


extern char InputPath[MAX_PATH];     //存放读入的目录路径   
extern char OutputPath[MAX_PATH];     //存放输出的目录路径

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
	int number; // 区站号
	int year; // 年
	int month; // 月
	int day; // 日
	double water; // 20-20时降水量
	double Max; // 日最高气温
	double Min; // 日最低气温
	double aver; // 平均气温
};
//输出结果：
//年份    一般性高温（35 ℃ - 38 ℃）天 危害性高温（38 ℃ - 40 ℃）天
//强危害性高温（≥ 40 ℃）天   极端最高气温（各台站每一年日高温最大值）℃
//热浪日数  最长热浪持续日数
struct Answer {
	int year; // 年份
	int num1; // 一般性高温（35 ℃ - 38 ℃）天
	int num2; // 危害性高温（38 ℃ - 40 ℃）天
	int num3; // 强危害性高温（≥ 40 ℃）天
	double Max; // 极端最高气温（各台站每一年日高温最大值）℃
	int day1; // 热浪日数
	int day2; // 最长热浪持续日数
};

static int D[13] = { 0, 31, 0, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
static bool judge(int y) {
	return y % 400 == 0 || (y % 4 == 0 && y % 100);
}

static Data num[MAXN];
static Answer ans[MAXN];
static double rec[MAXN]; // 存储1961 - 1990的所有日最高温度
static bool cmp(Data a, Data b) {
	if (a.year != b.year) {
		return a.year < b.year;
	}
	else {
		return a.month != b.month ? a.month < b.month : a.day < b.day;
	}
}

// 放入一个文件夹里面
// 每个省单独一个文件夹
// 每个省下面有两个文件夹in 和 out
// in文件夹里面存的是站台1961 - 2015年的所有数据
// out文件夹里面存的是站台每年以及1961 - 1990 和 1991 - 2015的均值



/*
要求：
InputPath -> 所有数据文件夹路径
OutputPath -> 和InputPath 一样
*/
class Work_Station {
public:
	void Work1(LPCSTR FullPathName, LPCSTR outputPath1) { // 每个站每一年的平均数据
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
		//如果输入的数据 没有按年月日严格排列
		sort(num, num + N, cmp);

		//判断1961-2016的数据全不全
		int s = -1;
		for (int i = 0; i < N; i++) {
			if (num[i].year == 1961) {
				s = i; break;
			}
		}
		if (s == -1) {
			printf("数据不全\n");
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
			printf("数据不全\n");
			return;
		}

		// 处理缺测数据
		for (int i = 0; i < N; i++) {
			if (num[i].Max >= 30000) {
				num[i].Max = 0;
			}
		}
		int j = 0; // 从1961年开始
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

				ans[i].Max = max(ans[i].Max, num[j].Max); // 求解每年极端最高气温

				if (num[j].Max >= 350 && num[j].Max < 380) {
					ans[i].num1++;
				} // 求解一般性高温（35 ℃ - 38 ℃）天

				if (num[j].Max >= 380 && num[j].Max < 400) {
					ans[i].num2++;
				} // 求解危害性高温（38 ℃ - 40 ℃）天

				if (num[j].Max >= 400) {
					ans[i].num3++;
				} // 求解强危害性高温（≥ 40 ℃）天

			}
		}
		double mark = 320; // 热浪的临界温度值
		//求解热浪的临界温度值
		sort(rec, rec + M); // 升序排列
		//找第95百分位 温度值
		if ((M * 95) % 100 == 0) {
			mark = max(mark, 1.0 * rec[(M * 95) / 100 - 1]);
		}
		else {
			int pos = (M * 95) / 100 - 1;
			mark = max(mark, 1.0 * (rec[pos] + rec[pos + 1]) / 2);
		} // 取平均值

		j = 0;
		for (int i = 0; i < N; i++) {
			if (num[i].year == 1961) {//从1961年
				j = i; break;
			}
		}
		for (int i = 1961; i <= year; i++) {
			ans[i].day1 = 0; ans[i].day2 = 0;
			int s = -1; // 记录热浪的起始点
			for (; j < N; j++) {
				if (num[j].year != i) break;
				if (num[j].Max >= mark) {
					if (s == -1) { // 未设置起点
						s = j;
					}
				}
				else { // 断了
					if (s != -1) { // 是否存在起点
						int cnt = j - s; // 持续天数
						if (cnt >= 3) { // 超过三天
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
		printf("年份    ");
		printf(" 一般性高温（35℃-38℃）天    ");
		printf(" 危害性高温（38℃-40℃）天    ");
		printf("强危害性高温（≥40℃）天   ");
		printf(" 极端最高气温（各台站每一年日高温最大值）℃");
		printf("     热浪日数          ");
		printf(" 最长热浪持续日数\n");

		for (int i = 1961; i <= year; i++) {
			printf("%-1d                       ", ans[i].year);
			printf("%-1d                         ", ans[i].num1);
			printf("%-1d                         ", ans[i].num2);
			printf("  %-1d                         ", ans[i].num3);
			printf("     %-1.0lf                      ", ans[i].Max);
			printf("        %-1d                        ", ans[i].day1);
			printf("%-1d                         \n", ans[i].day2);
		}

		//1961 - 1990 均值
		printf("1961-1990均值              ");
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

		//1991 - year 均值
		printf("1991-%d均值              ", year);
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
		// 构造路径
		char FullPathName[LEN];
		strcpy(FilePathName, Path);
		strcat(FilePathName, "\\*.*");
		hError = FindFirstFile(FilePathName, &FindData);
		if (hError == INVALID_HANDLE_VALUE) {
			printf("搜索失败!");
			return 0;
		}
		while (::FindNextFile(hError, &FindData)) {
			// 过虑.和..
			if (strcmp(FindData.cFileName, ".") == 0
				|| strcmp(FindData.cFileName, "..") == 0) {
				continue;
			}
			// 构造完整路径
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
				char outputPath1[LEN]; // Work1中输出文件的路径
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
				Work1(FullPathName, outputPath1); // 统计所有基础信息
			}
			if (FindData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
				DirectoryList(FullPathName);
			}
		}
		return 0;
	}
};

/*
筛选要求：
InputPath -> 存储所有数据的文件夹路径
OutputPath -> 要输出的文档路径（需要新建一个文档）
*/
class Work_Total {
public:
	char outputPath2[LEN]; // 每个省输出文件的路径
	void Work2_Init() { // 用于Work2
		// 求出 均值数据输出路径
		freopen(OutputPath, "a", stdout);
		printf("区站号    ");
		printf("第一阶段   ");
		printf(" 一般性高温（35℃-38℃）天    ");
		printf(" 危害性高温（38℃-40℃）天    ");
		printf("强危害性高温（≥40℃）天   ");
		printf(" 极端最高气温（各台站每一年日高温最大值）℃");
		printf("     热浪日数          ");
		printf(" 最长热浪持续日数        ");

		printf("第二阶段   ");
		printf(" 一般性高温（35℃-38℃）天    ");
		printf(" 危害性高温（38℃-40℃）天    ");
		printf("强危害性高温（≥40℃）天   ");
		printf(" 极端最高气温（各台站每一年日高温最大值）℃");
		printf("     热浪日数          ");
		printf(" 最长热浪持续日数\n");
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
		// 构造路径
		char FullPathName[LEN];
		strcpy(FilePathName, Path);
		strcat(FilePathName, "\\*.*");
		hError = FindFirstFile(FilePathName, &FindData);
		if (hError == INVALID_HANDLE_VALUE) {
			printf("搜索失败!");
			return 0;
		}
		while (::FindNextFile(hError, &FindData)) {
			// 过虑.和..
			if (strcmp(FindData.cFileName, ".") == 0
				|| strcmp(FindData.cFileName, "..") == 0) {
				continue;
			}
			// 构造完整路径
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
			// 求出区站号
			char number[1000];
			for (int i = 0; i <= 4; i++) {
				number[i] = FindData.cFileName[i];
			}
			number[5] = 0;

			if (!Stop) {
				//cout << FullPathName << endl;
				Work2(FullPathName, number); // 统计均值
			}
			if (FindData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
				DirectoryList(FullPathName);
			}
		}
		return 0;
	}
};

/*
筛选要求：
InputPath -> 当前省当前年份所有站台数据的文档路径
OutputPath -> 当前省的in文件夹的路径
*/
class Work_Screen {
public:
	void Work3(LPCSTR Path, char *s) { // 筛选区站号为s的最新年份的站点数据，路径为Path
		freopen(InputPath, "r", stdin); // 打开该省最新年份所有站点的数据文件
		freopen(Path, "a", stdout); //输出路径　追加
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
		// 构造路径
		char FullPathName[LEN];
		strcpy(FilePathName, Path);
		strcat(FilePathName, "\\*.*");
		hError = FindFirstFile(FilePathName, &FindData);
		if (hError == INVALID_HANDLE_VALUE) {
			printf("搜索失败!");
			return 0;
		}
		while (::FindNextFile(hError, &FindData)) {
			// 过虑.和..
			if (strcmp(FindData.cFileName, ".") == 0
				|| strcmp(FindData.cFileName, "..") == 0) {
				continue;
			}
			// 构造完整路径
			sprintf(FullPathName, "%s\\%s", Path, FindData.cFileName);
			// 求出区站号
			char number[1000];
			for (int i = 0; i <= 4; i++) {
				number[i] = FindData.cFileName[i];
			}
			number[5] = 0;
			Work3(FullPathName, number); // 筛选区站号为number且路径为FullPathName的数据
			if (FindData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
				DirectoryList(FullPathName);
			}
		}
		return 0;
	}
};

// 求出年均数据的时候
// 分两步：
// 一、 先把所有区站每年的平均数据存到一个文档里面
// 二、 再对新文档进行一次处理即可

// 对于第一步：
// InputPath -> 存储数据的总文件夹
// OutputPath -> 要输出的文档路径
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
		// 构造路径
		char FullPathName[LEN];
		strcpy(FilePathName, Path);
		strcat(FilePathName, "\\*.*");
		hError = FindFirstFile(FilePathName, &FindData);
		if (hError == INVALID_HANDLE_VALUE) {
			printf("搜索失败!");
			return 0;
		}
		while (::FindNextFile(hError, &FindData)) {
			// 过虑.和..
			if (strcmp(FindData.cFileName, ".") == 0
				|| strcmp(FindData.cFileName, "..") == 0) {
				continue;
			}
			// 构造完整路径
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


// 显示用来表示状态的 各种字体
class Show_State { 
public:
	void drawString(const char* str) {
		static int isFirstCall = 1;
		static GLuint lists;
		if (isFirstCall)
		{ // 如果是第一次调用，执行初始化
			// 为每一个ASCII字符产生一个显示列表
			isFirstCall = 0;
			// 申请MAX_CHAR个连续的显示列表编号
			lists = glGenLists(MAX_CHAR);
			// 把每个字符的绘制命令都装到对应的显示列表中
			wglUseFontBitmaps(wglGetCurrentDC(), 0, MAX_CHAR, lists);
		}
		// 调用每个字符对应的显示列表，绘制每个字符
		for (; *str != '\0'; ++str) {
			glCallList(lists + *str);
		}
	}

	void drawCNString(const char* str) {
		int len, i;
		wchar_t* wstring;
		HDC hDC = wglGetCurrentDC();
		GLuint list = glGenLists(1);
		// 计算字符的个数
		// 如果是双字节字符的（比如中文字符），两个字节才算一个字符
		// 否则一个字节算一个字符
		len = 0;
		for (i = 0; str[i] != '\0'; ++i) {
			if (IsDBCSLeadByte(str[i])) {
				++i;
			}
			++len;
		}

		// 将混合字符转化为宽字符
		wstring = (wchar_t*)malloc((len + 1) * sizeof(wchar_t));
		MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, str, -1, wstring, len);
		wstring[len] = L'\0';

		// 逐个输出字符
		for (i = 0; i<len; ++i) {
			wglUseFontBitmapsW(hDC, wstring[i], 1, list);
			glCallList(list);
		}

		// 回收所有临时资源
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

		/* selectFont(48, GB2312_CHARSET, "华文中宋");
		glColor3f(1.0f, 1.0f, 0.0f);
		glRasterPos2f(cx / 2, cy / 2);
		drawCNString(""); */

		/* selectFont(48, GB2312_CHARSET, "黑体_GB2312");
		//selectFont(48, DEFAULT_CHARSET, "华文仿宋");
		glColor3f(0.0f, 1.0f, 0.0f);
		glRasterPos2f(-0.7f, 0.0f);
		drawCNString("傳統的中國漢字"); */

		if (op == 1) {
			selectFont(80, GB2312_CHARSET, "华文行楷");
			//selectFont(48, DEFAULT_CHARSET, "华文仿宋");
			glColor3f(0.0f, 1.0f, 1.0f);
			glRasterPos2f(3.9, 5);
			drawCNString("欢迎使用！");
		}
		else if (op == 2) {
			// selectFont(60, GB2312_CHARSET, "黑体_GB2312");
			selectFont(80, DEFAULT_CHARSET, "华文仿宋");
			glColor3f(1.0f, 1.0f, 0.0f);
			glRasterPos2f(3.6, 5);
			drawCNString("程序执行中...");
		}
		else {
			selectFont(80, GB2312_CHARSET, "华文仿宋");
			glColor3f(0.0f, 1.0f, 0.0f);
			glRasterPos2f(3.9, 5);
			drawCNString("执行完毕！"); 
		}
	}
};