# win32API
win32 API

UINT = Unsigned Int
WPARAM = word-parameter (과거 16비트 -> 현재 32비트)
LPARAM = long-parameter (과거부터 32비트)
LRESULT = long, HRESULT = int
LPVOID = void*
HINSTANCE = InstanceID, Handle + Instance (not ProcessID)
LOWORD = int형 자료의 하위 2바이트 (HIWORD -> 상위 2바이트)
HINSTANCE = InstanceID, Handle + Instance (not ProcessID)

LP = Long Pointer, 64 or 32 포인터 값
C = Constant = const
W = Wide Char = Unicode
LPCSTR =  불변 문자 포인터 값
LPCWSTR = 유니코드 불변 문자 포인터 값

CALLBACK = 콜백 함수

GetWindowLongPtrW / GWLP_HINSTANCE = 응용 프로그램 인스턴스 가져오기

CB_GETCURSEL = CB에서 현재 선택한 인덱스 검색
CB_GETLBTEXT = CB에서 검색할 문자열의 인덱스

SetWindowText = 타이틀 창 이름 바꾸기
MAKELONG = LONG 타입 만들어서 변환
ZeroMemory = 구조체 초기화 