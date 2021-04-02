/*
 * 求next数组
 */
void getNext(char *s, int len, int *next){
   int i=0,j=next[0]=-1;
   while(i<len){
      if(j==-1||s[i]==s[j]){
         next[++i]=++j;
      }
      else{
         j=next[j];
      }
   }
}

/*
 * kmp 
 * 如果匹配成功, 返回匹配成功的第一个位置
 * 如果匹配失败, 返回-1
 */
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

