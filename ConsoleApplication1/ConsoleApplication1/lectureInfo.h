#pragma once
#define TUITION_SIZE 6
#define EVALUATION_SIZE 7
#define LECTURETABLE_SIZE 12
typedef enum _messageNumber {
	MESSAGE_DEFAULT,
	NO_OVERLAP,
	TIME_OVERLAP,
	ALREADY_EXIST,
	EXCEED_POINT
} messageNumber;

typedef enum _classifyNumber {
	CLASSIFY_DEFAULT,
	SELECTIVE,//���ñ���
	MAJOR, //�������ñ���
	CORE //�ٽɱ���
} classifyNumber;

typedef enum _roomNumber {
	ROOM_DEFAULT,
	EDUCATE, // ������
	REFINEMENT, // �����
	INFORMATICS, // �����
	SCI_LIBRARY, // ������
	SCIENCE_HALL, // ���а�
	NEW_LAW_HALL, // ���а��Ű�
	LP_HALL, // L-P��
	WEST_HALL, // ����
	POLITIC // �����

} roomNumber;

typedef enum _ratingNumber {
	RATING_DEFAULT,
	GOOD,
	NORMAL,
	BAD
} ratingNumber;

typedef enum _whatDay {
	MON,
	TUE,
	WED,
	THU,
	FRI,
	SAT,
	SUN,
	DAY_DEFAULT
} whatDay;

typedef struct _timeBlock {
	enum whatDay dayofWeek; //����
	int period; //����
} timeBlock;

typedef struct _timeList {
	timeBlock timeblock;
	struct _timeList* next;
} timeList;

typedef timeList* timeListPtr;

typedef struct _evalNode {
	enum evalEnum standard;
	int weight;
} evalNode;

typedef struct _evalList {
	evalNode evalnode;
	struct _evalList* next;
} evalList;

typedef evalList* evalListPtr;

typedef enum _evalEnum {
	EVAL_MIDDLE_EXAM = 0, // �߰�
	EVAL_FINAL_EXAM, // �⸻
	EVAL_ASSIGNMENT, // ����
	EVAL_PRESENTATION, // ��ǥ
	EVAL_ATTENDANCE, // �⼮
	EVAL_UNDETERMINED_1, // ��1
	EVAL_UNDETERMINED_2, // ��2
	EVAL_DEFALUT
} evalEnum;

typedef enum _tuition_index {
	TUI_DEBATION = 0, //���
	TUI_PRESENTATION, // ��ǥ
	TUI_LECTURE, //  ����
	TUI_QUIZ, // ����
	TUI_UNDETERMINED_3, //����3
	TUI_UNDETERMINED_4, //����4
	TUI_DEFAULT
} tuition_index;

typedef enum _attendance {
	LOOSE, //����
	ATT_NORMAL, // ����
	TIGHT // ������
} AttendanceRate;

typedef struct _lectureInfo {
	int credit; //����
	unsigned char identifyNumber[8]; //�м���ȣ
	unsigned char name[75]; // ���Ǹ�
	enum classifyNumber classify; // ��������/�ٽ�/���� ���� �з�
	enum roomNumber room; // ���ǽ�
	enum Rating klueRating; // klue��
	enum AttendanceRate Att;
	int distance; // �Ÿ�
	timeListPtr lectureTime;
	int evaluationArray[EVALUATION_SIZE];
	int tuitionArray[TUITION_SIZE];
	unsigned char timeString[30];
	unsigned char evalString[100];
	unsigned char tuitionString[30];
} lectureInfo;
