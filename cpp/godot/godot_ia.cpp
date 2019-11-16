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
        //std::stringstream os; os << " - chat_id='" << chat_id << "'";
        //Godot::print(os.str().c_str());

        //pImpl->dialog.connect(chat_id, [&](const std::string& message){ this->received_message(chat_id, message);});
    }

    void GodotGameIA::_register_methods() {
        //register_property<GodotGameIA, int>("chat_id", &GodotGameIA::chat_id, 118716073);
        register_method("send_message", &GodotGameIA::send_message);
        register_method("register_callback", &GodotGameIA::register_callback);
        //register_signal<GodotGameIA>("received_message", "id", GODOT_VARIANT_TYPE_INT, "message", GODOT_VARIANT_TYPE_STRING);
    }
    
    void GodotGameIA::send_message(String message, Variant chat_id) {
        std::stringstream os; os << "GodotGameIA::send_message('" << message.utf8().get_data() << "')";
        Godot::print(os.str().c_str());

        pImpl->dialog.send_message(chat_id, message.utf8().get_data());
    }

    void GodotGameIA::register_callback(godot::Object *p_instance, Variant chat_id) {
        Godot::print("register callback");

        String gmessage = "mi mensaje";
        p_instance->call("gdscript_callback", gmessage);

        pImpl->dialog.connect(chat_id, [=](const std::string& message) {
            p_instance->call("gdscript_callback", message.c_str());
        });

        p_instance->call("gdscript_callback", gmessage);
    }


    void GodotGameIA::received_message(int32_t id, const std::string& message) {
        std::stringstream os; os << "GodotGameIA::received_message('" << id << "', '" << message << "')";
        Godot::print(os.str().c_str());

        String gmessage = message.c_str();
        emit_signal("received_message", id, gmessage);
    }
}
