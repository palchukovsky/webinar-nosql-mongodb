/*
 * The practice part of a webinar with an example
 * of how to use MongoDB C++ API.
 *
 * This program creates a MongoDB database and inserts some data,
 * and searches for some data by criteria.
 *
 * It uses http://mongocxx.org/mongocxx-v3/tutorial/ as a base example,
 * but another dataset. Please refer to the tutorial too.
 *
 * The full reference is available at:
 * https://mongodb.github.io/mongo-cxx-driver/api/current
 *
 * The file implements example "how to query some data from a database".
 */

#pragma once

#include <bsoncxx/builder/stream/array.hpp>
#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/builder/stream/helpers.hpp>
#include <bsoncxx/json.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>
#include <mongocxx/stdx.hpp>
#include <mongocxx/uri.hpp>

#include <iostream>

namespace stream = bsoncxx::builder::stream;

//! Queries and prints some database data.
void Query(const std::string &dbName, const std::string &collectionName) {
  std::cout << "Adding sallaries for employees..." << std::endl;

  // Connection initialization.
  const mongocxx::instance instance{};
  const mongocxx::client client{mongocxx::uri{}};
  auto db = client[dbName];
  auto collection = db[collectionName];

  // Who is CTO?
  {
    const auto &result =
        collection.find_one(stream::document{} << "position"
                                               << "CTO" << stream::finalize);
    if (result) {
      std::cout << "CTO's name is " << bsoncxx::to_json(*result) << std::endl;
    } else {
      std::cout << "Company DOESN'T HAVE CTO!" << std::endl;
    }
  }

  // Who are executors in the company?
  {
    auto cursor =
        collection.find(stream::document{} << "role"
                                           << "executor" << stream::finalize);

    std::cout << "Company executors:" << std::endl;
    for (const auto &doc : cursor) {
      std::cout << " - " << bsoncxx::to_json(doc) << std::endl;
    }
  }
}