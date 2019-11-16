
#pragma once

#include <memory>
#include <functional>

namespace ia {

    class DialogFlow {
        public:
            DialogFlow(const char* token);
            ~DialogFlow();

            void connect(int32_t id, std::function<void (const std::string&)> callback);
            void disconnect();

            void send_message(int32_t id, const std::string&);

        protected:
            struct Impl;
            std::unique_ptr<Impl> pImpl;
    };

}