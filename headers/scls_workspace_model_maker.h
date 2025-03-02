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
// This file contains the window for the Model Maker part of the software.
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

#ifndef SCLS_WORKSPACE_MODEL_MAKER
#define SCLS_WORKSPACE_MODEL_MAKER

#include "../../PLEOS/pleos_libs/pleos_mathematics.h"

// The namespace "scls" is used to simplify the all.
namespace scls {

    //*********
	//
	// Enhanced models
	//
	//*********

	// Returns the point of a gear
	double __gear_size_by_teeth(unsigned int teeth_number);
	std::shared_ptr<model_maker::Polygon> __gear_solid(double radius_center, unsigned int wheel_number);
	// Returns the points of a pipe
	std::shared_ptr<model_maker::Polygon> __pipe_solid(double radius_center);

	//*********
	//
	// Model Maker project
	//
	//*********

	// Shape in a project
	struct __Model_Maker_Shape {
	    // Constructor of the struct
	    __Model_Maker_Shape(std::string shape_name) : name(shape_name) {};

	    // Returns the shape into a polygon
	    std::shared_ptr<model_maker::Polygon> to_polygon() {
	        std::shared_ptr<model_maker::Polygon> to_return = std::make_shared<model_maker::Polygon>();

	        // Add the necessary exclusion points
	        to_return.get()->exclusion_points.push_back(std::vector<model_maker::Point>());
	        std::vector<model_maker::Point>& exclusion_points_to_pass = to_return.get()->exclusion_points[0];
            for(int i = 0;i<static_cast<int>(exclusion_points.size());i++) {exclusion_points_to_pass.push_back(*exclusion_points[i].get());}

	        // Add the necessary points
            std::vector<model_maker::Point>& points_to_pass = to_return.get()->points;
            for(int i = 0;i<static_cast<int>(points.size());i++) {points_to_pass.push_back(*points[i].get());}

	        return to_return;
	    };

	    // Name of the shape
	    std::string name;

	    // Every points of the exclusion of the shape
        std::vector<std::shared_ptr<model_maker::Point>> exclusion_points;
        // Every points in the shape
        std::vector<std::shared_ptr<model_maker::Point>> points;
	};

	// Layer in a project
	struct __Model_Maker_Layer {
	    // Constructor of the struct
	    __Model_Maker_Layer():layer_face(std::make_shared<model_maker::Face>()),points(layer_face.get()->points()){};
	    // Adds the layer to a graphic
	    void add_to_graphic(pleos::Graphic* graphic) {graphic->new_form_from_face("form", layer_face.get());};

	    // Transform datas
	    // Face transformation of the layer
	    std::shared_ptr<model_maker::Face> layer_face = std::make_shared<model_maker::Face>();

	    // Points in the layer
	    std::vector<std::shared_ptr<model_maker::Point>>& points;
	    // Name of the model layer
	    std::string name = "";

	    // Top connection behaviour
	    #define SCLS_WORKSPACE_MODEL_MAKER_SAME_SHAPE_TOP_CONNECTION_LAYER 0
	    struct {
	        // Type of the top connection
	        unsigned char type = SCLS_WORKSPACE_MODEL_MAKER_SAME_SHAPE_TOP_CONNECTION_LAYER;
	    } Top_Connection;
	};

	class __Model_Maker_Solid {
        // Class representating a model maker solid
    public:

        //*********
        //
        // __Model_Maker_Solid base members
        //
        //*********

        // __Model_Maker_Solid constructor
        __Model_Maker_Solid(std::string name);

        // Add a layer to the project
        void add_layer(std::string layer_name, std::shared_ptr<model_maker::Polygon> layer_polygon);

        // Getters and setter
        inline std::vector<std::shared_ptr<__Model_Maker_Layer>>& layers() {return a_layers;};
        inline std::string name() const {return a_name;};

    private:

        //*********
        //
        // __Model_Maker_Solid base attributes
        //
        //*********

        // Layers in the project
        std::vector<std::shared_ptr<__Model_Maker_Layer>> a_layers = std::vector<std::shared_ptr<__Model_Maker_Layer>>();
        // Name of the project
        std::string a_name = "";
	};

