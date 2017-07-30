#pragma once
#include"lectureInfo.h"
#include<libxml\parser.h>
#include"stringAdvance.h"
typedef enum _XMLelementMessage {
	XML_MESSAGE_DEFAULT,
	CODE,
	CLASS,
	TYPE,
	NAME,
	CREDIT,
	TIME,
	ROOM,
	DISTANCE,
	KLUE
} XMLelementMessage;

enum _classifyNumber getClassifyMessage(char* name) {
	switchs(name) {
		cases("major")
			return MAJOR;
		cases("selective")
			return SELECTIVE;
		cases("core")
			return CORE;
		defaults
			return CLASSIFY_DEFAULT;

	} switchs_end;
}
int atoiCustom(char* key, int isDistance) {
	int k = (isDistance == 0) ? strlen(key) : strlen(key) - 3;
	int sum = 0;
	for (int i = 0; i < k; i++) {
		sum *= 10;
		sum += (key[i] - '0');
	}
	return sum;
}
ratingNumber getKlueMessage(char* name) {
	switchs(name) {
		cases(u8"����")
			return BAD;
		cases(u8"�ܰ�")
			return GOOD;
		defaults
			return NORMAL;
	} switchs_end;
}
roomNumber getRoomMessage(char* name) {
	switchs(name) {
		cases(u8"������")
			return EDUCATE;
		cases(u8"�����")
			return REFINEMENT;
		cases(u8"�����")
			return INFORMATICS;
		cases(u8"������")
			return SCI_LIBRARY;
		cases(u8"���а�")
			return SCIENCE_HALL;
		cases(u8"���а��Ű�")
			return NEW_LAW_HALL;
		cases(u8"L-P��")
			return LP_HALL;
		cases(u8"����")
			return WEST_HALL;
		cases(u8"�����")
			return POLITIC;
		defaults
			return ROOM_DEFAULT;
	} switchs_end;
}
int getElementMessage(char* name) {
	switchs(name) {
		cases("code")
			return CODE;
		cases("class")
			return CLASS;
		cases("type")
			return TYPE;
		cases("name")
			return NAME;
		cases("credit")
			return CREDIT;
		cases("time")
			return TIME;
		cases("room")
			return ROOM;
		cases("distance")
			return DISTANCE;
		cases("klue")
			return KLUE;
		defaults
			return XML_MESSAGE_DEFAULT;
	} switchs_end;
}
whatDay whatDayFunc(char hangul[]) {
	switchs(hangul) {
		cases(u8"��")
			return MON;
		cases(u8"ȭ")
			return TUE;
		cases(u8"��")
			return WED;
		cases(u8"��")
			return THU;
		cases(u8"��")
			return FRI;
		cases(u8"��")
			return SAT;
		cases(u8"��")
			return SUN;
		defaults
			return DAY_DEFAULT;

	} switchs_end;
}
timeListPtr registerTimeList(char* key) {
	unsigned char hangul[5];
	int hangulMode = 1;
	int startTime = 0;
	int endTime = 0;
	int timePhase = 0;
	timeListPtr nullNode = (timeListPtr)malloc(sizeof(timeList));
	nullNode->next = NULL;
	int i = 0;
	int j = 0;
	while (key[i] != '\0') {
		if (hangulMode == 1) {
			if (key[i] == '(') {
				hangul[j] = '\0';
				j = 0;
				hangulMode = 0;
			}
			else if (key[i] != ' ') {
				hangul[j] = key[i];
				j++;
			}
		}
		else {
			if (key[i] == ')') {
				if (timePhase == 0 || timePhase == 2) {
					endTime = startTime;
				}
				for (int q = startTime; q <= endTime; q++) {
					timeListPtr tempNode = (timeListPtr)malloc(sizeof(timeList));
					tempNode->timeblock.dayofWeek = whatDayFunc((char*)hangul);
					tempNode->timeblock.period = q;
					tempNode->next = nullNode->next;
					nullNode->next = tempNode;
				}
				startTime = 0;
				endTime = 0;
				timePhase = 0;
				hangulMode = 1;
			}
			else if (key[i] == '-') {
				timePhase = 1;
			}
			else { // just number
				if (timePhase == 0) {
					startTime = key[i] - '0';
					if (key[i + 1] - '0' >= 0 && key[i + 1] - '0' <= 9) {
						timePhase = 2;
					}
				}
				else if (timePhase == 1) {
					endTime = key[i] - '0';
					if (key[i + 1] - '0' >= 0 && key[i + 1] - '0' <= 9) {
						timePhase = 3;
					}
				}
				else if (timePhase == 2) {
					startTime *= 10;
					startTime += key[i] - '0';
				}
				else if (timePhase == 3) {
					endTime *= 10;
					endTime += key[i] - '0';
				}
			}
		}
		i++;
	}
	return nullNode;
}