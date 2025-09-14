#pragma once
#include <cstdint>

namespace Core {
	class RWM {
	private:
		void* _moduleBase;
		void** _localPlayerPtr;
		void* _localPlayerObj;

		void Init();

	public:
		RWM();
		~RWM();

		void WritePlayerHealth(int hp);
		void WritePlayerAmmo(int ammo);

	};
}