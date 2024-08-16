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
    // SCLS_Workspace_Hub_Page main members
    //
    //*********

    // SCLS_Workspace_Hub_Page constructor
    SCLS_Workspace_Hub_Page::SCLS_Workspace_Hub_Page(_Window_Advanced_Struct* window_struct, std::string name) : GUI_Page(window_struct, name) {
        // Full fill the navigations buttons with empty shared pointers
        std::shared_ptr<GUI_Text> empty_shared_ptr;
        a_navigation_buttons["agatha"] = empty_shared_ptr;
        a_navigation_buttons["model_maker"] = empty_shared_ptr;
    }

    // Check navigations buttons
    void SCLS_Workspace_Hub_Page::check_navigation_buttons() {
        if(a_navigation_buttons["agatha"].get() != 0 && a_navigation_buttons["agatha"].get()->is_clicked_during_this_frame(GLFW_MOUSE_BUTTON_LEFT)) {
            a_should_display_agatha = true;
        }
        else if(a_navigation_buttons["model_maker"].get() != 0 && a_navigation_buttons["model_maker"].get()->is_clicked_during_this_frame(GLFW_MOUSE_BUTTON_LEFT)) {
            a_should_display_model_maker = true;
        }
    }

    // Create an object from a type
    std::shared_ptr<GUI_Object> SCLS_Workspace_Hub_Page::__create_loaded_object_from_type(std::string object_name, std::string object_type, GUI_Object* parent) {
        if(object_type == "navigation_scroller") {
            std::shared_ptr<GUI_Scroller> scroller = *parent->new_object<GUI_Scroller>(object_name);
            a_navigation_scroller = scroller;

            // Return the shared pointer
            std::shared_ptr<GUI_Object> to_return = scroller;
            return to_return;
        }
        else if(object_type.substr(0, 10) == "navigation" && object_type.size() > 11) {
            std::shared_ptr<GUI_Text> button = *parent->new_object<GUI_Text>(object_name);
            std::string path = object_type.substr(11, object_type.size() - 11);
            a_navigation_buttons[path] = button;

            // Return the shared pointer
            std::shared_ptr<GUI_Object> to_return = button;
            return to_return;
        }
        return GUI_Page::__create_loaded_object_from_type(object_name, object_type, parent);
    };

    // Update the event of the page
    void SCLS_Workspace_Hub_Page::update_event() {
        GUI_Page::update_event();
        a_should_display_agatha = false;
        a_should_display_model_maker = false;
        check_navigation_buttons();
    }

    // Check the state of the hub
    void SCLS_Workspace_Window::check_hub_state() {
        if(a_hub_page.get()->should_display_agatha()) {
            hide_all_pages_2d();
            display_page_2d(a_agatha_page.get()->name());
        }
        else if(a_hub_page.get()->should_display_model_maker()) {
            hide_all_pages_2d();
            display_page_2d(a_model_maker_page.get()->name());
        }
    }

    // Create an object from a type
    std::shared_ptr<Object> SCLS_Workspace_Window::__create_loaded_object_from_type(std::string object_name, std::string object_type) {
        if(object_type == "hub") {
            std::shared_ptr<SCLS_Workspace_Hub_Page> hub = *new_page_2d<SCLS_Workspace_Hub_Page>(object_name);

            // Get the special page
            a_hub_page = hub;

            // Return the good object
            std::shared_ptr<Object> to_return = hub;
            return to_return;
        }
        else if(object_type == "agatha") {
            std::shared_ptr<SCLS_Workspace_Agatha_Page> agatha = *new_page_2d<SCLS_Workspace_Agatha_Page>(object_name);

            // Get the special page
            a_agatha_page = agatha;

            // Return the good object
            std::shared_ptr<Object> to_return = agatha;
            return to_return;
        }
        else if(object_type == "model_maker") {
            std::shared_ptr<SCLS_Workspace_Model_Maker_Page> model_maker = *new_page_2d<SCLS_Workspace_Model_Maker_Page>(object_name);

            // Get the special page
            a_model_maker_page = model_maker;

            // Return the good object
            std::shared_ptr<Object> to_return = model_maker;
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

            window.get()->check_hub_state();

            window.get()->render();
        }

        return 0;
    }
}
