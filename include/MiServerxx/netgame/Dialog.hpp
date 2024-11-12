#pragma once
#include <cstdint>

namespace mimp {
	class CDialog {
	public:
		CDialog(const uint16_t id, const uint8_t style, const char* tittle, const char* btn1, const char* btn2, const char* info);
		inline const uint16_t GetId(void) const{
			return this->m_id;
		}

		inline const uint8_t GetStyle(void) const{
			return this->m_style;
		}

		inline const char* GetTittle(void) const {
			return this->m_tittle;
		}

		inline const char* GetBtn1(void) const {
			return this->m_button1Text;
		}

		inline const char* GetBtn2(void) const {
			return this->m_button2Text;
		}

		inline const char* GetInfo(void) const {
			return this->m_info;
		}

		static int Create(const uint16_t id, const uint8_t style, const char* tittle, const char* btn1, const char* btn2, const char* info);

	private:
		uint16_t m_id;
		uint8_t m_style;
		char m_tittle[255];
		char m_button1Text[255];
		char m_button2Text[255];
		char m_info[4096];
	};
}
