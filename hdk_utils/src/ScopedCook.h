#ifndef _HDKUTILS_SCOPED_COOK__H_
#define _HDKUTILS_SCOPED_COOK__H_

#include <UT/UT_Interrupt.h>
#include <SOP/SOP_Node.h>


namespace hdk_utils {

	/*
	 * @class ScopedCook
	 */
	class ScopedCook
	{
	public:
		ScopedCook(SOP_Node& sop, OP_Context& ctxt, const char* msg = 0);
		~ScopedCook();
		OP_ERROR error();
		bool good();

	protected:
		SOP_Node& m_sop;
		UT_Interrupt* m_boss;
		bool m_inputsLocked;
	};

}

#endif


/***
    Copyright 2008-2012 Dr D Studios Pty Limited (ACN 127 184 954) (Dr. D Studios)

    This file is part of anim-studio-tools.

    anim-studio-tools is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    anim-studio-tools is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with anim-studio-tools.  If not, see <http://www.gnu.org/licenses/>.
***/
