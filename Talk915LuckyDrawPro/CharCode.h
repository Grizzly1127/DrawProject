/************************************
*comment:GBK��unicode�ַ�����ת�� 
*auth:huangyubin
*date:2015.12.30
*************************************/

#ifndef __STRING_CODE_CONVERT_H__
#define __STRING_CODE_CONVERT_H__


class CharCode
{
public:
	CharCode(const char* pszSrc);
	CharCode(const TCHAR* pszSrc);
	~CharCode();

	//����gbk����
	const char* GetStringA();
	//����unicode����
	const TCHAR* GetStringW();
	

private:
	char* m_pszDes;
	TCHAR* m_pwcharDes;

	char* WideToMuit(TCHAR* ptcSrc);
	TCHAR* MuitToWide(char* pSrc);

};

#endif