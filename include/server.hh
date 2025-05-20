#pragma once

#include "context.hh"
#include "router.hh"
#include <boost/asio.hpp>
#include <boost/beast.hpp>
#include <boost/json.hpp>
#include <iostream>
#include <map>
#include <string>
#include <thread>
#include <vector>
#include  "define.hh"

namespace beast = boost::beast; // from <boost/beast.hpp>
namespace http = beast::http;   // from <boost/beast/http.hpp>
namespace net = boost::asio;    // from <boost/asio.hpp>
using tcp = net::ip::tcp;       // from <boost/asio/ip/tcp.hpp>

class Server {
private:
  short port;
  std::shared_ptr<Router> router;
  net::io_context io_context{1};

public:
  Server(short port, std::shared_ptr<Router> router);
  void session(tcp::socket socket);
  void run();
  short getPort();
};