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
 * The file implements example "how to create database and put data into it".
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

#include <algorithm>
#include <iostream>

//! Creates database with some data.
void Create(const std::string &dbName, const std::string &collectionName) {
  std::cout << "Creating database, removing before if already existing..."
            << std::endl;

  // This should be done only once.
  const mongocxx::instance instance{};

  // Create a client connection with the default URI (localhost, standart port).
  const mongocxx::client client{mongocxx::uri{}};

  // Access the database.
  auto db = client[dbName];

  // Now db is the object around database. If there is no database with such a
  // name - it will create it. Or, if there is one, it will continue to use it.
  // But in this example we are not going to use it, we need to create a fresh
  // one.

  // Actually, at this stage we event dont know - do we have successfully
  // connected client or not.

  db.drop();

  // For company employees we're creating separated collection.
  auto collection = db[collectionName];

  // Insert only one record - Lucas, a CEO
  {
    const auto &lucas = bsoncxx::builder::stream::document{}
                        << "name"
                        << "Lucas"
                        << "position"
                        << "CEO"
                        << "role"
                        << "head" << bsoncxx::builder::stream::finalize;

    // Insert record.
    collection.insert_one(lucas.view());
  }

  // Insert many.
  {
    std::vector<bsoncxx::document::value> employess;

    // William, a CTO.
    employess.emplace_back(bsoncxx::builder::stream::document{}
                           << "name"
                           << "William"
                           << "position"
                           << "CTO"
                           << "role"
                           << "head" << bsoncxx::builder::stream::finalize);

    // Oliver, a developer.
    employess.emplace_back(bsoncxx::builder::stream::document{}
                           << "name"
                           << "Oliver"
                           << "position"
                           << "developer"
                           << "role"
                           << "executor" << bsoncxx::builder::stream::finalize);

    // Oscar, an analyst.
    employess.emplace_back(bsoncxx::builder::stream::document{}
                           << "name"
                           << "Oscar"
                           << "position"
                           << "analyst"
                           << "role"
                           << "executor" << bsoncxx::builder::stream::finalize);

    // Insert many.
    collection.insert_many(employess);
  }
}