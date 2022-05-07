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
 * The file implements example "how to update data in a database".
 */

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

//! Adds salaries from employees-executors.
void Update(const std::string &dbName, const std::string &collectionName) {
  std::cout << "Adding sallaries for employees..." << std::endl;

  // Connection initialization.
  const mongocxx::instance instance{};
  const mongocxx::client client{mongocxx::uri{}};
  auto db = client[dbName];
  auto collection = db[collectionName];

  // All executors have the same salary. Heads have - don't have any, yet.

  // "$set" here - operator to set value
  // https://www.mongodb.com/docs/manual/reference/operator/update/set/
  collection.update_many(stream::document{} << "role"
                                            << "executor" << stream::finalize,
                         stream::document{} << "$set" << stream::open_document
                                            << "salary" << 5000.0
                                            << stream::close_document
                                            << stream::finalize);

  // After a moment Lucas decided that for startup work analyst is very
  // important. Then he increased his salary.

  // "$inc" here - example how existent can be modified
  // https://www.mongodb.com/docs/manual/reference/operator/update/inc/
  collection.update_many(stream::document{} << "position"
                                            << "analyst" << stream::finalize,
                         stream::document{} << "$inc" << stream::open_document
                                            << "salary" << 555.55
                                            << stream::close_document
                                            << stream::finalize);
}