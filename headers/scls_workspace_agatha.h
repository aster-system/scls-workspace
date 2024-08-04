//******************
//
// scls_workspace_agatha.h
//
//******************
// Presentation :
//
// SCLS is a project containing base functions for C++.
// It can also be use in any projects.
//
// The Workspace of SCLS is a software made to handle development with SCLS more easily.
//
// This file contains the window for the Agatha part of the software.
//
//******************
//
// License (LGPL V3.0) :
//
// Copyright (C) 2024 by Aster System, Inc. <https://aster-system.github.io/aster-system/>
// This file is part of SCLS.
// SCLS is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
// SCLS is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.
// You should have received a copy of the GNU General Public License along with SCLS. If not, see <https://www.gnu.org/licenses/>.
//

#ifndef SCLS_WORKSPACE_AGATHA
#define SCLS_WORKSPACE_AGATHA

#include "../../scls-graphic-benoit/scls_graphic.h"

// The namespace "scls" is used to simplify the all.
namespace scls {

    //*********
	//
	// SCLS_Workspace_Agatha_Page class
	//
	//*********

	class SCLS_Workspace_Agatha_Page : public GUI_Page {
	    // Class representating the agatha part page of SCLS Workspace
    public:

        //*********
        //
        // SCLS_Workspace_Agatha_Page main members
        //
        //*********

        // SCLS_Workspace_Agatha_Page constructor
        SCLS_Workspace_Agatha_Page(_Window_Advanced_Struct* window_struct, std::string name);

        // Load an object in a page from XML
        virtual std::shared_ptr<GUI_Object> __create_loaded_object_from_type(std::string object_name, std::string object_type, GUI_Object* parent);

	private:
	};
}

#endif // SCLS_WORKSPACE_AGATHA
