#pragma once
typedef enum _messageNumber {
	MESSAGE_DEFAULT,
	NO_OVERLAP,
	TIME_OVERLAP,
	ALREADY_EXIST,
	EXCEED_POINT
} messageNumber;

typedef enum _classifyNumber {
	CLASSIFY_DEFAULT,
	SELECTIVE,//선택교양
	MAJOR, //전공관련교양
	CORE //핵심교양
} classifyNumber;

typedef enum _roomNumber {
	ROOM_DEFAULT,
	EDUCATE, // 교육관
	REFINEMENT, // 교양관
	INFORMATICS, // 정통관
	SCI_LIBRARY, // 과도관
	SCIENCE_HALL, // 이학관
	NEW_LAW_HALL, // 법학관신관
	LP_HALL, // L-P관
	WEST_HALL, // 서관
	POLITIC // 정경관
	
} roomNumber;

typedef enum _ratingNumber {
	RATING_DEFAULT,
	GOOD,
	NORMAL,
	BAD
} ratingNumber;

typedef enum _whatDay {
	DAY_DEFAULT,
	MON,
	TUE,
	WED,
	THU,
	FRI,
	SAT,
	SUN
} whatDay;

typedef struct _timeBlock {
	enum _whatDay dayofWeek; //요일
	int period; //교시
} timeBlock;

typedef struct _timeList {
	timeBlock timeblock;
	struct _timeList* next;
} timeList;

typedef timeList* timeListPtr;

typedef struct _lectureInfo {
	int classNumber; // 분반
	int credit; //학점
	char identifyNumber[8]; //학술번호
	char name[75]; // 강의명
	classifyNumber classify; // 전공관련/핵심/선택 교양 분류
	roomNumber room; // 강의실
	ratingNumber klueRating; // klue평가
	int distance; // 거리
	timeListPtr lectureTime;
	char timeString[30];
} lectureInfo;
