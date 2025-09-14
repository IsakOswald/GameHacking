#include "rwm.hpp"
#include <Windows.h>
namespace Core {

	//YAW is at 0x34 in the player struct.
	//PITCH is at 0x38 in the player stuct.

	//Need to find player positions.

	RWM::RWM() 
	{
		Init();
	}

	RWM::~RWM() = default;

	void RWM::Init() 
	{
		//Get the module base (ac_client.exe)
		_moduleBase = GetModuleHandleA("ac_client.exe");
		
		//Get the address of the localPlayerPtr.
		//ac_client.exe+17E0A8
		_localPlayerPtr = reinterpret_cast<void**>(reinterpret_cast<uintptr_t>(_moduleBase) + 0x17E0A8);

		//Now get the address of the actual instance of the player.
		_localPlayerObj = *_localPlayerPtr;
			
	}

	void RWM::WritePlayerHealth(int hp)
	{
		//make sure that we are holding a initilised instance.
		if (!_localPlayerObj || !_localPlayerPtr) return;
		
		//Move the pointer by 0xEC. It will be poiting to a int now.
		int* healthAddress = reinterpret_cast<int*>(reinterpret_cast<uintptr_t>(_localPlayerObj) + 0xEC);
		
		//Write
		* healthAddress = hp;
	}


	void RWM::WritePlayerAmmo(int ammo)
	{
		//make sure that we are holding a initilised instance.
		if (!_localPlayerObj || !_localPlayerPtr) return;

		int* ammoAddress = reinterpret_cast<int*>(reinterpret_cast<uintptr_t>(_localPlayerObj) + 0x140);

		*ammoAddress = ammo;
	}


}