    //*********
	//
	// SCLS_Workspace_Model_Maker_Page class
	//
	//*********

	// Draw a line on an image
	void __draw_line_in_image(Image* texture, model_maker::Point* point_1, model_maker::Point* point_2, unsigned short line_width, Color line_color, double multiplier);
	inline void __draw_line_in_image(Image* texture, model_maker::Point point_1, model_maker::Point point_2, unsigned short line_width, Color line_color){__draw_line_in_image(texture, &point_1, &point_2, line_width, line_color, 1.0);};
	inline void __draw_line_in_image(Image* texture, std::shared_ptr<model_maker::Point> point_1, std::shared_ptr<model_maker::Point> point_2, unsigned short line_width, Color line_color){__draw_line_in_image(texture, point_1.get(), point_2.get(), line_width, line_color, 1.0);};
	inline void __draw_line_in_image(Image* texture, model_maker::Point* point_1, model_maker::Point* point_2, unsigned short line_width, Color line_color){__draw_line_in_image(texture, point_1, point_2, line_width, line_color, 1.0);};
	inline void __draw_line_in_image(std::shared_ptr<Image> texture, model_maker::Point* point_1, model_maker::Point* point_2, unsigned short line_width, Color line_color){__draw_line_in_image(texture.get(), point_1, point_2, line_width, line_color);};
	inline void __draw_line_in_image(std::shared_ptr<Image> texture, model_maker::Point* point_1, model_maker::Point* point_2, unsigned short line_width, Color line_color, double multiplier){__draw_line_in_image(texture.get(), point_1, point_2, line_width, line_color, multiplier);};
	// Draw a point on an image
	void __draw_point_in_image(Image* texture, model_maker::Point* point_to_draw, unsigned short point_width, Color point_color, double multiplicator);
	inline void __draw_point_in_image(Image* texture, model_maker::Point point_to_draw, unsigned short point_width, Color point_color){__draw_point_in_image(texture, &point_to_draw, point_width, point_color, 1);};
	inline void __draw_point_in_image(Image* texture, std::shared_ptr<model_maker::Point> point_to_draw, unsigned short point_width, Color point_color){__draw_point_in_image(texture, point_to_draw.get(), point_width, point_color, 1);};
	inline void __draw_point_in_image(Image* texture, model_maker::Point* point_to_draw, unsigned short point_width, Color point_color){__draw_point_in_image(texture, point_to_draw, point_width, point_color, 1);};
	inline void __draw_point_in_image(std::shared_ptr<Image> texture, model_maker::Point* point_to_draw, unsigned short point_width, Color point_color){__draw_point_in_image(texture.get(), point_to_draw, point_width, point_color, 1);};
	inline void __draw_point_in_image(std::shared_ptr<Image> texture, std::shared_ptr<model_maker::Point> point_to_draw, unsigned short point_width, Color point_color){__draw_point_in_image(texture.get(), point_to_draw.get(), point_width, point_color, 1);}
	inline void __draw_point_in_image(std::shared_ptr<Image> texture, std::shared_ptr<model_maker::Point> point_to_draw, unsigned short point_width, Color point_color, double multiplicator){__draw_point_in_image(texture.get(), point_to_draw.get(), point_width, point_color, multiplicator);};
    // Draw a set of points on an image
    void __draw_points_in_image(Image* texture, const std::vector<std::shared_ptr<model_maker::Point>>& shape_to_draw, unsigned int point_width, Color point_color, unsigned int line_width, Color line_color);
    // Draw a face on an image
    void __draw_face_in_image(Image* texture, model_maker::Face* face_to_draw);
    // Draw a layer on an image
    inline void __draw_layer_in_image(Image* texture, __Model_Maker_Layer* layer_to_draw){__draw_face_in_image(texture, layer_to_draw->layer_face.get());};
    inline void __draw_layer_in_image(Image* texture, std::shared_ptr<__Model_Maker_Layer> layer_to_draw){__draw_layer_in_image(texture, layer_to_draw.get());};
    inline void __draw_layer_in_image(std::shared_ptr<Image> texture, std::shared_ptr<__Model_Maker_Layer> layer_to_draw){__draw_layer_in_image(texture.get(), layer_to_draw.get());};
    inline void __draw_layer_in_image(std::shared_ptr<Image> texture, __Model_Maker_Layer* layer_to_draw){__draw_layer_in_image(texture.get(), layer_to_draw);};
    // Draw a shape 2D on an image
    void __draw_shape_2d_in_image(Image* texture, __Model_Maker_Shape* shape_to_draw);
    inline void __draw_shape_2d_in_image(Image* texture, std::shared_ptr<__Model_Maker_Shape> shape_to_draw){__draw_shape_2d_in_image(texture, shape_to_draw.get());};
    inline void __draw_shape_2d_in_image(std::shared_ptr<Image> texture, __Model_Maker_Shape* shape_to_draw){__draw_shape_2d_in_image(texture.get(), shape_to_draw);};
    inline void __draw_shape_2d_in_image(std::shared_ptr<Image> texture, std::shared_ptr<__Model_Maker_Shape> shape_to_draw){__draw_shape_2d_in_image(texture.get(), shape_to_draw.get());};
    // Draw a set of triangles on an image
    void __draw_triangles_in_image(Image* texture, const std::vector<std::shared_ptr<model_maker::Point>>& shape_to_draw, unsigned int point_width, Color point_color, unsigned int line_width, Color line_color);

