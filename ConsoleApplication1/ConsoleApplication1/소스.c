#pragma comment(lib, "Ws2_32.lib")
#include"parserCustom.h"
#include <stdlib.h>
#define lectureSize 20
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
	doc = xmlParseFile("dummy-beta.xml");
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

	pFile = fopen("lecture_info_beta.ini", "w");

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
	for (int i = 0; i < LECTURETABLE_SIZE; i++) {
		printf("%s \n", lectureTable[i].identifyNumber);
		switch (lectureTable[i].classify)
		{
		case CORE:
			printf("%s \n", u8"핵심교양");
			break;
		case MAJOR:
			printf("%s \n", u8"전필교양");
			break;
		case SELECTIVE:
			printf("%s \n", u8"선택교양");
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
				printf("%s", u8"월");
				break;
			case TUE:
				printf("%s", u8"화");
				break;
			case WED:
				printf("%s", u8"수");
				break;
			case THU:
				printf("%s", u8"목");
				break;
			case FRI:
				printf("%s", u8"금");
				break;
			case SAT:
				printf("%s", u8"토");
				break;
			case SUN:
				printf("%s", u8"일");
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
			printf("%s \n", u8"교육관");
			break;
		case REFINEMENT:
			printf("%s \n", u8"교양관");
			break;
		case INFORMATICS:
			printf("%s \n", u8"정통관");
			break;
		case SCI_LIBRARY:
			printf("%s \n", u8"과도관");
			break;
		case SCIENCE_HALL:
			printf("%s \n", u8"이학관");
			break;
		case NEW_LAW_HALL:
			printf("%s \n", u8"법학관신관");
			break;
		case LP_HALL:
			printf("%s \n", u8"L-P관");
			break;
		case WEST_HALL:
			printf("%s \n", u8"서관");
			break;
		case POLITIC:
			printf("%s \n", u8"정경관");
			break;
		default:
			break;
		}
		printf("%d%s \n", lectureTable[i].distance, u8"분");
		switch (lectureTable[i].klueRating)
		{
		case KLUE_GOOD:
			printf("%s \n", u8"꿀강");
			break;
		case KLUE_NORMAL:
			printf("%s \n", u8"보통");
			break;
		case KLUE_BAD:
			printf("%s \n", u8"지뢰");
			break;
		default:
			break;
		}
		switch (lectureTable[i].Att)
		{
		case ATT_LOOSE:
			printf("%s \n", u8"느슨");
			break;
		case ATT_NORMAL:
			printf("%s \n", u8"보통");
			break;
		case ATT_TIGHT:
			printf("%s \n", u8"칼같음");
			break;
		default:
			break;
		}
		printf("%s \n", lectureTable[i].evalString);
		for (int ii = 0; ii < EVALUATION_SIZE; ii++) {
			if (lectureTable[i].evaluationArray[ii] != 0) {
				switch (ii) {
				case EVAL_MIDDLE_EXAM:
					printf(u8"중간 ");
					break;
				case EVAL_FINAL_EXAM:
					printf(u8"기말 ");
					break;
				case EVAL_ASSIGNMENT:
					printf(u8"중간 ");
					break;
				case EVAL_PRESENTATION:
					printf(u8"중간 ");
					break;
				case EVAL_ATTENDANCE:
					printf(u8"중간 ");
					break;
				case EVAL_UNDETERMINED_1:
					printf(u8"중간 ");
					break;
				case EVAL_UNDETERMINED_2:
					printf(u8"중간 ");
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
					printf(u8"토론 ");
					break;
				case TUI_PRESENTATION:
					printf(u8"발표 ");
					break;
				case TUI_LECTURE:
					printf(u8"강의 ");
					break;
				case TUI_QUIZ:
					printf(u8"퀴즈 ");
					break;
				case TUI_UNDETERMINED_3:
					printf(u8"미3 ");
					break;
				case TUI_UNDETERMINED_4:
					printf(u8"미4 ");
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
	for (int i = 0; i < LECTURETABLE_SIZE; i++) {
		fprintf(pFile, "%s=%s\n", lectureTable[i].identifyNumber, lectureTable[i].name);
	}
	fprintf(pFile, "[time]\n");
	for (int i = 0; i < LECTURETABLE_SIZE; i++) {
		fprintf(pFile, "%s=%s\n", lectureTable[i].identifyNumber, lectureTable[i].timeString);
	}
	fprintf(pFile, "[classify]\n");
	for (int i = 0; i < LECTURETABLE_SIZE; i++) {
		fprintf(pFile, "%s=", lectureTable[i].identifyNumber);
		switch (lectureTable[i].classify)
		{
		case CORE:
			fprintf(pFile, u8"핵심교양\n");
			break;
		case SELECTIVE:
			fprintf(pFile, u8"선택교양\n");
			break;
		case MAJOR:
			fprintf(pFile, u8"전공관련교양\n");
			break;
		default:
			fprintf(pFile, u8"안됨\n");
			break;
		}
	}
	fprintf(pFile, "[room]\n");
	for (int i = 0; i < LECTURETABLE_SIZE; i++) {
		fprintf(pFile, "%s=", lectureTable[i].identifyNumber);
		switch (lectureTable[i].room)
		{
		case EDUCATE:
			fprintf(pFile, u8"교육관\n");
			break;
		case REFINEMENT:
			fprintf(pFile, u8"교양관\n");
			break;
		case INFORMATICS:
			fprintf(pFile, u8"정통관\n");
			break;
		case SCI_LIBRARY:
			fprintf(pFile, u8"과도관\n");
			break;
		case SCIENCE_HALL:
			fprintf(pFile, u8"이학관\n");
			break;
		case NEW_LAW_HALL:
			fprintf(pFile, u8"법학신관\n");
			break;
		case LP_HALL:
			fprintf(pFile, u8"L-P관\n");
			break;
		case WEST_HALL:
			fprintf(pFile, u8"서관\n");
			break;
		case POLITIC:
			fprintf(pFile, u8"정경관\n");
			break;
		default:
			fprintf(pFile, u8"안됨\n");
			break;
		}
	}
	fprintf(pFile, "[credit]\n");
	for (int i = 0; i < LECTURETABLE_SIZE; i++) {
		fprintf(pFile, "%s=%d\n", lectureTable[i].identifyNumber, lectureTable[i].credit);
	}
	fprintf(pFile, "[evaluation_method]\n");
	for (int i = 0; i < LECTURETABLE_SIZE; i++) {
		fprintf(pFile, "%s=%s\n", lectureTable[i].identifyNumber, lectureTable[i].evalString);
	}
	fprintf(pFile, "[tuition_method]\n");
	for (int i = 0; i < LECTURETABLE_SIZE; i++) {
		fprintf(pFile, "%s=%s\n", lectureTable[i].identifyNumber, lectureTable[i].tuitionString);
	}

	fprintf(pFile, "[klue]\n");
	for (int i = 0; i < LECTURETABLE_SIZE; i++) {
		fprintf(pFile, "%s=", lectureTable[i].identifyNumber);
		switch (lectureTable[i].klueRating)
		{
		case KLUE_VGOOD:
			fprintf(pFile, u8"절평\n");
			break;
		case KLUE_GOOD:
			fprintf(pFile, u8"전달력좋음\n");
			break;
		case KLUE_NORMAL:
			fprintf(pFile, u8"보통\n");
			break;
		case KLUE_BAD:
			fprintf(pFile, u8"전달력나쁨\n");
			break;
		case KLUE_VBAD:
			fprintf(pFile, u8"쓰레기\n");
			break;
		default:
			fprintf(pFile, u8"안됨\n");
			break;
		}
	}

	fprintf(pFile, "[attendance]\n");
	for (int i = 0; i < LECTURETABLE_SIZE; i++) {
		fprintf(pFile, "%s=", lectureTable[i].identifyNumber);
		switch (lectureTable[i].Att)
		{
		case ATT_VLOOSE:
			fprintf(pFile, u8"안부름\n");
			break;
		case ATT_LOOSE:
			fprintf(pFile, u8"가끔부름\n");
			break;
		case ATT_NORMAL:
			fprintf(pFile, u8"보통\n");
			break;
		case ATT_TIGHT:
			fprintf(pFile, u8"자주부름\n");
			break;
		case ATT_VTIGHT:
			fprintf(pFile, u8"매일부름\n");
			break;
		default:
			fprintf(pFile, u8"안됨\n");
			break;
		}
	}

	fprintf(pFile, "[distance]\n");
	for (int i = 0; i < LECTURETABLE_SIZE; i++) {
		fprintf(pFile, "%s=%d\n", lectureTable[i].identifyNumber, lectureTable[i].distance);
	}

	fprintf(pFile, "[time_room]\n");
	for (int i = 0; i < LECTURETABLE_SIZE; i++) {
		fprintf(pFile, "%s=%s ", lectureTable[i].identifyNumber, lectureTable[i].timeString, lectureTable[i]);
		switch (lectureTable[i].room)
		{
		case EDUCATE:
			fprintf(pFile, u8"교육관\n");
			break;
		case REFINEMENT:
			fprintf(pFile, u8"교양관\n");
			break;
		case INFORMATICS:
			fprintf(pFile, u8"정통관\n");
			break;
		case SCI_LIBRARY:
			fprintf(pFile, u8"과도관\n");
			break;
		case SCIENCE_HALL:
			fprintf(pFile, u8"이학관\n");
			break;
		case NEW_LAW_HALL:
			fprintf(pFile, u8"법학신관\n");
			break;
		case LP_HALL:
			fprintf(pFile, u8"L-P관\n");
			break;
		case WEST_HALL:
			fprintf(pFile, u8"서관\n");
			break;
		case POLITIC:
			fprintf(pFile, u8"정경관\n");
			break;
		default:
			fprintf(pFile, u8"안됨\n");
			break;
		}
	}
	fprintf(pFile, "[classify_credit]\n");
	for (int i = 0; i < LECTURETABLE_SIZE; i++) {
		fprintf(pFile, "%s=", lectureTable[i].identifyNumber);
		switch (lectureTable[i].classify)
		{
		case CORE:
			fprintf(pFile, u8"핵심교양");
			break;
		case SELECTIVE:
			fprintf(pFile, u8"선택교양");
			break;
		case MAJOR:
			fprintf(pFile, u8"전공관련교양");
			break;
		default:
			fprintf(pFile, u8"안됨");
			break;
		}
		fprintf(pFile, ". %d\n", lectureTable[i].credit);
	}
	fclose(pFile);
}