#include "csv_loader.hpp"
#include <fstream>
#include "spdlog/spdlog.h"
#include <tgbot/tgbot.h>

void line_callback(TgBot::Bot& bot, TgBot::Message::Ptr message, std::vector<std::string> const& elements) {
  for (size_t i = 0; i < elements.size(); i++) {
    bot.getApi().sendMessage(message->chat->id, elements[i]);
    spdlog::debug("Sent {}", elements[i]);
  }
}

int main(int argc, char** argv) {

  TgBot::Bot bot(BOT_TOKEN);
 
  bot.getEvents().onCommand("start", [&bot, &argc, &argv](TgBot::Message::Ptr message) {
    std::string delim = ",";
    CsvLoader ldr(delim);
    ldr.set_callback(std::bind(&line_callback, bot, message, std::placeholders::_1));

    spdlog::info("Attempting to open {}", argv[argc - 1]);

    std::ifstream stream(argv[argc - 1]);

    if (!stream.is_open()) {
      spdlog::error("Failed to open {}", argv[argc - 1]);
    }

    ldr.run(stream);
  });
  
  try {
      spdlog::info("Bot username: {}", bot.getApi().getMe()->username.c_str());
      TgBot::TgLongPoll longPoll(bot);
      while (true) {
          spdlog::debug("Long poll started");
          longPoll.start();
      }
  } catch (TgBot::TgException& e) {
      printf("error: %s\n", e.what());
  }

  return 0;
}
