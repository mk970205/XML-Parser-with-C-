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
	KLUE,
	ATTENDANCE,
	EVAL,
	TUITION
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
		cases(u8"지뢰")
			return KLUE_BAD;
		cases(u8"꿀강")
			return KLUE_GOOD;
		defaults
			return KLUE_NORMAL;
	} switchs_end;
}

int getAttMessage(char* name) {
	switchs(name) {
		cases("TIGHT")
			return ATT_TIGHT;
		cases("LOOSE")
			return ATT_LOOSE;
		cases("NORMAL")
			return ATT_NORMAL;
		defaults
			return ATT_NORMAL;
	} switchs_end;
	return 0;
}

roomNumber getRoomMessage(char* name) {
	switchs(name) {
		cases(u8"교육관")
			return EDUCATE;
		cases(u8"교양관")
			return REFINEMENT;
		cases(u8"정통관")
			return INFORMATICS;
		cases(u8"과도관")
			return SCI_LIBRARY;
		cases(u8"이학관")
			return SCIENCE_HALL;
		cases(u8"법학관신관")
			return NEW_LAW_HALL;
		cases(u8"L-P관")
			return LP_HALL;
		cases(u8"서관")
			return WEST_HALL;
		cases(u8"정경관")
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
		cases("attendance")
			return ATTENDANCE;
		cases("eval")
			return EVAL;
		cases("tuition")
			return TUITION;
		defaults
			return XML_MESSAGE_DEFAULT;
	} switchs_end;
}
whatDay whatDayFunc(char hangul[]) {
	switchs(hangul) {
		cases(u8"월")
			return MON;
		cases(u8"화")
			return TUE;
		cases(u8"수")
			return WED;
		cases(u8"목")
			return THU;
		cases(u8"금")
			return FRI;
		cases(u8"토")
			return SAT;
		cases(u8"일")
			return SUN;
		defaults
			return DAY_DEFAULT;

	} switchs_end;
}

int getEvalMessage(char hangul[]) {
	switchs(hangul) {
		cases(u8"중간")
			return EVAL_MIDDLE_EXAM;
		cases(u8"기말")
			return EVAL_FINAL_EXAM;
		cases(u8"과제")
			return EVAL_ASSIGNMENT;
		cases(u8"발표")
			return EVAL_PRESENTATION;
		cases(u8"출석")
			return EVAL_ATTENDANCE;
		cases(u8"미1")
			return EVAL_UNDETERMINED_1;
		cases(u8"미2")
			return EVAL_UNDETERMINED_2;
		defaults
			return EVAL_DEFALUT;

	} switchs_end;
	return 0;
}

int getTuitionMessage(char hangul[]) {
	switchs(hangul) {
		cases(u8"강의")
			return TUI_LECTURE;
		cases(u8"발표")
			return TUI_PRESENTATION;
		cases(u8"토론")
			return TUI_DEBATION;
		cases(u8"퀴즈")
			return TUI_QUIZ;
		cases(u8"미3")
			return TUI_UNDETERMINED_3;
		cases(u8"미4")
			return TUI_UNDETERMINED_4;
		defaults
			return TUI_DEFAULT;

	} switchs_end;
	return 0;
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

void registerEvaluation(char* key, int evaluationArray[]) {
	unsigned char hangul[12];
	unsigned char soojja[6];
	int hangulMode = 1;
	int i = 0;
	int j = 0;
	int whatEval;
	int howMuch;
	for (int k = 0; k < EVALUATION_SIZE; k++) {
		evaluationArray[k] = 0;
	}
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
				soojja[j] = '\0';
				j = 0;
				hangulMode = 1;
				whatEval = getEvalMessage(hangul);
				howMuch = atoiCustom(soojja, 0);
				evaluationArray[whatEval] = howMuch;

			}
			else { // just number
				soojja[j] = key[i];
				j++;
			}
		}
		i++;
	}
}

void registerTuition(char* key, int tuitionArray[]) {
	unsigned char hangul[9];
	int hangulMode = 1;
	int i = 0;
	int j = 0;
	int whatTuition;
	for (int k = 0; k < TUITION_SIZE; k++) {
		tuitionArray[k] = 0;
	}
	while (key[i] != '\0') {
		if (key[i] != ' ') {
			hangul[j] = key[i];
			j++;
		}
		else {
			hangul[j] = '\0';
			whatTuition = getTuitionMessage(hangul);
			tuitionArray[whatTuition] = 1;
			j = 0;
		}
		i++;
	}
	hangul[j] = '\0';
	whatTuition = getTuitionMessage(hangul);
	tuitionArray[whatTuition] = 1;
	j = 0;
}