	class SCLS_Workspace_Model_Maker_Page : public GUI_Page {
	    // Class representating the agatha part page of SCLS Workspace
    public:

        //*********
        //
        // SCLS_Workspace_Model_Maker_Page main members
        //
        //*********

        // SCLS_Workspace_Model_Maker_Page constructor
        SCLS_Workspace_Model_Maker_Page(_Window_Advanced_Struct* window_struct, std::string name);

        // Function called after an XML loading
        virtual void after_xml_loading() {GUI_Page::after_xml_loading();display_solid_creator();load_navigation_layer_creator();load_top_connection_layer_main();};
        // Load an object in a page from XML
        virtual std::shared_ptr<GUI_Object> __create_loaded_object_from_type(std::string object_name, std::string object_type, GUI_Object* parent);

        //*********
        //
        // Displaying members
        //
        //*********

        // Display the layer creator
        void display_layer_creator();
        // Display the layer main
        void display_layer_main();
        // Display the shape 2D
        void display_shape_2d();
        // Display the shape 2D creator
        void display_shape_2d_creator();
        // Display the shape 2D point edition
        void display_shape_2d_point_edition();
        // Display the solid creator
        void display_solid_creator();
        // Display the main solid page
        void display_solid_main();
        // Hide all the agatha part
        void hide_all();

        //*********
        //
        // Event members
        //
        //*********

        // Check the layer creator events
        void check_layer_creator();
        // Check the movement of the current point in the page 2D
        void check_page_2d_current_point_movement();
        // Check the shape 2D events
        void check_shape_2d();
        // Check the shape 2D creator events
        void check_shape_2d_creator();
        // Check the solid creator events
        void check_solid_creator();
        // Check the solid footer events
        void check_solid_footer();
        // Check the solid navigation events
        void check_solid_navigation();
        // Update the events of the page
        virtual void update_event();
        // Update the texture 2D
        void update_texture_2d();
        // Update the base of the texture 2D
        void update_texture_2d_base();

        //*********
        //
        // Model maker layer handling
        //
        //*********

        // Apply the modifications of a layer
        void apply_layer_modification();
        // Loads the navigation of the layer creator page
        void load_navigation_layer_creator();
        // Loads the navigation of the other shape layer creator page
        void load_selection_other_shape_layer_creator();
        // Loads the top connection navigation of the layer main page
        void load_top_connection_layer_main();
        // Unloads the navigation of the other shape layer creator page
        void unload_selection_other_shape_layer_creator() {a_selection_other_shape_layer_creator_body.get()->reset();a_current_state.loaded_shape_2d_by_selection.clear();};

        // Adds a new layer to the solid
        void add_layer_solid();
        // Displays the gear page in the layer creator
        void display_layer_creator_gear();
        // Displays the other shape page in the layer creator
        void display_layer_creator_other_shape();
        // Displays the regular polygon page in the layer creator
        void display_layer_creator_regular_polygon();
        // Hides all the page of the layer creator
        void hide_all_layer_creator();

