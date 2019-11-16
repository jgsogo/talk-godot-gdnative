
#pragma once 

#include <core/Godot.hpp>
#include <Reference.hpp>

#include <memory>

namespace godot {

    class GodotGameIA : public Reference {
        GODOT_CLASS(GodotGameIA, Reference);
    public:
        GodotGameIA();
        ~GodotGameIA();

        void _init(); // _init must exist as it is called by Godot
        static void _register_methods();

        void send_message(String message, Variant chat_id);

        void register_callback(godot::Object *p_instance, Variant chat_id);

    protected:
        void received_message(int32_t id, const std::string& message);
    protected:
        struct Impl;
        std::unique_ptr<Impl> pImpl;
    };

}
