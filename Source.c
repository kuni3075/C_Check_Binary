#pragma warning(disable: 4996)
#include <stdio.h>
#include <time.h>

#define DATA_NUM 4

char GlobalBuf[100] = { 0 };
int ContinueFlag = 10;

/*�t�@�C�����̓ǂݍ���*/
void GetFileName(char s[], int lim) {
	int c, i;

	for (i = 0; i < lim - 1 && (c = getchar()) != '\n'; ++i) {
		s[i] = c;
	}
	s[i] = '\0';
}

/*�o�C�i���̃e�X�g�t�@�C���쐬*/
int Make_Test_Binary(void) {

	int i = 0;
	char buf1[DATA_NUM] = { 255,2,3,4 };
	int buf2[DATA_NUM] = { 0 };
	FILE *file;

	/*�t�@�C���I�[�v��*/
	file = fopen("test.dat", "wb");
	if (file == NULL) {
		printf("�t�@�C���I�[�v���Ɏ��s\n");
		return -1;
	}
	else {
		printf("�t�@�C���I�[�v������\n");
	}

	/*�e�X�g�f�[�^�쐬*/
	for (i = 0; i < DATA_NUM; i++)
	{
		fwrite(&buf1[i], 1, 2, file);
	}

	fclose(file);
	return 0;
}

/*�o�C�i���t�@�C���̓ǂݍ���&�\��*/
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
		/*�t�@�C���I�[�v��*/
		printf("�o�C�i���t�@�C�����h���b�O&�h���b�v����Enter\n\n");
		GetFileName(FileName, 1000);
		fp = fopen(FileName, "rb");
		if (fp == NULL) {
			printf("\n�t�@�C���I�[�v���Ɏ��s\n");
			printf("�C�ӂ̃L�[�ŏI��");
			getchar();
			return -1;
		}
		else {
			printf("\n�t�@�C���I�[�v������\n\n");
		}

		printf("Read_A       = ");
		Read_Binary(fp, 0x3AC3, 4);
		printf("\n");

		printf("\n���̃t�@�C����ǂݍ��݂܂����H�@Enter -> Yes, �C�ӂ̃L�[+Enter -> �I��\n\n");
		ContinueFlag = getchar();
	}

	fclose(fp);
	return 0;
}