        // Returns the currently selected layer
        __Model_Maker_Layer* current_layer() {return a_current_state.current_layer.get();};

        // Getters and setter
        inline std::string name_layer_creator_body() const {return a_name_layer_creator_body.get()->text();};
        inline std::string name_shape_2d_layer_creator_body() const {if(a_selection_other_shape_layer_creator_body.get()->currently_selected_objects().size() <= 0) return std::string(); return a_selection_other_shape_layer_creator_body.get()->currently_selected_objects()[0].name();};
        inline unsigned int side_regular_polygon_layer_creator_body() const {try{return string_to_double(a_side_regular_polygon_layer_creator_body.get()->text());}catch(std::invalid_argument){return 0;}};
        inline unsigned int teeth_gear_layer_creator_body() const {try{return string_to_double(a_teeth_gear_layer_creator_body.get()->text());}catch(std::invalid_argument){return 0;}};

        //*********
        //
        // Model maker shape 2D handling
        //
        //*********

        // Define each possible shape 2D point type
        #define SCLS_WORKSPACE_MODEL_MAKER_SHAPE_2D_EXCLUSION_POINT 1
        #define SCLS_WORKSPACE_MODEL_MAKER_SHAPE_2D_POINT 0

        // Adds a point to the current shape 2D
        inline void add_point_current_shape_2d(std::shared_ptr<model_maker::Point> new_point) {
            if(a_current_state.current_shape_2d_point_type == SCLS_WORKSPACE_MODEL_MAKER_SHAPE_2D_POINT) current_shape_2d()->points.push_back(new_point);
            else if(a_current_state.current_shape_2d_point_type == SCLS_WORKSPACE_MODEL_MAKER_SHAPE_2D_EXCLUSION_POINT) current_shape_2d()->exclusion_points.push_back(new_point);
        };
        // Creates a new shape 2D
        std::shared_ptr<__Model_Maker_Shape> create_shape_2d();
        // Load each navigation buttons in the shape 2D page
        void load_navigation_shape_2d(bool reset_navigation = true);
        // Unload each navigation buttons in the shape 2D page
        void unload_navigation_shape_2d() {a_loaded_shape_2d_point_by_button.clear();a_navigation_buttons_shape_2d.clear();a_shape_2d_navigation.get()->reset();};

        // Returns the currently selected point of the shape 2D
        inline model_maker::Point* current_shape_2d_point() const {return a_current_state.current_shape_2d_point.get();};
        // Returns the chosen shape 2D
         __Model_Maker_Shape* chosen_shape_2d() {try{return a_current_state.loaded_shape_2d_by_selection[name_shape_2d_layer_creator_body()].get();}catch(std::range_error){return 0;}};
        // Returns the currently selected shape 2D
        __Model_Maker_Shape* current_shape_2d() {return a_current_state.current_shape_2d.get();};
        // Returns a 2D shape by its name
        __Model_Maker_Shape* shape_2d_by_name(std::string shape_name) {for(int i = 0;i<static_cast<int>(a_loaded_shape_2d.size());i++){if(a_loaded_shape_2d[i].get()->name == shape_name) return a_loaded_shape_2d[i].get(); } return 0;};
        // Returns a 2D shape by its name
        std::shared_ptr<__Model_Maker_Shape> shape_2d_shared_ptr_by_name(std::string shape_name) {for(int i = 0;i<static_cast<int>(a_loaded_shape_2d.size());i++){if(a_loaded_shape_2d[i].get()->name == shape_name) return a_loaded_shape_2d[i]; } return std::shared_ptr<__Model_Maker_Shape>();};

        // Getters and setter
        inline std::string name_shape_2d_creator_body() const {if(a_name_shape_2d_creator_body.get() == 0) return ""; return a_name_shape_2d_creator_body.get()->text();};
        inline double point_edition_x_shape_2d_main_body() const {try{return string_to_double(a_point_edition_x_shape_2d_main_body.get()->text());}catch(std::invalid_argument){return 0;}};
        inline double point_edition_z_shape_2d_main_body() const {try{return string_to_double(a_point_edition_z_shape_2d_main_body.get()->text());}catch(std::invalid_argument){return 0;}};

