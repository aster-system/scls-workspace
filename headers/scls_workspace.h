//******************
//
// scls_workspace.h
//
//******************
// Presentation :
//
// SCLS is a project containing base functions for C++.
// It can also be use in any projects.
//
// The Workspace of SCLS is a software made to handle development with SCLS more easily.
//
// This file contains the window of the software.
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

#ifndef SCLS_WORKSPACE
#define SCLS_WORKSPACE

#include "scls_workspace_agatha.h"
#include "scls_workspace_model_maker.h"

// The namespace "scls" is used to simplify the all.
namespace scls {

    //*********
	//
	// The SCLS_Workspace_Window and SCLS_Workspace_Page class
	//
	//*********

	class SCLS_Workspace_Hub_Page : public GUI_Page {
	    // Class representating the hub page of SCLS Workspace
    public:

        //*********
        //
        // SCLS_Workspace_Hub_Page main members
        //
        //*********

        // SCLS_Workspace_Hub_Page constructor
        SCLS_Workspace_Hub_Page(_Window_Advanced_Struct* window_struct, std::string name);

        // Load an object in a page from XML
        virtual std::shared_ptr<GUI_Object> __create_loaded_object_from_type(std::string object_name, std::string object_type, GUI_Object* parent);

        // Getters and setters
        inline bool should_display_agatha() const {return a_should_display_agatha;};
        inline bool should_display_model_maker() const {return a_should_display_model_maker;};

        //*********
        //
        // Event handling
        //
        //*********

        // Check navigations buttons
        void check_navigation_buttons();
        // Update the event of the page
        virtual void update_event();

	private:

        //*********
        //
        // SCLS_Workspace_Hub_Page main members
        //
        //*********

        // Navigation buttons by path
        std::map<std::string, std::shared_ptr<GUI_Text>> a_navigation_buttons = std::map<std::string, std::shared_ptr<GUI_Text>>();
        // Scroller of the hub
        std::shared_ptr<GUI_Scroller> a_navigation_scroller;

        // If the agatha page should be displayer
        bool a_should_display_agatha = false;
        // If the model maker page should be displayer
        bool a_should_display_model_maker = false;
	};

	class SCLS_Workspace_Window : public Window {
	    // Class representating the window of SCLS Workspace
    public:

        //*********
        //
        // SCLS_Workspace_Window main members
        //
        //*********

        // SCLS_Workspace_Window constructor
        SCLS_Workspace_Window(int window_width, int window_height, std::string a_exec_path) : Window(window_width, window_height, a_exec_path) {};

        // Check the state of the hub
        void check_hub_state();

        // Create an object from a type
        virtual std::shared_ptr<Object> __create_loaded_object_from_type(std::string object_name, std::string object_type);

    private:

        //*********
        //
        // SCLS_Workspace_Page main members
        //
        //*********

        // Agatha page
        std::shared_ptr<SCLS_Workspace_Agatha_Page> a_agatha_page;
        // Hub page
        std::shared_ptr<SCLS_Workspace_Hub_Page> a_hub_page;
        // Model maker page
        std::shared_ptr<SCLS_Workspace_Model_Maker_Page> a_model_maker_page;
	};

    // Use the SCLS Worspace
    int use_scls_workspace(std::string program_path);
}

#endif // SCLS_WORKSPACE
