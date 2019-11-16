
#include "ia.h"

#include <thread>
#include "tgbot/tgbot.h"

namespace ia {

    void run_bot(TgBot::Bot* bot) {
        try {
            //printf("Bot username: %s\n", bot->getApi().getMe()->username.c_str());
            TgBot::TgLongPoll longPoll(*bot);
            while (true) {
                printf("Long poll started\n");
                longPoll.start();
            }
        } catch (TgBot::TgException& e) {
            //printf("error: %s\n", e.what());
        }
    }

    struct DialogFlow::Impl {
        Impl(const char* token) : _bot(token) {}
        TgBot::Bot _bot;
        std::map<int32_t, std::function<void (const std::string&)>> callbacks;
        std::thread bot_thread;
    };

    DialogFlow::DialogFlow(const char* token) : pImpl(std::make_unique<Impl>(token)) {
        pImpl->_bot.getEvents().onAnyMessage([&](TgBot::Message::Ptr message) {
            printf("User %lld wrote %s\n", message->chat->id, message->text.c_str());
            if (StringTools::startsWith(message->text, "/start")) {
                return;
            }

            auto it = pImpl->callbacks.find(message->chat->id);
            if (it != pImpl->callbacks.end()) {
                it->second(message->text);
            }
        });

        //std::cout << "Launch thread" << std::endl;
        pImpl->bot_thread = std::thread{run_bot, &pImpl->_bot};
        //std::cout << "After thread" << std::endl;
    }

    DialogFlow::~DialogFlow() {}

    void DialogFlow::connect(int32_t id, std::function<void (const std::string&)> callback) {
        pImpl->callbacks[id] = callback;
    }

    void DialogFlow::disconnect() {
    }

    void DialogFlow::send_message(int32_t id, const std::string& message) {
        // Only send if connected before
        auto it = pImpl->callbacks.find(id);
        if (it != pImpl->callbacks.end()) {
            pImpl->_bot.getApi().sendMessage(id, message);    
        }
    }

}