        //*********
        //
        // Model maker solid handling
        //
        //*********

        // Creates a new solid
        std::shared_ptr<__Model_Maker_Solid> create_solid();
        // Generate the solid
        std::shared_ptr<model_maker::Solid> generate_solid();
        // Loads the navigation of the solid page
        void load_navigation_solid();
        // Unloads the navigation of the solid page
        void unload_navigation_solid() {a_layer_by_navigation_buttons_solid.clear();a_navigation_buttons_solid.clear();a_solid_main_navigation.get()->reset();};

        // Update the view of the solid main
        void update_solid_view();

        // Returns the currently selected solid
        __Model_Maker_Solid* current_solid() {return a_current_state.current_solid.get();};

        // Getters and setter
        inline std::string name_solid_creator_body() const {return a_name_solid_creator_body.get()->text();};

        //*********
        //
        // Page 2D Texture handling
        //
        //*********

        // Returns the page 2D current point
        inline model_maker::Point* page_2d_current_point() const {return a_current_state.current_page_2d_point.get();};
        // Returns the page 2D current point object
        inline GUI_Object* page_2d_current_point_object() const {return a_current_state.current_page_2d_point_object.get();};
        // Reset the page 2D current point
        inline void reset_page_2d_current_point() {
            // Create the point
            a_current_state.current_page_2d_point = std::make_shared<model_maker::Point>();
            a_current_state.current_page_2d_point.get()->set_x(0);
            a_current_state.current_page_2d_point.get()->set_z(0);
            move_shape_2d_current_point();
        };
        // Move the current shape 2D point
        inline void move_shape_2d_current_point() {
            if(a_shape_2d_body.get() == 0) return;

            // Move the object
            glm::vec4 texture_final_rect = a_shape_2d_body.get()->texture_rect();
            page_2d_current_point_object()->set_x_in_pixel((0.5 + page_2d_current_point()->x() * texture_final_rect[2]) * static_cast<double>(a_shape_2d_body.get()->width_in_pixel()) - (static_cast<double>(page_2d_current_point_object()->width_in_pixel()) / 2.0));
            page_2d_current_point_object()->set_y_in_pixel((0.5 + page_2d_current_point()->z() * texture_final_rect[3]) * static_cast<double>(a_shape_2d_body.get()->height_in_pixel()) - (static_cast<double>(page_2d_current_point_object()->height_in_pixel()) / 2.0));
        };

	private:

	    //*********
        //
        // Current state of the page
        //
        //*********

        // Struct representating the current state of the page
        struct {
            // Define each possible current pages
            #define SCLS_WORKSPACE_MODEL_MAKER_LAYER_CREATOR 1
            #define SCLS_WORKSPACE_MODEL_MAKER_LAYER_MAIN 4
            #define SCLS_WORKSPACE_MODEL_MAKER_SHAPE_2D 0
            #define SCLS_WORKSPACE_MODEL_MAKER_SHAPE_2D_CREATOR 5
            #define SCLS_WORKSPACE_MODEL_MAKER_SOLID_CREATOR 2
            #define SCLS_WORKSPACE_MODEL_MAKER_SOLID_MAIN 3
            // Define each possible file chosen

            // Current file chosen in Model Maker
            unsigned short current_file_chosen = 0;
            // Current page of Model Maker
            unsigned short current_page = SCLS_WORKSPACE_MODEL_MAKER_SOLID_CREATOR;

            // Current texture handling
            // Current handled point 2D page
            std::shared_ptr<model_maker::Point> current_page_2d_point;
            // Object for the current handled point 2D page
            std::shared_ptr<GUI_Object> current_page_2d_point_object;
            // Current page 2D texture base
            std::shared_ptr<Image> current_page_2d_texture;
            // If the texture has been changed or not
            bool current_page_2d_texture_changed = false;
            // Current page 2D texture path
            std::string current_page_2d_texture_path = "";

