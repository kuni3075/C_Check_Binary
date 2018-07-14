#pragma warning(disable: 4996)
#include <stdio.h>
#include <time.h>

#define DATA_NUM 4

char GlobalBuf[100] = { 0 };
int ContinueFlag = 10;

/*ファイル名の読み込み*/
void GetFileName(char s[], int lim) {
	int c, i;

	for (i = 0; i < lim - 1 && (c = getchar()) != '\n'; ++i) {
		s[i] = c;
	}
	s[i] = '\0';
}

/*バイナリのテストファイル作成*/
int Make_Test_Binary(void) {

	int i = 0;
	char buf1[DATA_NUM] = { 255,2,3,4 };
	int buf2[DATA_NUM] = { 0 };
	FILE *file;

	/*ファイルオープン*/
	file = fopen("test.dat", "wb");
	if (file == NULL) {
		printf("ファイルオープンに失敗\n");
		return -1;
	}
	else {
		printf("ファイルオープン成功\n");
	}

	/*テストデータ作成*/
	for (i = 0; i < DATA_NUM; i++)
	{
		fwrite(&buf1[i], 1, 2, file);
	}

	fclose(file);
	return 0;
}

/*バイナリファイルの読み込み&表示*/
void Read_Binary(FILE *fp, int DataAdd, int ByteNum) {
	int i = 0;
	unsigned char buf[100] = { 0 };

	for (i = 0; i < ByteNum; i++)
	{
		fseek(fp, DataAdd - i, SEEK_SET);
		fread(&buf[i], 1, 1, fp);
		printf("%02X", buf[i]);
		GlobalBuf[i] = buf[i];
	}
	
}

int main(void)
{
	char FileName[1000];
	char test01[10] = { 0 };
	FILE *fp = NULL;
	struct tm StandardTime;


	while (ContinueFlag == 10) {
		/*ファイルオープン*/
		printf("バイナリファイルをドラッグ&ドロップしてEnter\n\n");
		GetFileName(FileName, 1000);
		fp = fopen(FileName, "rb");
		if (fp == NULL) {
			printf("\nファイルオープンに失敗\n");
			printf("任意のキーで終了");
			getchar();
			return -1;
		}
		else {
			printf("\nファイルオープン成功\n\n");
		}

		printf("Read_A       = ");
		Read_Binary(fp, 0x3AC3, 4);
		printf("\n");

		printf("\n次のファイルを読み込みますか？　Enter -> Yes, 任意のキー+Enter -> 終了\n\n");
		ContinueFlag = getchar();	/* Enter -> 10 */
	}

	fclose(fp);
	return 0;
}
