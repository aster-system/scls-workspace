//******************
//
// scls_workspace.cpp
//
//******************
// Presentation :
//
// SCLS is a project containing base functions for C++.
// It can also be use in any projects.
//
// The Workspace of SCLS is a software made to handle development with SCLS more easily.
//
// This file contains the source code of scls_workspace.h.
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

#include "../headers/scls_workspace.h"

// The namespace "scls" is used to simplify the all.
namespace scls {

    //*********
    //
    // SCLS_Workspace_Page main members
    //
    //*********

    // SCLS_Workspace_Page constructor
    SCLS_Workspace_Page::SCLS_Workspace_Page(_Window_Advanced_Struct* window_struct, std::string name) : GUI_Page(window_struct, name) { }

    // Create an object from a type
    std::shared_ptr<Object> SCLS_Workspace_Window::__create_loaded_object_from_type(std::string object_name, std::string object_type) {
        if(object_type == "workspace") {
            std::shared_ptr<Object> to_return = *new_page_2d<SCLS_Workspace_Page>(object_name);
            return to_return;
        }
        return Window::__create_loaded_object_from_type(object_name, object_type);
    }

    // Use the SCLS Worspace
    int use_scls_workspace(std::string program_path) {
        // Create the window
        std::shared_ptr<SCLS_Workspace_Window> window = std::make_shared<SCLS_Workspace_Window>(1600, 900, program_path);
        window.get()->load_from_xml("assets/gui/window.txt");

        // Software loop
        while(window.get()->run()) {
            window.get()->update_event();
            window.get()->update();

            window.get()->render();
        }

        return 0;
    }
}