            // Layer handling
            // Currently used layer
            std::shared_ptr<__Model_Maker_Layer> current_layer;

            // Shape 2D handling
            // Currently used shape 2D point type
            unsigned int current_shape_2d_point_type = SCLS_WORKSPACE_MODEL_MAKER_SHAPE_2D_POINT;
            // Currently used shape 2D
            std::shared_ptr<__Model_Maker_Shape> current_shape_2d;
            // Currently handled shape 2D point
            std::shared_ptr<model_maker::Point> current_shape_2d_point;
            // Loaded shape 2D by selection
            std::map<std::string, std::shared_ptr<__Model_Maker_Shape>> loaded_shape_2d_by_selection;

            // Solid handling
            // Every loaded solids in the software
            std::vector<std::shared_ptr<__Model_Maker_Solid>> current_loaded_solids = std::vector<std::shared_ptr<__Model_Maker_Solid>>();
            // Currently used solid
            std::shared_ptr<__Model_Maker_Solid> current_solid;
        } a_current_state;

        //*********
        //
        // Shape 2D handler
        //
        //*********

        // Each loaded shape 2D
        std::vector<std::shared_ptr<__Model_Maker_Shape>> a_loaded_shape_2d = std::vector<std::shared_ptr<__Model_Maker_Shape>>();
        // Loaded shape 2D point by buttons
        std::map<GUI_Text*, std::shared_ptr<model_maker::Point>> a_loaded_shape_2d_point_by_button;
        // Each navigations button in the shape 2D navigation
        std::vector<std::shared_ptr<GUI_Text>> a_navigation_buttons_shape_2d = std::vector<std::shared_ptr<GUI_Text>>();

        //*********
        //
        // Solid handler
        //
        //*********

        // Each layers attached to the navigations buttons for the solid page
        std::map<GUI_Text*, std::shared_ptr<__Model_Maker_Layer>> a_layer_by_navigation_buttons_solid = std::map<GUI_Text*, std::shared_ptr<__Model_Maker_Layer>>();
        // Each navigations buttons for the solid page
        std::vector<std::shared_ptr<GUI_Text>> a_navigation_buttons_solid = std::vector<std::shared_ptr<GUI_Text>>();

	    //*********
        //
        // GUI stuffs
        //
        //*********

        // Name of the regular polygon page of layer creator
        #define SCLS_WORKSPACE_MODEL_MAKER_GEAR_POLYGON_LAYER_CREATOR std::string("gear_button_layer_navigation_model_maker")
        #define SCLS_WORKSPACE_MODEL_MAKER_PIPE_POLYGON_LAYER_CREATOR std::string("pipe_button_layer_navigation_model_maker")
        #define SCLS_WORKSPACE_MODEL_MAKER_OTHER_SHAPE_POLYGON_LAYER_CREATOR std::string("other_shape_button_layer_navigation_model_maker")
        #define SCLS_WORKSPACE_MODEL_MAKER_REGULAR_POLYGON_LAYER_CREATOR std::string("regular_polygon_button_layer_navigation_model_maker")
        #define SCLS_WORKSPACE_MODEL_MAKER_SAME_SHAPE_TOP_CONNECTION_LAYER_MAIN std::string("same_shape_button_top_connection_layer_main_model_maker")

