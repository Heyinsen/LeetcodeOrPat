#pragma warning(disable:4996)
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
using namespace std;
const int maxm = 15;
const int maxlength = 65;
char str[maxm][maxlength];

//返回的s, 子串的长度, 第一个字符串的位置
void getNextSubStr(char* s, int len, int pos) {
	for (int i = pos; i < pos + len; i++) {
		s[i - pos] = str[0][i];
	}
	s[pos + len] = '\0';
}

//求next数组
void getNext(char* s, int len, int* next) {
	int i = 0, j;
	j = next[0] = -1;
	while (i < len) {
		if (j == -1 || s[i] == s[j]) {
			next[++i] = ++j;
		}
		else {
			j = next[j];
		}
	}
}

int kmp(char* s, int lens, char* p, int lenp, int *next) {
	int i = 0, j = 0;
	while (i < lens && j < lenp) {
		if (j == -1 || s[i] == p[j]) {
			i++;
			j++;
		}
		else {
			j = next[j];
		}
	}
	if (j == lenp) {
		return i - j;
	}
	else {
		return -1;
	}
}

int main() {
	int n;
	cin >> n;
	while (n--) {
		int m;
		scanf("%d", &m);
		for (int i = 0; i < m; i++) {
			scanf("%s", str[i]);
		}
		int ans = 0;
		char ans_str[maxlength];
		ans_str[0] = '\0';
		//暴力枚举第一个字符串所有的子串, T(n+ n-1 + n-2 + n-3 ...+ 1 == n^2)
		//KMP匹配的模式字符串和其next数组
		char s[maxlength];
		int next[maxlength];
		for (int len = 1; len <= 60; len++) {
			//判断是否所有的该长度的字符串都匹配失败, 如果是, 那么找不到更长的可以匹配的字符串了, 结束判断
			bool f = true;
			for (int pos = 0; pos < 60 - len + 1; pos++) {
				getNextSubStr(s, len, pos);
				getNext(s, len, next);
				//这个子串是否在所有的字符串中匹配成功
				bool flag = true;
				for (int i = 1; i < m; i++) {
					if (kmp(str[i], 60, s, len, next) == -1) {
						flag = false;//有一个字符串没有匹配成功.
						break;
					}
				}
				if (flag == true) {
					f = false;
				}
				//如果这个字符串匹配成功了, 更新ans
				if (flag == true) {
					//ans必然小于等于len, 所以只有if和else
					if (ans == len) {
						//选择字典序较小的
						if (strcmp(ans_str, s) > 0) {
							strcpy(ans_str, s);
						}
					}
					//ans小于len
					else {
						ans = len;
						strcpy(ans_str, s);
					}
				}
			}
			if (f == true) {
				break;
			}
		}

		if (ans < 3) {
			cout << "no significant commonalities\n";
		}
		else {
			printf("%s\n", ans_str);
		}
	}
	return 0;
}
/*
3
2
GATACCAGATACCAGATACCAGATACCAGATACCAGATACCAGATACCAGATACCAGATA
AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
3
GATACCAGATACCAGATACCAGATACCAGATACCAGATACCAGATACCAGATACCAGATA
GATACTAGATACTAGATACTAGATACTAAAGGAAAGGGAAAAGGGGAAAAAGGGGGAAAA
GATACCAGATACCAGATACCAGATACCAAAGGAAAGGGAAAAGGGGAAAAAGGGGGAAAA
3
CATCATCATCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC
ACATCATCATAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
AACATCATCATTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT
*/
