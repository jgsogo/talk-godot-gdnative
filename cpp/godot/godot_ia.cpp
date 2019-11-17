#include "godot_ia.h"

#include <sstream>
#include "../lib/ia.h"


namespace godot {

    struct GodotGameIA::Impl {
        Impl(const char* token) : dialog(token) {
            if (!token) {
                Godot::print("Need to provide token!");
                //throw std::runtime_error("Need to provide token!");
            }
        };
        ia::DialogFlow dialog;
    };

    GodotGameIA::GodotGameIA() : pImpl(std::make_unique<Impl>(std::getenv("TOKEN"))) {
        Godot::print("GodotGameIA::GodotGameIA");
    }

    GodotGameIA::~GodotGameIA() {}

    void GodotGameIA::_init() {
        Godot::print("GodotGameIA::_init");
    }

    void GodotGameIA::_register_methods() {
        register_method("send_message", &GodotGameIA::send_message);
        register_method("register_callback", &GodotGameIA::register_callback);
        register_signal<GodotGameIA>("callback_ready", "id", GODOT_VARIANT_TYPE_INT, "message", GODOT_VARIANT_TYPE_STRING);
    }
    
    void GodotGameIA::send_message(String message, Variant chat_id) {
        std::stringstream os; os << "GodotGameIA::send_message('" << message.utf8().get_data() << "')";
        Godot::print(os.str().c_str());

        pImpl->dialog.send_message(chat_id, message.utf8().get_data());
    }

    void GodotGameIA::register_callback(godot::Object *p_instance, Variant chat_id) {
        Godot::print("register callback");

        pImpl->dialog.connect(chat_id, [=](const std::string& message) {
            p_instance->call("gdscript_callback", message.c_str());
        });

        String msg = "Hola aventurero!";
        emit_signal("callback_ready", chat_id, msg);
    }

}