        // Bodies / footers / navigation
        // Body of the layer type gear of layer creator part
        std::shared_ptr<GUI_Object> a_gear_layer_creator_body;
        // Body of the layer creator part
        std::shared_ptr<GUI_Object> a_layer_creator_body;
        // Footer of the layer creator part
        std::shared_ptr<GUI_Object> a_layer_creator_footer;
        // Navigation of the layer creator part
        std::shared_ptr<GUI_Scroller_Choice> a_layer_creator_navigation;
        // Body of the layer main part
        std::shared_ptr<GUI_Object> a_layer_main_body;
        // Navigation of the top connection of the layer main part
        std::shared_ptr<GUI_Scroller_Choice> a_layer_main_top_connection_navigation;
        // Body of the layer type other shape of layer creator part
        std::shared_ptr<GUI_Object> a_other_shape_layer_creator_body;
        // Point edition part of the footer of the page shape 2D part
        std::shared_ptr<GUI_Object> a_point_edition_shape_2d_footer;
        // Body of the layer type of layer creator part
        std::shared_ptr<GUI_Object> a_regular_polygon_layer_creator_body;
        // Navigation of the other shape layer creator part
        std::shared_ptr<GUI_Scroller_Choice> a_selection_other_shape_layer_creator_body;
        // Body of the page shape 2D part
        std::shared_ptr<GUI_Object> a_shape_2d_body;
        // Body of the page 2D part
        std::shared_ptr<GUI_Object> a_shape_2d_creator_body;
        // Footer of the page shape 2D part
        std::shared_ptr<GUI_Object> a_shape_2d_footer;
        // Navigation of the page shape 2D part
        std::shared_ptr<GUI_Scroller> a_shape_2d_navigation;
        // Body of the solid creator part
        std::shared_ptr<GUI_Object> a_solid_creator_body;
        // Footer of the solid creator part
        std::shared_ptr<GUI_Object> a_solid_creator_footer;
        // Body of the solid main part
        std::shared_ptr<GUI_Object> a_solid_main_body;
        // Footer of the solid main part
        std::shared_ptr<GUI_Object> a_solid_main_footer;
        // Navigation of the solid main part
        std::shared_ptr<GUI_Scroller> a_solid_main_navigation;

        // Buttons
        // Button to add a new layer to a solid
        std::shared_ptr<GUI_Text> a_new_layer_solid_main_footer;
        // Button to add a new shape to the other forms
        std::shared_ptr<GUI_Text> a_new_other_shape_layer_creator;
        // Button to validate the creation of a layer
        std::shared_ptr<GUI_Text> a_validate_layer_creator_body;
        // Button to validate a shape
        std::shared_ptr<GUI_Text> a_validate_shape_2d_body;
        // Button to validate the creation of a shape
        std::shared_ptr<GUI_Text> a_validate_shape_2d_creator_body;
        // Button to validate the creation of a model maker solid
        std::shared_ptr<GUI_Text> a_validate_solid_creator_body;

        // Informational
        // Height value of the main layer
        std::shared_ptr<GUI_Text_Input> a_height_layer_main_body;
        // Length value of the main layer
        std::shared_ptr<GUI_Text_Input> a_length_layer_main_body;
        // Regular polygon side
        std::shared_ptr<GUI_Text_Input> a_side_regular_polygon_layer_creator_body;
        // Gear teeth
        std::shared_ptr<GUI_Text_Input> a_teeth_gear_layer_creator_body;
        // Title of the main layer
        std::shared_ptr<GUI_Text> a_title_layer_main_body;
        // Title of the point edition part of the footer of the page shape 2D part
        std::shared_ptr<GUI_Text> a_title_point_edition_shape_2d_footer;
        // Title of the main solid
        std::shared_ptr<GUI_Text> a_title_solid_main_body;
        // View of the main solid
        std::shared_ptr<pleos::Graphic_Object> a_view_solid_main_body;
        // Width value of the main layer
        std::shared_ptr<GUI_Text_Input> a_width_layer_main_body;
        // X value of the main layer
        std::shared_ptr<GUI_Text_Input> a_x_layer_main_body;
        // Y value of the main layer
        std::shared_ptr<GUI_Text_Input> a_y_layer_main_body;
        // Z value of the main layer
        std::shared_ptr<GUI_Text_Input> a_z_layer_main_body;

        // Text_inputs
        // Name of a layer creator
        std::shared_ptr<GUI_Text_Input> a_name_layer_creator_body;
        // Name of a shape 2D creator
        std::shared_ptr<GUI_Text_Input> a_name_shape_2d_creator_body;
        // Name of a model maker project
        std::shared_ptr<GUI_Text_Input> a_name_solid_creator_body;
        // X value of the point in the shape 2D
        std::shared_ptr<GUI_Text_Input> a_point_edition_x_shape_2d_main_body;
        // Z value of the point in the shape 2D
        std::shared_ptr<GUI_Text_Input> a_point_edition_z_shape_2d_main_body;
	};
}

#endif // SCLS_WORKSPACE_MODEL_MAKER
