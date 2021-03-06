/**
 * @file
 * @ingroup Input
 */
#ifndef BB_FLASHPOINTER_H
#define BB_FLASHPOINTER_H

#include "BaconBox/Input/Pointer/Pointer.h"
#include <AS3/AS3.h>
#include <AS3/AS3++.h>

namespace BaconBox {

	class FlashPointer : public Pointer {
		friend class InputManager;
	protected:
		/**
		 * Default constructor.
		 */
		FlashPointer();
		
		/**
		 * Destructor.
		 */
		~FlashPointer();
	
		void updateDevice();

	private:

		AS3::local::var mouseFun;
		static AS3::local::var mouseEventListener(void *arg, AS3::local::var as3Args);
		
		struct{
			Vector2 pos;
			bool leftButton;
		} mouseState;

	};
}

#endif
