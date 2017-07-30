#pragma comment(lib, "Ws2_32.lib")
#include"parserCustom.h"
#include <stdlib.h>
#include <iconv.h>
#define lectureSize 17
lectureInfo lectureTable[lectureSize];

int main() {
	system("chcp 65001");
	xmlDocPtr doc;
	xmlNodePtr cur;
	xmlNodePtr savePoint1;
	xmlNodePtr savePoint2;
	xmlChar* key;
	FILE* pFile;
	char idnum[8];
	char* nameString;
	int atoiCustomStore;
	int i;
	int keyLength = 0;
	doc = xmlParseFile("dummy.xml");
	if (doc == NULL) {
		printf("Document not parsed successfully. \n");
		return 0;
	}

	cur = xmlDocGetRootElement(doc);

	if (cur == NULL) {
		printf("empty document\n");
		xmlFreeDoc(doc);
		return 0;
	}

	if (strcmp((char*)cur->name, "root")) {
		printf("document of the wrong type, root node != root \n");
		xmlFreeDoc(doc);
		return 0;
	}

	int ret;
	iconv_t it;
	it = iconv_open("EUC-KR", "UTF-8");
	
	size_t in_size, out_size;
	char euc_buf[50];
	char euc_buf2[50];
	char* input_buf_ptr;
	char* output_buf_ptr;

	pFile = fopen("lecture_info.ini", "w");

	cur = cur->children;
	i = 0;
	while (cur != NULL) { //cur : text major text core -> ...
		savePoint1 = cur;
		if (!strcmp((char*)cur->name, "major") ||
			!strcmp((char*)cur->name, "selective") ||
			!strcmp((char*)cur->name, "core")) {

			lectureTable[i].classify = getClassifyMessage((char*)cur->name);
			cur = cur->children;
			while (cur != NULL) { //cur : text code text class ...
				savePoint2 = cur;
				nameString = (char*)cur->name;
				if (getElementMessage(nameString) != XML_MESSAGE_DEFAULT) {
					cur = cur->children;
					key = xmlNodeListGetString(doc, cur, 1);
					keyLength = strlen((char*)key);
					switch (getElementMessage(nameString)) {
					case CODE:
						strcpy_s(lectureTable[i].identifyNumber, sizeof(lectureTable[i].identifyNumber), (char*)key);
						break;
					case CLASS:
						lectureTable[i].classNumber = atoiCustom((char*)key, 0);
						break;
					case TYPE:
						break;
					case NAME:
						strcpy_s(lectureTable[i].name, sizeof(lectureTable[i].name), (char*)key);
						break;
					case CREDIT:
						lectureTable[i].credit = atoiCustom((char*)key, 0);
						break;
					case TIME:
						strcpy_s(lectureTable[i].timeString, sizeof(lectureTable[i].timeString), (char*)key);
						lectureTable[i].lectureTime = registerTimeList((char*)key);
						break;
					case ROOM:
						lectureTable[i].room = getRoomMessage((char*)key);
						break;
					case DISTANCE:
						lectureTable[i].distance = atoiCustom((char*)key, 1);
						break;
					case KLUE:
						lectureTable[i].klueRating = getKlueMessage((char*)key);
						break;
					case XML_MESSAGE_DEFAULT:
						break;
					default:
						break;
					}
					xmlFree(key);
				}
				cur = savePoint2;
				cur = cur->next;
			}
			i++;
		}
		cur = savePoint1;
		cur = cur->next;
	}
	for (int i = 0; i < 17; i++) {
		printf("%s \n", lectureTable[i].identifyNumber);
		printf("%d \n", lectureTable[i].classNumber);
		switch (lectureTable[i].classify)
		{
		case CORE:
			printf("%s \n", u8"�ٽɱ���");
			break;
		case MAJOR:
			printf("%s \n", u8"���ʱ���");
			break;
		case SELECTIVE:
			printf("%s \n", u8"���ñ���");
			break;
		default:
			break;
		}
		printf("%s \n", lectureTable[i].name);
		printf("%d \n", lectureTable[i].credit);
		printf("%s \n", lectureTable[i].timeString);
		for (timeListPtr j = lectureTable[i].lectureTime->next; j != NULL; j = j->next) {
			switch (j->timeblock.dayofWeek)
			{
			case MON:
				printf("%s", u8"��");
				break;
			case TUE:
				printf("%s", u8"ȭ");
				break;
			case WED:
				printf("%s", u8"��");
				break;
			case THU:
				printf("%s", u8"��");
				break;
			case FRI:
				printf("%s", u8"��");
				break;
			case SAT:
				printf("%s", u8"��");
				break;
			case SUN:
				printf("%s", u8"��");
				break;
			default:
				break;
			}
			printf("%d ", j->timeblock.period);
		}
		printf("\n");
		switch (lectureTable[i].room)
		{
		case EDUCATE:
			printf("%s \n", u8"������");
			break;
		case REFINEMENT:
			printf("%s \n", u8"�����");
			break;
		case INFORMATICS:
			printf("%s \n", u8"�����");
			break;
		case SCI_LIBRARY:
			printf("%s \n", u8"������");
			break;
		case SCIENCE_HALL:
			printf("%s \n", u8"���а�");
			break;
		case NEW_LAW_HALL:
			printf("%s \n", u8"���а��Ű�");
			break;
		case LP_HALL:
			printf("%s \n", u8"L-P��");
			break;
		case WEST_HALL:
			printf("%s \n", u8"����");
			break;
		case POLITIC:
			printf("%s \n", u8"�����");
			break;
		default:
			break;
		}
		printf("%d%s \n", lectureTable[i].distance, u8"��");
		switch (lectureTable[i].klueRating)
		{
		case GOOD:
			printf("%s \n", u8"�ܰ�");
			break;
		case NORMAL:
			printf("%s \n", u8"����");
			break;
		case BAD:
			printf("%s \n", u8"����");
			break;
		default:
			break;
		}
		printf("\n");
	}
	xmlFreeDoc(doc);
	
	fprintf(pFile, "[name]\n");
	for (int i = 0; i < lectureSize; i++) {
		memset(euc_buf, '\0', 50);
		input_buf_ptr = lectureTable[i].name;
		output_buf_ptr = euc_buf;
		in_size = strlen(lectureTable[i].name);
		out_size = sizeof(euc_buf);

		ret = iconv(it, &input_buf_ptr, &in_size, &output_buf_ptr, &out_size);

		if (ret < 0)
		{
			printf("ret : %d, errno : %d\n", ret, errno);
			return(-1);
		}
		fprintf(pFile, "%s=%s\n", lectureTable[i].identifyNumber, euc_buf);
	}
	fprintf(pFile, "[time]\n");
	for (int i = 0; i < lectureSize; i++) {
		memset(euc_buf2, '\0', 50);
		input_buf_ptr = lectureTable[i].timeString;
		output_buf_ptr = euc_buf2;
		in_size = strlen(lectureTable[i].timeString);
		out_size = sizeof(euc_buf2);

		ret = iconv(it, &input_buf_ptr, &in_size, &output_buf_ptr, &out_size);

		if (ret < 0)
		{
			printf("ret : %d, errno : %d\n", ret, errno);
			return(-1);
		}
		fprintf(pFile, "%s=%s\n", lectureTable[i].identifyNumber, euc_buf2);
	}
	fprintf(pFile, "[classify]\n");
	for (int i = 0; i < lectureSize; i++) {
		fprintf(pFile, "%s=", lectureTable[i].identifyNumber);
		switch (lectureTable[i].classify)
		{
		case CORE:
			fprintf(pFile, "�ٽɱ���\n");
			break;
		case SELECTIVE:
			fprintf(pFile, "���ñ���\n");
			break;
		case MAJOR:
			fprintf(pFile, "�������ñ���\n");
			break;
		default:
			fprintf(pFile, "�ȵ�\n");
			break;
		}
	}
	fprintf(pFile, "[room]\n");
	for (int i = 0; i < lectureSize; i++) {
		fprintf(pFile, "%s=", lectureTable[i].identifyNumber);
		switch (lectureTable[i].room)
		{
		case EDUCATE:
			fprintf(pFile, "������\n");
			break;
		case REFINEMENT:
			fprintf(pFile, "�����\n");
			break;
		case INFORMATICS:
			fprintf(pFile, "�����\n");
			break;
		case SCI_LIBRARY:
			fprintf(pFile, "������\n");
			break;
		case SCIENCE_HALL:
			fprintf(pFile, "���а�\n");
			break;
		case NEW_LAW_HALL:
			fprintf(pFile, "���нŰ�\n");
			break;
		case LP_HALL:
			fprintf(pFile, "L-P��\n");
			break;
		case WEST_HALL:
			fprintf(pFile, "����\n");
			break;
		case POLITIC:
			fprintf(pFile, "�����\n");
			break;
		default:
			fprintf(pFile, "�ȵ�\n");
			break;
		}
	}
	fprintf(pFile, "[credit]\n");
	for (int i = 0; i < lectureSize; i++) {
		fprintf(pFile, "%s=%d\n", lectureTable[i].identifyNumber, lectureTable[i].credit);
	}
	fprintf(pFile, "[evaluation_method]\n");
	for (int i = 0; i < lectureSize; i++) {
		fprintf(pFile, "%s=%s\n", lectureTable[i].identifyNumber, "����1(50) ����2(50)");
	}
	fprintf(pFile, "[tuition_method]\n");
	for (int i = 0; i < lectureSize; i++) {
		fprintf(pFile, "%s=%s\n", lectureTable[i].identifyNumber, "����3 ����4");
	}
	fclose(pFile);
	iconv_close(it);
}