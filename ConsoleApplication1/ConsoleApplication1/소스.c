#pragma comment(lib, "Ws2_32.lib")
#include"parserCustom.h"
#include <stdlib.h>
lectureInfo lectureTable[LECTURE_SIZE];

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
	doc = xmlParseFile("lecture.xml");
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
					case ATTENDANCE:
						lectureTable[i].Att = getAttMessage(key);
						break;
					case EVAL:
						strcpy_s(lectureTable[i].evalString, sizeof(lectureTable[i].evalString), key);
						registerEvaluation(key, lectureTable[i].evaluationArray);
						break;
					case TUITION:
						strcpy_s(lectureTable[i].tuitionString, sizeof(lectureTable[i].tuitionString), key);
						registerTuition(key, lectureTable[i].tuitionArray);
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
	for (int i = 0; i < LECTURE_SIZE; i++) {
		printf("%s \n", lectureTable[i].identifyNumber);
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
		case HANA_SCIENCE:
			printf("%s \n", u8"���а�");
			break;
		case OLD_LAW_HALL:
			printf("%s \n", u8"���а�����");
			break;
		case CREATIVE:
			printf("%s \n", u8"â�ǰ�");
			break;
		case FUSION:
			printf("%s \n", u8"�̷����հ�");
			break;
		case BIO_HALL:
			printf("%s \n", u8"�����");
			break;
		case GYM_HALL:
			printf("%s \n", u8"ȭ��ü����");
			break;
		case GLOBAL_HALL:
			printf("%s \n", u8"������");
			break;
		default:
			break;
		}
		printf("%d%s \n", lectureTable[i].distance, u8"��");
		switch (lectureTable[i].klueRating)
		{
		case RATING_VGOOD:
			printf("%s \n", u8"����");
			break;
		case RATING_GOOD:
			printf("%s \n", u8"���޷�����");
			break;
		case RATING_NORMAL:
			printf("%s \n", u8"����");
			break;
		case RATING_BAD:
			printf("%s \n", u8"���޷³���");
			break;
		case RATING_VBAD:
			printf("%s \n", u8"������");
			break;
		default:
			break;
		}
		switch (lectureTable[i].Att)
		{
		case ATT_VLOOSE:
			printf("%s \n", u8"�Ⱥθ�");
			break;
		case ATT_LOOSE:
			printf("%s \n", u8"�����θ�");
			break;
		case ATT_NORMAL:
			printf("%s \n", u8"����");
			break;
		case ATT_VTIGHT:
			printf("%s \n", u8"���Ϻθ�");
			break;
		case ATT_TIGHT:
			printf("%s \n", u8"���ֺθ�");
			break;
		default:
			break;
		}
		printf("%s \n", lectureTable[i].evalString);
		for (int ii = 0; ii < EVALUATION_SIZE; ii++) {
			if (lectureTable[i].evaluationArray[ii] != 0) {
				switch (ii) {
				case EVAL_MIDDLE_EXAM:
					printf(u8"�߰� ");
					break;
				case EVAL_FINAL_EXAM:
					printf(u8"�⸻ ");
					break;
				case EVAL_ASSIGNMENT:
					printf(u8"�߰� ");
					break;
				case EVAL_PRESENTATION:
					printf(u8"�߰� ");
					break;
				case EVAL_ATTENDANCE:
					printf(u8"�߰� ");
					break;
				case EVAL_UNDETERMINED_1:
					printf(u8"�߰� ");
					break;
				case EVAL_UNDETERMINED_2:
					printf(u8"�߰� ");
					break;
				default:
					break;
				}
				printf("%d \n", lectureTable[i].evaluationArray[ii]);
			}
		}
		printf("%s \n", lectureTable[i].tuitionString);
		for (int ii = 0; ii < TUITION_SIZE; ii++) {
			if (lectureTable[i].tuitionArray[ii] != 0) {
				switch (ii) {
				case TUI_DEBATION:
					printf(u8"��� ");
					break;
				case TUI_PRESENTATION:
					printf(u8"��ǥ ");
					break;
				case TUI_LECTURE:
					printf(u8"���� ");
					break;
				case TUI_QUIZ:
					printf(u8"���� ");
					break;
				case TUI_UNDETERMINED_3:
					printf(u8"��3 ");
					break;
				case TUI_UNDETERMINED_4:
					printf(u8"��4 ");
					break;
				case TUI_DEFAULT:
					break;
				default:
					break;
				}
			}
		}
		printf("\n");
	}
	xmlFreeDoc(doc);
	
	fprintf(pFile, "[name]\n");
	for (int i = 0; i < LECTURE_SIZE; i++) {
		fprintf(pFile, "%s=%s\n", lectureTable[i].identifyNumber, lectureTable[i].name);
	}
	fprintf(pFile, "[time]\n");
	for (int i = 0; i < LECTURE_SIZE; i++) {
		fprintf(pFile, "%s=%s\n", lectureTable[i].identifyNumber, lectureTable[i].timeString);
	}
	fprintf(pFile, "[classify]\n");
	for (int i = 0; i < LECTURE_SIZE; i++) {
		fprintf(pFile, "%s=", lectureTable[i].identifyNumber);
		switch (lectureTable[i].classify)
		{
		case CORE:
			fprintf(pFile, u8"�ٽɱ���\n");
			break;
		case SELECTIVE:
			fprintf(pFile, u8"���ñ���\n");
			break;
		case MAJOR:
			fprintf(pFile, u8"�������ñ���\n");
			break;
		default:
			fprintf(pFile, u8"�ȵ�\n");
			break;
		}
	}
	fprintf(pFile, "[room]\n");
	for (int i = 0; i < LECTURE_SIZE; i++) {
		fprintf(pFile, "%s=", lectureTable[i].identifyNumber);
		switch (lectureTable[i].room)
		{
		case EDUCATE:
			fprintf(pFile, u8"������\n");
			break;
		case REFINEMENT:
			fprintf(pFile, u8"�����\n");
			break;
		case INFORMATICS:
			fprintf(pFile, u8"�����\n");
			break;
		case SCI_LIBRARY:
			fprintf(pFile, u8"������\n");
			break;
		case SCIENCE_HALL:
			fprintf(pFile, u8"���а�\n");
			break;
		case NEW_LAW_HALL:
			fprintf(pFile, u8"���нŰ�\n");
			break;
		case LP_HALL:
			fprintf(pFile, u8"L-P��\n");
			break;
		case WEST_HALL:
			fprintf(pFile, u8"����\n");
			break;
		case POLITIC:
			fprintf(pFile, u8"�����\n");
			break;
		case HANA_SCIENCE:
			fprintf(pFile, u8"���а�\n");
			break;
		case OLD_LAW_HALL:
			fprintf(pFile, u8"���а�����\n");
			break;
		case CREATIVE:
			fprintf(pFile, u8"â�ǰ�\n");
			break;
		case FUSION:
			fprintf(pFile, u8"�̷����հ�\n");
			break;
		case BIO_HALL:
			fprintf(pFile, u8"�����\n");
			break;
		case GYM_HALL:
			fprintf(pFile, u8"ȭ��ü����\n");
			break;
		case GLOBAL_HALL:
			fprintf(pFile, u8"������\n");
			break;
		default:
			fprintf(pFile, u8"�ȵ�\n");
			break;
		}
	}
	fprintf(pFile, "[credit]\n");
	for (int i = 0; i < LECTURE_SIZE; i++) {
		fprintf(pFile, "%s=%d\n", lectureTable[i].identifyNumber, lectureTable[i].credit);
	}
	fprintf(pFile, "[distance]\n");
	for (int i = 0; i < LECTURE_SIZE; i++) {
		fprintf(pFile, "%s=%d%s\n", lectureTable[i].identifyNumber, lectureTable[i].distance, u8"��");
	}
	fprintf(pFile, "[rating]\n");
	for (int i = 0; i < LECTURE_SIZE; i++) {
		fprintf(pFile, "%s=", lectureTable[i].identifyNumber);
		switch (lectureTable[i].klueRating)
		{
		case RATING_VBAD:
			fprintf(pFile, u8"������\n");
			break;
		case RATING_BAD:
			fprintf(pFile, u8"���޷³���\n");
			break;
		case RATING_NORMAL:
			fprintf(pFile, u8"����\n");
			break;
		case RATING_GOOD:
			fprintf(pFile, u8"���޷�����\n");
			break;
		case RATING_VGOOD:
			fprintf(pFile, u8"����\n");
			break;
		default:
			fprintf(pFile, u8"�ȵ�\n");
			break;
		}
	}
	fprintf(pFile, "[Attendance]\n");
	for (int i = 0; i < LECTURE_SIZE; i++) {
		fprintf(pFile, "%s=", lectureTable[i].identifyNumber);
		switch (lectureTable[i].Att)
		{
		case ATT_VLOOSE:
			fprintf(pFile, u8"�Ⱥθ�\n");
			break;
		case ATT_LOOSE:
			fprintf(pFile, u8"�����θ�\n");
			break;
		case ATT_NORMAL:
			fprintf(pFile, u8"����\n");
			break;
		case ATT_TIGHT:
			fprintf(pFile, u8"���ֺθ�\n");
			break;
		case ATT_VTIGHT:
			fprintf(pFile, u8"���Ϻθ�\n");
			break;
		default:
			fprintf(pFile, u8"�ȵ�\n");
			break;
		}
	}
	fprintf(pFile, "[evaluation_method]\n");
	for (int i = 0; i < LECTURE_SIZE; i++) {
		fprintf(pFile, "%s=%s\n", lectureTable[i].identifyNumber, lectureTable[i].evalString);
	}
	fprintf(pFile, "[tuition_method]\n");
	for (int i = 0; i < LECTURE_SIZE; i++) {
		fprintf(pFile, "%s=%s\n", lectureTable[i].identifyNumber, lectureTable[i].tuitionString);
	}

	fprintf(pFile, "[time_room]\n");
	for (int i = 0; i < LECTURE_SIZE; i++) {
		fprintf(pFile, "%s=%s ", lectureTable[i].identifyNumber, lectureTable[i].timeString, lectureTable[i]);
		switch (lectureTable[i].room)
		{
		case EDUCATE:
			fprintf(pFile, u8"������\n");
			break;
		case REFINEMENT:
			fprintf(pFile, u8"�����\n");
			break;
		case INFORMATICS:
			fprintf(pFile, u8"�����\n");
			break;
		case SCI_LIBRARY:
			fprintf(pFile, u8"������\n");
			break;
		case SCIENCE_HALL:
			fprintf(pFile, u8"���а�\n");
			break;
		case NEW_LAW_HALL:
			fprintf(pFile, u8"���нŰ�\n");
			break;
		case LP_HALL:
			fprintf(pFile, u8"L-P��\n");
			break;
		case WEST_HALL:
			fprintf(pFile, u8"����\n");
			break;
		case POLITIC:
			fprintf(pFile, u8"�����\n");
			break;
		case HANA_SCIENCE:
			fprintf(pFile, u8"�ϳ���\n");
			break;
		case OLD_LAW_HALL:
			fprintf(pFile, u8"���а�����\n");
			break;
		case CREATIVE:
			fprintf(pFile, u8"â�ǰ�\n");
			break;
		case FUSION:
			fprintf(pFile, u8"�̷����հ�\n");
			break;
		case BIO_HALL:
			fprintf(pFile, u8"�����\n");
			break;
		case GYM_HALL:
			fprintf(pFile, u8"ȭ��ü����\n");
			break;
		case GLOBAL_HALL:
			fprintf(pFile, u8"������\n");
			break;
		default:
			fprintf(pFile, u8"�ȵ�\n");
			break;
		}
	}
	fprintf(pFile, "[classify_credit]\n");
	for (int i = 0; i < LECTURE_SIZE; i++) {
		fprintf(pFile, "%s=", lectureTable[i].identifyNumber);
		switch (lectureTable[i].classify)
		{
		case CORE:
			fprintf(pFile, u8"�ٽɱ���");
			break;
		case SELECTIVE:
			fprintf(pFile, u8"���ñ���");
			break;
		case MAJOR:
			fprintf(pFile, u8"�������ñ���");
			break;
		default:
			fprintf(pFile, u8"�ȵ�");
			break;
		}
		fprintf(pFile, ". %d\n", lectureTable[i].credit);
	}
	fclose(pFile);
}