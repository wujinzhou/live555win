#pragma once

class ErrorCode
{
public:
	ErrorCode(void);
	~ErrorCode(void);
	enum {
		EC_SUCCESS = 0,
		EC_PARAM_ERROR = 1,
		EC_KEY_NOT_FOUND = 2,
	};
};
