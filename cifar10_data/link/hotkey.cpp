#include <windows.h>
#include <stdio.h>
#include <iostream>
#include <io.h>
#include <conio.h>
#include <windows.h>
#include <Shlwapi.h>

#include "hotkey.h"

#pragma comment( lib,"shlwapi.lib")

std::string kmess[HOTKEYS] = {					//�ȼ���ʾ��Ϣ
	"ALT_F1 �������ӿ��ƿ���!",					//����
	"ALT_F6 �Ͽ�����!" ,						//����
	"ALT_F7 ���Ӳ��ԣ���ӡ���̣�",
	"ALT_F8 ��ʼ�������淽���������ȼ�ǰ�뽫���ָ�����ϽǺڳ�����λ�ã���",//����
	"ALT_F9 �������ӿ��ƿ���!",							//����
	"ALT_F10 ���뷽��!",
	"ALT_F11 �ͻ����Զ����ӱ�־��",
	"ALT_F12 �������޷���ģʽ��",						//����
	"CTRL_ALT_F1 ѭ���޸Ĳ�����",						//����
	"CTRL_ALT_F2 ʶ�������ļ�ͼ��",
	"CTRL_ALT_F3 ���ӷ������ƿ��أ�",					//����
	"CTRL_ALT_F4 ����ֹͣ˼��������������",				//����
};



//ע��HotKey��
void hotkey(void)
{
	if (RegisterHotKey(NULL, ALT_F1, MOD_ALT | MOD_NOREPEAT, VK_F1))	std::cout << ((kmess[ALT_F1-1]).c_str()) << std::endl;
	if (RegisterHotKey(NULL, ALT_F6, MOD_ALT | MOD_NOREPEAT, VK_F6))	std::cout << ((kmess[ALT_F6-1]).c_str()) << std::endl;
	if (RegisterHotKey(NULL, ALT_F7, MOD_ALT | MOD_NOREPEAT, VK_F7))	std::cout << ((kmess[ALT_F7-1]).c_str()) << std::endl;
	if (RegisterHotKey(NULL, ALT_F8, MOD_ALT | MOD_NOREPEAT, VK_F8))	std::cout << ((kmess[ALT_F8-1]).c_str()) << std::endl;
	if (RegisterHotKey(NULL, ALT_F9, MOD_ALT | MOD_NOREPEAT, VK_F9))	std::cout << ((kmess[ALT_F9-1]).c_str()) << std::endl;
	if (RegisterHotKey(NULL, ALT_F10, MOD_ALT | MOD_NOREPEAT, VK_F10))	std::cout << ((kmess[ALT_F10-1]).c_str()) << std::endl;
	if (RegisterHotKey(NULL, ALT_F11, MOD_ALT | MOD_NOREPEAT, VK_F11))	std::cout << ((kmess[ALT_F11-1]).c_str()) << std::endl;
	if (RegisterHotKey(NULL, ALT_F12, MOD_ALT | MOD_NOREPEAT, VK_F12))	std::cout << ((kmess[ALT_F12-1]).c_str()) << std::endl;

	if (RegisterHotKey(NULL, CTRL_ALT_F1, MOD_CONTROL | MOD_ALT | MOD_NOREPEAT, VK_F1))	std::cout << ((kmess[CTRL_ALT_F1-1]).c_str()) << std::endl;
	if (RegisterHotKey(NULL, CTRL_ALT_F2, MOD_CONTROL | MOD_ALT | MOD_NOREPEAT, VK_F2))	std::cout << ((kmess[CTRL_ALT_F2-1]).c_str()) << std::endl;
	if (RegisterHotKey(NULL, CTRL_ALT_F3, MOD_CONTROL | MOD_ALT | MOD_NOREPEAT, VK_F3))	std::cout << ((kmess[CTRL_ALT_F3-1]).c_str()) << std::endl;
	if (RegisterHotKey(NULL, CTRL_ALT_F4, MOD_CONTROL | MOD_ALT | MOD_NOREPEAT, VK_F4))	std::cout << ((kmess[CTRL_ALT_F4-1]).c_str()) << std::endl;
}

//ע��HotKey, �ͷ���Դ��
void unhotkey(void)
{
	::UnregisterHotKey(NULL, ALT_F1);
	::UnregisterHotKey(NULL, ALT_F6);
	::UnregisterHotKey(NULL, ALT_F7);
	::UnregisterHotKey(NULL, ALT_F8);	
	::UnregisterHotKey(NULL, ALT_F9);	
	::UnregisterHotKey(NULL, ALT_F10);
	::UnregisterHotKey(NULL, ALT_F11);
	::UnregisterHotKey(NULL, ALT_F12);

	::UnregisterHotKey(NULL, CTRL_ALT_F1);
	::UnregisterHotKey(NULL, CTRL_ALT_F2);
	::UnregisterHotKey(NULL, CTRL_ALT_F3);
	::UnregisterHotKey(NULL, CTRL_ALT_F4);
}

void onhotkey(MSG msg)
{
	switch(msg.wParam)
	{
	case ALT_F1:	
	case ALT_F9:	
	case ALT_F6:	
		break;
	default:
		break;	
	}
}
