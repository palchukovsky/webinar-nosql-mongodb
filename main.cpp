/*
 * The practice part of a webinar with an example
 * of how to use MongoDB C++ API.
 *
 * This program creates a MongoDB database and inserts some data,
 * and searches for some data by criteria.
 *
 * The full reference is available at:
 * https://mongodb.github.io/mongo-cxx-driver/api/current
 *
 * It uses http://mongocxx.org/mongocxx-v3/tutorial/ as a base example,
 * but another dataset. Please refer to the tutorial too.
 */

#include "create.hpp"
#include "query.hpp"
#include "update.hpp"

#include <iostream>
#include <unordered_map>

namespace {
const auto createCmd = "create";
const auto updateCmd = "update";
const auto queryCmd = "query";

void ShowHelp(const std::string &name) {
  std::cout << "Usage:" << std::endl
            << name << " < " << createCmd << " | " << updateCmd << " | "
            << queryCmd << " >" << std::endl;
}

}  // namespace

int main(const int argc, const char *argv[]) {
  const auto &dbName = "company";
  const auto &collectionName = "employees";

  if (argc < 2) {
    ShowHelp(argv[0]);
    return 1;
  }

  try {
    const std::unordered_map<std::string, std::function<void()>> allCommdads = {
        {createCmd, []() { Create(dbName, collectionName); }},
        {updateCmd, []() { Update(dbName, collectionName); }},
        {queryCmd, []() { Query(dbName, collectionName); }},
    };

    const auto &cmd = allCommdads.find(argv[1]);
    if (cmd == allCommdads.cend()) {
      ShowHelp(argv[0]);
      return 1;
    }

    cmd->second();

    return 0;

  } catch (const std::exception &ex) {
    std::cerr << "Exception: " << ex.what() << std::endl;
  }

  std::cout << "Success!" << std::endl;
  return 0;
}
